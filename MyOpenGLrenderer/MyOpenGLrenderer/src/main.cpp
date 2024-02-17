#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <vector>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "Primitives/Vertex.h"
#include "Model/Mesh.h"

#include "ECS/Entity.h"
#include "ECS/Camera.h"

#include "OpenGL/Renderer/Renderer.h"

#include "MeshGenerators/Quad.h"
#include "MeshGenerators/Sphere.h"

#include "stb_image.h"

#include "imgui.h"

#include "Profiler.h"

bool wireframe = false;

bool hide_mouse = true;
bool firstMouse = true;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    PROFILE_FUNCTION();
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (key == GLFW_KEY_F && action == GLFW_PRESS)
    {
        if (wireframe)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            wireframe = false;
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            wireframe = true;
        }
    }

    if (key == GLFW_KEY_LEFT_ALT && action == GLFW_PRESS)
    {
        if (hide_mouse)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            hide_mouse = false;
        }
        else
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            hide_mouse = true;
            firstMouse = true;
        }
    }
}

float lastX;
float lastY;

float sensitivity = 0.1f;

float yaw;
float pitch;

glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    PROFILE_FUNCTION();
    if (!hide_mouse)
        return;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
}

float fov = 45;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    PROFILE_FUNCTION();
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

short window_Width = 1280;
short window_Height = 720;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    PROFILE_FUNCTION();
    glViewport(0, 0, width, height);
    window_Width = width;
    window_Height = height;
}


int main()
{
#ifdef PROFILING
    Instrumentor::Instance().beginSession("Profile");
#endif // PROFILING
    PROFILE_FUNCTION();
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(window_Width, window_Height, "LearnOpenGL", NULL, NULL);
    if (!window)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    glViewport(0, 0, window_Width, window_Height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    const char* glsl_version = "#version 130";
    ImGui_ImplOpenGL3_Init(glsl_version);



    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    //glDepthMask(GL_FALSE);
    glDepthFunc(GL_LESS);


    Entity entity;

    entity.mesh = createQuad();

    Entity entity2;

    entity2.mesh = createQuad();

    entity2.Transform.Rotation = glm::vec3(0.0f, -90.0f, 0.0f);

    Entity entity3;

    entity3.Transform.Position = glm::vec3(0.5f, 1.0f, 0.5f);
    entity3.addChild(&entity2);

    Entity entity4;
    entity4.addChild(&entity3);
    entity4.addChild(&entity);


    Entity sphere;
    sphere.mesh = CreateSphereMESH(0.5f, 36, 18);
    sphere.addSphereCollider();
    sphere.collider->isTrigger = true;
    sphere.OnTriggerEnter = [](Entity* coll) {
        std::cout << "TRIGGER!!!! "<< coll->Transform.Position.y << '\n';
    };

    Entity sphere2;
    sphere2.mesh = CreateSphereMESH(0.5f, 36, 18);
    for (int i = 0; i < sphere2.mesh->vertices.size(); i++)
        sphere2.mesh->vertices[i].Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    sphere2.Transform.Position = glm::vec3(0.5f, 0.5f, 0.0f);
    sphere2.mesh->updateData();
    sphere2.addSphereCollider();

    sphere2.rigidBody = new RigidBody();
    sphere2.rigidBody->mass = 1.0f;
    sphere2.rigidBody->force = glm::vec3(300.0f, 500.0f, 0.0f);



    Entity entity6;
    entity6.mesh = createQuad();
    entity6.Transform.Position = glm::vec3(0.0f, 0.0f, 0.5f);
    entity6.Transform.Rotation = glm::vec3(0.0f, 0.0f, 90.0f);
    Entity entity7;
    entity7.mesh = createQuad();
    entity7.Transform.Position = glm::vec3(0.0f, 0.0f, 0.2f);
    entity7.Transform.Rotation = glm::vec3(0.0f, 0.0f, 180.0f);
    Entity entity8;
    entity8.mesh = createQuad();
    entity8.Transform.Position = glm::vec3(0.0f, 0.0f, 0.1f);
    entity8.Transform.Rotation = glm::vec3(0.0f, 0.0f, 260.0f);
    Entity entity9;
    entity9.mesh = createQuad();
    entity9.Transform.Position = glm::vec3(0.0f, 0.0f, 0.7f);

    Entity entity10;
    entity10.mesh = createQuad();
    entity10.Transform.Position = glm::vec3(0.0f, 0.0f, -1.6f);
    entity10.Transform.Rotation = glm::vec3(0.0f, 0.0f, 90.0f);
    Entity entity11;
    entity11.mesh = createQuad();
    entity11.Transform.Position = glm::vec3(0.0f, 0.0f, -1.7f);
    Entity entity12;
    entity12.mesh = createQuad();
    entity12.Transform.Position = glm::vec3(0.0f, 0.0f, -1.71f);
    Entity entity13;
    entity13.mesh = createQuad();
    entity13.Transform.Position = glm::vec3(0.0f, 0.0f, -1.72f);

    Entity texturedQuad;
    texturedQuad.mesh = createQuad();
    texturedQuad.Transform.Position = glm::vec3(0.0f, 0.0f, -2.00f);
    texturedQuad.mesh->is_Transparent = false;
    for (int i = 0; i < texturedQuad.mesh->vertices.size(); i++)
        texturedQuad.mesh->vertices[i].Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    texturedQuad.mesh->updateData();
    Texture quadTexture;
    quadTexture.loadTexture("assets/textures/pop_cat.png", TextureType::ColorTexture);
    texturedQuad.mesh->textures.push_back(quadTexture);
    texturedQuad.addAABB();


    Entity lightEntity;

    PointLight pointLight;

    lightEntity.pointLight = &pointLight;

    lightEntity.Transform.Position = glm::vec3(0.0f, 1.0f, 0.0f);
    lightEntity.mesh = CreateSphereMESH(0.03f, 9, 5, true);
    lightEntity.mesh->is_Transparent = true;
    lightEntity.mesh->is_Wireframe = true;

    Entity lightEntity2;
    PointLight pointLight2;
    pointLight2.lightColor = glm::vec3(1.0f, 0.0f, 0.0f);
    lightEntity2.pointLight = &pointLight2;
    lightEntity2.Transform.Position = glm::vec3(0.0f, 1.0f, 0.0f);
    lightEntity2.mesh = CreateSphereMESH(0.03f, 9, 5, true);
    lightEntity2.mesh->is_Transparent = true;
    lightEntity2.mesh->is_Wireframe = true;
    Entity lightEntity3;
    PointLight pointLight3;
    pointLight3.lightColor = glm::vec3(0.0f, 1.0f, 0.0f);
    lightEntity3.pointLight = &pointLight3;
    lightEntity3.Transform.Position = glm::vec3(0.0f, 1.0f, -0.5f);
    lightEntity3.mesh = CreateSphereMESH(0.03f, 9, 5, true);
    lightEntity3.mesh->is_Transparent = true;
    lightEntity3.mesh->is_Wireframe = true;
    Entity lightEntity4;
    PointLight pointLight4;
    pointLight4.lightColor = glm::vec3(0.0f, 0.0f, 1.0f);
    lightEntity4.pointLight = &pointLight4;
    lightEntity4.Transform.Position = glm::vec3(0.0f, 1.0f, 0.5f);
    lightEntity4.mesh = CreateSphereMESH(0.03f, 9, 5, true);
    lightEntity4.mesh->is_Transparent = true;
    lightEntity4.mesh->is_Wireframe = true;

    Renderer renderer("assets/shaders/shader.vert", "assets/shaders/shader.frag");

    Scene scene;

    Light ambient;
    //ambient.lightColor = glm::vec3(1.0f);
    //ambient.ambient = 0.20f;

    scene.ambientLight = &ambient;

    scene.gravity = glm::vec3(0, -9.81f, 0);

    scene.Entities.push_back(&entity4);
    scene.Entities.push_back(&entity6);
    scene.Entities.push_back(&entity7);
    scene.Entities.push_back(&entity8);
    scene.Entities.push_back(&entity9);
    scene.Entities.push_back(&entity10);
    scene.Entities.push_back(&entity11);
    scene.Entities.push_back(&entity12);
    scene.Entities.push_back(&entity13);

    scene.Entities.push_back(&texturedQuad);

    scene.Entities.push_back(&lightEntity);
    scene.Entities.push_back(&lightEntity2);
    scene.Entities.push_back(&lightEntity3);
    scene.Entities.push_back(&lightEntity4);

    scene.Entities.push_back(&sphere);
    scene.Entities.push_back(&sphere2);

    for (int i = 0; i < 0; i++)
    {
        Entity* newEntity = new Entity;
        newEntity->mesh = CreateSphereMESH(0.5f, 36, 18);
        scene.Entities.push_back(newEntity);
    }

    Camera camera;

    scene.Camera = &camera;

    renderer.Scene = &scene;

    double currentFrame = 0;
    double lastFrame = 0;
    double deltaTime = 0;

    glfwSwapInterval(0);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //uint32_t FrameBufferWidht = 1920;
    //uint32_t FrameBufferHeight = 1080;
    //
    //GLuint FramebufferName = 0;
    //glGenFramebuffers(1, &FramebufferName);
    //glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
    //
    //GLuint renderedTexture;
    //glGenTextures(1, &renderedTexture);
    //glBindTexture(GL_TEXTURE_2D, renderedTexture);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, FrameBufferWidht, FrameBufferHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //
    //GLuint depthrenderbuffer;
    //glGenRenderbuffers(1, &depthrenderbuffer);
    //glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
    //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, FrameBufferWidht, FrameBufferHeight);
    //glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);
    //
    //glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);
    //GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
    //glDrawBuffers(1, DrawBuffers);
    //
    //if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    //    return 0;
    //
    //glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //
    //
    //std::vector<Vertex> vertices;
    //Vertex vertex;
    //vertex.Normal = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
    //vertex.Color = glm::vec4(1.0f);
    //vertex.Position = glm::vec3(-1.0f, -1.0f, 0.0f);
    //vertex.TexCoords = glm::vec2(0.0f, 0.0f);
    //vertices.push_back(vertex);
    //vertex.Position = glm::vec3(1.0f, -1.0f, 0.0f);
    //vertex.TexCoords = glm::vec2(1.0f, 0.0f);
    //vertices.push_back(vertex);
    //vertex.Position = glm::vec3(1.0f, 1.0f, 0.0f);
    //vertex.TexCoords = glm::vec2(1.0f, 1.0f);
    //vertices.push_back(vertex);
    //vertex.Position = glm::vec3(-1.0f, 1.0f, 0.0f);
    //vertex.TexCoords = glm::vec2(0.0f, 1.0f);
    //vertices.push_back(vertex);
    //std::vector<unsigned int> indices = {
    //    0, 1, 2,
    //    2, 3, 0
    //};
    //
    //Mesh mesh(vertices, indices);
    //Texture fulltex;
    //fulltex.ID = renderedTexture;
    //fulltex.name = "RenderedTexture";
    //mesh.textures.push_back(fulltex);
    //
    //Shader fullShader("assets/shaders/Main.vert", "assets/shaders/Main.frag");

    GLint oldFBO;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &oldFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, oldFBO);

    while (!glfwWindowShouldClose(window))
    {
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        camera.width = window_Width;
        camera.height = window_Height;
        camera.Transform.Front = glm::normalize(direction);
        camera.FOV = fov;

        renderer.Scene->PhisycsPass(deltaTime);


        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        {
            ImGui::Begin("Hello, world!");
            //ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            if (ImGui::Button("Spawn Ball"))
            {
                Entity* newSphere = new Entity();
                newSphere->mesh = CreateSphereMESH(0.5f, 36, 18);
                for (int i = 0; i < newSphere->mesh->vertices.size(); i++)
                    newSphere->mesh->vertices[i].Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
                newSphere->Transform.Position = glm::vec3(0.5f, 0.5f, 0.0f);
                newSphere->mesh->updateData();
                newSphere->addSphereCollider();

                newSphere->rigidBody = new RigidBody();
                newSphere->rigidBody->mass = 1.0f;
                newSphere->rigidBody->force = glm::vec3(300.0f, 500.0f, 0.0f);
                scene.Entities.push_back(newSphere);
            }
            //ImGui::SameLine();
            //ImGui::Text("counter = %d", counter);

            ImGui::SliderFloat("sphere x", &sphere2.Transform.Position.x, -10.0f, 10.0f);
            ImGui::SliderFloat("sphere y", &sphere2.Transform.Position.y, -10.0f, 10.0f);
            ImGui::SliderFloat("sphere z", &sphere2.Transform.Position.z, -10.0f, 10.0f);

            ImGui::SliderFloat("pointLight x", &lightEntity.Transform.Position.x, -10.0f, 10.0f);
            ImGui::SliderFloat("pointLight y", &lightEntity.Transform.Position.y, -10.0f, 10.0f);
            ImGui::SliderFloat("pointLight z", &lightEntity.Transform.Position.z, -10.0f, 10.0f);
            ImGui::SliderFloat("pointLight r", &lightEntity.pointLight->lightColor.r, 0.0f, 2.0f);
            ImGui::SliderFloat("pointLight g", &lightEntity.pointLight->lightColor.g, 0.0f, 2.0f);
            ImGui::SliderFloat("pointLight b", &lightEntity.pointLight->lightColor.b, 0.0f, 2.0f);
            ImGui::SliderFloat("pointLight linear", &lightEntity.pointLight->linear, -1.0f, 2.0f);
            ImGui::SliderFloat("pointLight quadratic", &lightEntity.pointLight->quadratic, -1.0f, 2.0f);

            ImGui::SliderFloat("ambient r", &ambient.lightColor.r, 0.0f, 2.0f);
            ImGui::SliderFloat("ambient g", &ambient.lightColor.g, 0.0f, 2.0f);
            ImGui::SliderFloat("ambient b", &ambient.lightColor.b, 0.0f, 2.0f);
            ImGui::SliderFloat("ambient intensity", &ambient.ambient, 0.0f, 1.0f);
            

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
        ImGui::Render();

        float cameraSpeed = 2.5f * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.Transform.Position += cameraSpeed * camera.Transform.Front;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.Transform.Position -= cameraSpeed * camera.Transform.Front;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.Transform.Position -= glm::normalize(glm::cross(camera.Transform.Front, camera.Transform.Up)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.Transform.Position += glm::normalize(glm::cross(camera.Transform.Front, camera.Transform.Up)) * cameraSpeed;

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            camera.Transform.Position += camera.Transform.Up * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            camera.Transform.Position -= camera.Transform.Up * cameraSpeed;



        //glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, oldFBO);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        //glEnable(GL_DEPTH_TEST);
        //glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
        
        renderer.draw();
        //glBindFramebuffer(GL_FRAMEBUFFER, 0);
        //glDisable(GL_DEPTH_TEST);
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //fullShader.bind();
        //mesh.draw(fullShader);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    Texture::Delete();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
#ifdef PROFILING
    Instrumentor::Instance().endSession();
#endif // PROFILING
    return 0;
}
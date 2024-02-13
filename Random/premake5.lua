outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

GLFWi = "GLFW/include"
GLFWl = "GLFW/lib"
GLFWs = "glfw3.lib"

workspace "Hexxy2DV2"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

    platforms
    {
        "Windows"
    }


project "Hexxy2DV2"
    location "Hexxy2DV2"
    kind "ConsoleApp"
    language "C++"

    targetdir (".bin/" .. outputdir .. "/%{prj.name}")
    objdir (".obj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",

        "%{prj.name}/vendor/GLM/glm/**.h",
        "%{prj.name}/vendor/GLM/glm/**.hpp",
        "%{prj.name}/vendor/GLM/glm/**.inl",

        "%{prj.name}/vendor/STB/**.c",
        "%{prj.name}/vendor/STB/**.h",

        "%{prj.name}/vendor/GLAD/**.c",
        "%{prj.name}/vendor/GLAD/**.h",

        "%{prj.name}/vendor/IMGUI/**.cpp",
        "%{prj.name}/vendor/IMGUI/**.h",

        "%{prj.name}/vendor/spdlog-1.x/include/**.cpp",
        "%{prj.name}/vendor/spdlog-1.x/include/**.h"
    }

    includedirs
    {
        GLFWi,
        "%{prj.name}/vendor/GLAD/include/",
        "%{prj.name}/vendor/GLM/glm/",
        "%{prj.name}/vendor/STB/",
        "%{prj.name}/vendor/IMGUI/",
        "%{prj.name}/vendor/spdlog-1.x/include/"
    }

    libdirs
    {
        GLFWl
    }

    links
    {
        "kernel32",
        "user32",
        "gdi32",

        "opengl32.lib",
        GLFWs
    }

    postbuildcommands
    {}

    filter "system:Windows"
        cppdialect "C++20"
        staticruntime "off"
        systemversion "latest"

        defines
        {
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "HEX_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "HEX_RELEASE"
        optimize "On"
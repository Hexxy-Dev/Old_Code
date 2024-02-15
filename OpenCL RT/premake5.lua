outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

GLFWi = "GLFW/include"
GLFWl = "GLFW/lib"
GLFWs = "glfw3.lib"

workspace "Parallel Programming Heterogeneous Systems"
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


project "OpenCL"
    location "OpenCL"
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

        "$(CUDA_PATH)/include/**.h",
        "$(CUDA_PATH)/include/**.hpp"
    }

    includedirs
    {
        GLFWi,
        "%{prj.name}/vendor/GLAD/include/",
        "%{prj.name}/vendor/GLM/glm/",
        "%{prj.name}/vendor/STB/",
        "%{prj.name}/vendor/IMGUI/",

        "$(CUDA_PATH)/include"
    }

    libdirs
    {
        GLFWl,

        "$(CUDA_PATH)/lib/x64"
    }

    links
    {
        "kernel32",
        "user32",
        "gdi32",

        "opengl32.lib",
        GLFWs,

        "OpenCl.lib"
    }

    postbuildcommands
    {
        --"{COPYDIR} \"%{prj.location}/assets\" \"%{cfg.targetdir}/assets\""
    }

    filter "system:Windows"
        cppdialect "C++17"
        staticruntime "off"
        systemversion "latest"

        defines
        {
            "_CRT_SECURE_NO_WARNINGS",
            "GLFW_INCLUDE_NONE"
        }

        --linkoptions "/NODEFAULTLIB:MSVCRT"

    filter "configurations:Debug"
        defines "HEX_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "HEX_RELEASE"
        optimize "On"
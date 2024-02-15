outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

GLFWIncludeDir = "GLFW/include"
GLFWLibs = "GLFW/lib"
GLFW = "glfw3"

VulkanIncludeDir = "C:/VulkanSDK/1.2.182.0/Include"
VulkanLibs = "C:/VulkanSDK/1.2.182.0/Lib"
Vulkan = "vulkan-1"

workspace "Vulkan experimenting"
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


project "Vulkan experimenting"
    location "Vulkan experimenting"
    kind "ConsoleApp"
    language "C++"

    targetdir (".bin/" .. outputdir .. "/%{prj.name}")
    objdir (".obj/" .. outputdir .. "/%{prj.name}")


    SRC = "%{prj.name}/src/"

    GLM = "%{prj.name}/vendor/GLM/"
    STB = "%{prj.name}/vendor/STB/"
    TINYOBJLOADER = "%{prj.name}/vendor/tinyobjloader"


    files
    {
        SRC .. "**.h",
        SRC .. "**.cpp",

        GLM .. "**.h",
        GLM .. "**.hpp",
        GLM .. "**.inl",

        STB .. "**.c",
        STB .. "**.h",

        TINYOBJLOADER .. "**.h",
    }

    includedirs
    {
        GLFWIncludeDir,
        GLM,
        STB,
        TINYOBJLOADER,

        VulkanIncludeDir
    }

    libdirs
    {
        GLFWLibs,

        VulkanLibs
    }

    links
    {
        "kernel32",
        "user32",
        "gdi32",

        GLFW,

        Vulkan
    }

    postbuildcommands
    {
        "call glslc.exe \"%{prj.location}/shaderSource/shader.frag\" -o \"%{prj.location}/assets/shaders/frag.spv\"",
        "call glslc.exe \"%{prj.location}/shaderSource/shader.vert\" -o \"%{prj.location}/assets/shaders/vert.spv\"",

        "{COPYDIR} \"%{prj.location}/assets\" \"%{cfg.targetdir}/assets\""
    }

    filter "system:Windows"
        cppdialect "C++17"
        staticruntime "off"
        systemversion "latest"

        defines
        {
            "_CRT_SECURE_NO_WARNINGS",

            "GLFW_INCLUDE_NONE",
            "GLFW_INCLUDE_VULKAN",

            "GLM_FORCE_RADIANS",
            "GLM_FORCE_DEPTH_ZERO_TO_ONE"
        }

        linkoptions "/NODEFAULTLIB:MSVCRT"

    filter "configurations:Debug"
        defines "HEX_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "HEX_RELEASE"
        optimize "On"
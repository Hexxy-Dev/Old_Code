outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

workspace "Networking"
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


project "Client"
    location "Client"
    kind "ConsoleApp"
    language "C++"

    targetdir (".bin/" .. outputdir .. "/%{prj.name}")
    objdir (".obj/" .. outputdir .. "/%{prj.name}")

    dependson
    {
        "Server"
    }

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
    }

    libdirs
    {
    }

    links
    {
    }

    postbuildcommands
    {
    }

    filter "system:Windows"
        cppdialect "C++17"
        staticruntime "off"
        systemversion "latest"

        defines
        {
            "_CRT_SECURE_NO_WARNINGS",
        }

    filter "configurations:Debug"
        defines "HEX_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "HEX_RELEASE"
        optimize "On"





project "Server"
    location "Server"
    kind "ConsoleApp"
    language "C++"

    targetdir (".bin/" .. outputdir .. "/%{prj.name}")
    objdir (".obj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
    }

    libdirs
    {
    }

    links
    {
    }

    postbuildcommands
    {
    }

    filter "system:Windows"
        cppdialect "C++17"
        staticruntime "off"
        systemversion "latest"

        defines
        {
            "_CRT_SECURE_NO_WARNINGS",
        }

    filter "configurations:Debug"
        defines "HEX_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "HEX_RELEASE"
        optimize "On"
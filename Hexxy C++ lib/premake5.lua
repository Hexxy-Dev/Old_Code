outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

workspace "Hexxy C++ lib"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    platforms
    {
        "Windows"
    }


project "Hexxy C++ lib"
    location "Hexxy C++ lib"
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
        }

    filter "configurations:Debug"
        defines "HEX_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "HEX_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "HEX_DIST"
        optimize "On"
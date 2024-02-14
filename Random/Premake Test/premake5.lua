defines
{
    "_CRT_SECURE_NO_WARNINGS"
}


workspace "Test"
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




outputdir = "%{cfg.buildcfg}-%{cfg.system}-${cfg.architecture}"



project "Test"
    location "Test"
    kind "SharedLib"
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
        "%{prj.name}/vendor/"
    }

    filter "system:Windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "_CRT_SECURE_NO_WARNINGS"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relativepath} ../bin/" .. outputdir .. "/Test2")
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

    filter { "system:Windows", "configurations:Release" }
        buildoptions "/MT"







project "Test2"
    location "Test2"
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
        "%{prj.name}/vendor/",
        "Test/src/"
    }

    links
    {
        "Test"
    }

    filter "system:Windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "_CRT_SECURE_NO_WARNINGS"
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

    filter { "system:Windows", "configurations:Release" }
        buildoptions "/MT"
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
    "%{prj.name}/src/"
}

libdirs
{
}

links
{
}

filter "system:Windows"
    cppdialect "C++17"
    staticruntime "off"
    systemversion "latest"

filter "configurations:Debug"
    symbols "On"

filter "configurations:Release"
    optimize "On"
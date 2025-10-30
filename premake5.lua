-- premake5.lua
workspace "Parcheesi"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "Parcheesi"
    location "build"

project "Parcheesi"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"         -- puedes poner "on" si quieres runtime estático

    -- dónde dejar los ejecutables y los .obj
    targetdir ("%{wks.location}/bin/%{cfg.buildcfg}")
    objdir    ("%{wks.location}/bin-int/%{cfg.buildcfg}")

    -- tus fuentes
    files {
        "**.h",
        "**.cc"
    }

    -- si tuvieras carpetas de include externas, las pones aquí
    -- includedirs { "include" }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        runtime "Release"
        optimize "On"

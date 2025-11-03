workspace "Parcheesi"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "Parcheesi"
    location "build"

--------------------------------
-- Static lib: jop_player
--------------------------------
project "jop_player"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    files {
        "jop_player.h",
        "jop_player.cc"
    }

    includedirs {
        "."    -- root folder
    }

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

    filter {}    -- clear filters

--------------------------------
-- Static lib: ParcheesiBoard
--------------------------------
project "ParcheesiBoard"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    files {
        "jop_parcheesi.h",
        "jop_parcheesi.cc",
        "iparcheesi.h"
    }

    includedirs {
        "."
    }

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

    filter {}    -- clear filters

------------------------
-- Executable: Parcheesi
------------------------
project "Parcheesi"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    -- Solo los .cc del ejecutable
    files {
        "main.cc",
        "game.cc"
    }

    -- Carpeta raíz para todos los .h (incluye zagerfe_player.h)
    includedirs {
        "."
    }

    -- Donde está el .lib externo
    libdirs {
        "."   
    }

    -- Librerías a enlazar
    links {
        "jop_player",
        "ParcheesiBoard",
        "PlayerElena",
        "ParcheesiRaqPlayer",
        "PlayerGSH" 
    }

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

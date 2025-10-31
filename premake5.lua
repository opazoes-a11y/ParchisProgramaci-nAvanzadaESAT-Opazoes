workspace "Parcheesi"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "Parcheesi"
    location "build"

-- ========================
-- Project: ParcheesiPlayer
-- ========================
project "ParcheesiPlayer"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    files {
        "jop_player.h",
        "jop_player.cc"
    }

-- =======================
-- Project: ParcheesiBoard
-- =======================
project "ParcheesiBoard"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    files {
        "jop_parcheesi.h",
        "jop_parcheesi.cc"
    }

-- =================
-- Project: Parcheesi
-- =================
project "Parcheesi"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    files {
        "**.h",
        "**.cc"
    }

    links { "ParcheesiPlayer", "ParcheesiBoard" }

    includedirs {
        ".",           -- root folder (so headers like jop_player.h work)
        "ParcheesiPlayer",
        "ParcheesiBoard"
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

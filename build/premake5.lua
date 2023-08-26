workspace "ArchInstallerTui"
    configurations { "Debug", "Release" }

project "ArchInstallerTui"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
  
    files { "../src/**.hpp", "../src/**.cpp" }
    links { "ncurses", "menu" }
    includedirs { "../src" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        
    filter "configurations:Release"
        defines { "NDEBUG" }
        symbols "On"


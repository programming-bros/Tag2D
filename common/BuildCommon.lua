project "Common"
	location "../common"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "Off"

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.c",
		"src/**.hpp",
		"src/**.cpp"
	}

	includedirs
	{
		"src",
		"external"
	}

	postbuildcommands
	{
			--'{COPY} "assets" "%{cfg.targetdir}"'
	}

	filter "configurations:Debug"
		defines { "BUILD_DEBUG" }
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines { "BUILD_RELEASE" }
		runtime "Release"
		optimize "On"
		symbols "On"

	filter "configurations:Dist"
		defines { "BUILD_DIST" }
		runtime "Release"
		optimize "On"
		symbols "Off"

	-- Windows
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"PLATFORM_WINDOWS"
		}

		postbuildcommands
		{
		}

	-- Mac OS
	filter "system:macosx"

		defines
		{
			"PLATFORM_MACOS"
		}

		postbuildcommands
		{
		}

	-- Linux
	filter "system:linux"

		defines
		{
			"PLATFORM_LINUX"
		}

		postbuildcommands
		{
		}
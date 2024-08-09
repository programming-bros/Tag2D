project "Client"
	location "../client"
	kind "ConsoleApp"
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
		"src/**.cpp",
	}

	includedirs
	{
		"src",
		"../common/src",
		"external",
		"external/glad/include",
		"external/glfw/include",
		--"../common/external/glm"
		--"external/ImGui"
	}

	links
	{
		"Common",
		"glad",
		"glfw",
		--"ImGui"
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

		links
		{
		}

		defines
		{
			"PLATFORM_WINDOWS"
		}

		postbuildcommands
		{
		}

	-- Mac OS
	filter "system:macosx"

		links
		{
			"glad",
			"glfw",
			--"ImGui",
			"IOKit.framework",
			"Cocoa.framework",
			"OpenGL.framework",
			"QuartzCore.framework"
		}

		defines
		{
			"PLATFORM_MACOS"
		}

		postbuildcommands
		{
		}

	-- Linux
	filter "system:linux"

		links
		{
			"glad",
			"glfw",
			--"ImGui",
			"GL",
			"X11",
			"Xi",
			"Xrandr",
			"Xxf86vm",
			"Xinerama",
			"Xcursor",
			"rt",
			"m",
			"pthread"
		}

		defines
		{
			"PLATFORM_LINUX"
		}

		postbuildcommands
		{
		}

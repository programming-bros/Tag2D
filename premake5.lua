workspace "Tag2D"
	architecture "x64"

	configurations { "Debug", "Release", "Dist" } -- Debug, Release, Distribution. Debug has symbols, Release has optimizations, Dist has no symbols and optimizations.
	startproject "Client"

	-- Workspace-wide build options for MSVC
	filter "system:windows"
		buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

	flags { "MultiProcessorCompile" }

	filter "system:macosx" -- If the architecture is MacOSX, then we want to set the architecture to ARM64
		architecture "ARM64"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Game"
	include "client/BuildClient.lua"
	include "server/BuildServer.lua"
	include "common/BuildCommon.lua"

group "Dependencies"
	include "client/external/glad/premake5.lua"
	include "client/external/glfw/premake5.lua"
	--include "client/external/ImGui/premake5.lua"
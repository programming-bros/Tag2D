#include <memory>

#include "Server.h"
#include "Console.h"
#include "Globals.h"
#include "FrameCounter.h"
#include "../../common/src/Logger.h"

int main()
{
	InitGlobals();

	Tag2D::Server server = Tag2D::Server();

	if (!server.Init(SERVER_ADDRESS, SERVER_PORT))
	{
		log_error("Socket failed.");
		return -1;
	}

	Tag2D::Console console = Tag2D::Console();
	Tag2D::FrameCounter frameCounter = Tag2D::FrameCounter();

	console.RegisterCommand("enable_fps_output", [&frameCounter]() { frameCounter.SetConstantShowFrames(true); });
	console.RegisterCommand("disable_fps_output", [&frameCounter]() { frameCounter.SetConstantShowFrames(false); });

	server.RegisterOnFrameCallback([&console]() { console.OnFrame(); });
	server.RegisterOnFrameCallback([&frameCounter]() { frameCounter.OnFrame(); });
		 
	server.Start();

	server.Stop();
}

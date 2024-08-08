#include "Server.h"
#include "Logger.h"
#include <iostream>

namespace Tag2D
{
	Server::Server()
		: m_ShouldRun(false), m_Frame(0), m_Socket(Socket()),
		m_LastFrameTimestamp(std::make_shared<Timestep>())
	{
		log_info("Created socket object");
	}

	Server::~Server()
	{
		Stop();
	}

	void Server::Init(const char* address, uint16_t port)
	{
		log_info("Initializing server object...\n");

		if (!m_Socket.Init(address, port))
		{
			log_error("Server can't be initialized because of socket error.");
			return;
		}

		m_ShouldRun = true;
	}

	void Server::Start()
	{
		m_LastFrameTimestamp->Update();
		while (m_ShouldRun)
		{
			OnFrame();
		}
	}

	void Server::Stop()
	{
		log_info("Stopping server...");
		m_ShouldRun = true;
	}

	void Server::RegisterOnFrameCallback(OnFrameCallbackFn callback)
	{
		m_OnFrameCallbacks.push_back(callback);

		log_info("New!w OnFrame Callback!d function has been added");
	}

	void Server::OnFrame()
	{
		//m_Socket.OnFrame();

		for (const auto& function : m_OnFrameCallbacks)
		{
			function();
		}
	}
}
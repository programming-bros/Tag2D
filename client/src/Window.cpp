#include "Window.h"
#include "Logger.h"
#include "Input.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Tag2D
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		log_error("GLFW Error (%i) : %s", error, description);
	}

	Window::Window(const WindowProperties& properties)
		: m_Data{}
	{
		m_Data.Title = properties.Title;
		m_Data.IconPath = properties.IconPath;
		m_Data.Width = properties.Width;
		m_Data.Height = properties.Height;

		log_info("Creating window \"%s\" (%i, %i)", m_Data.Title.c_str(), m_Data.Width, m_Data.Height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			if (!success)
				log_error("Could not intialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef APPLE
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

		// TODO: CMDR-JohnAlex: Add the ability to load as different window modes. (Windowed, Fullscreen, Borderless)
		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);

		glfwMakeContextCurrent(m_Window);
		LoadIcon(m_Data.IconPath);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!status)
		{
			log_error("Failed to initialize glad!");
		}
		
		glfwSetWindowUserPointer(m_Window, &m_Data);
		glfwSetFramebufferSizeCallback(m_Window, FramebufferSizeCallback);

		log_info("Window initialized succesfully");
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	void Window::OnUpdate()
	{
		Input::Instance().ProcessInput(m_Window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::OnUpdatePost()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);

		float time = static_cast<float>(glfwGetTime());
		float deltatime = time - m_LastFrameTime;
		m_LastFrameTime = time;
	}

	void Window::SetVSync(bool enabled)
	{
		m_Data.VSync = enabled;
		glfwSwapInterval(enabled);
	}

	void Window::SetTitle(const std::string& title)
	{
		m_Data.Title = title;
		glfwSetWindowTitle(m_Window, m_Data.Title.c_str());
	}

	void Window::SetIconPath(const std::string& iconPath)
	{
		m_Data.IconPath = iconPath;
		LoadIcon(m_Data.IconPath);
	}

	std::pair<float, float> Window::GetWindowPosition() const
	{
		int width, height;
		glfwGetWindowPos(m_Window, &width, &height);
		return { width, height };
	}

	void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void Window::LoadIcon(const std::string& iconPath)
	{
		constexpr uint8_t CHANNELS = 4; // 3 - RGB (jpeg), 4 - RGBA (png)
		m_Data.Icon[0].pixels = stbi_load(iconPath.c_str(), &m_Data.Icon[0].width, &m_Data.Icon[0].height, 0, CHANNELS);

		if (stbi_failure_reason())
		{
			log_error("Icon load failed: %s", stbi_failure_reason());
			return;
		}

		glfwSetWindowIcon(m_Window, 1, &m_Data.Icon[0]);
		stbi_image_free(m_Data.Icon[0].pixels);
	}
}
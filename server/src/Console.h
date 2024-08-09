#ifndef CONSOLE_H
#define CONSOLE_H

#include <vector>
#include <functional>
#include <unordered_map>
#include <string>
#include <iostream>

#include "pc.h"


#ifdef WINDOWS
	#include <conio.h>
#elif defined(LINUX) || defined(APPLE)
	#include <ncurses.h>
#else
	#error Unsupported platform
#endif

#define ENTER_KEY_CODE 13
#define BACKSPACE_KEY_CODE 8

#define MAX_USER_INPUT_SIZE UINT8_MAX

// FIXME: Use lambda for registering callbacks (better performance)

namespace Tag2D
{
	// The console class it's responsible with reading user input, registering console commands and processing them.

	using CommandCallback = std::function<void()>;

	class Console
	{
	public:
		Console();
		~Console();

		void RegisterCommand(const std::string& command, CommandCallback callback);
		void OnFrame();

	private:
		void UserSentInput();

	private:
		char m_Input[MAX_USER_INPUT_SIZE];
		uint8_t m_Offset;

		std::unordered_map<std::string, CommandCallback> m_Commands;
	};
}

#endif // CONSOLE_H

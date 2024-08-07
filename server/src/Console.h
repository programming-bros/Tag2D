#ifndef CONSOLE_H
#define CONSOLE_H

#include <vector>
#include <functional>
#include <unordered_map>
#include <string>
#include <conio.h>

#define ENTER_KEY_CODE 13
#define BACKSPACE_KEY_CODE 8

#define MAX_USER_INPUT_SIZE UINT8_MAX

namespace Tag2D
{
	// The console class it's responsible with registering console commands. It has a Bi-Directional relation with the Server class.

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
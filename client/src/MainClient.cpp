#include "Globals.h"
#include <Application.h>

#include <iostream>

int main()
{
	InitGlobals();

	Tag2D::Application::Instance().Init();

	log_info("Game application initialized succesfully")

	Tag2D::Application::Instance().Run();
}
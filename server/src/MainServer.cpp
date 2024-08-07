#include <memory>

#include "Server.h"
#include "Console.h"
#include "Logger.h"

int main()
{
	std::shared_ptr<Tag2D::LoggerOptions> options = std::make_shared<Tag2D::LoggerOptions>();
	options->info_prefix = "!w[INFO]!d ";
	options->warning_prefix = "!y[WARNING]!d ";
	options->error_prefix = "!r[WARNING]!d ";

	Tag2D::Logger::Instance().Init(options);

	Tag2D::Logger::Instance().error("Logger error test. !wRan!ydom!g co!rlor");

	std::shared_ptr<Tag2D::Server> server = std::make_shared<Tag2D::Server>();
	server->Init(SERVER_ADDRESS, SERVER_PORT);
	server->Start();

	server.reset();
}
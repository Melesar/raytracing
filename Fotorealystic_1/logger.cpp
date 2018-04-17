#include "logger.h"
#include "scene.h"

void Logger::output()
{
	auto end = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - startTime);
	long millisPassed = duration.count();

	file << "Rendering completed in " << millisPassed / 1000 << " sec" << std::endl;

	printable->print(file);

	file.close();
}

void Logger::start()
{
	startTime = std::chrono::steady_clock::now();
}

Logger::Logger(Printable * printable)
{
	this->printable = printable;

	file.open(fileName, std::ios::app);
	file << std::endl;
}

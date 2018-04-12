#include "logger.h"

void Logger::output()
{
	auto end = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - startTime);
	long millisPassed = duration.count();

	file << "Rendering completed in " << millisPassed / 1000 << " sec" << std::endl;
	file << "Scene configuration: " << std::endl;
	file << scene << std::endl;

	file.close();
}

void Logger::start()
{
	startTime = std::chrono::steady_clock::now();
}

Logger::Logger(Scene * scene)
{
	this->scene = scene;

	file.open(fileName);
}

#pragma once

#include <string>
#include <chrono>
#include <fstream>

class Scene;

class Logger
{
	std::string fileName = "render_log.txt";

	std::chrono::time_point<std::chrono::steady_clock> startTime;
	std::ofstream file;

	Scene* scene;

public:

	void output();
	void start();

	Logger(Scene* scene);
};
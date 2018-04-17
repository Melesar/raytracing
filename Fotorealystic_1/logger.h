#pragma once

#include <string>
#include <chrono>
#include <fstream>
#include "printable.h"

class Scene;

class Logger
{
	std::string fileName = "render_log.txt";

	std::chrono::time_point<std::chrono::steady_clock> startTime;
	std::ofstream file;

	Printable* printable;

public:

	void output();
	void start();

	Logger(Printable* scene);
};
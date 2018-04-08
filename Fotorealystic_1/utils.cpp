#include "utils.h"

void Utils::replace(std::string & str, const std::string & pattern, const std::string & sub)
{
	int start = str.find(pattern);
	int len = pattern.length();

	while (start != std::string::npos) {
		str.replace(start, len, sub);
		start = str.find(pattern);
	}

}

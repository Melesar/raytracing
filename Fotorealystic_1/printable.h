#pragma once
#include <ostream>

class Printable
{
public:

	virtual void print(std::ostream& stream) const = 0;
};

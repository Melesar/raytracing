#pragma once

#include <iostream>


struct Color
{
	double r, g, b;

	Color();
	Color(double r, double g, double b) : r(r), g(g), b(b) {}

	void set(double r, double g, double b);

	Color& operator *= (const Color& other);
	friend Color operator * (Color left, const Color& right);

	Color& operator *= (const double& value);
	friend Color operator * (Color color, const double value);
	friend Color operator * (double value, const Color& color);

	friend std::ostream& operator << (std::ostream& stream, const Color& color);

private:

	static double normalize(double value)
	{
		if (value < 0) {
			return 0;
		}

		if (value > 1) {
			return 1;
		}

		return value;
	}
};

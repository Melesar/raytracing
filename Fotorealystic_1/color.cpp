#include "color.h"
#include <math.h>

void Color::set(double r, double g, double b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

Color & Color::operator+=(const Color & other)
{
	r = r + other.r;
	g = g + other.g;
	b = b + other.b;

	return *this;
}

Color & Color::operator*=(const Color & other)
{
	r = r * other.r;
	g = g * other.g;
	b = b * other.b;

	return *this;
}

Color & Color::operator*=(const double & value)
{
	r = r * value;
	g = g * value;
	b = b * value;

	return *this;
}

Color& Color::operator/=(const double & value)
{
	r = r / value;
	g = g / value;
	b = b / value;

	return *this;
}

bool Color::operator==(const Color & other)
{
	double delta = 0.000001;
	return abs(r - other.r) < delta
		&& abs(g - other.g) < delta
		&& abs(b - other.b) < delta;
}

Color operator+(Color left, const Color & right)
{
	left += right;
	return left;
}

Color operator*(Color left, const Color & right)
{
	left *= right;
	return left;
}

Color operator*(Color color, const double value)
{
	color *= value;
	return color;
}

Color operator * (double value, const Color& color)
{
	return color * value;
}

std::ostream & operator<<(std::ostream & stream, const Color & color)
{
	char r = (char)(255 * Color::normalize(color.r));
	char g = (char)(255 * Color::normalize(color.g));
	char b = (char)(255 * Color::normalize(color.b));

	stream << r << g << b;

	return stream;
}

#include "color.h"
#include <math.h>

void Color::set(double r, double g, double b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

void Color::normalize()
{
	r = Color::normalize(r);
	g = Color::normalize(g);
	b = Color::normalize(b);
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
	double delta = 0.000000001;
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
	int r = (int)(255 * Color::normalize(color.r));
	int g = (int)(255 * Color::normalize(color.g));
	int b = (int)(255 * Color::normalize(color.b));

	stream << '(' << r << ", " << g << ", " << b << ')';

	return stream;
}

std::istream & operator>>(std::istream & stream, Color & color)
{
	double r, g, b;
	stream >> r >> g >> b;

	color.r = r;
	color.g = g;
	color.b = b;

	return stream;
}

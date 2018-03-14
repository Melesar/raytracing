#include "color.h"

Color::Color()
{
	r = g = b = 0;
}

void Color::set(double r, double g, double b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

Color & Color::operator*=(const Color & other)
{
	r = normalize(r * other.r);
	g = normalize(g * other.g);;
	b = normalize(b * other.b);;

	return *this;
}

Color & Color::operator*=(const double & value)
{
	r = normalize(r * value);
	g = normalize(g * value);
	b = normalize(b * value);

	return *this;
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

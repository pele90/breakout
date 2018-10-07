#include "Vector2D.h"

Vector2D::Vector2D() : x(0.0), y(0.0){}

Vector2D::Vector2D(float sourceX, float sourceY)
{
	x = sourceX;
	y = sourceY;
}

Vector2D::~Vector2D(){}

Vector2D Vector2D::operator+(const Vector2D &v) const
{
	return Vector2D(x + v.x, y + v.y);
}

Vector2D Vector2D::operator-(const Vector2D &v) const
{
	return Vector2D(x - v.x, y - v.y);
}

Vector2D Vector2D::operator*(const Vector2D &v) const
{
	return Vector2D(x*v.x, y*v.y);
}

Vector2D Vector2D::operator/(const Vector2D &v) const
{
	return Vector2D(x / v.x, y / v.y);
}

bool Vector2D::operator==(const Vector2D &v) const
{
	return ((x == v.x) && (y == v.y));
}

Vector2D Vector2D::operator*(const float& scalar) const
{
	return Vector2D(x*scalar, y*scalar);
}

Vector2D Vector2D::operator/(const float& scalar) const
{
	return Vector2D(x / scalar, y / scalar);
}

float Vector2D::dotProduct(const Vector2D &a, const Vector2D &b)
{
	return ((a.x * b.x) + (a.y * b.y));
}

float Vector2D::magnitude(const Vector2D &v)
{
	return sqrt((v.x * v.x) + (v.y * v.y));
}

Vector2D Vector2D::normalize(const Vector2D &v)
{
	float magnitude = this->magnitude(v);
	return Vector2D(v.x / magnitude, v.y / magnitude);
}

float Vector2D::getX() const
{
	return this->x;
}

float Vector2D::getY() const
{
	return this->y;
}

void Vector2D::setX(float x)
{
	this->x = x;
}

void Vector2D::setY(float y)
{
	this->y = y;
}
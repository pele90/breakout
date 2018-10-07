#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <math.h>

class Vector2D
{
public:
	Vector2D();
	Vector2D(float x, float y);
	~Vector2D();

	Vector2D operator+(const Vector2D&) const;
	Vector2D operator-(const Vector2D&) const;
	Vector2D operator*(const Vector2D&) const;
	Vector2D operator/(const Vector2D&) const;
	bool operator==(const Vector2D&) const;
	Vector2D operator*(const float&) const;
	Vector2D operator/(const float&) const;

	float dotProduct(const Vector2D&, const Vector2D&);
	float magnitude(const Vector2D&);
	Vector2D normalize(const Vector2D&);

	float getX() const;
	float getY() const;
	void setX(float x);
	void setY(float y);

private:
	float x;
	float y;
};

#endif // !VECTOR2D_H

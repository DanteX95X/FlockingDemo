#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>

struct Vector2
{
public:
	Vector2(double xInit = 0, double yInit = 0);
	
	Vector2 Normalize();
	double Length();

	Vector2& operator += (const Vector2& vector);
	Vector2& operator -= (const Vector2& vector);
	Vector2& operator *= (const double coefficient);
	Vector2& operator /= (const double coefficient);
	Vector2& operator = (const Vector2& vector);

	friend const Vector2 operator - (const Vector2& vector);
	friend const Vector2 operator - (const Vector2& first, const Vector2& second);
	friend const Vector2 operator + (const Vector2& first, const Vector2& second);
	friend const Vector2 operator * (const Vector2& vector, const double coefficient);
	friend const Vector2 operator * (const double coefficient, const Vector2& vector);
	friend const Vector2 operator / (const Vector2& vector, const double coefficient);

	friend bool operator == (const Vector2& first, const Vector2& second);
	friend bool operator != (const Vector2& first, const Vector2& second);
	friend bool operator < (const Vector2& first, const Vector2& second);
	
	friend std::ostream& operator << (std::ostream& os, const Vector2& vector);

	double x;
	double y;

};

#endif // VECTOR2_H

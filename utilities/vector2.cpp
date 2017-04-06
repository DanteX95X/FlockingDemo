#include "vector2.h"
#define _USE_MATH_DEFINES
#include <math.h>

Vector2::Vector2(double xInit, double yInit)
	: x{xInit}, y{yInit}
{

}

Vector2 Vector2::Normalize()
{
	double norm = Length();
	if(norm > 0)
	{
		x /= norm;
		y /= norm;
	}
	return *this;
}

double Vector2::Length()
{
	return sqrt(x*x + y*y);
}

Vector2 Vector2::Rotate(double degrees)
{
	Vector2 result = *this;
	double angle = degrees * M_PI / 180;
	//result.x = cos(angle)*this->x - sin(angle)*this->y;
	//result.y = sin(angle)*this->x + cos(angle)*this->y;
	double length = result.Length();
	result.x = cos(angle) * length;
	result.y = sin(angle) * length;
	return result;
}

void Vector2::Limit(double maxLength)
{
	if(Length() > maxLength)
	{
		Normalize();
		*this *= maxLength;
	}
}

Vector2& Vector2::operator += (const Vector2& vector)
{
	x += vector.x;
	y += vector.y;
	return *this;
}

Vector2& Vector2::operator -= (const Vector2& vector)
{
	return *this += -vector;
}

Vector2& Vector2::operator *= (const double coefficient)
{
	x *= coefficient;
	y *= coefficient;
	return *this;
}

Vector2& Vector2::operator /= (const double coefficient)
{
	x /= coefficient;
	y /= coefficient;
	return *this;
}

Vector2& Vector2::operator = (const Vector2& vector)
{
	x = vector.x;
	y = vector.y;
	return *this;
}

Vector2 operator - (const Vector2& vector)
{
	return Vector2(-vector.x, -vector.y);
}

Vector2 operator + (const Vector2& first, const Vector2& second)
{
	return Vector2(first.x + second.x, first.y + second.y);
}

Vector2 operator - (const Vector2& first, const Vector2& second)
{
	return Vector2(first.x - second.x, first.y - second.y);
}

Vector2 operator * (const Vector2& vector, const double coefficient)
{
	return Vector2(vector.x * coefficient, vector.y * coefficient);
}

Vector2 operator * (const double coefficient, const Vector2& vector)
{
	return vector * coefficient;
}

Vector2 operator / (const Vector2& vector, const double coefficient)
{
	return Vector2(vector.x / coefficient, vector.y / coefficient);
}

bool operator == (const Vector2& first, const Vector2& second)
{
	return first.x == second.x && first.y == second.y;
}

bool operator != (const Vector2& first, const Vector2& second)
{
	return !(first == second);
}

bool operator < (const Vector2& first, const Vector2& second)
{
	return ( first.x < second.x ) || ( ( first.x == second.x ) && ( first.y < second.y ) );
}


std::ostream& operator << (std::ostream& os, const Vector2& vector)
{
	os << "( " << vector.x << ", " << vector.y << " )";
	return os;
}

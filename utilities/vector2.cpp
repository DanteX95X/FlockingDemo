#include "vector2.h"

Vector2::Vector2(double xInit, double yInit)
	: x{xInit}, y{yInit}
{

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

Vector2& Vector2::operator = (const Vector2& vector)
{
	x = vector.x;
	y = vector.y;
	return *this;
}

const Vector2 operator - (const Vector2& vector)
{
	return Vector2(-vector.x, -vector.y);
}

const Vector2 operator + (const Vector2& first, const Vector2& second)
{
	return Vector2(first.x + second.x, first.y + second.y);
}

const Vector2 operator - (const Vector2& first, const Vector2& second)
{
	return Vector2(first.x - second.x, first.y - second.y);
}

const Vector2 operator * (const Vector2& vector, const double coefficient)
{
	return Vector2(vector.x * coefficient, vector.y * coefficient);
}

const Vector2 operator * (const double coefficient, const Vector2& vector)
{
	return vector * coefficient;
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
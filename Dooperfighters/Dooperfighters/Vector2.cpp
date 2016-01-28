#include "Vector2.h"

using namespace Sheep;


/* +==== Constructors ====+ */
Vector2::Vector2() : x(0), y(0) {}
Vector2::Vector2(const real ix, const real jy) : x(ix), y(jy) {}

/* +== Copy ==+ */
#pragma region Copying
Vector2::Vector2(const Vector2& cpy)
{
	*this = cpy;
}

Vector2& Vector2::operator = (const Vector2& rhs)
{
	x = rhs.x;
	y = rhs.y;

	return *this;
}
#pragma endregion

/* +==== General Vector Methods ====+ */
#pragma region General Vector Methods
void Vector2::invert()
{
	x = -x;
	y = -y;
}

real Vector2::magnitude() const
{
	// TODO: int to float
	//return (int)real_sqrt(x * x + y * y);
	return 0;
}

real Vector2::squareMagnitude() const /* <-- To avoid using square root: http://stackoverflow.com/questions/6884359/c-practical-computational-complexity-of-cmath-sqrt */
{
	return x * x + y * y;
}

void Vector2::normalize()
{
	real n = magnitude();
	if (n > 0)
		*this *= ((real)1) / n;
}
#pragma endregion

/* +== Scalars ==+ */
#pragma region Scalars
	/* -Multiplication- */
Vector2 Vector2::operator * (const real rhs) const
{
	return Vector2(x * rhs, y * rhs);
}

void Vector2::operator *= (const real rhs)
{
	x *= rhs;
	y *= rhs;
}

	/* -Add- */
Vector2 Vector2::operator + (const Vector2& rhs) const
{
	return Vector2(x + rhs.x, y + rhs.y);
}

void Vector2::operator += (const Vector2& rhs)
{
	x += rhs.x;
	y += rhs.y;
}
	/* -Subtract- */
Vector2 Vector2::operator - (const Vector2& rhs) const
{
	return Vector2(x - rhs.x, y - rhs.y);
}

void Vector2::operator -= (const Vector2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
}

/* -Add and Multiply (x2)- */
void Vector2::addScaledVector(const Vector2& vector, real scale)	/* <-- two in one, for convienence sake */
{
	x += vector.x * scale;
	y += vector.y * scale;
}
#pragma endregion

/* +== Component Product ==+ */
#pragma region Component
Vector2 Vector2::componentProduct(const Vector2& vector) const
{
	return Vector2(x * vector.x, y * vector.y);
}
void Vector2::componentProductUpdate(const Vector2& vector)
{
	x *= vector.x;
	y *= vector.y;
}
#pragma endregion

/* +== Scalar (Dot) Product ==+ */
real Vector2::operator * (const Vector2& vector) const
{
	return x * vector.x + y * vector.y;
}
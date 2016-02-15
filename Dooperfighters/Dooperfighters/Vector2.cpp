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
void Vector2::Invert()
{
	x = -x;
	y = -y;
}

real Vector2::Magnitude(const Vector2& otherPoint) const
{
	return real_sqrt(((otherPoint.x - x) * (otherPoint.x - x)) + 
					 ((otherPoint.y - y) * (otherPoint.y - y)));
}

real Vector2::SquareMagnitude(const Vector2& otherPoint) const /* <-- To avoid using square root: http://stackoverflow.com/questions/6884359/c-practical-computational-complexity-of-cmath-sqrt */
{
	return ((otherPoint.x - x) * (otherPoint.x - x)) +
		   ((otherPoint.y - y) * (otherPoint.y - y));
}

void Vector2::Normalize(const Vector2& otherPoint)
{
	*this /= SquareMagnitude(otherPoint);
}

Vector2 Vector2::Normalized(const Vector2& otherPoint) const
{
	int magnitude = Magnitude(otherPoint);
	Vector2 pos = (*this);
	Vector2 derp = (*this) / magnitude;
	return derp;
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
	/* -Division- */
Vector2 Vector2::operator / (const real rhs) const
{
	if (rhs > 0)
		return Vector2(x / rhs, y / rhs);

	return Vector2(0, 0);
}

void Vector2::operator /= (const real rhs)
{
	x /= rhs;
	y /= rhs;
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
void Vector2::AddScaledVector(const Vector2& vector, real scale)	/* <-- two in one, for convienence sake */
{
	x += vector.x * scale;
	y += vector.y * scale;
}
#pragma endregion

/* +== Component Product ==+ */
#pragma region Component
Vector2 Vector2::ComponentProduct(const Vector2& vector) const
{
	return Vector2(x * vector.x, y * vector.y);
}
void Vector2::ComponentProductUpdate(const Vector2& vector)
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
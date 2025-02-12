#include "SheepTransform2D.h"
#include "Vector2.h"
#include "Utility.h"

using namespace Sheep;

#pragma region Constructor
Transform2D::Transform2D(real x, real y) : mRotation(0)
{
	mPosition = new Vector2((real)x, (real)y);
	mScale = new Vector2(1, 1);
	mDirection = new Vector2(1, 1);
}

Transform2D::Transform2D() : mRotation(0)
{
	mPosition = new Vector2(0, 0);
	mScale = new Vector2(1, 1);
	mDirection = new Vector2(1, 1);
}

Transform2D::Transform2D(const Vector2& pos) : mRotation(0)
{
	mPosition = new Vector2(pos);
	mScale = new Vector2(1, 1);
	mDirection = new Vector2(1, 1);
}

Transform2D::~Transform2D()
{
	delete mPosition;
	mPosition = nullptr;
	delete mScale;
	mScale = nullptr;
	delete mDirection;
	mDirection = nullptr;
}

/* +=== Copy ===+ */
Transform2D::Transform2D(const Transform2D& cpy)
{
	*this = cpy;
}

Transform2D& Transform2D::operator = (const Transform2D& rhs)
{
	if (!mPosition)
		mPosition = new Vector2();

	if (!mScale)
		mScale = new Vector2();
	
	*mPosition = rhs.GetPosition();
	*mScale = rhs.GetScale();
	mRotation = rhs.GetRotation();

	return *this;
}
#pragma endregion

/* +==== Transformation ====+ */
#pragma region Transformation
void Transform2D::Translate(real x, real y)
{
	mPosition->x += x;
	mPosition->y += y;
}

void Transform2D::Translate(const Vector2& pos)
{
	*mPosition += pos;
}

void Transform2D::Scale(real x, real y)
{
	mScale->x += x;
	mScale->y += y;
}

void Transform2D::Scale(real s)
{
	mScale->x += s;
	mScale->y += s;
}

void Transform2D::Scale(const Vector2& scale)
{
	*mScale += scale;
}

void Transform2D::Rotate(float angle_deg)
{
	mRotation += angle_deg;
}
#pragma endregion

/* +==== Setter Methods ====+ */
#pragma region Setter Methods
void Transform2D::SetPosition(real x, real y)
{
	mPosition->x = x;
	mPosition->y = y;
}
void Transform2D::SetPosition(const Vector2& pos)
{
	*mPosition = pos;
}

void Transform2D::SetScale(real x, real y)
{
	mScale->x = x;
	mScale->y = y;
}

void Transform2D::SetScale(const Vector2& pos)
{
	*mScale = pos;
}

void Transform2D::SetRotation(real angle_deg)
{
	mRotation = angle_deg;
}

#pragma endregion

/* +==== Getter Methods ====+ */
#pragma region Getter Methods
Vector2 Transform2D::GetPosition() const
{
	return *mPosition;
}
Vector2 Transform2D::GetScale() const
{
	return *mScale;
}

float Transform2D::GetRotation() const
{
	return mRotation;
}

Vector2 Transform2D::GetDirection(const Vector2& facing)
{
	if (mCurrentRotation != mRotation)
	{
		mCurrentRotation = mRotation;
		*mDirection = getBasicRotation(facing, toRadian<real>(mRotation));
	}

	return *mDirection;
}

#pragma endregion
/* +==== Operator overloading ====+ */
#pragma region Operator Overloading
Transform2D Transform2D::operator + (const Transform2D& rhs) const
{
	Transform2D t = *this;
	t.SetPosition(*mPosition + rhs.GetPosition());
	t.SetRotation(mRotation + rhs.GetRotation());
	t.SetScale(*mScale + rhs.GetScale());

	return t;
}

Transform2D Transform2D::operator - (const Transform2D& rhs) const
{
	Transform2D t = *this;
	t.SetPosition(*mPosition - rhs.GetPosition());
	t.SetRotation(mRotation - rhs.GetRotation());
	t.SetScale(*mScale - rhs.GetScale());

	return t;
}

void Transform2D::operator += (const Transform2D& rhs)
{
	*mPosition += rhs.GetPosition();
	mRotation += rhs.GetRotation();
	*mScale += rhs.GetScale();
}
void Transform2D::operator -= (const Transform2D& rhs)
{
	*mPosition -= rhs.GetPosition();
	mRotation -= rhs.GetRotation();
	*mScale -= rhs.GetScale();
}

Transform2D Transform2D::operator * (real scale) const
{
	Transform2D t = *this;
	t.SetPosition(*mPosition * scale);
	t.SetRotation(mRotation * scale);
	t.SetScale(*mScale * scale);

	return t;
}

void Transform2D::operator *= (real scale)
{
	*mPosition *= scale;
	mRotation *= scale;
	*mScale *= scale;
}
#pragma endregion
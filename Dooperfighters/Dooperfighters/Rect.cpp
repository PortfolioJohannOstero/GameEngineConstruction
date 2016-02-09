#include "Rect.h"

using namespace Sheep;

/* +==== Constructors ====+ */
Rect::Rect() :left(0), right(0), top(0), bottom(0) {}
Rect::Rect(int l, int r, int t, int b) : left(l), right(r), top(t), bottom(b) {}
Rect::Rect(int width, int height) : left(0), right(width), top(0), bottom(height) {}

Rect::Rect(const Vector2& worldSpace, const Rect& boundary)
{
	left = worldSpace.x;
	right = worldSpace.x + boundary.Width();

	top = worldSpace.y;
	bottom = worldSpace.y + boundary.Height();
}

/* +=== Copy ===+ */
Rect::Rect(const Rect& cpy)
{
	*this = cpy;
}

/* +==== Get Dimension ====+ */
#pragma region Get Dimension
int Rect::Width() const
{
	return right - left;
}

int Rect::Height() const
{
	return bottom - top;
}

int Rect::Area() const
{
	return Width() * Height();
}
#pragma endregion

/* +==== Set dimension ====+ */
#pragma region Set Dimension
void Rect::setDimension(int l, int r, int t, int b)
{
	left = l;
	right = r;
	top = t;
	bottom = b;
}

void Rect::setDimension(int width, int height)
{
	setDimension(0, width, 0, height);
}

void Rect::Translate(int x, int y)
{
	left += x;
	right += x;

	top += y;
	bottom += y;
}

void Rect::Translate(const Vector2& pos)
{
	Translate(pos.x, pos.y);
}
#pragma endregion

/* +==== Collider Handling ====+ */
#pragma region Collider Handling
bool Rect::CompletelyOutside(const Rect& rect, int x, int y)
{
	return x >	rect.right	||
		   y >	rect.bottom	||
		   x <	rect.left - Width() ||
		   y <	rect.top  - Height();
}

void Rect::ClipTo(const Rect& rect)
{
	if (left < rect.left)
		left = rect.left;
	if (right > rect.right)
		right = rect.right;

	if (top < rect.top)
		top = rect.top;
	if (bottom > rect.bottom)
		bottom = rect.bottom;
}
#pragma endregion

/* +==== Operator Overloading ====+ */
#pragma region Operator Overloading
 Rect& Rect::operator = (const Rect& rhs)
{
	left = rhs.left;
	right = rhs.right;
	top = rhs.top;
	bottom = rhs.bottom;
	return *this;
}

Rect Rect::operator + (int rhs) const
{
	Rect rect = *this;
	rect.left	+= rhs;
	rect.right	+= rhs;
	rect.top	+= rhs;
	rect.bottom += rhs;
	return rect;
}

Rect Rect::operator - (int rhs) const
{
	Rect rect = *this;
	rect.left	-= rhs;
	rect.right	-= rhs;
	rect.top	-= rhs;
	rect.bottom -= rhs;
	return rect;
}

Rect Rect::operator / (int rhs) const
{
	Rect rect = *this;
	rect.left	/= rhs;
	rect.right	/= rhs;
	rect.top	/= rhs;
	rect.bottom /= rhs;
	return rect;
}

Rect Rect::operator * (int rhs) const
{
	Rect rect = *this;
	rect.left	*= rhs;
	rect.right	*= rhs;
	rect.top	*= rhs;
	rect.bottom *= rhs;
	return rect;
}

void Rect::operator += (int rhs)
{
	left	+= rhs;
	right	+= rhs;
	top		+= rhs;
	bottom	+= rhs;
}

void Rect::operator -= (int rhs)
{
	left	-= rhs;
	right	-= rhs;
	top		-= rhs;
	bottom	-= rhs;
}

void Rect::operator /= (int rhs)
{
	left	/= rhs;
	right	/= rhs;
	top		/= rhs;
	bottom	/= rhs;
}

void Rect::operator *= (int rhs)
{
	left	*= rhs;
	right	*= rhs;
	top		*= rhs;
	bottom	*= rhs;
}

Rect Rect::operator + (const Rect& rhs) const
{
	Rect rect = *this;
	rect.left	+= rhs.left;
	rect.right	+= rhs.right;
	rect.top	+= rhs.top;
	rect.bottom += rhs.bottom;
	return rect;
}

Rect Rect::operator - (const Rect& rhs) const
{
	Rect rect = *this;
	rect.left	-= rhs.left;
	rect.right	-= rhs.right;
	rect.top	-= rhs.top;
	rect.bottom -= rhs.bottom;
	return rect;
}
Rect Rect::operator / (const Rect& rhs) const
{
	Rect rect = *this;
	rect.left	/= rhs.left;
	rect.right	/= rhs.right;
	rect.top	/= rhs.top;
	rect.bottom /= rhs.bottom;
	return rect;
}

Rect Rect::operator * (const Rect& rhs) const
{
	Rect rect = *this;
	rect.left	*= rhs.left;
	rect.right	*= rhs.right;
	rect.top	*= rhs.top;
	rect.bottom *= rhs.bottom;
	return rect;
}


void Rect::operator += (const Rect& rhs)
{
	left	+=	rhs.left;
	right	+= rhs.right;
	top		+= rhs.top;
	bottom	+= rhs.bottom;
}

void Rect::operator -= (const Rect& rhs)
{
	left	-= rhs.left;
	right	-= rhs.right;
	top		-= rhs.top;
	bottom	-= rhs.bottom;
}

void Rect::operator /= (const Rect& rhs)
{
	left	/= rhs.left;
	right	/= rhs.right;
	top		/= rhs.top;
	bottom	/= rhs.bottom;
}

void Rect::operator *= (const Rect& rhs)
{
	left	*= rhs.left;
	right	*= rhs.right;
	top		*= rhs.top;
	bottom	*= rhs.bottom;
}

bool Rect::operator == (const Rect& rhs) const
{
	return left   == rhs.left  && 
		   right  == rhs.right &&
		   top	  == rhs.top   &&
		   bottom == rhs.bottom;
}
bool Rect::operator != (const Rect& rhs) const
{
	return left   != rhs.left  && 
		   right  != rhs.right &&
		   top	  != rhs.top   &&
		   bottom != rhs.bottom;
}

#pragma endregion
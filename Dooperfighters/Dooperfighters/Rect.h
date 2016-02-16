#ifndef RECT
#define RECT

#include "Vector2.h"

namespace Sheep
{
	class Rect
	{
	public:
		int left, right, top, bottom;


		/* +==== Constructors ====+ */
		Rect(); /* <-- set eveyrhting to zero */
		Rect(int l, int r, int t, int b);
		Rect(int width, int height);
		Rect(const Vector2& worldSpace, const Rect& boundary);
		Rect(const Rect& cpy);

		/* +==== Set dimensions ====+ */
		void setDimension(int l, int r, int t, int b);
		void setDimension(int width, int height);
		void Translate(int x, int y);
		void Translate(const Sheep::Vector2& pos);
		void Rotate(const int angle);

		/* +==== Get Dimension ====+ */
		int Width() const;
		int Height() const;
		int Area() const;
		Vector2 Center() const;

		/* +==== Collider Handling ====+ */
		bool CompletelyOutside(const Rect& rect, int x, int y);
		void ClipTo(const Rect& rect);
		bool Contains(const Vector2& pos);

		/* +==== Operator Overloading ====+ */
		#pragma region Operator Overloading
		Rect& operator = (const Rect& rhs);

		Rect operator + (int rhs) const;
		Rect operator - (int rhs) const;
		Rect operator / (int rhs) const;
		Rect operator * (int rhs) const;

		void operator += (int rhs);
		void operator -= (int rhs);
		void operator /= (int rhs);
		void operator *= (int rhs);

		Rect operator + (const Rect& rhs) const;
		Rect operator - (const Rect& rhs) const;
		Rect operator / (const Rect& rhs) const;
		Rect operator * (const Rect& rhs) const;

		void operator += (const Rect& rhs);
		void operator -= (const Rect& rhs);
		void operator /= (const Rect& rhs);
		void operator *= (const Rect& rhs);

		bool operator == (const Rect& rhs) const;
		bool operator != (const Rect& rhs) const;

		#pragma endregion
	};
}


#endif
#ifndef VECTOR2
#define VECTOR2

/*
+=============================================+
+==============================================+
Vector3.h
Engine: Sheep Engine
Author: Jóhann Østerø.
--
This is a standard 2D Vector Class.
+==============================================+
+============================================+
*/

#include "Precision.h"

namespace Sheep
{
	class Vector2
	{
	public:
		real x, y;

		/* +==== Constructors ====+ */
		Vector2(); /* <-- Default: x,y = 0 */
		Vector2(const real ix, const real jy);

			/* +== Copy ==+ */
		Vector2(const Vector2& cpy);
		Vector2& operator = (const Vector2& rhs);

		/* +==== General Vector Methods ====+ */
		void Invert();

		real Magnitude(const Vector2& otherPoint) const;
		real SquareMagnitude(const Vector2& otherPoint) const; /* <-- To avoid using square root: http://stackoverflow.com/questions/6884359/c-practical-computational-complexity-of-cmath-sqrt */

		void Normalize(const Vector2& otherPoint);
		Vector2 Normalized(const Vector2& otherPoint) const;

		/* +== Scalars ==+ */
		Vector2 operator * (const real rhs) const;
		void operator   *= (const real rhs);
		
		Vector2 operator / (const real rhs) const;
		void operator /= (const real rhs);

		Vector2 operator + (const Vector2& rhs) const;
		void operator   += (const Vector2& rhs);

		Vector2 operator - (const Vector2& rhs) const;
		void operator   -= (const Vector2& rhs);

		void AddScaledVector(const Vector2& vector, real scale);	/* <-- two in one, for convienence sake */

		/* +== Component Product ==+ */
		Vector2 ComponentProduct(const Vector2& vector) const; /* <-- returns the component product */
		void ComponentProductUpdate(const Vector2& vector); /* <-- updates it to the component product*/

		/* +== Scalar (Dot) Product ==+ */
		//real scalarProduct(const Vector2& vector);
		real operator * (const Vector2& vector) const; /* <-- Scalar product (dot product) */

		/* +== Vector (Cross) Product ==+ */
		//Vector2 vectorProduct(const Vector2& vector) const;
		//void vectorProductUpdate(const Vector2& vector);
	};

	inline Vector2 Right()
	{
		return Vector2(1, 0);
	}

	inline Vector2 Left()
	{
		return Vector2(-1, 0);
	}

	inline Vector2 Up()
	{
		return Vector2(0, 1);
	}

	inline Vector2 Down()
	{
		return Vector2(0, -1);
	}

}


#endif
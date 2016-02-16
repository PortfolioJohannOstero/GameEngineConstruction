#ifndef SHEEP_TRANSFORM2D
#define SHEEP_TRANSFORM2D

#include "Precision.h"

namespace Sheep
{
	class Vector2;
	class Transform2D
	{
	public:
		/* +==== Constructor ====+ */
		Transform2D();
		Transform2D(real x, real y);
		Transform2D(const Vector2& pos);
		~Transform2D();

		/* +=== Copy ===+ */
		Transform2D(const Transform2D& cpy);
		Transform2D& operator = (const Transform2D& rhs);

		/* +==== Transformation ====+ */
		void Translate(real x, real y);
		void Translate(const Vector2& pos);

		void Scale(real x, real y);
		void Scale(real s);
		void Scale(const Vector2& scale);

		void Rotate(real angle_deg);

		/* +==== Setter Methods ====+ */
		void SetPosition(real x, real y);
		void SetPosition(const Vector2& pos);

		void SetScale(real x, real y);
		void SetScale(const Vector2& pos);

		void SetRotation(real angle_deg);

		/* +==== Getter Methods ====+ */
		Vector2 GetPosition() const;
		Vector2 GetScale() const;
		float GetRotation() const;
		Vector2 GetDirection(const Vector2& facing);
		Transform2D GetPreviousTransform() const;

		/* +==== Operator overloading ====+ */
		Transform2D operator + (const Transform2D& rhs) const;
		Transform2D operator - (const Transform2D& rhs) const;
		void operator += (const Transform2D& rhs);
		void operator -= (const Transform2D& rhs);

		Transform2D operator * (real scale) const;
		void operator *= (real scale);

	private:
		Vector2* mPosition = nullptr;
		Vector2* mScale = nullptr;
		float mRotation;

		Vector2* mDirection = nullptr;
		float mCurrentRotation;
	};
}

#endif
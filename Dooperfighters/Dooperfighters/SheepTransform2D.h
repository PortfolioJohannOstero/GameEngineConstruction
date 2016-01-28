#pragma once

namespace Sheep
{
	class Vector2;
	class Transform2D
	{
	public:
		/* +==== Constructor ====+ */
		Transform2D();
		Transform2D(int x, int y);
		Transform2D(const Vector2& pos);
		~Transform2D();

		/* +=== Copy ===+ */
		Transform2D(const Transform2D& cpy);
		Transform2D& operator = (const Transform2D& rhs);

		/* +==== Transformation ====+ */
		void Translate(int x, int y);
		void Translate(const Vector2& pos);

		void Scale(int x, int y);
		void Scale(int s);
		void Scale(const Vector2& scale);

		void Rotate(int angle);

		/* +==== Setter Methods ====+ */
		void SetPosition(int x, int y);
		void SetPosition(const Vector2& pos);

		void SetScale(int x, int y);
		void SetCale(const Vector2& pos);

		void SetRotation(int angle_deg);

		/* +==== Getter Methods ====+ */
		Vector2 GetPosition() const;
		Vector2 GetScale() const;
		int GetRotation() const;

	private:
		Vector2* mPosition = nullptr;
		Vector2* mScale = nullptr;
		int mRotation;
	};
}
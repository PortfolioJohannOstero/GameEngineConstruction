#ifndef SHEEP_OBJECT
#define SHEEP_OBJECT

/*
+=============================================+
+==============================================+
Object.h
Engine: Sheep Engine
Author: Jóhann Østerø.
--
This is the base Object, every other object inherits from this object.
The object has an overloadable renderer and overloadable collision checks.

It supports OnCollisionExit and OnCollisionEnter.
This class is an interface, which means that every object that inherits from this one has to overload the Update method.
This class is designed with Polymorphism in mind


NOTE: Show Debugging: <TAB> 
+==============================================+
+============================================+
*/

#include "SheepTag.h"
#include "SheepView.h"
#include "SheepDebugMessage.h"
#include "Precision.h"

#include <vector>

namespace Sheep
{
	class Vector2;
	class Transform2D;
	class Rect;
	class Animator;
	class Object
	{
	public:
		/* +==== Constructors ====+ */
		Object(const std::string& name, unsigned int spriteId, eTAG tag = NEUTRAL);
		Object(const std::string& name, real speed, int health, int damage, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag = NEUTRAL);
		Object(const std::string& name, real speed, int health, int damage, real x, real y, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag = NEUTRAL);
		virtual ~Object();

		/* +=== Copy ===+ */
		Object(const Object& cpy);
		Object& operator = (const Object& rhs);

		/* +==== Setters ====+ */
		void SetActive(bool isActive);
	
		void SetName(const std::string& name);
		void SetSpeed(real speed);
		void SetHealth(int health);
		void SetCollisionDamage(int damage);
		void SetTag(eTAG tag);
		void SetCollisionBorder(const Rect& border);
		Vector2 GetPreviousPosition() const;

		/* +=== Getters ===+ */
		bool isActive() const;
		std::string GetName() const;
		real GetSpeed() const;
		int GetHealth() const;
		int GetCollisionDamage() const;
		eTAG GetTag() const;
		Rect GetCollisionBorder() const;
		Vector2 GetCollisionBorderOffset() const;

		Transform2D* transform = nullptr;

		/* +=== Property handling ===+ */
		void TakeDamage(int damage);
		void AddAnimation(const Animator& animation);

		/* +==== Collision Handling ====+ */
		void AddCollisionTag(eTAG tag);
		virtual void OnCollisionEnter(Object* otherObject);
		virtual void OnCollisionExit(Object* otherObject);
		void CollisionCheck(std::vector<Object*>& mapObjects);

		/* +==== Object Control ====+ */
		virtual void Update() = 0;
		virtual void Render();

	protected:
		unsigned int mSpriteId = 0;
		bool mIsActive;

		Transform2D* mPreviousTransform = nullptr;
		Rect* mCollisionBorder = nullptr;
		eTAG mTag;
		std::vector<eTAG> mCollisionCheckTags; // <--- Allows the user to determine what the object needs to do a collition check with. This is to reduce computation as well as leave more control to the user

		int mFrameNumber = 0;
		Animator* mAnimation = nullptr;

		std::string mName;
		real mSpeed;
		int mHealth;
		int mCollisionDamage;
		Vector2* mCollisionBoxOffset = nullptr; // <--- used to offset the collision box. to allow for complete flexibility

	private:
		Object* mCurrentHitObject = nullptr;
		bool HitCheck(const Vector2& objectHit_position, const Rect& objectHit_boundary);
	};
}

#endif
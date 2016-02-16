#include "SheepObject.h"

#include "SheepTransform2D.h"
#include "Vector2.h"
#include "SheepSprite.h"

#include "Utility_Animation.h"
#include "SheepDebug.h"

using namespace Sheep;

/* +==== Constructors ====+ */
#pragma region Constructors
Object::Object(const std::string& name, unsigned int spriteId, eTAG tag)
	: mName(name), mSpriteId(spriteId), mSpeed(1.0f), mHealth(1), mCollisionDamage(1), mIsActive(true), mTag(tag)
{
	transform = new Transform2D();
	mPreviousTransform = new Transform2D();
	mCollisionBorder = new Rect();
	mCollisionBoxOffset = new Vector2();
}

Object::Object(const std::string& name, real speed, int health, int damage, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag)
	: mName(name), mSpriteId(spriteId), mSpeed(speed), mHealth(health), mCollisionDamage(damage), mIsActive(true), mTag(tag)
{
	transform = new Transform2D(position);
	mPreviousTransform = new Transform2D(position);
	mCollisionBorder = new Rect(collisionBox.Width(), collisionBox.Height());
	mCollisionBoxOffset = new Vector2(collisionBoxOffset);
}

Object::Object(const std::string& name, real speed, int health, int damage, real x, real y, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag)
	: mName(name), mSpriteId(spriteId), mSpeed(speed), mHealth(health), mCollisionDamage(damage), mIsActive(true), mTag(tag)
{
	transform = new Transform2D(x, y);
	mPreviousTransform = new Transform2D(x, y);
	mCollisionBorder = new Rect(collisionBox.Width(), collisionBox.Height());
	mCollisionBoxOffset = new Vector2(collisionBoxOffset);
}

Object::~Object()
{
	delete transform;
	transform = nullptr;
	delete mPreviousTransform;
	mPreviousTransform = nullptr;
	delete mCollisionBorder;
	mCollisionBorder = nullptr;

	delete mCollisionBoxOffset;
	mCollisionBoxOffset = nullptr;
}
#pragma endregion

/* +=== Copy ===+ */
#pragma region Copy
Object::Object(const Object& cpy)
{
	*this = cpy;
}

Object& Object::operator = (const Object& rhs)
{
	if (!transform)
		transform = new Transform2D();

	if (!mPreviousTransform)
		mPreviousTransform = new Transform2D();

	if (!mCollisionBorder)
		mCollisionBorder = new Rect();

	*transform = *rhs.transform;
	*mPreviousTransform = *rhs.mPreviousTransform;
	*mCollisionBorder = *rhs.mCollisionBorder;
	
	mSpriteId = rhs.mSpriteId;
	mIsActive = mIsActive;
	mTag = rhs.mTag;
	mSpeed = rhs.mSpeed;
	mHealth = rhs.mHealth;
	mCollisionDamage = rhs.mCollisionDamage;

	return *this;
}
#pragma endregion

/* +==== Setters ====+ */
#pragma region Setters
void Object::SetActive(bool isActive)
{
	mIsActive = isActive;
}
void Object::SetName(const std::string& name)
{
	mName = name;
}
void Object::SetSpeed(real speed)
{
	mSpeed = speed;
}
void Object::SetHealth(int health)
{
	mHealth = health;
}
void Object::SetCollisionDamage(int damage)
{
	mCollisionDamage = damage;
}
void Object::SetTag(eTAG tag)
{
	mTag = tag;
}
void Object::SetCollisionBorder(const Rect& border)
{
	*mCollisionBorder = border;
}
#pragma endregion

/* +==== Getters ====+ */
#pragma region Getters
bool Object::isActive() const
{
	return mIsActive;
}
std::string Object::GetName() const
{
	return mName;
}
real Object::GetSpeed() const
{
	return mSpeed;
}
int Object::GetHealth() const
{
	return mHealth;
}
int Object::GetCollisionDamage() const
{
	return mCollisionDamage;
}
eTAG Object::GetTag() const
{
	return mTag;
}
Rect Object::GetCollisionBorder() const
{
	return *mCollisionBorder;
}
Vector2 Object::GetCollisionBorderOffset() const
{
	return *mCollisionBoxOffset;
}


Vector2 Object::GetPreviousPosition() const
{
	return mPreviousTransform->GetPosition();
}

#pragma endregion

/* +=== Rendering ===+ */
void Object::Render()
{
	if (mIsActive)
	{
		Transform2D interpolatedPos = Lerp<Transform2D, DWORD>(*mPreviousTransform, *transform, HAPI->GetTime());
		VIEW.Render(mSpriteId, interpolatedPos, mPreviousTransform->GetRotation(), 0);

		const float prevRot = mPreviousTransform->GetRotation();
		const float currRot = transform->GetRotation();

		Debug::DisplayCollisionBox(*this, { 255, 255, 0 });
		Debug::DisplayDirection(*this, 30, { 255, 0, 0 });
	}
}

/* +==== Collision Handling ====+ */
#pragma region Collision Handling
void Object::AddCollisionTag(eTAG tag)
{
	for (const auto& collideTag : mCollisionCheckTags)
	{
		if (collideTag == tag)
			return;
	}

	mCollisionCheckTags.push_back(tag);
}

void Object::OnCollisionEnter(Object* otherObject) {}
void Object::OnCollisionExit(Object* otherObject) {}

void Object::CollisionCheck(std::vector<Object*>& mapObjects)
{
	if (mCollisionCheckTags.size() <= 0 || mCollisionBorder == nullptr || !mIsActive)
		return;

	for (auto object : mapObjects)
	{
		if (object == this)
			continue;

		bool found = false;
		for (auto collisionTag : mCollisionCheckTags)
		{
			if (collisionTag == object->mTag)
			{
				found = true;
				break;
			}
		}

		if (!found)
			continue;

		// On Collision Enter
		if (HitCheck(object->transform->GetPosition(), *object->mCollisionBorder))
		{
			this->OnCollisionEnter(object);
			mCurrentHitObject = object;
		}
		// On Collision Exit
		else if (mCurrentHitObject != nullptr)
		{
			this->OnCollisionExit(mCurrentHitObject);
			mCurrentHitObject = nullptr;
		}
	}
#pragma endregion
}

bool Object::HitCheck(const Vector2& objectHit_position, const Rect& objectHit_boundary)
{
	const Rect boundaryToWorld_local(transform->GetPosition() + *mCollisionBoxOffset, *mCollisionBorder);
	const Rect boundaryToWorld_external(objectHit_position + *mCollisionBoxOffset, objectHit_boundary);

	// if object is outside of the bounding box then return true, then flips it
	return !(boundaryToWorld_external.left > boundaryToWorld_local.right || boundaryToWorld_external.right < boundaryToWorld_local.left ||
			 boundaryToWorld_external.top > boundaryToWorld_local.bottom || boundaryToWorld_external.bottom < boundaryToWorld_local.top);
}

#pragma endregion
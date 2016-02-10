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
	: mName(name), mSpriteId(spriteId), mSpeed(DEFAULT_VALUE), mHealth(DEFAULT_VALUE), mCollisionDamage(DEFAULT_VALUE), mIsActive(true), mTag(tag)
{
	transform = new Transform2D();
	mPreviousTransform = new Transform2D();
	mCollisionBorder = new Rect();
}

Object::Object(const std::string& name, unsigned int speed, int health, int damage, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, eTAG tag)
	: mName(name), mSpriteId(spriteId), mSpeed(speed), mHealth(health), mCollisionDamage(damage), mIsActive(true), mTag(tag)
{
	transform = new Transform2D(position);
	mPreviousTransform = new Transform2D(position);
	mCollisionBorder = new Rect(collisionBox.Width(), collisionBox.Height());
}

Object::Object(const std::string& name, unsigned int speed, int health, int damage, int x, int y, unsigned int spriteId, const Rect& collisionBox, eTAG tag)
	: mName(name), mSpriteId(spriteId), mSpeed(speed), mHealth(health), mCollisionDamage(damage), mIsActive(true), mTag(tag)
{
	transform = new Transform2D(x, y);
	mPreviousTransform = new Transform2D(x, y);
	mCollisionBorder = new Rect(collisionBox.Width(), collisionBox.Height());
}

Object::~Object()
{
	delete transform;
	transform = nullptr;
	delete mPreviousTransform;
	mPreviousTransform = nullptr;
	delete mCollisionBorder;
	mCollisionBorder = nullptr;
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
void Object::SetSpeed(unsigned int speed)
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
unsigned int Object::GetSpeed() const
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
#pragma endregion

/* +=== Rendering ===+ */
void Object::Render()
{
	if (mIsActive)
	{
		Transform2D interpolatedPos = Lerp<Transform2D, DWORD>(*mPreviousTransform, *transform, HAPI->GetTime());
		VIEW.Render(mSpriteId, *mPreviousTransform, 0);

		Sheep::Debug::DisplayCollisionBox(*this, { 255, 255, 0 });
		Sheep::Debug::DisplayDirection(*this, 30, { 255, 0, 0 });
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
	const Rect boundaryToWorld_local(transform->GetPosition(), *mCollisionBorder);
	const Rect boundaryToWorld_external(objectHit_position, objectHit_boundary);

	// if object is outside of the bounding box then return true, then flips it
	return !(boundaryToWorld_external.left > boundaryToWorld_local.right || boundaryToWorld_external.right < boundaryToWorld_local.left ||
			 boundaryToWorld_external.top > boundaryToWorld_local.bottom || boundaryToWorld_external.bottom < boundaryToWorld_local.top);
}

#pragma endregion
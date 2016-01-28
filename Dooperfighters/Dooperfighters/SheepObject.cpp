#include "SheepObject.h"

#include "SheepTransform2D.h"
#include "Vector2.h"
#include "SheepSprite.h"

using namespace Sheep;

/* +==== Constructors ====+ */
#pragma region Constructors
Object::Object(unsigned int spriteId, eTAG tag)
	: mSpriteId(spriteId), mSpeed(DEFAULT_VALUE), mHealth(DEFAULT_VALUE), mCollisionDamage(DEFAULT_VALUE), mIsActive(true), mTag(tag)
{
	transform = new Transform2D();
	mNextTransform = new Transform2D();
	mCollisionBorder = new Rect();
}

Object::Object(unsigned int speed, int health, int damage, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, eTAG tag)
	: mSpriteId(spriteId), mSpeed(speed), mHealth(health), mCollisionDamage(damage), mIsActive(true), mTag(tag)
{
	transform = new Transform2D(position);
	mNextTransform = new Transform2D(position);
	mCollisionBorder = new Rect(collisionBox.Width(), collisionBox.Height());
}

Object::Object(unsigned int speed, int health, int damage, int x, int y, unsigned int spriteId, const Rect& collisionBox, eTAG tag)
	:mSpriteId(spriteId), mSpeed(speed), mHealth(health), mCollisionDamage(damage), mIsActive(true), mTag(tag)
{
	transform = new Transform2D(x, y);
	mNextTransform = new Transform2D(x, y);
	mCollisionBorder = new Rect(collisionBox.Width(), collisionBox.Height());
}

Object::~Object()
{
	delete transform;
	transform = nullptr;
	delete mNextTransform;
	mNextTransform = nullptr;
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

	if (!mNextTransform)
		mNextTransform = new Transform2D();

	if (!mCollisionBorder)
		mCollisionBorder = new Rect();

	*transform = *rhs.transform;
	*mNextTransform = *rhs.mNextTransform;
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

/* +=== Tag handling ===+ */
void Object::AddCollisionTag(eTAG tag)
{
	for (const auto& collideTag : mCollisionCheckTags)
	{
		if (collideTag == tag)
			return;
	}

	mCollisionCheckTags.push_back(tag);
}

void Object::Render()
{
	if (mIsActive)
	{
		VIEW.Render(mSpriteId, *transform, 0);
		VIEW.Debug_DisplayCollisionBox(*transform, *mCollisionBorder, { 255, 255, 0 });
	}
		
}

void Object::OnCollisionEnter(Object* otherObject)
{}

void Object::OnCollisionExit(Object* otherObject)
{}

void Object::CollisionCheck(std::vector<Object*>& mapObjects)
{
	if (mCollisionCheckTags.size() <= 0 || mCollisionBorder == nullptr)
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
		if (mCollisionBorder->Contains(*object->mCollisionBorder, transform->GetPosition(), object->transform->GetPosition()))
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
}
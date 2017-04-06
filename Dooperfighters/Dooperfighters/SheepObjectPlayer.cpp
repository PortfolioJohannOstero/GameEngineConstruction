#include "SheepObjectPlayer.h"
#include "SheepTransform2D.h"
#include "Rect.h"

#include "SheepInput.h"
#include "SheepWorld.h"

#include "SheepAmmoCollection.h"
#include "SheepPhysics.h"
#include "Utility.h"

#include "SheepWorldMessages.h"

using namespace Sheep;

/* +==== Constructors ====+ */
#pragma region CONSTRUCTORS
ObjectPlayer::ObjectPlayer(const std::string& name, unsigned int spriteId, eTAG tag, const AmmoCollection& ammo) : Object(name, spriteId, tag)
{
	SetProjectileSpawnPoint(transform->GetPosition() + mCollisionBorder->Center());
	mProjectiles= new AmmoCollection(ammo);
}

ObjectPlayer::ObjectPlayer(const std::string& name, real speed, int health, int damage, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag, const AmmoCollection& ammo)
	: Object(name, speed, health, damage, position, spriteId, collisionBox, collisionBoxOffset, tag)
{
	SetProjectileSpawnPoint(transform->GetPosition() + mCollisionBorder->Center());
	mProjectiles = new AmmoCollection(ammo);
}

ObjectPlayer::ObjectPlayer(const std::string& name, real speed, int health, int damage, real x, real y, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag, const AmmoCollection& ammo)
	: Object(name, speed, health, damage, x, y, spriteId, collisionBox, collisionBoxOffset, tag)
{
	SetProjectileSpawnPoint(transform->GetPosition() + mCollisionBorder->Center());
	mProjectiles = new AmmoCollection(ammo);
}

ObjectPlayer::~ObjectPlayer()
{
	delete mProjectiles;
	mProjectiles = nullptr;
}
#pragma endregion constructors


void ObjectPlayer::Update()
{
	if (mHealth < 0)
		SetActive(false);

	if (!mIsActive)
		return;

	/* +=== out of bound check ===+ */
	const Rect& windowBoundary = VIEW.WindowBoundary();
	const Vector2& pos = transform->GetPosition();
	if (pos.x + mCollisionBorder->Width() + mCollisionBoxOffset->x > windowBoundary.Width())
	{
		transform->SetPosition(-mCollisionBorder->Width() - mCollisionBoxOffset->x, pos.y);
	}
	else if (pos.x + mCollisionBorder->Width() + mCollisionBoxOffset->x < 0)
		transform->SetPosition(windowBoundary.Width() + mCollisionBorder->Width() + mCollisionBoxOffset->x, pos.y);

	/* +=== Shooting ===+ */
	if (Input::Key_isPressed(mControls.fire_bullet) && mProjectiles->bullets.Shoot())
	{
		WORLD.SendMessage(eWorld_message_types::FIRE, &WorldMessage_Fire(this, eTAG::ENEMY, eTAG::PROJECTILE_BULLET, mProjectileSpawnPoint));
		DEBUG_MESSAGE.PushMessage(std::to_string(mProjectiles->bullets.GetAmmoCount()));
	}
	else if (Input::Key_isPressed(mControls.fire_missile) && mProjectiles->missiles.Shoot())
		WORLD.SendMessage(eWorld_message_types::FIRE, &WorldMessage_Fire(this, eTAG::ENEMY, eTAG::PROJECTILE_MISSILE, mProjectileSpawnPoint));
	else if (Input::Key_isPressed(mControls.fire_bomb) && mProjectiles->bombs.Shoot())
		WORLD.SendMessage(eWorld_message_types::FIRE, &WorldMessage_Fire(this, eTAG::ENEMY, eTAG::PROJECTILE_BOMB, mProjectileSpawnPoint));


	/* +=== Controls and Pseudo physics*/
	Vector2& dir = transform->GetDirection(Right());
	if (dir.y < -0.5f)
	{
		mCurrentSpeed -= 0.2f;
	}
	else if (dir.y > 0.2f)
	{
		mCurrentSpeed += 0.2f;
	}
	
	if (mCurrentSpeed > Physics::GetGravity()/2)
		mCurrentSpeed = Physics::GetGravity()/2;

	transform->Translate(dir * Physics::GetGravity());
	mProjectileSpawnPoint = transform->GetPosition() + mCollisionBorder->Center();
	transform->Translate(dir * mCurrentSpeed);

	if (Input::Key_isPressed(mControls.left) || Input::Controller_LeftAnalogueMoved(0, Sheep::ANALOGUE_DIRECTION::LEFT))
	{
		if (mCurrentSpeed > 0)
			mCurrentSpeed -= 0.2f;
	}
	else if (Input::Key_isPressed(mControls.right) || Input::Controller_LeftAnalogueMoved(0, Sheep::ANALOGUE_DIRECTION::RIGHT))
	{
		mCurrentSpeed += 0.2f;
	}

	if (Input::Key_isPressed(mControls.up) || Input::Controller_LeftAnalogueMoved(0, Sheep::ANALOGUE_DIRECTION::UP))
	{
		transform->Rotate(abs(mCurrentSpeed));
		mCollisionBorder->Rotate(1, transform->GetPosition());
	}
	else if (Input::Key_isPressed(mControls.down) || Input::Controller_LeftAnalogueMoved(0, Sheep::ANALOGUE_DIRECTION::DOWN))
	{
		transform->Rotate(-abs(mCurrentSpeed));
		mCollisionBorder->Rotate(1, transform->GetPosition());
	}
}

/* +==== Collision Handiling =====+ */
#pragma region COLLISION HANDLING
void ObjectPlayer::OnCollisionEnter(Object* otherObject)
{
	if (otherObject->GetTag() == ENEMY)
		otherObject->TakeDamage(mCollisionDamage);

}
#pragma endregion collision handling

/* +==== Controls ====+ */
void ObjectPlayer::SetControls(const PlayerControls& controls)
{
	mControls = controls;
}
void ObjectPlayer::SetControls(unsigned int left, unsigned int right, unsigned int up, unsigned int down, unsigned int fire_bullet, unsigned int fire_missile, unsigned int fire_bomb)
{
	mControls = PlayerControls(left, right, up, down, fire_bullet, fire_missile, fire_bomb);
}


/* +==== Projectile handling ====+ */
#pragma region PROJECTILE HANDLING
Vector2 ObjectPlayer::GetProjectileSpawnPoint() const
{
	return mProjectileSpawnPoint + *mCollisionBoxOffset;
}

void ObjectPlayer::SetProjectileSpawnPoint(const Vector2& point)
{
	mProjectileSpawnPoint = point;
}

/* +=== Getters and setters */
void ObjectPlayer::AddAmmo(int ammoCount, eTAG ammoType)
{
	switch (ammoType)
	{
	case eTAG::PROJECTILE_BULLET:
		mProjectiles->bullets.AddAmmo(ammoCount);
		break;
	case eTAG::PROJECTILE_MISSILE:
		mProjectiles->missiles.AddAmmo(ammoCount);
		break;
	case eTAG::PROJECTILE_BOMB:
		mProjectiles->bombs.AddAmmo(ammoCount);
		break;
	}
}

#pragma endregion projectile handling
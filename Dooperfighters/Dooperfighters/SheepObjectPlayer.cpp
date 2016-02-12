#include "SheepObjectPlayer.h"
#include "SheepTransform2D.h"
#include "Rect.h"

#include "SheepInput.h"
#include "SheepWorld.h"

#include "SheepAmmo.h"

using namespace Sheep;

/* +==== Constructors ====+ */
#pragma region CONSTRUCTORS
ObjectPlayer::ObjectPlayer(const std::string& name, unsigned int spriteId, eTAG tag, const Ammo& ammo) : Object(name, spriteId, tag)
{
	SetProjectileSpawnPoint(transform->GetPosition() + mCollisionBorder->Center());
	mProjectile_machineGun = new Ammo(ammo);
}

ObjectPlayer::ObjectPlayer(const std::string& name, unsigned int speed, int health, int damage, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, eTAG tag, const Ammo& ammo)
	: Object(name, speed, health, damage, position, spriteId, collisionBox, tag)
{
	SetProjectileSpawnPoint(transform->GetPosition() + mCollisionBorder->Center());
	mProjectile_machineGun = new Ammo(ammo);
}

ObjectPlayer::ObjectPlayer(const std::string& name, unsigned int speed, int health, int damage, int x, int y, unsigned int spriteId, const Rect& collisionBox, eTAG tag, const Ammo& ammo)
	: Object(name, speed, health, damage, x, y, spriteId, collisionBox, tag)
{
	SetProjectileSpawnPoint(transform->GetPosition() + mCollisionBorder->Center());
	mProjectile_machineGun = new Ammo(ammo);
}

ObjectPlayer::~ObjectPlayer()
{
	delete mProjectile_machineGun;
	mProjectile_machineGun = nullptr;
}
#pragma endregion constructors

void ObjectPlayer::Update()
{
	mPreviousTransform = transform;

	if (Input::Key_isPressed('Q'))
	{
		transform->Rotate(1);
		//DEBUG_MESSAGE.PushMessage("Player Rotation: " + std::to_string(transform->GetRotation()));
	}
	
	if (Input::Key_isPressed('B'))
	{
		AddAmmo(300);
		DEBUG_MESSAGE.PushMessage("Added 300 bullets to player", MESSAGE_TYPE::WARNING);
	}

	if (Input::Key_isPressed(mControls.fire) && mProjectile_machineGun->Shoot())
	{
		WORLD.SendMessage(eWorld_message_types::FIRE, this);
		DEBUG_MESSAGE.PushMessage(std::to_string(mProjectile_machineGun->GetAmmoCount()));
	}


	if (Input::Key_isPressed(mControls.left) || Input::Controller_LeftAnalogueMoved(0, Sheep::ANALOGUE_DIRECTION::LEFT))
	{
		transform->Translate(-1 * mSpeed, 0);
		mProjectileSpawnPoint.x -= mSpeed;
	}
	else if (Input::Key_isPressed(mControls.right) || Input::Controller_LeftAnalogueMoved(0, Sheep::ANALOGUE_DIRECTION::RIGHT))
	{
		transform->Translate(mSpeed, 0);
		mProjectileSpawnPoint.x += mSpeed;
	}

	if (Input::Key_isPressed(mControls.up) || Input::Controller_LeftAnalogueMoved(0, Sheep::ANALOGUE_DIRECTION::UP))
	{
		transform->Translate(0, -1 * mSpeed);
		mProjectileSpawnPoint.y -= mSpeed;
	}
	else if (Input::Key_isPressed(mControls.down) || Input::Controller_LeftAnalogueMoved(0, Sheep::ANALOGUE_DIRECTION::DOWN))
	{
		transform->Translate(0, mSpeed);
		mProjectileSpawnPoint.y += mSpeed;
	}
}

/* +==== Collision Handiling =====+ */
#pragma region COLLISION HANDLING
void ObjectPlayer::OnCollisionEnter(Object* otherObject)
{
	if (otherObject->GetTag() == ENEMY)
		otherObject->SetActive(false);

}

void ObjectPlayer::OnCollisionExit(Object* otherObject)
{
	if (otherObject->GetTag() == ENEMY)
		otherObject->SetActive(true);
}
#pragma endregion collision handling

/* +==== Controls ====+ */
void ObjectPlayer::SetControls(const PlayerControls& controls)
{
	mControls = controls;
}
void ObjectPlayer::SetControls(unsigned int left, unsigned int right, unsigned int up, unsigned int down, unsigned int fire)
{
	mControls = PlayerControls(left, right, up, down, fire);
}


/* +==== Projectile handling ====+ */
#pragma region PROJECTILE HANDLING
Vector2 ObjectPlayer::GetProjectileSpawnPoint() const
{
	return mProjectileSpawnPoint;
}

void ObjectPlayer::SetProjectileSpawnPoint(const Vector2& point)
{
	mProjectileSpawnPoint = point;
}

/* +=== Getters and setters */
void ObjectPlayer::AddAmmo(int ammoCount)
{
	mProjectile_machineGun->AddAmmo(ammoCount);
}

eTAG ObjectPlayer::GetAmmoType() const
{
	return mProjectile_machineGun->GetAmmoType();
}

#pragma endregion projectile handling
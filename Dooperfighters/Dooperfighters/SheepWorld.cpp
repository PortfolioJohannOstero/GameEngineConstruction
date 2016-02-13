#include "SheepWorld.h"
#include "Rect.h"

#include "SheepObject.h"
#include "SheepObjectPlayer.h"
#include "SheepObjectPickup.h"
#include "SheepObjectScenery.h"
#include "SheepObjectProjectile.h"

#include "SheepAmmo.h"

#include "SheepTransform2D.h"
#include "SheepInput.h"

#include "Utility.h"
#include "SheepDebugMessage.h"

using namespace Sheep;

/* +==== Singleton - Construction ====+ */
#pragma region Singleton - Construction
World* World::INSTANCE = nullptr;

/* +=== Create and destroy the singleton ===+ */
void World::Create()
{
	/* If instance has not been created */
	if (!INSTANCE)
		INSTANCE = new World();
}

void World::Destroy()
{
	/* If instance has been created */
	if (INSTANCE)
	{
		delete INSTANCE;
		INSTANCE = nullptr;

		VIEW.Destroy();
	}
}

World::~World()
{
	for (auto object : mObjectList)
	{
		delete object;
		object = nullptr;
	}

	mObjectList.clear();
}


/* +=== Initialises the HAPI library; creates a window ===+ */
bool World::Initialise( int screenWidth, int screenHeight)
{
	/* Check if the instance has been created and if the happy initialize */
	if (!INSTANCE)
		return false;
	
	VIEW.Create();
	if (!VIEW.Initialise(screenWidth, screenHeight, 10))
	{
		VIEW.Destroy();
		return false;
	}


	return true;
}
#pragma endregion

void World::SetFPS(unsigned int fps)
{
	mFPS = fps;
}


void World::SendMessage(eWorld_message_types messageType, const void* messenger)
{
	switch (messageType)
	{
	case eWorld_message_types::FIRE:
		if (Object* obj = FindProjectile(((ObjectPlayer*)messenger)->GetAmmoType()))
		{
			obj->transform->SetPosition(((ObjectPlayer*)messenger)->GetProjectileSpawnPoint());
			obj->transform->SetRotation(((Object*)messenger)->transform->GetRotation());
			((ObjectProjectile*)obj)->SetTarget(eTAG::ENEMY);
			obj->SetActive(true);
		}
	}
}

Object* World::FindProjectile(eTAG projectileType)
{
	for (auto& object : mObjectList)
	{
		if (object->GetTag() == projectileType && !object->isActive())
			return object;
	}

	return nullptr;
}




// TODO: Setup up using xml
void World::LoadLevel(unsigned int index)
{
	unsigned int bgIndex = 0;
	if (!VIEW.CreateSprite(bgIndex, "Sprites/testMap.jpg", 800, 600, 0, 0, BLITTING_TYPES::LINE_BY_LINE))
		return;

	unsigned int playerIndex;
	if (!VIEW.CreateSprite(playerIndex, "Sprites/spritesheet_plane_red.png", 90, 44, 8, 1, BLITTING_TYPES::TRANSPARENT_ROTATION))
		return;

	unsigned int bulletIndex;
	if (!VIEW.CreateSprite(bulletIndex, "Sprites/Bullet.png", 27, 7, 1, 1, BLITTING_TYPES::TRANSPARENT))
		return;

	Sheep::Rect collisionBox(82, 32);

	Ammo gameAmmo(300, 0.5, eTAG::PROJECTILE_BULLET);

	Sheep::ObjectPlayer* player = new Sheep::ObjectPlayer("Player", 10, 10, 10, 500, 500, playerIndex, collisionBox, Sheep::eTAG::PLAYER, gameAmmo);
	player->AddCollisionTag(Sheep::eTAG::ENEMY);
	player->SetControls('A', 'D', 'W', 'S', HK_SPACE);

	Sheep::SheepObjectScenery* background = new Sheep::SheepObjectScenery("Background", 10, 0, 0, bgIndex, { 0, 0, 0, 0 }, Sheep::eTAG::NEUTRAL);
	Sheep::ObjectPickup* enemy = new Sheep::ObjectPickup("Enemy", 10, 10, 10, 300, 300, playerIndex, collisionBox, Sheep::eTAG::ENEMY);

	mObjectList.push_back(background);
	mObjectList.push_back(player);
	mObjectList.push_back(enemy);

	for (int i = 0; i < 50; i++)
	{
		Sheep::ObjectProjectile* projectile = new Sheep::ObjectProjectile("Projectile", 2, 1, 10, 0, 0, bulletIndex, { 0, 25, 0, 6 }, Sheep::eTAG::PROJECTILE_BULLET);
		projectile->SetActive(false);
		projectile->AddCollisionTag(Sheep::eTAG::ENEMY);
		projectile->AddCollisionTag(Sheep::eTAG::PLAYER);
		mObjectList.push_back(projectile);
	}
}

void World::ExecuteGameLoop()
{
	DWORD timerClamp = HAPI->GetTime();
	while (HAPI->Update())
	{
		Input::CheckInput();

		if (timerClamp < HAPI->GetTime() - mFPS)
		{
			for (auto *object : mObjectList)
			{
				object->Update();
				object->CollisionCheck(mObjectList);
			}

			timerClamp = HAPI->GetTime(); // end of loop
		}

		// Rendering
		for (auto *object : mObjectList)
			object->Render();

		//HAPI->RenderText(10, 20, { 255, 255, 255 }, std::to_string(mObjectList[1]->transform->GetRotation()));
		DEBUG_MESSAGE.RenderMessages();
	}
}
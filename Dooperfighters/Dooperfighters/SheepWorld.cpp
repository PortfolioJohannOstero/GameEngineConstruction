 #include "SheepWorld.h"
#include "Rect.h"

#include "SheepObject.h"
#include "SheepObjectPlayer.h"
#include "SheepObjectScenery.h"
#include "SheepObjectProjectile.h"
#include "SheepObjectProjectile_Bomb.h"

#include "SheepObjectEnemyStationary.h"
#include "SheepObjectEnemyPatrol.h"
#include "SheepObjectEnemyFollow.h"
#include "SheepObjectEnemyTurretUtil.h"

#include "SheepAmmoCollection.h"
#include "SheepAnimator.h"

#include "SheepTransform2D.h"
#include "SheepInput.h"

#include "Utility.h"
#include "SheepDebugMessage.h"
#include "SheepWorldMessages.h"

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
	if (!VIEW.Initialise(screenWidth, screenHeight))
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
		WorldMessage_Fire* message = (WorldMessage_Fire*)messenger;

		if (Object* obj = FindProjectile(message->projectileType))
		{
			Vector2 position = message->firePoint;
			position.y -= obj->GetCollisionBorder().Center().y;

			obj->transform->SetPosition(position);
			obj->transform->SetRotation(message->messenger->transform->GetRotation());
			((ObjectProjectile*)obj)->SetTarget(message->target);
			obj->SetActive(true);
		}
	}
}

Object* World::FindProjectile(eTAG projectileType)
{
	for (int bulletIndex : mBulletManager)
	{
		if (mObjectList[bulletIndex]->GetTag() == projectileType && !mObjectList[bulletIndex]->isActive())
			return mObjectList[bulletIndex];
	}

	return nullptr;
}



// TODO: Setup up using xml
void World::LoadLevel(unsigned int index)
{
	// +==== Add Sprites
	unsigned int bgIndex = 0;
	if (!VIEW.CreateSprite(bgIndex, "Sprites/background_terrain.png", VIEW.WindowBoundary().Width(), VIEW.WindowBoundary().Height(), 0, 0, BLITTING_TYPES::LINE_BY_LINE))
		return;

	unsigned int fgIndex = 0;
	if (!VIEW.CreateSprite(fgIndex, "Sprites/background_foreground.png", VIEW.WindowBoundary().Width(), 136, 0, 0, BLITTING_TYPES::LINE_BY_LINE))
		return;

	unsigned int playerIndex;
	if (!VIEW.CreateSprite(playerIndex, "Sprites/spritesheet_plane_red_mini.png", 92, 78, 8, 1, BLITTING_TYPES::TRANSPARENT))
		return;

	unsigned int bulletIndex;
	if (!VIEW.CreateSprite(bulletIndex, "Sprites/projectile_bullet.png", 18, 18, 1, 1, BLITTING_TYPES::TRANSPARENT))
		return;

	unsigned int missileIndex;
	if (!VIEW.CreateSprite(missileIndex, "Sprites/projectile_missile.png", 60, 60, 1, 1, BLITTING_TYPES::TRANSPARENT))
		return;

	unsigned int bombIndex;
	if (!VIEW.CreateSprite(bombIndex, "Sprites/projectile_bomb.png", 55, 40, 1, 1, BLITTING_TYPES::TRANSPARENT))
		return;

	unsigned int enemy_gatlingunIndex;
	if (!VIEW.CreateSprite(enemy_gatlingunIndex, "Sprites/enemy_gatlingun.png", 73, 64, 2, 0, BLITTING_TYPES::TRANSPARENT))
		return;

	unsigned int enemy_followingMineIndex;
	if (!VIEW.CreateSprite(enemy_followingMineIndex, "Sprites/enemy_followingMine.png", 56, 56, 2, 0, BLITTING_TYPES::TRANSPARENT))
		return;

	// +==== Add Objects
	AmmoCollection ammoCollection;
	ammoCollection.bullets	= Ammo(300, 0.5, eTAG::PROJECTILE_BULLET);
	ammoCollection.missiles = Ammo(20, 3, eTAG::PROJECTILE_MISSILE);
	ammoCollection.bombs	= Ammo(4, 8, eTAG::PROJECTILE_BOMB);

	Animator playerAnim(1, 8, true);
	ObjectPlayer* player = new Sheep::ObjectPlayer("Player", 10, 10, 10, 200, 200, playerIndex, { 75, 29 }, Vector2(10, 25), Sheep::eTAG::PLAYER, ammoCollection);
	player->AddCollisionTag(Sheep::eTAG::ENEMY);
	player->SetControls('A', 'D', 'W', 'S', HK_SPACE, 'C', HK_CONTROL);

	ObjectEnemyStationary* enemy_gatlinGun = new ObjectEnemyStationary("Ducky the gatlingun", 50, 8000, Vector2(700, 700), enemy_gatlingunIndex, { 65, 29 }, Vector2(0, 40), eTAG::ENEMY);
	enemy_gatlinGun->AddCollisionTag(eTAG::PLAYER);
	ObjectEnemyTurretUtil* enemyUtil_gatlinGun = enemy_gatlinGun->AttachTurret(50, 1, { 500, 500 }, Vector2(-250, -500), 90, eTAG::PLAYER);

	ObjectEnemyPatrol* enemy_patrollingGatlingun = new ObjectEnemyPatrol("Ducky the wandering gatlingun", 2, 50, 8000, Vector2(200, 700), enemy_gatlingunIndex, { 65, 29 }, Vector2(0, 40), eTAG::ENEMY);
	enemy_patrollingGatlingun->AddPatrolPoint(Vector2(210, 700));
	enemy_patrollingGatlingun->AddPatrolPoint(Vector2(500, 750));
	enemy_patrollingGatlingun->AddPatrolPoint(Vector2(200, 700));


	SheepObjectScenery* background = new Sheep::SheepObjectScenery("Background", 10, 0, 0, bgIndex, { 0, 0, 0, 0 }, { 0, 0 }, Sheep::eTAG::NEUTRAL);
	SheepObjectScenery* foreground = new Sheep::SheepObjectScenery("Foreground", 10, -5, 550, fgIndex, { 0, 0, 0, 0 }, {0,  0}, Sheep::eTAG::NEUTRAL);
	
	// +=== Push Objects to World
	mObjectList.push_back(background);
	mObjectList.push_back(foreground);
	mObjectList.push_back(player);
	mObjectList.push_back(enemy_gatlinGun);
	mObjectList.push_back(enemyUtil_gatlinGun);
	mObjectList.push_back(enemy_patrollingGatlingun);

	for (int i = 0; i < 5; i++)
	{
		Vector2 randomPos((real)randomRange<int>(0, VIEW.WindowBoundary().Width()),
						  (real)randomRange<int>(0, VIEW.WindowBoundary().Height()));
		ObjectEnemyFollow* enemy_followingMine = new ObjectEnemyFollow("Following Mine", 2.f, 1, 50, randomPos, enemy_followingMineIndex, { 56, 56 }, Vector2(0, 0), eTAG::ENEMY);
		enemy_followingMine->SetTarget(player->transform);
		mObjectList.push_back(enemy_followingMine);
	}


	int projectileCount = 50;
	mBulletManager.resize(projectileCount * 3);
	for (int i = 0; i < projectileCount; i+= 3)
	{
		Sheep::ObjectProjectile* bullet = new Sheep::ObjectProjectile("Bullet", 30, 1, 0, 0, bulletIndex, { 15, 6 }, { 0, 5 }, Sheep::eTAG::PROJECTILE_BULLET);
		Sheep::ObjectProjectile* missile = new Sheep::ObjectProjectile("Rocket", 20, 80, 0, 0, missileIndex, { 30, 10 }, { 20, 30 }, Sheep::eTAG::PROJECTILE_MISSILE);
		Sheep::ObjectProjectile_Bomb* bomb = new Sheep::ObjectProjectile_Bomb("Bomb", 500, 0, 0, bombIndex, { 30, 10 }, { 20, 30 }, Sheep::eTAG::PROJECTILE_BOMB);
		bullet->SetActive(false);
		missile->SetActive(false);
		bomb->SetActive(false);

		bullet->AddCollisionTag(Sheep::eTAG::ENEMY);
		bullet->AddCollisionTag(Sheep::eTAG::PLAYER);
		missile->AddCollisionTag(Sheep::eTAG::ENEMY);
		missile->AddCollisionTag(Sheep::eTAG::PLAYER);
		bomb->AddCollisionTag(Sheep::eTAG::ENEMY);
		bomb->AddCollisionTag(Sheep::eTAG::PLAYER);

		mObjectList.push_back(bullet);
		mObjectList.push_back(missile);
		mObjectList.push_back(bomb);

		mBulletManager[i] = mObjectList.size() - 3;
		mBulletManager[i+1] = mObjectList.size() - 2;
		mBulletManager[i+2] = mObjectList.size() - 1;
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
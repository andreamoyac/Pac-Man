
#include "Enemy.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Globals.h"
#include <raymath.h>

Enemy::Enemy(const Point& p, State s, Look view) :
	Entity(p, ENEMY_PHYSICAL_WIDTH, ENEMY_PHYSICAL_HEIGHT, ENEMY_FRAME_SIZE, ENEMY_FRAME_SIZE)
{
	state = s;
	look = view;
	map = nullptr;
}
Enemy::~Enemy()
{
}
AppStatus Enemy::Initialise()
{
	int i;
	const int n = ENEMY_FRAME_SIZE;

	ResourceManager& data = ResourceManager::Instance();
	if (data.LoadTexture(Resource::IMG_PLAYER, "images/player.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}

	render = new Sprite(data.GetTexture(Resource::IMG_PLAYER));
	if (render == nullptr)
	{
		LOG("Failed to allocate memory for player sprite");
		return AppStatus::ERROR;
	}

	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetNumberAnimations((int)EnemyAnim::NUM_ANIMATIONS);

	sprite->SetAnimationDelay((int)EnemyAnim::EYES_UP, ANIM_DELAY);
	sprite->AddKeyFrame((int)EnemyAnim::EYES_UP, { 0, 4, n, n });
	sprite->SetAnimationDelay((int)EnemyAnim::EYES_DOWN, ANIM_DELAY);
	sprite->AddKeyFrame((int)EnemyAnim::EYES_DOWN, { 0, 1, n, n });
	sprite->SetAnimationDelay((int)EnemyAnim::EYES_LEFT, ANIM_DELAY);
	sprite->AddKeyFrame((int)EnemyAnim::EYES_LEFT, { 0, 2, -n, n });
	sprite->SetAnimationDelay((int)EnemyAnim::EYES_RIGHT, ANIM_DELAY);
	sprite->AddKeyFrame((int)EnemyAnim::EYES_RIGHT, { 0, 3, -n, n });

	sprite->SetAnimationDelay((int)EnemyAnim::WALKING_RIGHT, ANIM_DELAY);
	for (i = 0; i < 8; ++i)
		sprite->AddKeyFrame((int)EnemyAnim::WALKING_RIGHT, { (float)i * n, 4 * n, n, n });
	sprite->SetAnimationDelay((int)EnemyAnim::WALKING_LEFT, ANIM_DELAY);
	for (i = 0; i < 8; ++i)
		sprite->AddKeyFrame((int)EnemyAnim::WALKING_LEFT, { (float)i * n, 1 * n, -n, n });
	sprite->SetAnimationDelay((int)EnemyAnim::WALKING_UP, ANIM_DELAY);
	for (i = 0; i < 8; ++i)
		sprite->AddKeyFrame((int)EnemyAnim::WALKING_UP, { (float)i * n, 2 * n, -n, n });
	sprite->SetAnimationDelay((int)EnemyAnim::WALKING_DOWN, ANIM_DELAY);
	for (i = 0; i < 8; ++i)
		sprite->AddKeyFrame((int)EnemyAnim::WALKING_DOWN, { (float)i * n, 3 * n, -n, n });




	return AppStatus::OK;
}
void Enemy::SetTileMap(TileMap* tilemap)
{
	map = tilemap;
}
bool Enemy::IsLookingRight() const
{
	return look == Look::RIGHT;
}
bool Enemy::IsLookingLeft() const
{
	return look == Look::LEFT;
}
bool Enemy::IsLookingUp() const
{
	return look == Look::UP;
}
bool Enemy::IsLookingDown() const
{
	return look == Look::DOWN;
}
void Enemy::SetAnimation(int id)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetAnimation(id);
}
EnemyAnim Enemy::GetAnimation()
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	return (EnemyAnim)sprite->GetAnimation();
}
void Enemy::Stop()
{
	dir = { 0,0 };
	state = State::SCATTER;
	if (IsLookingRight())	SetAnimation((int)EnemyAnim::EYES_RIGHT);
	else					SetAnimation((int)EnemyAnim::EYES_LEFT);
}
void Enemy::StartWalkingLeft()
{
	state = State::CHASE;
	look = Look::LEFT;
	SetAnimation((int)EnemyAnim::WALKING_LEFT);
}
void Enemy::StartWalkingRight()
{
	state = State::CHASE;
	look = Look::RIGHT;
	SetAnimation((int)EnemyAnim::WALKING_RIGHT);
}
void Enemy::StartWalkingUp()
{
	state = State::CHASE;
	look = Look::UP;
	SetAnimation((int)EnemyAnim::WALKING_UP);
}
void Enemy::StartWalkingDown()
{
	state = State::CHASE;
	look = Look::DOWN;
	SetAnimation((int)EnemyAnim::WALKING_DOWN);
}
void Enemy::ChangeAnimRight()
{
	look = Look::RIGHT;
	switch (state)
	{
	case State::SCATTER:SetAnimation((int)EnemyAnim::EYES_RIGHT);    break;
	case State::CHASE: SetAnimation((int)EnemyAnim::WALKING_RIGHT); break;
	}
}
void Enemy::ChangeAnimLeft()
{
	look = Look::LEFT;
	switch (state)
	{
	case State::SCATTER:	 SetAnimation((int)EnemyAnim::EYES_LEFT);    break;
	case State::CHASE: SetAnimation((int)EnemyAnim::WALKING_LEFT); break;
	}
}
void Enemy::ChangeAnimUp()
{
	look = Look::UP;
	switch (state)
	{
	case State::SCATTER:	 SetAnimation((int)EnemyAnim::EYES_UP);    break;
	case State::CHASE: SetAnimation((int)EnemyAnim::WALKING_UP); break;
	}
}
void Enemy::ChangeAnimDown()
{
	look = Look::DOWN;
	switch (state)
	{
	case State::SCATTER:	 SetAnimation((int)EnemyAnim::EYES_DOWN);    break;
	case State::CHASE: SetAnimation((int)EnemyAnim::WALKING_DOWN); break;
	}
}
void Enemy::Update()
{


	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->Update();
}


	/*	box = GetHitbox();
		if (map->TestCollisionWallRight(box))
		{
			pos.y = prev_y;
			if (state == State::CHASE) Stop();
		}*/


void Enemy::DrawDebug(const Color& col) const
{
	Entity::DrawHitbox(pos.x, pos.y, width, height, col);

	DrawText(TextFormat("Position: (%d,%d)\nSize: %dx%d\nFrame: %dx%d", pos.x, pos.y, width, height, frame_width, frame_height), 18 * 16, 0, 8, LIGHTGRAY);
	DrawPixel(pos.x, pos.y, WHITE);
}
void Enemy::Release()
{
	ResourceManager& data = ResourceManager::Instance();
	data.ReleaseTexture(Resource::IMG_PLAYER);

	render->Release();
}
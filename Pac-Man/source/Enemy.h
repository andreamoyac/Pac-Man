#pragma once
#include "Entity.h"
#include "TileMap.h"

//Representation model size: 32x32
#define ENEMY_FRAME_SIZE		16

//Logical model size: 12x28
#define ENEMY_PHYSICAL_WIDTH	12
#define ENEMY_PHYSICAL_HEIGHT	28

//Horizontal speed and vertical speed while falling down
#define ENEMY_SPEED			2





//Logic states
enum class State {SCATTER, CHASE, FRIGHTENED };
enum class Look { RIGHT, LEFT, UP, DOWN };

//Rendering states
enum class EnemyAnim {
	EYES_LEFT, EYES_RIGHT, EYES_UP, EYES_DOWN,
	WALKING_LEFT, WALKING_RIGHT, WALKING_UP, WALKING_DOWN,
	BLUE_LEFT, BLUE_RIGHT, BLUE_UP, BLUE_DOWN,
	NUM_ANIMATIONS
};

class Enemy : public Entity
{
public:
	Enemy(const Point& p, State s, Look view);
	~Enemy();

	AppStatus Initialise();
	void SetTileMap(TileMap* tilemap);


	void Update();
	void DrawDebug(const Color& col) const;
	void Release();

private:
	bool IsLookingRight() const;
	bool IsLookingLeft() const;
	bool IsLookingUp() const;
	bool IsLookingDown() const;

	//Player mechanics
	void MoveX();
	void MoveY();
	void LogicJumping(); //creo q quitar
	void LogicClimbing();

	//Animation management
	void SetAnimation(int id);
	EnemyAnim GetAnimation();
	void Stop();
	void StartWalkingLeft();
	void StartWalkingRight();
	void StartWalkingUp();
	void StartWalkingDown();
	void ChangeAnimRight();
	void ChangeAnimLeft();
	void ChangeAnimUp();
	void ChangeAnimDown();
	void Dead();


	State state;
	Look look;

	TileMap* map;

};


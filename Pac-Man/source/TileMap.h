#pragma once
#include <raylib.h>
#include "Sprite.h"
#include "Point.h"
#include "AABB.h"
#include "Globals.h"
#include <unordered_map>

enum class Tile {

	// -1: area covered by an entity
	EMPTY = -1, 
	//  0: air tile
	AIR = 0,

	// 0 < id < 50: static tiles
		//DOUBLE
	DOUBLE_STRAIGHT_LINE_HORIZONTAL_UP = 1, DOUBLE_STRAIGHT_LINE_HORIZONTAL_DOWN, DOUBLE_STRAIGHT_LINE_VERTICAL_LEFT, DOUBLE_STRAIGHT_LINE_VERTICAL_RIGHT,
	DOUBLE_ROUND_TILE_TL, DOUBLE_ROUND_TILE_TR, DOUBLE_ROUND_TILE_BL, DOUBLE_ROUND_TILE_BR,
	DOUBLE_LINE_UP_ROUND_TILE_TL, DOUBLE_LINE_UP_ROUND_TILE_TR, 
	DOUBLE_LINE_RIGHT_ROUND_TILE_BR, DOUBLE_LINE_RIGHT_ROUND_TILE_TR, DOUBLE_LINE_LEFT_ROUND_TILE_BL, DOUBLE_LINE_LEFT_ROUND_TILE_TL,
	DOUBLE_ROUND_TILE_MINI_TL, DOUBLE_ROUND_TILE_MINI_TR, DOUBLE_ROUND_TILE_MINI_BL, DOUBLE_ROUND_TILE_MINI_BR,
	DOUBLE_END_LEFT=75, DOUBLE_END_RIGHT=74,
	
	//SINGLE
	STRAIGHT_LINE_HORIZONTAL_UP=21, STRAIGHT_LINE_HORIZONTAL_DOWN=42, STRAIGHT_LINE_VERTICAL_RIGHT=41, STRAIGHT_LINE_VERTICAL_LEFT=40,
	SINGLE_ROUND_TILE_TL = 50, SINGLE_ROUND_TILE_TR = 51, SINGLE_ROUND_TILE_BL = 52, SINGLE_ROUND_TILE_BR = 53,
	BIG_ROUND_TILE_TL = 61, BIG_ROUND_TILE_TR = 62, BIG_ROUND_TILE_BL = 60, BIG_ROUND_TILE_BR = 63,
	
	//SQUARED
	SQUARE_TILE_TL=73, SQUARE_TILE_TR = 70, SQUARE_TILE_BL = 72, SQUARE_TILE_BR = 71,
	
	LADDER_L = 20, LADDER_R, LADDER_TOP_L, LADDER_TOP_R,
	LOCK_RED = 30, LOCK_YELLOW, 
	LASER_L = 40, LASER_R,

	// 50 <= id < 100: special tiles
	PELLET = 50,
	ENERGIZER = 60,
	CHERRY = 70,

	// id >= 100: entities' initial locations
	PACMAN = 100,
	BLINKY_RED, PINKY_PINK, INKY_CYAN, CLYDE_ORANGE,

	//Intervals
	STATIC_FIRST = DOUBLE_STRAIGHT_LINE_HORIZONTAL_UP,
	STATIC_LAST = SQUARE_TILE_BR,
	SOLID_FIRST = DOUBLE_STRAIGHT_LINE_HORIZONTAL_UP,
	SOLID_LAST = SQUARE_TILE_BR,
	SPECIAL_FIRST = PELLET,
	SPECIAL_LAST = CHERRY,
	ENTITY_FIRST = PACMAN,
	ENTITY_LAST = CLYDE_ORANGE
};

class TileMap
{
public:
	TileMap();
	~TileMap();

	AppStatus Initialise();
	AppStatus Load(int data[], int w, int h);
	void Update();
	void Render();
	void Release();

	//Test for collisions with walls
	bool TestCollisionWallLeft(const AABB& box) const;
	bool TestCollisionWallRight(const AABB& box) const;
	bool TestCollisionWallUp(const AABB& box) const;
	bool TestCollisionWallDown(const AABB& box) const;
	
	//Test collision with the ground and update 'py' with the maximum y-position to prevent
	//penetration of the grounded tile, that is, the pixel y-position above the grounded tile.
	//Grounded tile = solid tile (blocks) or ladder tops.
	bool TestCollisionGround(const AABB& box, int *py) const;
	
	//Test if there is a ground tile one pixel below the given box
	bool TestFalling(const AABB& box) const;
	
	//Test if box is on ladder and update 'px' with the x-center position of the ladder
	bool TestOnLadder(const AABB& box, int* px) const;
	
	//Test if box is on ladder top and update 'px' with the x-center position of the ladder
	bool TestOnLadderTop(const AABB& box, int* px) const;

private:
	void InitTileDictionary();

	Tile GetTileIndex(int x, int y) const;
	bool IsTileSolid(Tile tile) const;
	bool IsTileLadderTop(Tile tile) const;
	bool IsTileLadder(Tile tile) const;
	bool CollisionX(const Point& p, int distance) const;
	bool CollisionY(const Point& p, int distance) const;
	int GetLadderCenterPos(int pixel_x, int pixel_y) const;

	//Tile map
	Tile *map;

	//Size of the tile map
	int size, width, height;
	
	//Dictionary of tile frames
	std::unordered_map<int, Rectangle> dict_rect;

	Sprite *laser;
	
	//Tile sheet
	const Texture2D *img_tiles;
};


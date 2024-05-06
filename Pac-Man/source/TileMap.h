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
	DOUBLE_END_LEFT, DOUBLE_END_RIGHT,
	
	//SINGLE
	STRAIGHT_LINE_HORIZONTAL_UP, STRAIGHT_LINE_HORIZONTAL_DOWN, STRAIGHT_LINE_VERTICAL_RIGHT, STRAIGHT_LINE_VERTICAL_LEFT,
	SINGLE_ROUND_TILE_TL, SINGLE_ROUND_TILE_TR, SINGLE_ROUND_TILE_BL, SINGLE_ROUND_TILE_BR,
	BIG_ROUND_TILE_TL, BIG_ROUND_TILE_TR, BIG_ROUND_TILE_BL, BIG_ROUND_TILE_BR,
	
	//SQUARED
	SQUARE_TILE_TL, SQUARE_TILE_TR , SQUARE_TILE_BL, SQUARE_TILE_BR,
	
	PINK_RECTANGLE_DOOR,

	// 50 <= id < 80: special tiles
	PELLET = 50,
	ENERGIZER = 60,
	CHERRY = 70,

	// 80 <= id < 100: LIFES AND EXTRAS
	CURRENT_FRUITS=80,
	CURRENT_LIFES,

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
	

private:
	void InitTileDictionary();

	Tile GetTileIndex(int x, int y) const;
	bool IsTileSolid(Tile tile) const;
	bool CollisionX(const Point& p, int distance) const;
	bool CollisionY(const Point& p, int distance) const;

	//Tile map
	Tile *map;

	//Size of the tile map
	int size, width, height;
	
	//Dictionary of tile frames
	std::unordered_map<int, Rectangle> dict_rect;

	Sprite *fruits;
	Sprite* lifes;
	
	//Tile sheet
	const Texture2D *img_tiles;
};


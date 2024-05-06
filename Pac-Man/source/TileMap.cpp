#include "TileMap.h"
#include "Globals.h"
#include "ResourceManager.h"
#include <cstring>

TileMap::TileMap()
{
	map = nullptr;
	width =0;
	height =0;
	lifes = nullptr;
	fruits = nullptr;
	img_tiles = nullptr;

	InitTileDictionary();
}
TileMap::~TileMap()
{
	if (map != nullptr)
	{
		delete[] map;
		map = nullptr;
	}
	if (fruits != nullptr)
	{
		fruits->Release();
		delete fruits;
		fruits = nullptr;
	}
	if (lifes != nullptr)
	{
		lifes->Release();
		delete lifes;
		lifes = nullptr;
	}
}
void TileMap::InitTileDictionary()
{
	const int n = TILE_SIZE;

	dict_rect[(int)Tile::DOUBLE_STRAIGHT_LINE_HORIZONTAL_UP] = { 10*n,  24*n, n, n };
	dict_rect[(int)Tile::DOUBLE_STRAIGHT_LINE_HORIZONTAL_DOWN] = { 13*n,  24*n, n, n };
	dict_rect[(int)Tile::DOUBLE_STRAIGHT_LINE_VERTICAL_LEFT] = { 3 * n, 24*n, n, n };
	dict_rect[(int)Tile::DOUBLE_STRAIGHT_LINE_VERTICAL_RIGHT] = { 2 * n, 24*n, n, n };
	dict_rect[(int)Tile::DOUBLE_ROUND_TILE_TL] = {  n,  24*n, n, n };
	dict_rect[(int)Tile::DOUBLE_ROUND_TILE_TR] = { 0,  24*n, n, n };
	dict_rect[(int)Tile::DOUBLE_ROUND_TILE_BL] = { 5*n, 24*n, n, n };
	dict_rect[(int)Tile::DOUBLE_ROUND_TILE_BR] = { 4* n, 24*n, n, n };
	dict_rect[(int)Tile::DOUBLE_LINE_UP_ROUND_TILE_TL] = { 6 * n,  26*n, n, n };
	dict_rect[(int)Tile::DOUBLE_LINE_UP_ROUND_TILE_TR] = { 7 * n, 26*n, n, n };
	dict_rect[(int)Tile::DOUBLE_LINE_RIGHT_ROUND_TILE_BR] = { 6 * n, 24*n, n, n };
	dict_rect[(int)Tile::DOUBLE_LINE_RIGHT_ROUND_TILE_TR] = { 8 * n, 24*n, n, n };
	dict_rect[(int)Tile::DOUBLE_LINE_LEFT_ROUND_TILE_BL] = { 7 * n, 24*n, n, n };
	dict_rect[(int)Tile::DOUBLE_LINE_LEFT_ROUND_TILE_TL] = { 9 * n, 24*n, n, n };
	dict_rect[(int)Tile::DOUBLE_ROUND_TILE_MINI_TL] = { 4 * n, 25 * n, n, n };
	dict_rect[(int)Tile::DOUBLE_ROUND_TILE_MINI_TR] = { 5 * n, 25 * n, n, n };
	dict_rect[(int)Tile::DOUBLE_ROUND_TILE_MINI_BL] = { 6 * n, 25 * n, n, n };
	dict_rect[(int)Tile::DOUBLE_ROUND_TILE_MINI_BR] = { 7 * n, 25 * n, n, n };
	dict_rect[(int)Tile::DOUBLE_END_LEFT] = { 0, 26 * n, n, n };
	dict_rect[(int)Tile::DOUBLE_END_RIGHT] = { n, 26 * n, n, n };

	dict_rect[(int)Tile::STRAIGHT_LINE_HORIZONTAL_UP] = { 12 * n, 24 * n, n, n };
	dict_rect[(int)Tile::STRAIGHT_LINE_HORIZONTAL_DOWN] = { 11 * n, 24 * n, n, n };
	dict_rect[(int)Tile::STRAIGHT_LINE_VERTICAL_RIGHT] = { 9 * n, 25 * n, n, n };
	dict_rect[(int)Tile::STRAIGHT_LINE_VERTICAL_LEFT] = { 8 * n, 25 * n, n, n };
	dict_rect[(int)Tile::SINGLE_ROUND_TILE_TL] = { 4 * n, 25 * n, n, n };
	dict_rect[(int)Tile::SINGLE_ROUND_TILE_TR] = { 5 * n, 25 * n, n, n };
	dict_rect[(int)Tile::SINGLE_ROUND_TILE_BL] = { 6 * n, 25 * n, n, n };
	dict_rect[(int)Tile::SINGLE_ROUND_TILE_BR] = { 7 * n, 25 * n, n, n };
	dict_rect[(int)Tile::BIG_ROUND_TILE_TL] = { 2 * n, 26 * n, n, n };
	dict_rect[(int)Tile::BIG_ROUND_TILE_TR] = { 3 * n, 26 * n, n, n };
	dict_rect[(int)Tile::BIG_ROUND_TILE_BL] = { 4 * n, 26 * n, n, n };
	dict_rect[(int)Tile::BIG_ROUND_TILE_BR] = { 5 * n, 26 * n, n, n };

	dict_rect[(int)Tile::SQUARE_TILE_TL] = { 10*n, 25 * n, n, n };
	dict_rect[(int)Tile::SQUARE_TILE_TR] = { 11 * n, 25 * n, n, n };
	dict_rect[(int)Tile::SQUARE_TILE_BL] = { 10 * n, 26 * n, n, n };
	dict_rect[(int)Tile::SQUARE_TILE_BR] = { 11 * n, 26 * n, n, n };
	
	dict_rect[(int)Tile::PINK_RECTANGLE_DOOR] = { 13 * n, 26 * n, n, n };

	dict_rect[(int)Tile::PELLET] = { 8 * n, 26 * n, n, n };
	dict_rect[(int)Tile::ENERGIZER] = { 12 * n, 26 * n, n, n };
	dict_rect[(int)Tile::CHERRY] = { 23 * n, 24 * n, n, n }; //DIRIA

	dict_rect[(int)Tile::CURRENT_FRUITS] = { 12 * n, 26 * n, n, n };
	dict_rect[(int)Tile::CURRENT_LIFES] = { 12 * n, 26 * n, n, n };

}
AppStatus TileMap::Initialise()
{
	ResourceManager& data = ResourceManager::Instance();

	if (data.LoadTexture(Resource::IMG_TILES, "images/tilemap.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}
	img_tiles = data.GetTexture(Resource::IMG_TILES);

	fruits = new Sprite(img_tiles);
	if (fruits == nullptr)
	{
		LOG("Failed to allocate memory for laser sprite");
		return AppStatus::ERROR;
	}
	fruits->SetNumberAnimations(1);
	fruits->SetAnimationDelay(0, ANIM_DELAY);
	fruits->AddKeyFrame(0, dict_rect[(int)Tile::SQUARE_TILE_BL]);
	fruits->AddKeyFrame(0, dict_rect[(int)Tile::SQUARE_TILE_BR]);
	fruits->AddKeyFrame(0, dict_rect[(int)Tile::SQUARE_TILE_TR]);
	fruits->SetAnimation(0);

	return AppStatus::OK;
	
	lifes = new Sprite(img_tiles);
	if (lifes == nullptr)
	{
		LOG("Failed to allocate memory for laser sprite");
		return AppStatus::ERROR;
	}
	lifes->SetNumberAnimations(1);
	lifes->SetAnimationDelay(0, ANIM_DELAY);
	lifes->AddKeyFrame(0, dict_rect[(int)Tile::SQUARE_TILE_BL]);
	lifes->AddKeyFrame(0, dict_rect[(int)Tile::SQUARE_TILE_BR]);
	lifes->AddKeyFrame(0, dict_rect[(int)Tile::SQUARE_TILE_TR]);
	lifes->SetAnimation(0);

	return AppStatus::OK;
}

AppStatus TileMap::Load(int data[], int w, int h)
{
	size = w*h;
	width = w;
	height = h;

	if (map != nullptr)	delete[] map;

	map = new Tile[size];
	if (map == nullptr)	
	{
		LOG("Failed to allocate memory for tile map");
		return AppStatus::ERROR;
	}
	memcpy(map, data, size * sizeof(int));

	return AppStatus::OK;
}
void TileMap::Update()
{
	/*if(DIE)
	lifes->Update();
	if(fruit)
	fruits->Update();*/
}
Tile TileMap::GetTileIndex(int x, int y) const
{
	int idx = x + y*width;
	if(idx < 0 || idx >= size)
	{
		LOG("Error: Index out of bounds. Tile map dimensions: %dx%d. Given index: (%d, %d)", width, height, x, y)
		return Tile::AIR;
	}
	return map[x + y * width];
}
bool TileMap::IsTileSolid(Tile tile) const
{
	return (Tile::SOLID_FIRST <= tile && tile <= Tile::SOLID_LAST);
}
bool TileMap::TestCollisionWallLeft(const AABB& box) const
{
	return CollisionX(box.pos, box.height);
}
bool TileMap::TestCollisionWallRight(const AABB& box) const
{
	return CollisionX(box.pos + Point(box.width - 1, 0), box.height);
}
bool TileMap::TestCollisionWallUp(const AABB& box) const
{
	return CollisionY(box.pos, box.height);
}
bool TileMap::TestCollisionWallDown(const AABB& box) const
{
	return CollisionY(box.pos + Point(box.width - 1, 0), box.height);
}

bool TileMap::CollisionX(const Point& p, int distance) const
{
	int x, y, y0, y1;

	//Calculate the tile coordinates and the range of tiles to check for collision
	x = p.x / TILE_SIZE;
	y0 = p.y / TILE_SIZE;
	y1 = (p.y + distance - 1) / TILE_SIZE;
	
	//Iterate over the tiles within the vertical range
	for (y = y0; y <= y1; ++y)
	{
		//One solid tile is sufficient
		if (IsTileSolid(GetTileIndex(x, y)))
			return true;
	}
	return false;
}
bool TileMap::CollisionY(const Point& p, int distance) const
{
	int x, y, x0, x1;
	Tile tile;

	//Calculate the tile coordinates and the range of tiles to check for collision
	y = p.y / TILE_SIZE;
	x0 = p.x / TILE_SIZE;
	x1 = (p.x + distance - 1) / TILE_SIZE;

	//Iterate over the tiles within the horizontal range
	for (x = x0; x <= x1; ++x)
	{
		tile = GetTileIndex(x, y);

		//One solid or laddertop tile is sufficient
		if (IsTileSolid(tile))
			return true;
	}
	return false;
}
//bool TileMap::TestOnLadder(const AABB& box, int* px) const
//{
//	int left, right, bottom;
//	int tx1, tx2, ty;
//	Tile tile1, tile2;
//	
//	//Control points
//	left = box.pos.x;
//	right = box.pos.x + box.width-1;
//	bottom = box.pos.y + box.height-1;
//
//	//Calculate the tile coordinates
//	tx1 = left / TILE_SIZE;
//	tx2 = right / TILE_SIZE;
//	ty = bottom / TILE_SIZE;
//
//	//To be able to climb up or down, both control points must be on ladder
//	tile1 = GetTileIndex(tx1, ty);
//	tile2 = GetTileIndex(tx2, ty);
//	if (IsTileLadder(tile1) && IsTileLadder(tile2))
//	{
//		*px = GetLadderCenterPos(left, bottom) - box.width/2;
//		return true;
//	}
//	return false;
//}
//bool TileMap::TestOnLadderTop(const AABB& box, int* px) const
//{
//	int left, right, bottom;
//	int tx1, tx2, ty;
//	Tile tile1, tile2;
//
//	//Control points
//	left = box.pos.x;
//	right = box.pos.x + box.width - 1;
//	bottom = box.pos.y + box.height - 1;
//
//	//Calculate the tile coordinates
//	tx1 = left / TILE_SIZE;
//	tx2 = right / TILE_SIZE;
//	ty = bottom / TILE_SIZE;
//
//	//To be able to climb up or down, both control points must be on ladder
//	tile1 = GetTileIndex(tx1, ty);
//	tile2 = GetTileIndex(tx2, ty);
//	if (IsTileLadderTop(tile1) && IsTileLadderTop(tile2))
//	{
//		*px = GetLadderCenterPos(left, bottom) - box.width / 2;
//		return true;
//	}
//	return false;
//}
//int TileMap::GetLadderCenterPos(int pixel_x, int pixel_y) const
//{
//	int tx, ty;
//	
//	tx = pixel_x / TILE_SIZE;
//	ty = pixel_y / TILE_SIZE;
//	Tile tile = GetTileIndex(tx, ty);
//
//	if (tile == Tile::LADDER_L || tile == Tile::LADDER_TOP_L)		return tx * TILE_SIZE + TILE_SIZE;
//	else if (tile == Tile::LADDER_R || tile == Tile::LADDER_TOP_R)	return tx * TILE_SIZE;
//	else
//	{
//		LOG("Internal error, tile should be a LADDER, coord: (%d,%d), tile type: %d", pixel_x, pixel_y, (int)tile);
//		return 0;
//	}
//}
void TileMap::Render()
{
	Tile tile;
	Rectangle rc;
	Vector2 pos;

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			tile = map[i * width + j];
			if (tile != Tile::AIR)
			{
				pos.x = (float)j * TILE_SIZE;
				pos.y = (float)i * TILE_SIZE;

					rc = dict_rect[(int)tile];
					DrawTextureRec(*img_tiles, rc, pos, WHITE);
				/*else
				{
					laser->Draw((int)pos.x, (int)pos.y);
				}*/
			}
		}
	}
}
void TileMap::Release()
{
	ResourceManager& data = ResourceManager::Instance(); 
	data.ReleaseTexture(Resource::IMG_TILES);

	//laser->Release();

	dict_rect.clear();
}
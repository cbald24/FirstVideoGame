#include "Map.h"
/*
the map objects constructer, set certain things to default values that will need to be changed by setter methods later
*/
Map::Map()
{
	mapHeight = 0;
	mapWidth = 0;
	tileSize = 0;

}
/*
the destructor for the map
*/
Map::~Map()
{
	mapHeight, mapWidth, tileSize = 0;
	tiles[0] = {};
}
/*
this method will return the int value for the height of the map
*/
int Map::getMapHeight()
{
	return mapHeight;
}
/*
this method will return the int value for the width of the map
*/
int Map::getMapWidth()
{
	return mapWidth;
}
/*
this method will return the int value for the size of the tiles
*/
int Map::getTileSize()
{
	return tileSize;
}
/*
this method will return the maps tiles variable to be used by other functions
*/
Tile Map::getTiles()
{
	return tiles[0];
}
/*
param (int mh): this int represents the map height
description: sets the maps mapHeight variable to mh
*/
void Map::setMapHeight(int mh)
{
	mapHeight = mh;
}
/*
param (int mw): this int represents the map width
description: sets the maps mapWidth variable to mw
*/
void Map::setMapWidth(int mw)
{
	mapWidth = mw;
}
/*
param (int ts): this int represents the map width
description: sets the maps tileSize variable to ts
*/
void Map::setTileSize(int ts)
{
	tileSize = ts;
}
/*
param (t):this is the tile aray we are going to set the local variable tiles to
description: this method sets the maps variable, tiles, to t
*/
void Map::setTiles(Tile t[375])
{
	for (int i = 0; i < 375; i++)
	{
		tiles[i] = t[i];
	}
}
/*
param (SDL_Rect cameraRect): the rect that represents the player camera that will be used to determine what needs to be rendered
param (SDL_Renderer renderTarget): a pointer to the render loction, which is the game window
description: this method will call another method to check if the camera and the current tile intersect, if they do it will tell that tile to render on the map
*/
void Map::renderTiles(SDL_Rect cameraRect, SDL_Renderer *renderTarget)
{
	bool collides = false;
	for (int i = 0; i < 375; i++)
	{
		collides = checkCollision(cameraRect, tiles[i].positionRect);
		if (collides)
		{
			tiles[i].Render(renderTarget, cameraRect);
		}
	}
}
/*
Param (SDL_Rect a): the first rect to use for collision detection
Param (SDL_Rect b): the second rect to use for collision detection
Return (bool) a bool that reflects if a nd b collide with each other
decripstion: this method is borrowed from http://lazyfoo.net/SDL_tutorials/lesson17/ and will find i out if 2 sdl rects are overlapping or next to each other
if they are it returns true if not it returns false
*/
bool Map::checkCollision(SDL_Rect a, SDL_Rect b)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA < topB)
	{
		return false;
	}
	if (topA > bottomB)
	{
		return false;
	}
	if (rightA < leftB)
	{
		return false;
	}
	if (leftA > rightB)
	{
		return false;
	}
	//If none of the sides from A are outside B
	return true;
}

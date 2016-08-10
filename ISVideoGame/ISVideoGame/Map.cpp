#include "Map.h"

Map::Map()
{
	mapHeight = 0;
	mapWidth = 0;
	tileSize = 0;

}

Map::~Map()
{
	mapHeight, mapWidth, tileSize = 0;
	tiles[0] = {};
}

int Map::getMapHeight()
{
	return mapHeight;
}

int Map::getMapWidth()
{
	return mapWidth;
}

int Map::getTileSize()
{
	return tileSize;
}

Tile* Map::getTiles()
{
	return tiles[0];
}

void Map::setMapHeight(int mh)
{
	mapHeight = mh;
}

void Map::setMapWidth(int mw)
{
	mapWidth = mw;
}

void Map::setTileSize(int ts)
{
	tileSize = ts;
}

void Map::setTiles(Tile* t)
{
	tiles[0] = t;
}
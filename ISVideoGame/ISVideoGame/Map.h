#pragma once

#include"Tile.h"
class Map
{
public:
	Map();
	~Map();
	int getMapHeight();
	int getMapWidth();
	int getTileSize();
	Tile* getTiles();
	void setMapHeight(int mh);
	void setMapWidth(int mw);
	void setTileSize(int ts);
	void setTiles(Tile* t[375]);

private:
	int mapHeight, mapWidth, tileSize;
	Tile* tiles[375];

};


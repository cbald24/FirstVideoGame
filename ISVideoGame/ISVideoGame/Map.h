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
	Tile getTiles();
	void setMapHeight(int mh);
	void setMapWidth(int mw);
	void setTileSize(int ts);
	void setTiles(Tile t[375]);
	void renderTiles(SDL_Rect cameraRect, SDL_Renderer *renderTarget);
private:
	int mapHeight, mapWidth, tileSize;
	Tile tiles[375];
	bool checkCollision(SDL_Rect a, SDL_Rect b);
};


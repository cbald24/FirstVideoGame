#pragma once
#include <SDL.h>
#include<iostream>
#include<SDL_image.h>
class Tile
{
public:
	Tile(bool s, int id, std::string filepath, SDL_Renderer *renderTarget, int col, int ts, bool k);
	Tile();
	~Tile();
	int getID();
	void Render(SDL_Renderer *renderTarget, SDL_Rect cameraRect);
	void setLocation(int mapHeight, int mapWidth, int number);
	SDL_Rect positionRect;
	bool getSolid();
	bool getKill();
private:
	int tileID;	
	SDL_Rect cropRect;
	SDL_Texture *texture;
	bool solid;
	bool willKill;
};


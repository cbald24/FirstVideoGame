#pragma once
#include <SDL.h>
#include<iostream>
#include<SDL_image.h>
class Tile
{
public:
	Tile(bool s, int id, std::string filepath, SDL_Renderer *renderTarget, int col, int ts);
	Tile();
	~Tile();
	int getID();
	void Render(SDL_Renderer *renderTarget);
	void setLocation(int mapHeight, int mapWidth, int number);
private:
	int tileID;
	bool solid;
	//bool willKill;
	SDL_Rect cropRect;
	SDL_Texture *texture;
	SDL_Rect postionRect;

};


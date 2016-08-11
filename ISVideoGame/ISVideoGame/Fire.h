#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include<iostream>
#include<cmath>
#include<string>
class Fire
{
public:
	Fire(SDL_Renderer *renderTarget, std::string filepath, int x, int y);
	~Fire();
	void Update(int x, int y, bool l);
	void Draw(SDL_Renderer *renderTarget, SDL_Rect cameraRect);
private:
	int frameWidth, frameHeight;
	SDL_Rect posRect;
	SDL_Rect cropRect;
	SDL_Texture *texture;
};


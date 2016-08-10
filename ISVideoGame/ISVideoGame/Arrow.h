#pragma once
#include<SDL.h>
#include<string>
#include"Player.h"
#include<SDL_image.h>
#include<string>
#include<iostream>
#include<cmath>

class Arrow
{
public:
	Arrow(SDL_Renderer *renderTarget, std::string filepath, int x, int y);
	~Arrow();
private:
	const int xFrames = 2;
	const int yFrames = 1;
	SDL_Rect cropRect;
	SDL_Texture *texture;
	float moveSpeed;
};

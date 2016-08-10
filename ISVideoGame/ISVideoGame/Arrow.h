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

	void Update(float delta, Player &p);
	void Draw(SDL_Renderer *renderTarget, SDL_Rect cameraRect);
	void setLeft(bool left);
private:
	int frameWidth, frameHeight;
	SDL_Rect posRect;
	SDL_Rect cropRect;
	SDL_Texture *texture;
	const float moveSpeed = 250.0f;
	bool pointedLeft;
	float timer;
	const float lifeSpan = 7.50f;
};

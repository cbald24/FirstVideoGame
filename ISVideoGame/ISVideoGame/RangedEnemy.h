#pragma once
#include<SDL.h>
#include<string>
#include<SDL_image.h>
#include<string>
#include<iostream>
#include<cmath>
#include"Player.h"
#include"Arrow.h"

class RangedEnemy
{
public:
	RangedEnemy(SDL_Renderer *renderTarget, std::string filepath, int x, int y, int framesX, int framesY);
	~RangedEnemy();
	void Update(float delta, Player &p);
	void Draw(SDL_Renderer *renderTarget, SDL_Rect cameraRect);
	
	int getPosX();
	int getPosY();
	SDL_Rect positionRect;
private:
	float timer;
	const float cooldown = 7.50f;
	SDL_Rect cropRect;
	SDL_Texture *texture;
	float frameCounter;
	int frameWidth, frameHeight;
	int textureWidth;
	bool onCooldown;
	SDL_Scancode keys[4];
	int health;
	bool left;
	Arrow *myArrow;
};


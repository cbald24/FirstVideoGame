#pragma once
#include<SDL.h>
#include<string>
#include<SDL_image.h>
#include<string>
#include<iostream>
#include<cmath>
#include"Fire.h"

class WeakGuy
{
public:
	WeakGuy(SDL_Renderer *renderTarget, std::string filepath, int x, int y, int framesX, int framesY);
	~WeakGuy();
	void Update(float delta, const Uint8 *keyState);
	void Draw(SDL_Renderer *renderTarget, SDL_Rect cameraRect);
	bool hitFire(Fire *f);
	int getPosX();
	int getPosY();
	SDL_Rect positionRect;

private:
	SDL_Rect cropRect;
	SDL_Texture *texture;
	float moveSpeed;
	float frameCounter;
	int frameWidth, frameHeight;
	int textureWidth;
	bool isActive;
	SDL_Scancode keys[4];
	int health;
	bool checkCollision(SDL_Rect a);

};


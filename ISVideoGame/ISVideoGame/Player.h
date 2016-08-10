#pragma once

#include<SDL.h>
#include<string>
#include"WeakGuy.h"


class Player
{
public:
	Player(SDL_Renderer *renderTarget, std::string filepath, int x, int y, int framesX, int framesY);
	~Player();

	void Update(float delta, const Uint8 *keyState);
	void Draw(SDL_Renderer *renderTarget, SDL_Rect cameraRect);
	bool IntersectsWith(WeakGuy &enemy);
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
};


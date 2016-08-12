#pragma once

#include<SDL.h>
#include<string>
#include"WeakGuy.h"
#include"Tile.h"
#include"Map.h"
#include"Fire.h"


class Player
{
public:
	Player(SDL_Renderer *renderTarget, std::string filepath, int x, int y, int framesX, int framesY);
	~Player();

	void Update(float delta, const Uint8 *keyState, Map *m, SDL_Renderer *renderTarget);
	void Draw(SDL_Renderer *renderTarget, SDL_Rect cameraRect);
	bool IntersectsWith(WeakGuy &enemy);
	int getPosX();
	int getPosY();

	SDL_Rect positionRect;

private:
	SDL_Rect cropRect;
	SDL_Texture *texture;
	int frameWidth, frameHeight;
	int textureWidth;
	bool isActive, onCooldown, left;
	SDL_Scancode keys[4];
	int health;
	bool checkCollision(SDL_Rect a);
	bool checkMapCollision(SDL_Rect a);
	void updateFrame(bool a, float d);
	Fire *fistOfFury; 	
	const float cd = 3.0f;
	void updateGravity(float d, Map *m);
	float yVelocity, xVelocity, frameCounter, timer;
	const float gravity = 9.8f;
	const float moveSpeed = 200.0f;
	bool isJumping, isFalling;
	void jump();
	void moveLeft(Map *m, float d);
	void moveRight(Map *m, float d);
	void fireFists(Map *m, float d, SDL_Renderer *renderTarget);
	void cooldownUpdate(float d);
	void midAirUpdate(Map *m, float d);
};


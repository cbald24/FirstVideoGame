#include "Player.h"
#include<SDL_image.h>
#include<string>
#include<iostream>
#include<cmath>

Player::Player(SDL_Renderer *renderTarget, std::string filepath, int x, int y, int framesX, int framesY)
{
	health = 3;//sets the health of the player to 3
	SDL_Surface *surface = IMG_Load(filepath.c_str()); //reads in the players sprite sheet and sets it to a surface that will be optimized into a texture
	if (surface == NULL) //error checks to make sure it read somethin in
	{
		std::cout << "Opps" << std::endl; //if error output
	}
	else //is no error
	{
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 250, 50, 250)); //sets this certain pink color to transparent
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);		//create a texture for the renderer out of the surface
	}

	SDL_FreeSurface(surface); //free the SDL surface from the memory

	SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h); //

	positionRect.x = x; //sets the player charecter's x postion on the world map
	positionRect.y = y; //sets the player's y postion on the world map

	textureWidth = cropRect.w; //sets the width of the texture 

	cropRect.w /= framesX; //sets the width of the crop rectangle based on the number a frames passed
	cropRect.h /= framesY; //sets the height of the crop rectangle based on the number of frames passed

	frameWidth = cropRect.w; //sets the framewidth and postion rect's width based on the crop rects width
	frameHeight = positionRect.h =  cropRect.h; //sets the frameheight and postion rect's heights based on the crop rects height
	positionRect.w = cropRect.w;
	positionRect.h = cropRect.h;
	left = onCooldown = isActive = isJumping = isFalling = false;
	keys[0] = SDL_SCANCODE_Q; //sets first key of the array to a 'w key pressed' code
	keys[1] = SDL_SCANCODE_SPACE; //sets second key of the array to a 'w key pressed' code
	keys[2] = SDL_SCANCODE_A;//sets third key of the array to a 'w key pressed' code
	keys[3] = SDL_SCANCODE_D;//sets fourth key of the array to a 'w key pressed' code
	yVelocity = 0.0f;
	moveSpeed = 200.0f;
}
/*
the deconstructor for the player object
*/
Player::~Player()
{
	SDL_DestroyTexture(texture);//destroys the players texture to prevent memory leak
}
/*
(param) float delta: this will be used in math equations to make movement and game frame refresh rate work more smoothly
(param) const Uint8 *keyState: the current state of the keyboards button presses
This method will update the player's current postion and the next frame in his animation
*/
void Player::Update(float delta, const Uint8 *keyState, Map *m, SDL_Renderer *renderTarget)
{
	isActive = true; //sets the bool for iff the player is actively moving to true
	if (onCooldown)
	{
		timer -= delta;
		if (timer <= 0)
		{
			onCooldown = false;
		}
		else if (timer <= 1)
		{
			fistOfFury = nullptr;
		}
		else
		{
			timer -= delta;
			fistOfFury->Update(positionRect.x, positionRect.y - 12, left);
		}
	}
	
	int index = ((positionRect.y / m->getTileSize()) * m->getMapWidth()) + (positionRect.x / m->getTileSize());
	if (keyState[keys[0]])
	{
		if (!onCooldown)
		{
			if (left)
			{
				fistOfFury = new Fire(renderTarget, "fire.png", positionRect.x, positionRect.y - 12);
				onCooldown = true;
				timer = cd;
			}
			else
			{
				fistOfFury = new Fire(renderTarget, "fire.png", positionRect.x + 34, positionRect.y - 12);
				onCooldown = true;
				timer = cd;
			}
		}
	}
	else if (keyState[keys[1]])
	{
		if (!isJumping)
		{
			isJumping = true;
			yVelocity = -250.0f;
		}
		
	}
	else if (keyState[keys[2]]) //if the key being pushed is a
	{	
		if (isFalling)
		{
			cropRect.y = 0;

		}
		else
		{
			cropRect.y = frameHeight * 2;
		}
		positionRect.x -= (moveSpeed * delta);			
		left = true;
		index = (((positionRect.y) / m->getTileSize()) * m->getMapWidth()) + (positionRect.x / m->getTileSize());
		if(m->getTiles()[index].getSolid())
		{
			positionRect.x = (m->getTiles()[index].positionRect.x + 96);
		}
		index = (((positionRect.y + 49) / m->getTileSize()) * m->getMapWidth()) + (positionRect.x / m->getTileSize());
		if (m->getTiles()[index].getSolid())
		{
			positionRect.x = (m->getTiles()[index].positionRect.x + 96);
		}
	}
	else if (keyState[keys[3]]) //if the key being pushed is d
	{
		if (isFalling)
		{
			cropRect.y = frameHeight;

		}
		else
		{
			cropRect.y = frameHeight * 3;
		}
		positionRect.x += (moveSpeed * delta) + 1;		
		left = false;
		index = (((positionRect.y) / m->getTileSize()) * m->getMapWidth()) + ((positionRect.x + 34) / m->getTileSize());
		if(m->getTiles()[index].getSolid())
		{
			positionRect.x = (m->getTiles()[index].positionRect.x - 34);
		}
		index = (((positionRect.y + 49) / m->getTileSize()) * m->getMapWidth()) + ((positionRect.x + 34) / m->getTileSize());
		if (m->getTiles()[index].getSolid())
		{
			positionRect.x = (m->getTiles()[index].positionRect.x - 34);
		}
	}	
	else //if none of the correct keys are being pushed
	{
		isActive = false; //set the players is active bool to false
		if (isFalling)
		{
			if (left)
			{
				cropRect.y = 0;
				
			}
			else
			{
				cropRect.y = frameHeight;
				
			}
		}
	}
	int index2;
	if (isJumping)
	{
		positionRect.y += (yVelocity * delta);
		index = (((positionRect.y + 50) / m->getTileSize()) * m->getMapWidth()) + (positionRect.x / m->getTileSize());
		if(m->getTiles()[index].getSolid()) //check bottom left corner
		{
			positionRect.y = (m->getTiles()[index].positionRect.y - 50);
		}
		index = (((positionRect.y + 50) / m->getTileSize()) * m->getMapWidth()) + ((positionRect.x + 34) / m->getTileSize());
		if (m->getTiles()[index].getSolid()) //check bottom left corner
		{
			positionRect.y = (m->getTiles()[index].positionRect.y - 50);
		}
		index = (((positionRect.y) / m->getTileSize()) * m->getMapWidth()) + (positionRect.x / m->getTileSize());
		if(m->getTiles()[index].getSolid()) //check top left corner
		{
			positionRect.y = (m->getTiles()[index].positionRect.y + 96);
			yVelocity = 0;
		}
		index = (((positionRect.y) / m->getTileSize()) * m->getMapWidth()) + ((positionRect.x + 34) / m->getTileSize());
		if(m->getTiles()[index].getSolid()) //check top right corner
		{
			positionRect.y = (m->getTiles()[index].positionRect.y + 96);
			yVelocity = 0;
		}
		
	}
	
	updateGravity(delta, m);
	
	updateFrame(isActive, delta);

}
/*
(param) SDL_Renderer *renderTarget: a pointer to the render location
(param) SDL_Rect cameraRect: the rectangle for the camera
This method will draw the player character at the render loaction provided
*/
void Player::Draw(SDL_Renderer *renderTarget, SDL_Rect cameraRect)
{
	SDL_Rect drawingRect = { positionRect.x - cameraRect.x, positionRect.y - cameraRect.y, positionRect.w, positionRect.h }; //sets the players drawing location based on the players postion and the camera
	SDL_RenderCopy(renderTarget, texture, &cropRect, &drawingRect); // create a copy of the player texture to be rendered
	if (onCooldown && fistOfFury != nullptr)
	{
		fistOfFury->Draw(renderTarget, cameraRect);
	}
}
/*
Description: returns the x postion of the player
*/
int Player::getPosX()
{
	return positionRect.x; //returns the players x location in the world
}
/*
Description: returns the y postion of the player
*/
int Player::getPosY()
{
	return positionRect.y; //returns the players y location in the world
}

bool Player::IntersectsWith(WeakGuy &enemy)
{
	if (checkCollision(enemy.positionRect))
	{
		SDL_SetTextureColorMod(texture, 255, 255, 255);
		return false;
	}
	else
	{
		SDL_SetTextureColorMod(texture, 250, 0, 0);
		return true;
	}
}

/*
Param (SDL_Rect a): the first rect to use for collision detection
Param (SDL_Rect b): the second rect to use for collision detection
Return (bool) a bool that reflects if a nd b collide with each other
decripstion: this method is borrowed from http://lazyfoo.net/SDL_tutorials/lesson17/ and will find i out if 2 sdl rects are overlapping or next to each other
if they are it returns true if not it returns false
*/
bool Player::checkCollision(SDL_Rect a)
{
	if (positionRect.x + positionRect.w < a.x || positionRect.x > a.x + a.w
		|| positionRect.y + positionRect.h < a.y || positionRect.y > a.y + a.h)
	{
		return true;
	}
	return false;
}

bool Player::checkMapCollision(SDL_Rect a)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = positionRect.x;
	rightB = positionRect.x + positionRect.w;
	topB = positionRect.y;
	bottomB = positionRect.y + positionRect.h;

	//If any of the sides from A are outside of B
	if (bottomA < topB)
	{
		return false;
	}
	if (topA > bottomB)
	{
		return false;
	}
	if (rightA < leftB)
	{
		return false;
	}
	if (leftA > rightB)
	{
		return false;
	}
	//If none of the sides from A are outside B
	return true;
}
/*
Param (float d):this will be the delta value that was given to the update method
description: this method will handle the updating the player frame and helps declutter the update method
*/
void Player::updateFrame(bool a, float d)
{
	if (isFalling)
	{
		if (cropRect.x != (frameWidth * 5))
		{
			frameCounter += 4 * d; //update the frame counter

			if (frameCounter >= 0.25f) //if the frame counter is more then
			{
				frameCounter = 0; //set frame counter to 0
				cropRect.x += frameWidth; //adjust to the next frame in the sprite animation
				
			}
		}
	}
	else
	{
		if (a) //if the player is active
		{
			frameCounter += 2 * d; //update the frame counter

			if (frameCounter >= 0.25f) //if the frame counter is more then
			{
				frameCounter = 0; //set frame counter to 0
				cropRect.x += frameWidth; //adjust to the next frame in the sprite animation
				if (cropRect.x >= textureWidth) //if at the end of the sprite sheet
				{
					cropRect.x = 0; //reset back to first frame
				}
			}
		}
		else //if inactive
		{
			frameCounter = 0; //set current player frame to 0 
			cropRect.x = 0; //set idle postion for sprite sheet
		}
	}
}

void Player::updateGravity(float d, Map *m)
{
	int index = (((positionRect.y+50) / m->getTileSize()) * m->getMapWidth()) + (positionRect.x / m->getTileSize());
	if (!m->getTiles()[index].getSolid())
	{
		yVelocity += gravity;
		positionRect.y += yVelocity * d;
		if (yVelocity > 0)
		{
			if (!isFalling)
			{
				cropRect.x = 0;
			}
			isFalling = true;
		}
	}
	else
	{		
		yVelocity = 0;
		isFalling = false;
		isJumping = false;
	}
}
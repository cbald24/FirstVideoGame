#include "RangedEnemy.h"
#include"Monster.h"
#include"Fire.h"


RangedEnemy::RangedEnemy(SDL_Renderer *renderTarget, std::string filepath, int x, int y, int framesX, int framesY)
{
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

	frameWidth = positionRect.w = cropRect.w; //sets the framewidth and postion rect's width based on the crop rects width
	frameHeight = positionRect.h = cropRect.h; //sets the frameheight and postion rect's heights based on the crop rects height
	onCooldown = false;
	left = true;
	draw = false;
}

RangedEnemy::~RangedEnemy()
{
	SDL_DestroyTexture(texture);//destroys the archers texture to prevent memory leak
	myArrow->~Arrow();
}
/*

*/
void RangedEnemy::Update(float delta, Player &p, SDL_Renderer *renderTarget)
{	
	if (p.positionRect.x < positionRect.x) // if the camera is to the left of the archer
	{
		cropRect.y = 0;
		left = true;
	}
	else
	{
		cropRect.y = frameHeight;
		left = false;
	}
	frameCounter += 2 * delta; //update the frame counter
	if (onCooldown)
	{
		timer += delta;
	}
	if (timer >= cooldown)
	{
		onCooldown = false;
		timer = 0;
		draw = false;
	}
	if (frameCounter >= 0.25f && !onCooldown) //if the frame counter is more then
	{
		frameCounter = 0; //set frame counter to 0
		cropRect.x += frameWidth; //adjust to the next frame in the sprite animation
		if (cropRect.x == 495) //if the current frame of the shoot animation at the point where he releases the arrow
		{		
			myArrow = new Arrow(renderTarget, "arrow.png", positionRect.x, positionRect.y + 20);
			myArrow->setLeft(left);
			
			draw = true;
		}
		if (cropRect.x >= textureWidth) //if at the end of the sprite sheet
		{
			cropRect.x = 0; //reset back to first frame
			onCooldown = true;
		}
	}
	if (draw)
	{
		myArrow->Update(delta);
	}

}

void RangedEnemy::Draw(SDL_Renderer *renderTarget, SDL_Rect cameraRect)
{
	SDL_Rect drawingRect = { positionRect.x - cameraRect.x, positionRect.y - cameraRect.y, positionRect.w, positionRect.h }; //sets the players drawing location based on the players postion and the camera
	SDL_RenderCopy(renderTarget, texture, &cropRect, &drawingRect); // create a copy of the player texture to be rendered
	if (draw)
	{
		myArrow->Draw(renderTarget, cameraRect);
	}
}
/*
description: this method will return the value of the x postion for the archer enemy
*/
int RangedEnemy::getPosX()
{
	return positionRect.x; //returns the players x location in the world
}
/*
description: this method will return the value of the y postion for the archer enemy
*/
int RangedEnemy::getPosY()
{
	return positionRect.y; //returns the players y location in the world
}

bool RangedEnemy::checkCollision(SDL_Rect a)
{
	if (positionRect.x + positionRect.w < a.x || positionRect.x > a.x + a.w
		|| positionRect.y + positionRect.h < a.y || positionRect.y > a.y + a.h)
	{
		return true;
	}
	return false;
}

bool RangedEnemy::hitFire(Fire *f)
{
	if (f != nullptr)
	{
		if (checkCollision(f->posRect))
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
	else
	{
		SDL_SetTextureColorMod(texture, 255, 255, 255);
	}
}
#include"WeakGuy.h"
#include"Monster.h"

WeakGuy::WeakGuy(SDL_Renderer *renderTarget, std::string filepath, int x, int y, int framesX, int framesY)
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
	isActive = false;

	keys[0] = SDL_SCANCODE_T; //sets first key of the array to a 'w key pressed' code
	keys[1] = SDL_SCANCODE_G; //sets second key of the array to a 'w key pressed' code
	keys[2] = SDL_SCANCODE_F;//sets third key of the array to a 'w key pressed' code
	keys[3] = SDL_SCANCODE_H;//sets fourth key of the array to a 'w key pressed' code

	moveSpeed = 200.0f;
}


WeakGuy::~WeakGuy()
{

}

void WeakGuy::Update(float delta, const Uint8 *keyState)
{
	isActive = true; //sets the bool for iff the player is actively moving to true
	if (keyState[keys[0]]) //if the key being pushed is w
	{
		positionRect.y -= moveSpeed * delta;
		
	}
	else if (keyState[keys[1]]) //if the key being pushed is s
	{
		positionRect.y += moveSpeed * delta;
		
	}
	else if (keyState[keys[2]]) //if the key being pushed is a
	{

		positionRect.x -= moveSpeed * delta;
		cropRect.y = 0;
	}
	else if (keyState[keys[3]]) //if the key being pushed is d
	{
		positionRect.x += moveSpeed * delta;
		cropRect.y = frameHeight;
	}
	else //if none of the correct keys are being pushed
	{
		isActive = false; //set the players is active bool to false
	}

	if (isActive) //if the player is active
	{
		frameCounter += 2 * delta; //update the frame counter

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

void WeakGuy::Draw(SDL_Renderer *renderTarget, SDL_Rect cameraRect)
{
	SDL_Rect drawingRect = { positionRect.x - cameraRect.x, positionRect.y - cameraRect.y, positionRect.w, positionRect.h }; //sets the players drawing location based on the players postion and the camera
	SDL_RenderCopy(renderTarget, texture, &cropRect, &drawingRect); // create a copy of the player texture to be rendered
}

int WeakGuy::getPosX()
{
	return positionRect.x; //returns the players x location in the world
}

int WeakGuy::getPosY()
{
	return positionRect.y; //returns the players y location in the world
}
/*
the
*/
bool WeakGuy::checkCollision(SDL_Rect a)
{
	if (positionRect.x + positionRect.w < a.x || positionRect.x > a.x + a.w
		|| positionRect.y + positionRect.h < a.y || positionRect.y > a.y + a.h)
	{
		return true;
	}
	return false;
}

bool WeakGuy::hitFire(Fire *f)
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
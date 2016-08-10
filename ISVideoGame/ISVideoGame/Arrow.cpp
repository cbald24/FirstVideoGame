#include "Arrow.h"



Arrow::Arrow(SDL_Renderer *renderTarget, std::string filepath, int x, int y)
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

	SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h); 
	posRect.x = x;
	posRect.y = y;
	cropRect.w /= xFrames;
	frameWidth = cropRect.w;
	frameHeight = cropRect.h;
	if (!pointedLeft)
	{
		cropRect.w += frameWidth;
	}
	
}


Arrow::~Arrow()
{
	SDL_DestroyTexture(texture);
}

bool Arrow::Update(float delta, Player &p)
{
	if (pointedLeft)
	{
		posRect.x -= moveSpeed;
	}
	else
	{
		posRect.x += moveSpeed;
	}
	timer += delta;
	if (timer >= lifeSpan)
	{
		delete this;
	}
	return true;
}

void Arrow::Draw(SDL_Renderer *renderTarget, SDL_Rect cameraRect)
{
	SDL_Rect drawingRect = { posRect.x - cameraRect.x, posRect.y - cameraRect.y, posRect.w, posRect.h }; //sets the arrows drawing location based on the arrows postion and the camera
	SDL_RenderCopy(renderTarget, texture, &cropRect, &drawingRect); // create a copy of the arrow texture to be rendered
}

void Arrow::setLeft(bool left)
{
	pointedLeft = left;
}
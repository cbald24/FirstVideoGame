#include "Tile.h"


Tile::Tile(bool s, int id, std::string filepath, SDL_Renderer *renderTarget, int col, int ts, bool k)
{
	solid = s;
	willKill = k;
	tileID = id;
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
	
	//SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h);
	cropRect.w = cropRect.h = positionRect.h = positionRect.w = ts;
	cropRect.x = ((id % col) * cropRect.w); //take the id number which also resembles the index in the imaginary
	cropRect.y = ((id / col) * cropRect.h);

	
}

Tile::Tile()
{
	solid = false;
	tileID = 0;
}

Tile::~Tile()
{

}

void Tile::Render(SDL_Renderer *renderTarget, SDL_Rect cameraRect)
{
	SDL_Rect drawingRect = { positionRect.x - cameraRect.x, positionRect.y - cameraRect.y, positionRect.w, positionRect.h }; //sets the tile's drawing location based on the players postion and the camera
	SDL_RenderCopy(renderTarget, texture, &cropRect, &drawingRect);
}

int Tile::getID()
{
	return tileID;
}
/*
sets the tiles location based on a formula using the height and width of the map and the number in line the tile is
*/
void Tile::setLocation(int mapHeight, int mapWidth, int number)
{
	positionRect.x = (number % mapWidth) * cropRect.w;
	positionRect.y = (number / mapWidth) * cropRect.h;
}

bool Tile::getKill()
{
	return willKill;
}

bool Tile::getSolid()
{
	return solid;
}
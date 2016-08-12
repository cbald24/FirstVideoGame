#include"tinyxml2.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <SDL_gamecontroller.h>
#include"Player.h"
#include"Tile.h"
#include"Map.h"
#include"WeakGuy.h"
#include"Boss.h"
#include"RangedEnemy.h"
#include"Arrow.h"

Map ReadMap(std::string filepath, SDL_Renderer *renderTargert)
{
	int mapHeight, mapWidth, tileSize, tileID, col;
	bool solid; 
	bool kill;
	Map worldMap = Map();
	Tile tileSet[20];
	Tile tempTile;
	Tile tiles[375];
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError eResult = doc.LoadFile(filepath.c_str());
	if (eResult != tinyxml2::XML_SUCCESS)
	{
		std::cout << "Problem Reading in xml" << std::endl;
	}
	tinyxml2::XMLElement * node = doc.FirstChildElement("map");
	node->QueryIntAttribute("width", &mapWidth); //gets the number of tiles in the width of the map
	node->QueryIntAttribute("height", &mapHeight); //gets the number of tiles in the height of the map
	node->QueryIntAttribute("tilewidth", &tileSize);
	int tilesNeeded = mapHeight * mapWidth;
	
	worldMap.setMapHeight(mapHeight);
	worldMap.setMapWidth(mapWidth);
	worldMap.setTileSize(tileSize);

	node = node->FirstChildElement("tileset");
	node->QueryIntAttribute("columns", &col);
	tinyxml2::XMLElement *fallBack = node;
	node = node->FirstChildElement("tile");
	tinyxml2::XMLElement *temp;
	for (int i = 0; i < 20; i++)
	{
		temp = node;
		node->QueryIntAttribute("id", &tileID);
		node = node->FirstChildElement("properties")->FirstChildElement("property");
		kill = node->BoolAttribute("value");
		node = node->NextSiblingElement();
		solid = node->BoolAttribute("value");
		tempTile = Tile(solid, tileID, "tiles.png", renderTargert, col, tileSize, kill);
		tileSet[i] = tempTile;
		node = temp->NextSiblingElement("tile");
	}
	node = fallBack;
	node = node->NextSiblingElement("layer")->FirstChildElement("data");
	bool found = false;
	int count = 0;
	int j = 0;
	for (tinyxml2::XMLElement *child = node->FirstChildElement("tile"); child != NULL; child = child->NextSiblingElement())
	{
		found = false; 
		tileID = child->IntAttribute("gid");	
		while (!found)
		{
			if (tileSet[count].getID() == tileID-1)
			{
				tiles[j] = tileSet[count];
				tiles[j].setLocation(mapHeight, mapWidth, j);
				count = 0;
				found = true;
			}
			else
			{
				count++;
			}
		}
		node->NextSiblingElement();
		j++;
	}
	worldMap.setTiles(tiles);
	return worldMap;
}

SDL_Texture *LoadTexture(std::string filepath, SDL_Renderer *renderTarget)
{
	SDL_Texture *texture = nullptr;
	SDL_Surface *surface = IMG_Load(filepath.c_str());
	if (surface == NULL)
	{
		std::cout << "problem loading in texture" << std::endl;
	}
	else
	{
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 250, 50, 250));
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		
	}

	SDL_FreeSurface(surface);
	
	return texture;
}



int main(int argc, char* args[])
{
	SDL_Window *window = nullptr; //the window the game pops up in
	SDL_GameController *controller = nullptr; //xbox controller
	SDL_Renderer *renderTarget = nullptr; //a renderer that will set the destination for textures to show up on the game window
	int textureWidth, textureHeight;	//
	int currentTime = 0;//time to help frames and buffering
	int prevTime = 0;//helps create the delta
	float delta = 0.0f;
	const Uint8 *keyState; //the keystate of the keyboard
	SDL_Event ev; //an event that currently is used to exit
	const int screenHeight = 400; //the window height in pixels
	const int screenWidth = 750; //the window width in pixels
	SDL_Rect cameraRect = { 0, 0, screenWidth, screenHeight }; //the SDL rect that wil be the camera set to the same dimensions as the game window
	int levelWidth; //the default width of the level
	int levelHeight; //the default height of the level
	
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER); //inits the video and controller functions to operate the game

	int imgflags = IMG_INIT_PNG; //inits the abality to read and use .png files
	if (IMG_Init(imgflags) != imgflags) //check for error
	{
		std::cout << "Error" << IMG_GetError() << std::endl; //error message
	}

	window = SDL_CreateWindow("Independent Study: THE GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN); //creates the game window, gives it a title and makes it display
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //creates the renderer and sets its target to the game window

	Map daMap = ReadMap("backgroundTest.tmx", renderTarget);
	levelHeight = daMap.getMapHeight() * daMap.getTileSize();
	levelWidth = daMap.getMapWidth() * daMap.getTileSize();

	Player player1 = Player(renderTarget, "playerSprites.png", 0, levelHeight-338, 9, 5); //creates the player object using preset values detrimened by the sprite sheet dimensions for images
	WeakGuy enemy1 = WeakGuy(renderTarget, "weakBadGuy.png", 500, levelHeight-338, 9, 3);
	RangedEnemy archer = RangedEnemy(renderTarget, "rangedBadGuy.png", 1000, levelHeight - 343, 13, 3);

	bool isRunning = true; //set bool to true to make loop go infinetly till game needs exited
	while (isRunning) //loop that manages the game actions
	{
		prevTime = currentTime; //sets previous time to the current time
		currentTime = SDL_GetTicks(); //gets the current run time
		delta = (currentTime - prevTime) / 1000.0f; //calculates the delta 
		while (SDL_PollEvent(&ev) != 0) // checks to se if an sdl event happened
		{
			if (ev.type == SDL_QUIT) //if the event is to quit then
				isRunning = false; //set isRunning to false to exit loop and close game
		}
		
		keyState = SDL_GetKeyboardState(NULL);//this will find which keys are being pressed
		player1.Update(delta, keyState, &daMap, renderTarget); //this passes the delta and updates the players sprite and postion
		enemy1.Update(delta, keyState);
		archer.Update(delta, player1, renderTarget);

		player1.IntersectsWith(enemy1);

		cameraRect.x = player1.getPosX() - 375; //sets the camera postion on the players x
		cameraRect.y = player1.getPosY() - 200; //sets the camera postion on the players y to center the camera on the player

		//this is a block of code designed to prevent the screen from strectching and causes the player to move to the corner and not the center of the camera
		if (cameraRect.x < 0)
			cameraRect.x = 0;
		if (cameraRect.y < 0)
			cameraRect.y = 0;
		if (cameraRect.x + cameraRect.w >= levelWidth)
			cameraRect.x = levelWidth - 750;
		if (cameraRect.y + cameraRect.h >= levelHeight)
			cameraRect.y = levelHeight - 400;

		SDL_RenderClear(renderTarget); //clears the old render objects
		//SDL_RenderCopy(renderTarget, texture, &cameraRect, NULL); //sets the renderer after the wipe
		
		daMap.renderTiles(cameraRect, renderTarget);

		player1.Draw(renderTarget, cameraRect); //draws the player
		enemy1.Draw(renderTarget, cameraRect);
		archer.Draw(renderTarget, cameraRect);
		//green.Draw(renderTarget, cameraRect);
		SDL_RenderPresent(renderTarget); //renders the new objects
	}	
	return 0; //end main
}
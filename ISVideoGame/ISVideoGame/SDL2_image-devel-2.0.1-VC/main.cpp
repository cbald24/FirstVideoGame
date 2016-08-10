#include <SDL.h>
#include <SDL_gamecontroller.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>


SDL_Texture *LoadTexture(std::string filepath, SDL_Renderer *renderTarget)
{
	SDL_Texture *texture = nullptr;
	SDL_Surface *surface = IMG_Load(filepath.c_str());
	if (surface == NULL)
	{
		std::cout << "Opps" << std::endl;
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		
	}

	SDL_FreeSurface(surface);

	return texture;
}


int main(int argc, char* args[])
{
	const int FPS = 60;
	const Uint8 *keyState;
	float frameTime = 0;

	SDL_Window *window = nullptr; //this will be the window
	SDL_Texture *curImage = nullptr;
	SDL_GameController *controller = nullptr;
	SDL_Renderer *renderTarget = nullptr;
	SDL_Rect playerRect;
	int frameHeight, frameWidth;
	int textureWidth, textureHeight;
	int currentTime = 0;
	int prevTime = 0;
	float deltaTime = 0;
	float ms = 200;
	SDL_Rect playerPos;
	playerPos.x = playerPos.y = 0;
	playerPos.h = playerPos.w = 64;
	

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
	if (TTF_Init() < 0)
	{
		std::cout << "Error" << TTF_GetError() << std::endl;
	}

	int imgflags = IMG_INIT_PNG;
	if (IMG_Init(imgflags) != imgflags)
	{
		std::cout << "Error" << IMG_GetError() << std::endl;
	}

	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		if (SDL_IsGameController(i))
		{
			controller = SDL_GameControllerOpen(i);
		}
	}

	window = SDL_CreateWindow("IT WORKS!!!!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1500, 800, SDL_WINDOW_SHOWN); //this opens the window that will be the game
	renderTarget = SDL_CreateRenderer(window, 1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	curImage = LoadTexture("spritesheettest.png", renderTarget);
	//image1 = SDL_LoadBMP("test.bmp");
	//image2 = SDL_LoadBMP("test1.bmp");
	//image3 = SDL_LoadBMP("test2.bmp");
	//curImage = image1;

	SDL_QueryTexture(curImage, NULL, NULL, &textureWidth, &textureHeight);
	
	frameWidth = textureWidth / 8;
	frameHeight = textureHeight / 3;

	playerRect.x = playerRect.y = 0;
	playerRect.w = frameWidth;
	playerRect.h = frameHeight;

	

	bool isRunning = true;
	SDL_Event ev;

	while (isRunning)
	{
		prevTime = currentTime;
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - prevTime) / 1000.0f;
		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT)
			{
				isRunning = false;

			}					
			/*else if (ev.type == SDL_CONTROLLERBUTTONDOWN)
			{
				switch (ev.cbutton.button)
				{
				case SDL_CONTROLLER_BUTTON_A:
					curImage = image1;
					break;
				case SDL_CONTROLLER_BUTTON_B:
					curImage = image2;
					break;
				case SDL_CONTROLLER_BUTTON_X:
					curImage = image3;
					break;
				}
				}
			*/
		}

		keyState = SDL_GetKeyboardState(NULL);
		if (keyState[SDL_SCANCODE_RIGHT])
		{
			playerPos.x += ms * deltaTime;
		}
		else if (keyState[SDL_SCANCODE_LEFT] && keyState[SDL_SCANCODE_UP])
		{
			playerPos.x -= ms * deltaTime;
			playerPos.y -= ms * deltaTime;
		}
		else if (keyState[SDL_SCANCODE_UP])
		{
			playerPos.y -= ms * deltaTime;
		}
		else if (keyState[SDL_SCANCODE_DOWN])
		{
			playerPos.y += ms * deltaTime;
		}
		frameTime += deltaTime;

		if (frameTime >= 0.25f)
		{
			frameTime = 0;
			playerRect.x += frameWidth;
			if (playerRect.x >= textureWidth)
			{
				playerRect.x = 0;
			}
		}

		SDL_RenderClear(renderTarget);
		SDL_RenderCopy(renderTarget, curImage, &playerRect, &playerPos);
		SDL_RenderPresent(renderTarget);
	}

	/*
	if (SDL_Init(SDL_INIT_VIDEO) < 0) //we check and see if we can intialize the video
	{
		std::cout << "Video Initialization Error: " << SDL_GetError() << std::endl; //print an error message if we can't load the video
	}
	else //else we open the window
	{
		window = SDL_CreateWindow("IT WORKS!!!!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 500, SDL_WINDOW_SHOWN); //this opens the window that will be the game
		if (window == NULL) //error check to make sure the window exist
		{
			std::cout << "you done fucked up: " << SDL_GetError() << std::endl; //error message if window somehow doesn't exist
		}
		else //when the window does exist
		{
			windowSurface = SDL_GetWindowSurface(window); //gets the sdl surface assciated with the given window
			imageSurface = SDL_LoadBMP("test.bmp"); //load the bitmap image onto the window


			if (imageSurface == NULL)  //error check to see if the image is null
			{
				std::cout << "No pretty piccture: " << SDL_GetError() << std::endl; //prints the error message if the image is null
			}
			else
			{
				SDL_BlitSurface(imageSurface, NULL, windowSurface, NULL); //makes the windowsurface show the image surface
				SDL_UpdateWindowSurface(window); //updates the window to show you the correct image
				SDL_Delay(10000); //keeps window from closing for 10 secs
			}

			

		}
	}
	*/
	



	//SDL_FreeSurface(image1);
	//SDL_FreeSurface(image2);
	//SDL_FreeSurface(image3);


	SDL_DestroyWindow(window);
	SDL_DestroyTexture(curImage);
	SDL_DestroyRenderer(renderTarget);
	window = nullptr;
	//curImage = image1 = image2 = image3 = nullptr;
	SDL_Quit();

	return 0; //arbitray return 0
}
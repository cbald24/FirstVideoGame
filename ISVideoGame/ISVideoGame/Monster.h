#pragma once
class Monster
{
public:
	Monster();
	~Monster();
	//void Draw(SDL_Renderer *renderTarget, SDL_Rect cameraRect);
	void Kill();
private:
	int health;
};


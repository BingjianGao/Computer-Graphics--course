#include "SDL.h"
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "SDLauxiliary.h"
using namespace std;
using glm::vec3;
// ---------------------------------------------------------
// GLOBAL VARIABLES
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int f = SCREEN_HEIGHT/2;
const float velocity = 0.0001;
vector<vec3> stars(1000);
int t;


SDL_Surface* screen;
// ---------------------------------------------------------
// FUNCTION DECLARATIONS
void Draw();
void Update();

// ---------------------------------------------------------
// FUNCTION DEFINITIONS

int main(int argc, char* argv[])
{
	
	screen = InitializeSDL(SCREEN_WIDTH, SCREEN_HEIGHT);

	
	t = SDL_GetTicks();
	for (int i = 0; i < stars.size(); ++i)
	{
		stars[i].x = -1+float(rand()) / (float(RAND_MAX)/2);
		stars[i].y = -1 + float(rand()) / (float(RAND_MAX) / 2);
		stars[i].z = float(rand()) / float(RAND_MAX);
	}
	
	while (NoQuitMessageSDL())
	{
		Update();
		Draw();
	}
	SDL_SaveBMP(screen, "screenshot.bmp");
	return 0;
}
void Draw()
{
	SDL_FillRect(screen, 0, 0);
	if (SDL_MUSTLOCK(screen))
		SDL_LockSurface(screen);
	SDL_FillRect(screen, 0, 0);
	/*
		for (int y = 0; y < SCREEN_HEIGHT; ++y)
		{
			for (int x = 0; x < SCREEN_WIDTH; ++x)
			{
				
				vec3 color(0, 0, 0);
				PutPixelSDL(screen, x, y, color);
			}
		}
	*/
	
	int u;
	int v;

	for (size_t s = 0; s<stars.size(); ++s)
	{
		
		u = f*(stars[s].x / stars[s].z) + SCREEN_WIDTH / 2;
		v = f*(stars[s].y / stars[s].z) + SCREEN_HEIGHT / 2;
		vec3 color = 0.2f * vec3(1, 1, 1) / (stars[s].z*stars[s].z); //(1, 1, 1); 
		PutPixelSDL(screen, u, v, color);

		// Add code for projecting and drawing each star
		
	}
	if (SDL_MUSTLOCK(screen))
		SDL_UnlockSurface(screen);
	SDL_UpdateRect(screen, 0, 0, 0, 0);
}
void Update()
{
	int t2 = SDL_GetTicks();
	float dt = t - t2;
	t = t2;
	
	for (int s = 0; s < stars.size(); ++s)
	{

		stars[s].z = stars[s ].z - velocity*dt;

		if (stars[s].z <= 0)
			stars[s].z += 1;
		if (stars[s].z > 1)
			stars[s].z -= 1;
	}
}

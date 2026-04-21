#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

//position
class point3D{

	int x, y, z;
	SDL_Point sdlp;

	point3D(int _x, int _y, int _z);

	SDL_Point convertToSDL();
}

//motion


//physical objects
class Planet{

	public:

	double position[2];

	double velocity;

	double mass;
	double radius;
	double F;

	Planet(double position_x, double position_y, double _mass, double _radius);

	void render(SDL_Renderer* rendrer);


	//motion
	
	
};

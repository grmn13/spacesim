#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Renderer.hpp"

//position
class point3D{

	public:

	double x, y, z;
	
	double screenX, screenY;

	SDL_Point sdlp;

	point3D(int _x, int _y, int _z);

	void rotateX(double theta);
	void rotateY(double theta);
	void rotateZ(double theta);

	void project(double distance, double focalLength);

	void convertToSDL();
};

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

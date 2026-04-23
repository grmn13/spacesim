#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

#include "Renderer.hpp"

//position
struct point3D{

	double x, y, z;
	double screenX, screenY;
};


//physical objects
class Planet{

	public:

	double posX, posY, posZ;

	std::vector<point3D> points;

	double velocity;

	double mass;
	double radius;
	double F;


	Planet(double _x, double _y, double _z, double _mass, double _radius);

	//display
	void render(SDL_Renderer* rendrer);
	void project(double distance, double focalLength);

	//motion
	void rotateX(double theta);
	void rotateY(double theta);
	void rotateZ(double theta);


	
};

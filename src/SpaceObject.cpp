#include "SpaceObject.hpp"

point3D::point3D(int _x, int _y, int _z){

	x = _x;
	y = _y;
	z = _z;

	sdlp.x = x;
	sdlp.y = y;
}

point3D::SDL_Point convertToSDL(){

	sdlp.x = x;
	sdlp.y = y;
}

Planet::Planet(double position_x, double position_y, double _mass, double _radius){

	position[0] = position_x;
	position[1] = position_y;

	mass = _mass;
	radius = _radius;
}

void Planet::render(SDL_Renderer* renderer){

	
}

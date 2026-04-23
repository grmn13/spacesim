#include <cmath>

#include "SpaceObject.hpp"



point3D::point3D(int _x, int _y, int _z){

	x = _x;
	y = _y;
	z = _z;

	sdlp.x = x;
	sdlp.y = y;
}

void point3D::convertToSDL(){

	sdlp.x = x;
	sdlp.y = y;
}

void point3D::rotateX(double theta){

	double cosT = cos(theta);
	double sinT = sin(theta);

	double rotY = y - centerY;

	y = rotY * cosT - z * sinT + centerY;
	z = rotY * sinT + z * cosT;

	screenX = x;
	screenY = y;
}

void point3D::rotateY(double theta){

	double cosT = cos(theta);
	double sinT = sin(theta);

	double rotX = x - centerX;

	x = rotX * cosT + z * sinT + centerX;
	z = z * cosT - rotX * sinT;

	screenX = x;
	screenY = y;
}

void point3D::rotateZ(double theta){

	double cosT = cos(theta);
	double sinT = sin(theta);

	double rotX = x - centerX;
	double rotY = y - centerY;

	x = rotX * cosT - rotY * sinT + centerX;
	y = rotX * sinT + rotY * cosT + centerY;

	screenX = x;
	screenY = y;
}

void point3D::project(double distance, double focalLength){

	double denom = distance - z;
	if(denom < 0.1) denom = 0.1;

	double zConversion = focalLength / denom;

	double tempX = x - centerX;
	double tempY = y - centerY;

	screenX = tempX * zConversion + centerX;
	screenY = tempY * zConversion + centerY;
}

Planet::Planet(double position_x, double position_y, double _mass, double _radius){

	position[0] = position_x;
	position[1] = position_y;

	mass = _mass;
	radius = _radius;
}

void Planet::render(SDL_Renderer* renderer){

	
}

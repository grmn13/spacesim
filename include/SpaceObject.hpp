#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

#include "Renderer.hpp"

//required forward declarations
class SpaceObject;

//helper functions

const double PI = M_PI;
const double HALF_PI = M_PI / 2;
double map(double value, double f1, double l1, double f2, double l2);


//position
struct point3D{

	double x, y, z;
	double screenX, screenY;

	void rotateX(double cosT, double sinT);
	void rotateY(double cosT, double sinT);
	void rotateZ(double cosT, double sinT);
};

class Camera{

	public:

	double fov;

	double posX, posY, posZ;
	double tiltX, tiltY, tiltZ;
	//double fwX, fwY, fwZ; //components of forward vector

	Camera(){
	
		posX = 0;
		posY = 0;
		posZ = -200;
		fov = 400;

		tiltX = 0;
		tiltY = 0;
		tiltZ = 0;
	}

	void moveX(double speed);
	void moveY(double speed);
	void moveZ(double speed);

	void worldCameraTransform(double &relX, double &relY, double &relZ);
};


//physical objects
class SpaceObject{

	public:

	double posX, posY, posZ;

	std::vector<point3D> points;

	double velocity;
	double angVelocityOrbit;
	double angVelocityRotation;

	double mass;
	double radius;
	double F;

	int objectRes;

	SpaceObject(double _x, double _y, double _z, double _mass, double _radius, double angVelocityOrbit, double angVelocityRotation);

	//display
	void render(SDL_Renderer* rendrer, textRenderer* txtRenderer);
	void project(Camera _cam);
	//void project(double distance, double focalLength);

	//motion
	void rotateX(double theta);
	void rotateY(double theta);
	void rotateZ(double theta);

	void orbitX(double theta);
	void orbitY(double theta);
	void orbitZ(double theta);
};

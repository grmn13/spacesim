#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

#include "Renderer.hpp"

//required forward declarations
class SpaceObject;

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

	Camera(){
	
		posX = 0;
		posY = 0;
		posZ = -150;
		fov = 200;

		tiltX = 0;
		tiltY = 0;
		tiltZ = 0;
	}
	
	void worldCameraTransform(double &relX, double &relY, double &relZ);
};


//physical objects
class SpaceObject{

	public:

	double posX, posY, posZ;

	std::vector<point3D> points;

	double velocity;

	double mass;
	double radius;
	double F;

	SpaceObject(double _x, double _y, double _z, double _mass, double _radius);

	//display
	void render(SDL_Renderer* rendrer);
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

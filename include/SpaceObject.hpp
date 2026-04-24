#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

#include "Renderer.hpp"

//position
struct point3D{

	double x, y, z;
	double screenX, screenY;

	void rotateX(double theta);
	void rotateY(double theta);
	void rotateZ(double theta);
};

class Camera{

	public:

	point3D position;
	double fov;

	Camera(){
	
		position.x = 0;
		position.y = 0;
		position.z = -150;
		fov = 200;
	}

	void rotateX(double theta);
	void rotateY(double theta);
	void rotateZ(double theta);
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
	void project(const Camera _cam);
	//void project(double distance, double focalLength);

	//motion
	void rotateX(double theta);
	void rotateY(double theta);
	void rotateZ(double theta);


	
};

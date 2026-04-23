#include <cmath>

#include "SpaceObject.hpp"


void Planet::rotateX(double theta){

	double cosT = cos(theta);
	double sinT = sin(theta);

	for(point3D &pt : points){

		double rotY = pt.y;

		pt.y = rotY * cosT - pt.z * sinT;
		pt.z = rotY * sinT + pt.z * cosT;

	}
}

void Planet::rotateY(double theta){

	double cosT = cos(theta);
	double sinT = sin(theta);

	for(point3D &pt : points){

		double rotX = pt.x;

		pt.x = rotX * cosT + pt.z * sinT;
		pt.z = pt.z * cosT - rotX * sinT;
	}
}

void Planet::rotateZ(double theta){

	double cosT = cos(theta);
	double sinT = sin(theta);

	for(point3D &pt : points){

		double rotX = pt.x;
		double rotY = pt.y;

		pt.x = rotX * cosT - rotY * sinT;
		pt.y = rotX * sinT + rotY * cosT;
	}
}

void Planet::project(double distance, double focalLength){

	for(point3D &pt : points){

		double ptPosX = pt.x + posX;
		double ptPosY = pt.y + posY;
		double ptPosZ = pt.z + posZ; 
		
		double denom = distance - ptPosZ;
		if(denom < 0.1) denom = 0.1;

		double zConversion = focalLength / denom;

		pt.screenX = ptPosX * zConversion + (RES[0] / 2);
		pt.screenY = ptPosY * zConversion + (RES[1] / 2);
	}
}

Planet::Planet(double _x, double _y, double _z, double _mass, double _radius){

	posX = _x;
	posY = _y;
	posZ = _z;

	mass = _mass;
	radius = _radius;
	
	points.push_back({-radius, radius, radius, 0, 0});
	points.push_back({radius, radius, radius, 0, 0});
	points.push_back({radius, -radius, radius, 0, 0});
	points.push_back({-radius, -radius, radius, 0, 0});
	points.push_back({-radius, radius, -radius, 0, 0});
	points.push_back({radius, radius, -radius, 0, 0});
	points.push_back({radius, -radius, -radius, 0, 0});
	points.push_back({-radius, -radius, -radius, 0, 0});
}

void Planet::render(SDL_Renderer* renderer){

	//render a rect here to see points, beware the half/size if u want to print all
	
	int hlf = points.size() / 2;

	for(int i = 0; i < hlf; i++){
	
		SDL_RenderDrawLine(renderer, points[i].screenX, points[i].screenY, points[(i + 1) % hlf].screenX, points[(i + 1) % hlf].screenY);
		SDL_RenderDrawLine(renderer, points[i].screenX, points[i].screenY, points[i + hlf].screenX, points[i + hlf].screenY);
		SDL_RenderDrawLine(renderer, points[i + hlf].screenX, points[i + hlf].screenY, points[((i + 1) % hlf) + hlf].screenX, points[((i + 1) % hlf) + hlf].screenY);
	}
}

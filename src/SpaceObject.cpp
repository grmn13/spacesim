#include <cmath>

#include "SpaceObject.hpp"

void point3D::rotateX(double theta){

	double cosT = cos(theta);
	double sinT = sin(theta);

	double rotY = y;

	y = rotY * cosT - z * sinT;
	z = rotY * sinT + z * cosT;

}

void point3D::rotateY(double theta){

	double cosT = cos(theta);
	double sinT = sin(theta);


	double rotX = x;

	x = rotX * cosT + z * sinT;
	z = z * cosT - rotX * sinT;
}

void point3D::rotateZ(double theta){

	double cosT = cos(theta);
	double sinT = sin(theta);

	double rotX = x;
	double rotY = y;

	x = rotX * cosT - rotY * sinT;
	y = rotX * sinT + rotY * cosT;
}

void Camera::rotateX(double theta){

	position.rotateX(theta);
}

void Camera::rotateY(double theta){

	position.rotateY(theta);
}

void Camera::rotateZ(double theta){

	position.rotateZ(theta);
}

void Planet::rotateX(double theta){

	for(point3D &pt : points){

		pt.rotateX(theta);
	}
}

void Planet::rotateY(double theta){

	for(point3D &pt : points){

		pt.rotateY(theta);
	}
}

void Planet::rotateZ(double theta){

	for(point3D &pt : points){

		pt.rotateZ(theta);
	}
}

//void Planet::project(Camera _cam, double distance, double fov){
void Planet::project(const Camera _cam){

	for(point3D &pt : points){

		double ptPosX = pt.x + posX - _cam.position.x;
		double ptPosY = pt.y + posY - _cam.position.y;
		double ptPosZ = pt.z + posZ - _cam.position.z; 
		
		//double denom = distance - ptPosZ;
		//if(denom < 0.1) denom = 0.1;
		if(ptPosZ < 0.1) ptPosZ = 0.1;

		double zConversion = _cam.fov / ptPosZ;

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

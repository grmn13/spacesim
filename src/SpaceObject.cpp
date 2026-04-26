#include <cmath>
#include <iostream>

#include "SpaceObject.hpp"

double map(double value, double f1, double l1, double f2, double l2){

	return f2 + (l2 - f2) * ((value - f1) / (l1 - f1));
}

void point3D::rotateX(double cosT, double sinT){

	double rotY = y;

	y = rotY * cosT - z * sinT;
	z = rotY * sinT + z * cosT;

}

void point3D::rotateY(double cosT, double sinT){

	double rotX = x;

	x = rotX * cosT + z * sinT;
	z = z * cosT - rotX * sinT;
}

void point3D::rotateZ(double cosT, double sinT){

	double rotX = x;
	double rotY = y;

	x = rotX * cosT - rotY * sinT;
	y = rotX * sinT + rotY * cosT;
}

void SpaceObject::orbitX(double theta){

	double cosT = cos(theta);
	double sinT = sin(theta);

	double ogY = posY;

	posY = ogY * cosT - posZ * sinT;
	posZ = ogY * sinT + posZ * cosT;
}

void SpaceObject::orbitY(double theta){

	double cosT = cos(theta);
	double sinT = sin(theta);

	double ogX = posX;

	posX = ogX * cosT + posZ * sinT;
	posZ = posZ * cosT - ogX * sinT;
}

void SpaceObject::orbitZ(double theta){

	double cosT = cos(theta);
	double sinT = sin(theta);

	double ogX = posX;
	double ogY = posY;

	posX = ogX * cosT - ogY * sinT;
	posY = ogX * sinT + ogY * cosT;
}

void SpaceObject::rotateX(double theta){

	double cosT = cos(theta);
	double sinT = sin(theta);

	for(point3D &pt : points){

		pt.rotateX(cosT, sinT);
	}
}

void SpaceObject::rotateY(double theta){

	double cosT = cos(theta);
	double sinT = sin(theta);

	for(point3D &pt : points){

		pt.rotateY(cosT, sinT);
	}
}

void SpaceObject::rotateZ(double theta){

	double cosT = cos(theta);
	double sinT = sin(theta);

	for(point3D &pt : points){

		pt.rotateZ(cosT, sinT);
	}
}

void Camera::moveX(double speed){

	posX += cos(tiltY) * speed;
	posZ -= sin(tiltY) * speed;
}

void Camera::moveY(double speed){

	posY += speed;
}

void Camera::moveZ(double speed){

	posX += cos(tiltX) * sin(tiltY) * speed;
	posY -= sin(tiltX) * speed; // negative due to inverted Y in SDL
	posZ += cos(tiltX) * cos(tiltY) * speed;

}

void Camera::worldCameraTransform(double &relX, double &relY, double &relZ){

	if(tiltY){

		double cosT = cos(-tiltY);
		double sinT = sin(-tiltY);

		double ogX = relX;
		
		relX = ogX * cosT + relZ * sinT;
		relZ = relZ * cosT - ogX * sinT;
	}

	if(tiltX){

		double cosT = cos(-tiltX);
		double sinT = sin(-tiltX);

		double ogY = relY;

		relY = ogY * cosT - relZ * sinT;
		relZ = ogY * sinT + relZ * cosT;
	}
}

void SpaceObject::project(Camera _cam){

	for(point3D &pt : points){

		double relPosX = pt.x + posX - _cam.posX;
		double relPosY = pt.y + posY - _cam.posY;
		double relPosZ = pt.z + posZ - _cam.posZ; 
		
		//double denom = distance - ptPosZ;
		//if(denom < 0.1) denom = 0.1;

		_cam.worldCameraTransform(relPosX, relPosY, relPosZ);

		if(relPosZ < 0.1) relPosZ = 0.1;
		double zConversion = _cam.fov / relPosZ;

		pt.screenX = relPosX * zConversion + (RES[0] / 2);
		pt.screenY = relPosY * zConversion + (RES[1] / 2);
	}
}

SpaceObject::SpaceObject(double _x, double _y, double _z, double _mass, double _radius, double _angVelocityOrbit, double _angVelocityRotation){

	posX = _x;
	posY = _y;
	posZ = _z;

	mass = _mass;
	radius = _radius;

	angVelocityOrbit = _angVelocityOrbit;
	angVelocityRotation = _angVelocityRotation;

	objectRes = 20;

	/*
	points.push_back({-radius, radius, radius, 0, 0});
	points.push_back({radius, radius, radius, 0, 0});
	points.push_back({radius, -radius, radius, 0, 0});
	points.push_back({-radius, -radius, radius, 0, 0});
	points.push_back({-radius, radius, -radius, 0, 0});
	points.push_back({radius, radius, -radius, 0, 0});
	points.push_back({radius, -radius, -radius, 0, 0});
	points.push_back({-radius, -radius, -radius, 0, 0});
	*/

	for(int i = 0; i < objectRes + 1; i++){
	
		float lat = map(i, 0, objectRes, -HALF_PI, HALF_PI);

		float cosLat = cos(lat);
		float sinLat = sin(lat);

		for(int j = 0; j < objectRes; j++){

			float lon = map(j, 0, objectRes, -PI, PI);

			float cosLon = cos(lon);
			float sinLon = sin(lon);

			float x = _radius * sinLon * cosLat;
			float y = _radius * sinLon * sinLat;
			float z = _radius * cosLon;

			points.push_back({x, y, z, 0, 0});
		}
	}
}

void SpaceObject::render(SDL_Renderer* renderer, textRenderer* txtRenderer){

	int pSize = points.size();

	for(int i = 0; i < objectRes; i++){
	
		for(int j = 0; j < objectRes; j++){

			//pt in current line
			int idx = j + (i * objectRes);

			//next pt wrapping around line
			int nx = (idx + 1) % objectRes + i * objectRes;

			//pt below in the grid
			int eq_nxl = (idx + objectRes) % pSize;

			SDL_RenderDrawLine(renderer, points[idx].screenX, points[idx].screenY, points[nx].screenX, points[nx].screenY);
			SDL_RenderDrawLine(renderer, points[idx].screenX, points[idx].screenY, points[eq_nxl].screenX, points[eq_nxl].screenY);
			SDL_RenderDrawLine(renderer, points[eq_nxl].screenX, points[eq_nxl].screenY, points[nx].screenX, points[nx].screenY);

		}
	}

}

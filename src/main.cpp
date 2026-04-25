#include <iostream>
#include <vector>
#include <numbers>
#include <string>
#include <map>

#include "Renderer.hpp"
#include "SpaceObject.hpp"

#define SPEED 50
#define FOVSPEED 40

double radToDeg(double radians);
void handleKb(const Uint8* _kbstate, Camera &_cam);

int main(){

        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;

        SDL_Init(SDL_INIT_EVERYTHING);

        SDL_CreateWindowAndRenderer(RES[0], RES[1], 0, &window, &renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
        textRenderer* txtRenderer = new textRenderer(renderer, "../src/Hack-Regular.ttf", 20);

	Camera cam;
	Hud hud;

	hud.stats.push_back({"cam X", &cam.posX});
	hud.stats.push_back({"cam Y", &cam.posY});
	hud.stats.push_back({"cam Z", &cam.posZ});
	hud.stats.push_back({"fov", &cam.fov});
	hud.stats.push_back({"tiltX", &cam.tiltX});
	hud.stats.push_back({"tiltY", &cam.tiltY});

	//SpaceObject sun(500, 500, 0, 1.989e30, 696e3);
	
	std::map<std::string, SpaceObject> astros;
	
	//the base of rotation-orbit is meant to be to the power of -7 to have them be accurat,
	
	/*
	astros.try_emplace("Sun", 0.00, 0.00, 0.00, 1.00, 50.00, 0.00, 28.7e-3);
	astros.try_emplace("Mercury", 78.00, 0.00, 0.00, 1.00, 15.00, 8.26e-3, 12.4e-3);
	astros.try_emplace("Venus", 144.00, 0.00, 0.00, 1.00, 20.00, 3.23e-3, -2.99e-3);
	astros.try_emplace("Earth", 200.00, 0.00, 0.00, 1.00, 20.00, 1.99e-3, 727.2e-3);
	astros.try_emplace("Mars", 304.00, 0.00, 0.00, 1.00, 16.00, 1.06e-3, 708.8e-3);
	astros.try_emplace("Jupiter", 1200.00, 0.00, 0.00, 1.00, 40.00, 1.67e-3, 1760.0e-3);
	astros.try_emplace("Saturn", 2180.00, 0.00, 0.00, 1.00, 35.00, 9.29e-3, 1630.0e-3);
	astros.try_emplace("Uranus", 3840.00, 0.00, 0.00, 1.00, 28.00, 2.37e-3, 1010.0e-3);
	astros.try_emplace("Neptune", 6000.00, 0.00, 0.00, 1.00, 28.00, 1.21e-3, 1080.0e-3);
	*/

	astros.try_emplace("Sun", 0.00, 0.00, 0.00, 1.00, 50.00, 0.00, 28.7e-4);
	astros.try_emplace("Mercury", 78.00, 0.00, 0.00, 1.00, 15.00, 8.26e-2, 12.4e-4);
	astros.try_emplace("Venus", 144.00, 0.00, 0.00, 1.00, 20.00, 3.23e-2, -2.99e-4);
	astros.try_emplace("Earth", 200.00, 0.00, 0.00, 1.00, 20.00, 1.99e-2, 727.2e-4);
	astros.try_emplace("Mars", 304.00, 0.00, 0.00, 1.00, 16.00, 1.06e-2, 708.8e-4);
	astros.try_emplace("Jupiter", 1200.00, 0.00, 0.00, 1.00, 40.00, 1.67e-2, 1760.0e-4);
	astros.try_emplace("Saturn", 2180.00, 0.00, 0.00, 1.00, 35.00, 9.29e-2, 1630.0e-4);
	astros.try_emplace("Uranus", 3840.00, 0.00, 0.00, 1.00, 28.00, 2.37e-2, 1010.0e-4);
	astros.try_emplace("Neptune", 6000.00, 0.00, 0.00, 1.00, 28.00, 1.21e-2, 1080.0e-4);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	const Uint8* kbstate = SDL_GetKeyboardState(NULL);

	bool run = true;
	while(run){

		SDL_Delay(16);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		SDL_PumpEvents();

		if(kbstate[SDL_SCANCODE_ESCAPE]){

			run = false;
		}
	
		handleKb(kbstate, cam);
		
		for(auto &astro : astros){

			SpaceObject* so = &astro.second;

			so->rotateY(so->angVelocityRotation);
			so->orbitY(so->angVelocityOrbit);
			so->project(cam);
			so->render(renderer);
		}
	
		hud.renderCrossHair(renderer);
		hud.renderStats(txtRenderer);

		SDL_RenderPresent(renderer);
	
	}


	return 0;
}

void handleKb(const Uint8* _kbstate, Camera &_cam){


	//i need to fix the movement is not taking
	//into account the tilt of the camera
	

	//_camera Z
	if(_kbstate[SDL_SCANCODE_W]){

		_cam.posZ += SPEED;
	}
	if(_kbstate[SDL_SCANCODE_S]){

		_cam.posZ -= SPEED;
	}

	//_camera X
	if(_kbstate[SDL_SCANCODE_A]){

		_cam.posX -= SPEED;
	}
	if(_kbstate[SDL_SCANCODE_D]){

		_cam.posX += SPEED;
	}

	//_camera Y
	if(_kbstate[SDL_SCANCODE_SPACE]){

		_cam.posY -= SPEED;
	}
	if(_kbstate[SDL_SCANCODE_LSHIFT]){

		_cam.posY += SPEED;
	}
	
	//camera fov
	if(_kbstate[SDL_SCANCODE_MINUS] && _cam.fov > 10){

		_cam.fov -= FOVSPEED;
	}
	if(_kbstate[SDL_SCANCODE_EQUALS]){

		_cam.fov += FOVSPEED;
	}

	//camera tilt X
	if(_kbstate[SDL_SCANCODE_UP]){

		_cam.tiltX = _cam.tiltX + (0.01 * (1500 / _cam.fov)) > 1.57 ? 1.57 : _cam.tiltX + (0.01 * (1500 / _cam.fov));
	}
	if(_kbstate[SDL_SCANCODE_DOWN]){

		_cam.tiltX = _cam.tiltX - (0.01 * (1500 / _cam.fov)) < -1.57 ? -1.57 : _cam.tiltX - (0.01 * (1500 / _cam.fov));
	}

	//camera tilt Y
	//
	//value is multiplied by 1500 / fov to make it adapt on distance
	if(_kbstate[SDL_SCANCODE_LEFT]){

		_cam.tiltY = std::fmod(_cam.tiltY - (0.01 * (1500 / _cam.fov)), 2 * PI);
	}
	if(_kbstate[SDL_SCANCODE_RIGHT]){

		_cam.tiltY = std::fmod(_cam.tiltY + (0.01 * (1500 / _cam.fov)), 2 * PI);
	}
}


double radToDeg(double radians){

	return radians * 180 / PI;
}

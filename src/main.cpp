#include <iostream>
#include <vector>
#include <numbers>

#include "Renderer.hpp"
#include "SpaceObject.hpp"

#define SPEED 15

const double PI = M_PI;

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
	//SpaceObject sun(500, 500, 0, 1.989e30, 696e3);
	SpaceObject sun(0, 0, 0, 100, 100);
	SpaceObject jupiter(1000, 0, 0, 50, 50);
	SpaceObject earth(600, 0, 0, 20, 20);

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

		sun.rotateY(0.02);
		sun.project(cam);
		sun.render(renderer);
	
		earth.rotateY(0.1);
		earth.orbitY(0.05);
		earth.project(cam);
		earth.render(renderer);
		
		jupiter.rotateY(0.1);
		jupiter.orbitY(0.02);
		jupiter.project(cam);
		jupiter.render(renderer);

		txtRenderer->renderVariable(10, 10, "cam X", cam.posX, {255, 255, 255});
		txtRenderer->renderVariable(10, 30, "cam Y", cam.posY, {255, 255, 255});
		txtRenderer->renderVariable(10, 50, "cam Z", cam.posZ, {255, 255, 255});
		txtRenderer->renderVariable(10, 70, "fov", cam.fov, {255, 255, 255});

		txtRenderer->renderVariable(10, 100, "tilt X", radToDeg(cam.tiltX), {255, 255, 255});
		txtRenderer->renderVariable(10, 120, "tilt Y", radToDeg(cam.tiltY), {255, 255, 255});

		SDL_RenderPresent(renderer);
	
	}


	return 0;
}

void handleKb(const Uint8* _kbstate, Camera &_cam){

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

		_cam.fov -= 10;
	}
	if(_kbstate[SDL_SCANCODE_EQUALS]){

		_cam.fov += 10;
	}

	//camera tilt X
	if(_kbstate[SDL_SCANCODE_UP] && _cam.tiltX <= 1.55){

		_cam.tiltX += 0.02;
	}
	if(_kbstate[SDL_SCANCODE_DOWN] && _cam.tiltX >= -1.55){

		_cam.tiltX -= 0.02;
	}

	//camera tilt Y
	if(_kbstate[SDL_SCANCODE_LEFT]){

		_cam.tiltY = std::fmod(_cam.tiltY - 0.02, 2 * PI);
	}
	if(_kbstate[SDL_SCANCODE_RIGHT]){

		_cam.tiltY = std::fmod(_cam.tiltY + 0.02, 2 * PI);
	}

	
}


double radToDeg(double radians){

	return radians * 180 / PI;
}

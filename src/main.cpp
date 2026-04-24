#include <iostream>
#include <vector>

#include "Renderer.hpp"
#include "SpaceObject.hpp"

#define SPEED 5

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
	//Planet sun(500, 500, 0, 1.989e30, 696e3);
	Planet sun(0, 0, 0, 50, 50);
	
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

		sun.rotateY(0.05);
		sun.project(cam);
		sun.render(renderer);
		
		txtRenderer->renderVariable(10, 10, "cam X", cam.position.x, {255, 255, 255});
		txtRenderer->renderVariable(10, 30, "cam Y", cam.position.y, {255, 255, 255});
		txtRenderer->renderVariable(10, 50, "cam Z", cam.position.z, {255, 255, 255});
		txtRenderer->renderVariable(10, 70, "fov", cam.fov, {255, 255, 255});

		SDL_RenderPresent(renderer);
	
	}


	return 0;
}

void handleKb(const Uint8* _kbstate, Camera &_cam){

	//_camera Z
	if(_kbstate[SDL_SCANCODE_W]){

		_cam.position.z += SPEED;
	}
	if(_kbstate[SDL_SCANCODE_S]){

		_cam.position.z -= SPEED;
	}

	//_camera X
	if(_kbstate[SDL_SCANCODE_A]){

		_cam.position.x -= SPEED;
	}
	if(_kbstate[SDL_SCANCODE_D]){

		_cam.position.x += SPEED;
	}

	//_camera Y
	if(_kbstate[SDL_SCANCODE_SPACE]){

		_cam.position.y -= SPEED;
	}
	if(_kbstate[SDL_SCANCODE_LSHIFT]){

		_cam.position.y += SPEED;
	}
	
	//camera fov
	if(_kbstate[SDL_SCANCODE_MINUS]){

		_cam.fov -= 10;
	}
	if(_kbstate[SDL_SCANCODE_EQUALS]){

		_cam.fov += 10;
	}

	//camera rotation
	if(_kbstate[SDL_SCANCODE_1]){

		_cam.rotateX(0.05);
	}
	if(_kbstate[SDL_SCANCODE_2]){

		_cam.rotateY(0.05);
	}
	if(_kbstate[SDL_SCANCODE_3]){

		_cam.rotateZ(0.05);
	}



}

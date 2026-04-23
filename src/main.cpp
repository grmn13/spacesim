#include <iostream>
#include <vector>

#include "Renderer.hpp"
#include "SpaceObject.hpp"


int main(){

        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;

        SDL_Init(SDL_INIT_EVERYTHING);

        SDL_CreateWindowAndRenderer(RES[0], RES[1], 0, &window, &renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
        textRenderer* txtRenderer = new textRenderer(renderer, "../src/Hack-Regular.ttf", 20);

	//Planet sun(500, 500, 0, 1.989e30, 696e3);
	Planet sun(0, 0, 0, 50, 50);
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	const Uint8* kbstate = SDL_GetKeyboardState(NULL);

	float distance = 300;
	float focalLength = 500;

	bool run = true;
	while(run){

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		SDL_PumpEvents();

		if(kbstate[SDL_SCANCODE_ESCAPE]){

			run = false;
		}
	
		SDL_Delay(16);

		if(kbstate[SDL_SCANCODE_W]){
		
			focalLength -= 1;
		}
		if(kbstate[SDL_SCANCODE_S]){

			focalLength += 1;
		}

		if(kbstate[SDL_SCANCODE_A]){

			distance -= 1;
		}
		if(kbstate[SDL_SCANCODE_D]){

			distance += 1;
		}
		
		
		sun.rotateX(0.03);
		sun.project(distance, focalLength);
		sun.render(renderer);

		txtRenderer->renderVariable(10, 10, "planet center X", sun.posX, {255, 255, 255});
		txtRenderer->renderVariable(10, 30, "planet center Y", sun.posY, {255, 255, 255});
	
		SDL_RenderPresent(renderer);
	
	}


	return 0;
}

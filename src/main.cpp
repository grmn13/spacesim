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

	Planet sun(500, 500, 1.989e30, 696e3);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	std::vector<point3D> objectPoints;

	point3D p1(RES[0] / 2 - 100, RES[1] / 2 - 100, 100);
	point3D p2(RES[0] / 2 + 100, RES[1] / 2 - 100, 100);
	point3D p3(RES[0] / 2 - 100, RES[1] / 2 + 100, -100);
	point3D p4(RES[0] / 2 + 100, RES[1] / 2 + 100, -100);

	objectPoints.push_back(p1);
	objectPoints.push_back(p2);
	objectPoints.push_back(p3);
	objectPoints.push_back(p4);

	double distance = 2;

	const Uint8* kbstate = SDL_GetKeyboardState(NULL);

	bool run = true;
	while(run){

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);


		SDL_PumpEvents();

		if(kbstate[SDL_SCANCODE_ESCAPE]){

			run = false;
		}
		
		SDL_Delay(32);
		for(int i = 0; i < objectPoints.size(); i++){

			objectPoints[i].rotateX(0.1);

			SDL_Rect tempRect;
			tempRect.x = objectPoints[i].x;
			tempRect.y = objectPoints[i].y;
			tempRect.w = 10;
			tempRect.h = 10;

			SDL_Rect* ptrToRect = &tempRect;
			
			SDL_RenderFillRect(renderer, ptrToRect);

			txtRenderer->renderVariable(10, 10, "x", objectPoints[0].x, {255, 255, 255});
			txtRenderer->renderVariable(10, 30, "y", objectPoints[0].y, {255, 255, 255});
			txtRenderer->renderVariable(10, 50, "z", objectPoints[0].z, {255, 255, 255});

			//SDL_RenderDrawPoint(renderer, objectPoints[i].sdlp.x, objectPoints[i].sdlp.y);
		}

		SDL_RenderPresent(renderer);
	
	}


	return 0;
}

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
	point3D p3(RES[0] / 2 - 100, RES[1] / 2 + 100, 100);
	point3D p4(RES[0] / 2 + 100, RES[1] / 2 + 100, 100);

	point3D p5(RES[0] / 2 - 100, RES[1] / 2 - 100, -100);
	point3D p6(RES[0] / 2 + 100, RES[1] / 2 - 100, -100);
	point3D p7(RES[0] / 2 - 100, RES[1] / 2 + 100, -100);
	point3D p8(RES[0] / 2 + 100, RES[1] / 2 + 100, -100);

	objectPoints.push_back(p1);
	objectPoints.push_back(p2);
	objectPoints.push_back(p3);
	objectPoints.push_back(p4);

	objectPoints.push_back(p5);
	objectPoints.push_back(p6);
	objectPoints.push_back(p7);
	objectPoints.push_back(p8);

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
		for(int i = 0; i < objectPoints.size(); i++){
	
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

			objectPoints[i].rotateY(0.03);
			objectPoints[i].rotateY(0.03);
			objectPoints[i].rotateZ(0.03);

			//objectPoints[i].project(200, 100);
			objectPoints[i].project(distance, focalLength);
			//objectPoints[i].project(50, 300);

			SDL_Rect tempRect;
			tempRect.x = objectPoints[i].screenX - 5;
			tempRect.y = objectPoints[i].screenY - 5;
			tempRect.w = 10;
			tempRect.h = 10;

			SDL_Rect* ptrToRect = &tempRect;
			
			SDL_RenderFillRect(renderer, ptrToRect);

			SDL_RenderDrawLine(renderer, objectPoints[0].screenX, objectPoints[0].screenY, objectPoints[1].screenX, objectPoints[1].screenY);
			SDL_RenderDrawLine(renderer, objectPoints[1].screenX, objectPoints[1].screenY, objectPoints[3].screenX, objectPoints[3].screenY);
			SDL_RenderDrawLine(renderer, objectPoints[2].screenX, objectPoints[2].screenY, objectPoints[0].screenX, objectPoints[0].screenY);
			SDL_RenderDrawLine(renderer, objectPoints[3].screenX, objectPoints[3].screenY, objectPoints[2].screenX, objectPoints[2].screenY);
	
			SDL_RenderDrawLine(renderer, objectPoints[4].screenX, objectPoints[4].screenY, objectPoints[5].screenX, objectPoints[5].screenY);
			SDL_RenderDrawLine(renderer, objectPoints[5].screenX, objectPoints[5].screenY, objectPoints[7].screenX, objectPoints[7].screenY);
			SDL_RenderDrawLine(renderer, objectPoints[6].screenX, objectPoints[6].screenY, objectPoints[4].screenX, objectPoints[4].screenY);
			SDL_RenderDrawLine(renderer, objectPoints[7].screenX, objectPoints[7].screenY, objectPoints[6].screenX, objectPoints[6].screenY);


			SDL_RenderDrawLine(renderer, objectPoints[0].screenX, objectPoints[0].screenY, objectPoints[4].screenX, objectPoints[4].screenY);
			SDL_RenderDrawLine(renderer, objectPoints[1].screenX, objectPoints[1].screenY, objectPoints[5].screenX, objectPoints[5].screenY);
			SDL_RenderDrawLine(renderer, objectPoints[2].screenX, objectPoints[2].screenY, objectPoints[6].screenX, objectPoints[6].screenY);
			SDL_RenderDrawLine(renderer, objectPoints[3].screenX, objectPoints[3].screenY, objectPoints[7].screenX, objectPoints[7].screenY);

			txtRenderer->renderVariable(10, 10, "screenX", objectPoints[0].screenX, {255, 255, 255});
			txtRenderer->renderVariable(10, 30, "screenY", objectPoints[0].screenY, {255, 255, 255});
			txtRenderer->renderVariable(10, 50, "z", objectPoints[0].z, {255, 255, 255});

			txtRenderer->renderVariable(10, 80, "focal length", focalLength, {255, 255, 255});
			txtRenderer->renderVariable(10, 100, "distance", distance, {255, 255, 255});
			//SDL_RenderDrawPoint(renderer, objectPoints[i].sdlp.x, objectPoints[i].sdlp.y);
		}

		SDL_RenderPresent(renderer);
	
	}


	return 0;
}

#include <iostream>
#include "Renderer.hpp"
#include "SpaceObject.hpp"

int RES[2] = {1000,1000};

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

	point3D p1(RES[0] / 2 - 20, RES[1] / 2 - 20, -40);
	point3D p2(RES[0] / 2 + 20, RES[1] / 2 - 20, -40);
	point3D p3(RES[0] / 2 - 20, RES[1] / 2 + 20, -40);
	point3D p4(RES[0] / 2 + 20, RES[1] / 2 + 20, -40);

	SDL_RenderPresent(renderer);

	int c;
	std::cin >> c;

	return 0;
}

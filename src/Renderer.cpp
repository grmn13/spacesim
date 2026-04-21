#include <iostream>
#include "Renderer.hpp"

textRenderer::textRenderer(SDL_Renderer* ren, const char* fontPath, int fontSize)

	: renderer(ren){

	if(!ren){

		std::cout << "error initializing renderer inside textRenderer" << std::endl;
	}

	if(TTF_Init() == -1){

		std::cout << "error initializing TTF inside textRenderer" << std::endl;
	}

	font = TTF_OpenFont(fontPath, fontSize);

	if(!font){

		std::cout << "error initializing font inside textRenderer" << std::endl;
	}

}

textRenderer::~textRenderer(){

	TTF_CloseFont(font);
	TTF_Quit();
}

void textRenderer::renderText(int x, int y, const std::string& text, SDL_Color color){ //

	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect rect = {x, y, surface->w, surface->h}; //
	SDL_RenderCopy(renderer, texture, NULL, &rect); //

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}



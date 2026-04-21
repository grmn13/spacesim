#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <sstream>

class textRenderer{

    public:

        SDL_Renderer* renderer;
        TTF_Font* font;

        textRenderer(SDL_Renderer* ren, const char* fontPath, int fontSize);

        ~textRenderer();

        void renderText(int x, int y, const std::string& text, SDL_Color color);

	template <typename T>
	void renderVariable(int x, int y, const std::string& label, T value, SDL_Color color){

		std::ostringstream oss;
		oss << label << ": " << value;
		renderText(x, y, oss.str(), color);
	}
};


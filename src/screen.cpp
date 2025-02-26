#include "screen.h"


Screen::Screen(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight) {
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(title, windowWidth, windowHeight, 0);

	renderer = SDL_CreateRenderer(window, NULL);

	texture = SDL_CreateTexture(
		renderer, SDL_PIXELFORMAT_RGB332, SDL_TEXTUREACCESS_STREAMING, textureWidth, textureHeight);
}

Screen::~Screen() {
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Screen::Update(void const* buffer, int pitch) {
	SDL_UpdateTexture(texture, nullptr, buffer, pitch);
	SDL_RenderClear(renderer);
	SDL_RenderTexture(renderer, texture, nullptr, nullptr);

	SDL_RenderPresent(renderer);
}
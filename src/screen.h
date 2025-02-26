#pragma once
#include <SDL3/SDL.h>
#include "bytes.h"

class Screen {
public:
	Screen(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight);

	~Screen();
	void Update(void const* buffer, int pitch);

private:
	SDL_Window* window{};
	SDL_Renderer* renderer{};
	SDL_Texture* texture{};
};

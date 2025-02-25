// Chip8.cpp : Defines the entry point for the application.
//

#define SDL_MAIN_USE_CALLBACKS 1
#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "chip8.h"

constexpr auto SCALE = 8;
#define WINDOW_WIDTH 64*SCALE
#define WINDOW_HEIGHT 32*SCALE

// for now we're doing sdl shenanegains to learn pixel addressing

//int main()
//{
//	
//	while (true) {
//		chip8->getNextOpcode();
//	}
//	delete chip8;
//	return 0;
//}

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static Uint64 last_time = 0;
static SDL_FRect pixels[64][32];
static SDL_FPoint points[500];
static Screen screen;

static Chip8 *chip8;


// Run once at startup
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
	int i;

	chip8 = new Chip8();
	chip8->reset();
	SDL_SetAppMetadata("Chip8 Emulator", "0.1", "com.pengpng.chip8emulator");

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (!SDL_CreateWindowAndRenderer("Chip8 Emulator", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer)) {
		SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	/* set up some random points */
	/*for (i = 0; i < SDL_arraysize(points); i++) {
		points[i].x = (SDL_randf() * 440.0f) + 100.0f;
		points[i].y = (SDL_randf() * 280.0f) + 100.0f;
	}*/

	for (i = 0; i < 64; i++)
		for (int j = 0; j < 32; j++) {
			pixels[i][j].x = i*SCALE;
			pixels[i][j].y = j*SCALE;
			pixels[i][j].w = pixels[i][j].h = SCALE;
		}

	return SDL_APP_CONTINUE;  /* carry on with the program! */
}

// runs when a new event occurs (catch input here!)
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
	if (event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;
	}
	chip8->sendKeyboard(); // TODO: send keyboard info to the cpu!
	return SDL_APP_CONTINUE;
}

// run once per frame! (maybe put emulator steps in here? (delays/timers))
SDL_AppResult SDL_AppIterate(void* appstate) {
	// const double now = ((double)SDL_GetTicks()) / 1000.0; // convert ms to seconds
	screen = chip8->getNextOpcode();
	SDL_FRect rect;
	for (int i = 0; i < 64; i++)
		for (int j = 0; j < 32; j++) {
			pixels[i][j].h = screen.pixels[i][j];
		}

	/* as you can see from this, rendering draws over whatever was drawn before it. */
	SDL_SetRenderDrawColor(renderer, 30, 30, 30, SDL_ALPHA_OPAQUE);  /* black, full alpha */
	SDL_RenderClear(renderer);  /* start with a blank canvas. */

	// These are our pixels!
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	for (int i = 0; i < 64; i++) SDL_RenderFillRects(renderer, pixels[i], SDL_arraysize(pixels));

	SDL_RenderPresent(renderer);  /* put it all on the screen! */

	return SDL_APP_CONTINUE;  /* carry on with the program! */
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
	delete(chip8);
}
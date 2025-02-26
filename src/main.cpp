// Chip8.cpp : Defines the entry point for the application.
//

#define SDL_MAIN_USE_CALLBACKS 1
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "chip8.h"

#define VIDEO_WIDTH 64
#define VIDEO_HEIGHT 32

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_AudioStream* stream = NULL;
static Uint64 last_time = 0;
static SDL_FRect pixels[64*32];
static int videoScale;
static int cycleDelay;
static int current_sine_sample = 0;

static Chip8 chip8;

// Run once at startup
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
	if (argc != 4) {
		std::cerr << "Usage: " << argv[0] << " <Scale> <Delay> <ROM>\n";
		std::exit(EXIT_FAILURE);
	
	}
	videoScale = std::stoi(argv[1]);
	cycleDelay = std::stoi(argv[2]);
	char const* romFilename = argv[3];	// This is not used yet! go into chip8.cpp and point to a file there!

#define WINDOW_WIDTH VIDEO_WIDTH*videoScale
#define WINDOW_HEIGHT VIDEO_HEIGHT*videoScale

	SDL_AudioSpec spec;

	chip8.reset();

	// Standard SDL Stuff
	SDL_SetAppMetadata("Chip8 Emulator", "0.1", "com.pengpng.chip8emulator");

	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	window = SDL_CreateWindow("Chip8 Emulator", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, NULL);
	if (window == NULL || renderer == NULL) {
		SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	spec.channels = 1;
	spec.format = SDL_AUDIO_F32;
	spec.freq = 8000;
	stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
	if (!stream) {
		SDL_Log("Couldn't create audio stream: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	SDL_ResumeAudioStreamDevice(stream);

	int col = 0, row = 0;	// just setting up an array of pixels, ya know?
	for (int i = 0; i < 64*32; i++) {
		pixels[i].x = col++*videoScale;
		pixels[i].y = row*videoScale;
		pixels[i].h = 0; pixels[i].w = videoScale;
		if (col > 63) {
			col = 0; row++;
		}
	}

	return SDL_APP_CONTINUE;  /* carry on with the program! */
}

// runs when a new event occurs (catch input here!)
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
	if (event->type == SDL_EVENT_QUIT || chip8.sendKeyboard(event)) {
		return SDL_APP_SUCCESS;
	}
	return SDL_APP_CONTINUE;
}

// run once per frame! (maybe put emulator steps in here? (delays/timers))
SDL_AppResult SDL_AppIterate(void* appstate) {
	//const double now = ((double)SDL_GetTicks()) / 1000.0; // convert ms to seconds

	chip8.getNextOpcode(); // This acts as a cycle for the emulator

	const int minimum_audio = (8000 * sizeof (float)) /2;
	if (SDL_GetAudioStreamAvailable(stream) < minimum_audio) {
		static float samples[512];
		int i;

		for (i = 0; i < SDL_arraysize(samples); i++) {
			const int freq = 580;
			const float phase = current_sine_sample*freq / 8000.0f;
			samples[i] = SDL_sinf(phase * 2 * SDL_PI_F);
			current_sine_sample++;
		}

		if (chip8.playSound()) {
			SDL_PutAudioStreamData(stream, samples, sizeof(samples));
		}

	}


	SDL_SetRenderDrawColor(renderer, 30, 30, 30, SDL_ALPHA_OPAQUE);
	for (int i = 0; i < 64 * 32; i++) {
		if (chip8.m_ram.m_screenData[i]) {
			pixels[i].h = videoScale;	// CHEATER
		} else {
			pixels[i].h = 0;
		}
	}

	SDL_RenderClear(renderer);

	// These are our pixels!
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 126);
	SDL_RenderFillRects(renderer, pixels, 64*32);

	SDL_RenderPresent(renderer);

	return SDL_APP_CONTINUE; 
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
	
}
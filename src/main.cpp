#include <SDL2/SDL.h>
#include <stdio.h>
#include "draw.h"
#include "planet.h"
#include "handler.h"
#include <vector>
#include "main.h"

// size of the window
const int WIDTH = 800;
const int HEIGHT = 600;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool init() {
	bool success = true;
	// init SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Could not init SDL: %s\n", SDL_GetError());
		success = false;
	} else {
		// create a window
		window = SDL_CreateWindow("grav-sim", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Could not create window: %s\n", SDL_GetError());
			success = false;
		} else {
			// create a renderer
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL) {
				printf("Could not create renderer: %s\n", SDL_GetError());
				success = false;
			}
		}

	}
	return success;
}

// clean up	
void close() {
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}

void setupEnvironment() {
	planets.push_back(*(new Planet(200, 300, 0, 5.47, 0.001, 1, 1)));
	planets.push_back(*(new Planet(595, 300, 0, -4, 30, 500, 1)));
	planets.push_back(*(new Planet(400, 300, 0, 0.033, 200, 1000, 2)));
}

bool running = true;
SDL_Event event;

void handleEvents() {
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_KEYDOWN:
				// values stored in keysDown will be later used to set the camera's velocity
				switch (event.key.keysym.sym) {
					case SDLK_UP:
						keysDown[0] = true;
						break;
					case SDLK_DOWN:
						keysDown[1] = true;
						break;
					case SDLK_RIGHT:
						keysDown[2] = true;
						break;
					case SDLK_LEFT:
						keysDown[3] = true;
						break;
					default:
						break;
				}
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym) {
					case SDLK_UP:
						keysDown[0] = false;
						break;
					case SDLK_DOWN:
						keysDown[1] = false;
						break;
					case SDLK_RIGHT:
						keysDown[2] = false;
						break;
					case SDLK_LEFT:
						keysDown[3] = false;
						break;
					default:
						break;
				}
				break;
			case SDL_QUIT:
				// this event happens when user clicks the "X" to close the window
				running = false;
				printf("Quitting\n");
				break;
			default:
				break;
		}
	}
}

void loop() {
	while (running) {
		handleEvents();
		updatePlanets();
		updateCam();
		draw(renderer);
	}
}


int main(int argc, char* argv[]) {
	if (!init()) {
		return 1;
	}
	setupEnvironment();
	loop();
	close(); 
	return 0;
}

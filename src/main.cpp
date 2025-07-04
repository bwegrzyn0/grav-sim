#include <SDL2/SDL.h>
#include <stdio.h>
#include "draw.h"

const int WIDTH = 800;
const int HEIGHT = 600;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool init() {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Could not init SDL: %s\n", SDL_GetError());
		success = false;
	} else {
		window = SDL_CreateWindow("grav-sim", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Could not create window: %s\n", SDL_GetError());
			success = false;
		} else {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL) {
				printf("Could not create renderer: %s\n", SDL_GetError());
				success = false;
			}
		}

	}
	return success;
}

void close() {
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}

bool running = true;
SDL_Event event;

void handleEvents() {
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_KEYDOWN:
				printf("Key press\n");
				break;
			case SDL_KEYUP:
				printf("Key up\n");
				break;
			case SDL_QUIT:
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
		draw(renderer);
	}
}


int main(int argc, char* argv[]) {
	if (!init()) {
		return 1;
	}
	loop();
	close(); 
	return 0;
}

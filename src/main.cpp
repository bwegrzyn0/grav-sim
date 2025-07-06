#include <SDL2/SDL.h>
#include <stdio.h>
#include "draw.h"
#include "planet.h"
#include "handler.h"
#include <vector>

// wymiary okna
const int WIDTH = 800;
const int HEIGHT = 600;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

// funkcja odpowiadająca za inicjalizację SDL
bool init() {
	bool success = true;
	// inicjalizuj SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Could not init SDL: %s\n", SDL_GetError());
		success = false;
	} else {
		// utwórz okno
		window = SDL_CreateWindow("grav-sim", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Could not create window: %s\n", SDL_GetError());
			success = false;
		} else {
			// stwórz renderer
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL) {
				printf("Could not create renderer: %s\n", SDL_GetError());
				success = false;
			}
		}

	}
	return success;
}

// funkcja odpowiadająca za "posprzątanie" po wszystkim
void close() {
	// zniszcz okno, zwolnij miejsce w pamięci, zamknij SDL
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}

// funkcja dodająca wszystkie planety itd.
void setupEnvironment() {
	planets.push_back(*(new Planet(100, 100, 0, 3, 0.001, 1, 1)));
	planets.push_back(*(new Planet(400, 300, 0, 0, 200, 1000, 2)));
}

bool running = true;
SDL_Event event;

// funkcja sprawdzająca eventy
void handleEvents() {
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			// wciskanie klawiszy
			case SDL_KEYDOWN:
				printf("Key press\n");
				break;
			case SDL_KEYUP:
				printf("Key up\n");
				break;
				// wyjście z okna - kliknięcie X
			case SDL_QUIT:
				running = false;
				printf("Quitting\n");
				break;
			default:
				break;
		}
	}
}

// pętla programu
void loop() {
	while (running) {
		handleEvents();
		// funkcja updatePlanets() pochodzi z pliku handler.cpp
		updatePlanets();
		// funkcja draw() pochodzi z pliku draw.cpp
		draw(renderer);
	}
}


int main(int argc, char* argv[]) {
	if (!init()) {
		// zwróć błąd, jeśli nie udało się zainicjalizować SDL
		return 1;
	}
	setupEnvironment();
	loop();
	close(); 
	return 0;
}

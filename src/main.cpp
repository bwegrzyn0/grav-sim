#include <SDL2/SDL.h>
#include <stdio.h>
#include "draw.h"
#include "planet.h"
#include "handler.h"
#include <vector>
#include "main.h"
#include <chrono>

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
	planets.push_back(*(new Planet(200, 300, 0, 5.47, 0.001, 1, 1)));
	planets.push_back(*(new Planet(595, 300, 0, -4, 30, 500, 1)));
	planets.push_back(*(new Planet(400, 300, 0, 0.033, 200, 1000, 2)));
}

bool running = true;
SDL_Event event;

// funkcja sprawdzająca eventy
void handleEvents() {
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			// wciskanie klawiszy
			case SDL_KEYDOWN:
				// potem z tablicy keysDown korzysta updateCam() aby ustawiać prędkość kamery
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

double deltaTime = 1000000000.0d / (float) TPS;
double delta = 0;
int ticks = 0;

// pętla programu
void loop() {
	auto lastTime = std::chrono::system_clock::now();
	auto lastTimeTicks = std::chrono::system_clock::now();
	while (running) {
		auto now = std::chrono::system_clock::now();
		auto duration = now - lastTime;
		auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);	
		float timeElapsed = ns.count();
		delta = timeElapsed / deltaTime;

		if (delta >= 1) {
			// funkcja updatePlanets() pochodzi z pliku handler.cpp
			// funkcje draw() i updateCam() pochodzą z pliku draw.cpp
			updatePlanets();
			updateCam();
			lastTime = now;
			delta--;
			ticks++;
		}

		handleEvents();
		draw(renderer);

		// co sekundę wypisz szybkość programu w tickach na sekundę
		auto nowTicks = std::chrono::system_clock::now();
		auto durationTicks = nowTicks - lastTimeTicks;
		auto nsTicks = std::chrono::duration_cast<std::chrono::nanoseconds>(durationTicks);	
		float timeElapsedTicks = nsTicks.count();
		if (timeElapsedTicks >= 1000000000) {
			printf("TPS: %d\n", ticks);
			ticks = 0;
			lastTimeTicks = nowTicks;
		}

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

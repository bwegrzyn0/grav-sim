#include <SDL2/SDL.h>
#include "handler.h"
#include "draw.h"
#include "main.h"

int SDL_RenderDrawCircle(SDL_Renderer* renderer, int x, int y, int radius);
int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);

void draw(SDL_Renderer* renderer) {
	// ustal kolor tła i je zapełń
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// renderujemy po kolei wszystkie planety
	for (int i = 0; i < planets.size(); i++) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillCircle(renderer, (int) planets.at(i).x - cam_x, (int) planets.at(i).y - cam_y, (int) (planets.at(i).radius * 100));
	}

	// wyświetl to, co zostało narysowane 
	SDL_RenderPresent(renderer);
}

void updateCam(float delta) {
	// ustawiamy prędkość kamery na postawie wciśniętych klawiszy
	if (keysDown[0])
		cam_vy = -cam_v;
	else if (keysDown[1])
		cam_vy = cam_v;
	else 
		cam_vy = 0;
	if (keysDown[2])
		cam_vx = cam_v;
	else if (keysDown[3])
		cam_vx = -cam_v;
	else 
		cam_vx = 0;
	// aktualizujemy położenie kamery
	// pomnożenie przez delta uniezależnia prędkość kamery od szybkości programu
	cam_x += cam_vx * delta;
	cam_y += cam_vy * delta;
}

// https://gist.github.com/Gumichan01/332c26f6197a432db91cc4327fcabb1c - wydajny algorytm do rasteryzacji kół i okręgów
int SDL_RenderDrawCircle(SDL_Renderer* renderer, int x, int y, int radius) {
	int offsetx, offsety, d;
	int status;

	offsetx = 0;
	offsety = radius;
	d = radius -1;
	status = 0;

	while (offsety >= offsetx) {
		status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
		status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
		status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
		status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
		status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
		status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
		status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
		status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

		if (status < 0) {
			status = -1;
			break;
		}

		if (d >= 2*offsetx) {
			d -= 2*offsetx + 1;
			offsetx +=1;
		}
		else if (d < 2 * (radius - offsety)) {
			d += 2 * offsety - 1;
			offsety -= 1;
		}
		else {
			d += 2 * (offsety - offsetx - 1);
			offsety -= 1;
			offsetx += 1;
		}
	}

	return status;
}


int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius) {
	int offsetx, offsety, d;
	int status;

	offsetx = 0;
	offsety = radius;
	d = radius -1;
	status = 0;

	while (offsety >= offsetx) {

		status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
				x + offsety, y + offsetx);
		status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
				x + offsetx, y + offsety);
		status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
				x + offsetx, y - offsety);
		status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
				x + offsety, y - offsetx);

		if (status < 0) {
			status = -1;
			break;
		}

		if (d >= 2*offsetx) {
			d -= 2*offsetx + 1;
			offsetx +=1;
		}
		else if (d < 2 * (radius - offsety)) {
			d += 2 * offsety - 1;
			offsety -= 1;
		}
		else {
			d += 2 * (offsety - offsetx - 1);
			offsety -= 1;
			offsetx += 1;
		}
	}

	return status;
}


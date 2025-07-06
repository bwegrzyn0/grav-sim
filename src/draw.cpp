#include <SDL2/SDL.h>
#include "handler.h"
#include "draw.h"
#include "main.h"

int SDL_RenderDrawCircle(SDL_Renderer* renderer, int x, int y, int radius);
int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);

void draw(SDL_Renderer* renderer) {
	// set the background color and fill it
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// render each planet
	for (int i = 0; i < planets.size(); i++) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillCircle(renderer, (int) planets.at(i).x - cam_x, (int) planets.at(i).y - cam_y, (int) (planets.at(i).radius * 100));
	}

	// present what has been drawn to the screen
	SDL_RenderPresent(renderer);
}

void updateCam() {
	// set the camera's velocity according to the keys held down
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
	cam_x += cam_vx;
	cam_y += cam_vy;
}

// https://gist.github.com/Gumichan01/332c26f6197a432db91cc4327fcabb1c - an SDL2 implementation of the midpoint algorithm to rasterize circles
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


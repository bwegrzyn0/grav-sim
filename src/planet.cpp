#include <SDL2/SDL.h>
#include "main.h"
#include "planet.h"

Planet::Planet(float _x, float _y, float _v_x, float _v_y) {
			x = _x;
			y = _y;
			v_x = _v_x;
			v_y = _v_y;
			// przyporządkowujemy zmienne lokalne przekazane do konstruktora zmiennym globalnym 		
}

void Planet::updatePos() {
	// algorytm dla równania drugiego rzędu (równanie ruchu ciała w polu grawitacyjnym) został opisany w jednym z poprzednich artykułów:
	// https://bwegrzyn0.github.io/programowanie/numeryczne-rozwi%C4%85zywanie-r%C3%B3wna%C5%84-r%C3%B3%C5%BCniczkowych-2-rz%C4%99du-metod%C4%85-rungego-kutty
	// w tym przypadku x to czas, czyli t, y to x lub y, a y' to v_x lub v_y
	// funkcja g(t, x, v_x) = v_x, czyli wielości k_1, k_2, itd. można obliczyć w następujący sposób (po podstawieniu do funkcji): 
	float k_1x = v_x;
	float k_2x = v_x + k_1x * dT / 2;
	float k_3x = v_x + k_2x * dT / 2;
	float k_4x = v_x + k_3x * dT / 2;
	x += dT / 6 * (k_1x + 2*k_2x + 2*k_3x + k_4x);
	// prędkość będzie aktualizowana w oddzielnym miejscu, po aktualizacji położenia
	// dT to krok czasowy zdefiniowany w pliku main.h

	float k_1y = v_y;
	float k_2y = v_y + k_1y * dT / 2;
	float k_3y = v_y + k_2y * dT / 2;
	float k_4y = v_y + k_3y * dT / 2;
	y += dT / 6 * (k_1y + 2*k_2y + 2*k_3y + k_4y);
}


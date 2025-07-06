#include "main.h"
#include "planet.h"
#include <vector>
#include <cmath>
#include <stdio.h>

Planet::Planet(float _x, float _y, float _v_x, float _v_y, float _mass, float _density, float _ID) {
	// przyporządkowujemy zmienne lokalne przekazane do konstruktora zmiennym globalnym 		
	x = _x;
	y = _y;
	v_x = _v_x;
	v_y = _v_y;
	mass = _mass;
	density = _density;
	ID = _ID; 
	a_x = 0;
	a_y = 0;
	// R = [3M/(4*PI*rho)]^(1/3) dla jednorodnej kuli
	radius = pow((double) (3.0f*mass/(4.0f*3.1415f*density)), 0.333d);
}

void Planet::updatePos(std::vector<Planet> planets) {
	// OBLICZANIE POŁOŻENIA
	// algorytm dla równania drugiego rzędu (równanie ruchu ciała w polu grawitacyjnym) został opisany w jednym z poprzednich artykułów:
	// https://bwegrzyn0.github.io/programowanie/numeryczne-rozwi%C4%85zywanie-r%C3%B3wna%C5%84-r%C3%B3%C5%BCniczkowych-2-rz%C4%99du-metod%C4%85-rungego-kutty
	// w tym przypadku x to czas, czyli t, y to x lub y, a y' to v_x lub v_y
	// funkcja g(t, x, v_x) = v_x, czyli wielości k_1, k_2, itd. można obliczyć w następujący sposób (po podstawieniu do funkcji): 
	float k_1x = v_x;
	float k_2x = v_x + k_1x * dT / 2;
	float k_3x = v_x + k_2x * dT / 2;
	float k_4x = v_x + k_3x * dT;
	x += dT / 6 * (k_1x + 2*k_2x + 2*k_3x + k_4x);
	// prędkość będzie aktualizowana w oddzielnym miejscu, po aktualizacji położenia
	// dT to krok czasowy zdefiniowany w pliku main.h

	float k_1y = v_y;
	float k_2y = v_y + k_1y * dT / 2;
	float k_3y = v_y + k_2y * dT / 2;
	float k_4y = v_y + k_3y * dT;
	y += dT / 6 * (k_1y + 2*k_2y + 2*k_3y + k_4y);

	// OBLICZANIE PRĘDKOŚCI
	// musimy zresetować przyspieszenie, aby obliczyć je na nowo
	a_x = 0;
	a_y = 0;
	// w pierwszej kolejności trzeba zsumować wkłady sił grawitacji od wszystkich planet
	for (int i = 0; i < planets.size(); i++) {
		if (planets.at(i).ID != ID) { // nie chcemy żeby planeta przyciągała sama siebie
			// obliczamy r^2
			float distance_squared = (x - planets.at(i).x)*(x - planets.at(i).x)+(y - planets.at(i).y)*(y - planets.at(i).y);
//			printf("%f\n", distance_squared);
			// obliczamy wartość przyspieszenia
			float a = G*planets.at(i).mass/distance_squared;
			// obliczamy wartość sinusa i cosinusa kąta między planetami
			float cos = (planets.at(i).x-x)/pow((double) distance_squared, 0.5d);
			float sin = (planets.at(i).y-y)/pow((double) distance_squared, 0.5d);
			// dodajemy składowe przyspieszenia
			a_x += a*cos;
			a_y += a*sin;
		}
	}

	// obliczamy prędkość za pomocą algorytmu Rungego-Kutty
	// użyjemy jeszcze raz wcześniejszych zmiennych k
	k_1x = a_x;
	k_2x = a_x + k_1x * dT / 2;
	k_3x = a_x + k_2x * dT / 2;
	k_4x = a_x + k_3x * dT;
	v_x += dT / 6 * (k_1x + 2*k_2x + 2*k_3x + k_4x);

	k_1y = a_y;
	k_2y = a_y + k_1y * dT / 2;
	k_3y = a_y + k_2y * dT / 2;
	k_4y = a_y + k_3y * dT;
	v_y += dT / 6 * (k_1y + 2*k_2y + 2*k_3y + k_4y);

}

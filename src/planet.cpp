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

void Planet::updatePos(std::vector<Planet> planets, float delta) {
	// OBLICZANIE POŁOŻENIA
	// pomnożenie przez delta uniezależnia od szybkości działania programu
	x += v_x * dT * delta;
	// dT to krok czasowy zdefiniowany w pliku main.h
	y += v_y * dT * delta;

	// OBLICZANIE PRĘDKOŚCI
	// musimy zresetować przyspieszenie, aby obliczyć je na nowo
	a_x = 0;
	a_y = 0;
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
	// aktualizujemy prędkość
	v_x += a_x * dT;
	v_y += a_y * dT;
}

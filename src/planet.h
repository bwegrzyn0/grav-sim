#ifndef PLANET_H
#define PLANET_H

#include <vector>

class Planet {
	public:
		// położenie planety
		float x;
		float y;
		// prędkość planety
		float v_x;
		float v_y;
		// masa planety
		float mass;
		// gęstość planety
		float density;
		// promień planety 
		float radius;
		// przyspieszenie planety
		float a_x;
		float a_y;
		// indentyfikator
		float ID;
		// konstruktor
		Planet(float _x, float _y, float _v_x, float _v_y, float _mass, float _density, float _ID);
		// funkcja aktualizująca położenie planety
		void updatePos(std::vector<Planet> planets);
};
#endif

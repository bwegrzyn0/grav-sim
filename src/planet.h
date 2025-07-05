#ifndef PLANET_H
#define PLANET_H
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
		// konstruktor
		Planet(float _x, float _y, float _v_x, float _v_y, float _mass, float _density);
		// funkcja aktualizująca położenie planety
		void updatePos();
};
#endif

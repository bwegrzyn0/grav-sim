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
		// konstruktor
		Planet(float x, float y, float v_x, float v_y);
		// funkcja aktualizująca położenie planety
		void updatePos();
};
#endif

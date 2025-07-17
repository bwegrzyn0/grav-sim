#include "planet.h"
#include "handler.h"
#include <vector>

// funkcja aktualizująca wszystkie planety
void updatePlanets(float delta) {
	// pętla for each tutaj nie zadziała!
	// tworzy ona NOWE obiekty Planet i zmienia ICH parametry pozostawiając obiekty w wektorze planets nienaruszonymi
	for (int i = 0; i < planets.size(); i++) {
		planets.at(i).updatePos(planets, delta);	
	}
}


#include "planet.h"
#include "handler.h"
#include <vector>

void updatePlanets() {
	// a for each loop won't cut it here
	// it creates NEW objects of type Planet and updates THEIR positions
	for (int i = 0; i < planets.size(); i++) {
		planets.at(i).updatePos(planets);	
	}
}


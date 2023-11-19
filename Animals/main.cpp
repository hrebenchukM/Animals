#include <iostream>
using namespace std;
#include <string>
#include "AnimalWorld.h"
#include <stdlib.h>

int main() {
	//srand(time(NULL));
	//Wolf* wolf = new Wolf();
	//Lion* lion = new Lion();
	//Bison* bison = new Bison();
	//Wildebeest* gnu = new Wildebeest();
	//Population* wolfPop = new Population(wolf, 3);

	//cout << endl << wolf->toString();
	//cout << endl << lion->toString();
	//cout << endl << bison->toString();
	//cout << endl << gnu->toString();
	//cout << endl << wolfPop->toString();



//	america->getFauna(1).getAnimal()->Eat(nullptr);

	AnimalWorld* aworld = new AnimalWorld();
	aworld->initContinents();
	aworld->PrintContinents();
	
	for (int d = 0; d < 3; d++) {
		aworld->passDay();
	}

}
#include "StartingPhase.h"

int main()
{
	StartingPhase* startingPhase = new StartingPhase();
	startingPhase->startGame();

	delete startingPhase;
	startingPhase = nullptr;
	
	return 0;
}
#include <iostream>
#include "Player.h"

int main() {
	// Create player pointers
	Player* p1 = new Player("player1");
	Player* p2 = new Player("player2");
	Player* p3 = new Player("player3");
	Player* p4 = new Player("player4");

	p1->PayCoin(2);
	p2->PayCoin(0);
	p3->PayCoin(9);
	p4->PayCoin(-5);
}
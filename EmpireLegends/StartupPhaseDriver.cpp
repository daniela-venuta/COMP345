#include "Cards.h";
#include "Player.h"

using namespace std;

int main()
{
	// vars needed for players
	vector<Player*> players;
	string colour;
	string username;

	// set up cards
	Card* cardOne = new Card("Dire dragon", "", "Place 3 armies and destroy one army");
	Card* cardTwo = new Card("Dire giant", "Immune to attack", "Place 3 armies and destroy army");
	Card* cardThree = new Card("Dire eye", "", "Place 4 armies");
	Card* cardFour = new Card("Dire Ogre", " +1 VP per 3 coins", "Move 2 armies");
	Card* cardFive = new Card("Lake", " +1 VP per Forest card", "Place 2 armies and move 3 armies");
	Card* cardSix = new Card("Noble Hills", " Three noble cards = 4 VP", "Place 3 armies");

	// add Cards to a vector
	vector<Card*> cardVector;
	cardVector.push_back(cardOne);
	cardVector.push_back(cardTwo);
	cardVector.push_back(cardThree);
	cardVector.push_back(cardFour);
	cardVector.push_back(cardFive);
	cardVector.push_back(cardSix);

	// Create deck and add cards (this creates a card hand as well)
	Deck* deck = new Deck(cardVector);
	cout << *deck;

	deck->shuffle();
	cout << *deck;

	// Draw cards from deck and add them to the hand
	deck->draw(6);
	cout << *deck;

	// Get players
	for (int i = 0; i < 2; i++) {
		cout << "player: ";
		cin >> username;
		
		// creates a new pointer for each player object and adds it to the player vector
		players.push_back(new Player(username, 14));
	}

	// select colours
	for (int i = 0; i < 2; i++)
	{
		const Player* player = players[i];
		Resources* resources = players[i]->getResources();
		
		cout << player->getName() << "choose your colour: ";
		cin >> colour;

		
		Colour col = Resources::parseColour(colour);
		resources->playerColour = col;
	}

	// 
	
	return 0;
}
#include "Player.h"
#include "BiddingFacility.h"
#include <string>

class GameStart
{
public:
	GameStart();
	~GameStart();

	GameMap* loadMap();
	int detPlayerCount();
	
	vector<Player*> getPlayers();
	
private:
	//int typeMap;
	//int numOfPlayers;
	vector<Player*> players;
	//vector<Player*> biddingPlayers;
};
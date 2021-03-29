#include "Player.h"
#include "BiddingFacility.h"
#include <string>

class GameStart
{
public:
	GameStart();
	~GameStart();

	void loadMap();
	void detPlayerCount();

private:
	int mapType;
	int numOfPlayers;
	vector<Player*> players;
	vector<Player*> biddingPlayers;
};
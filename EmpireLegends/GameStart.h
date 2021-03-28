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
	void playerBidding();

private:
	int mapType;
	int numOfPlayers;
	vector<Player*> players;
	BiddingFacility* biddingFacility;
	vector<Player*> biddingPlayers;
};
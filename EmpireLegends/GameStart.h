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
	Player* p1, * p2, * p3, * p4;
	string playerName1, playerName2, playerName3, playerName4;
	BiddingFacility* biddingFacility;
	vector<Player*> biddingPlayers;
};
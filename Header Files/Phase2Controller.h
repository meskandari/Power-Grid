#pragma once

#include "Controller.h"
#include "View.h"
#include "Phase2View.h"
#include "FactoryMarketView.h"
#include "AuctionView.h"
#include "PlayerFactoriesView.h"

class Phase2Controller : public Controller {
public:
	Phase2Controller();
	~Phase2Controller();
	void onClick(int _x, int _y);
	void onLoad();
	void onUnload();
	bool phasedEnded();
private:
	bool endOfPhase;
	Phase2View* phase2view;
	FactoryMarketView* facMarketView;
	AuctionView* auctionView;
	PlayerFactoriesView* playerFactoriesView;

	bool turnEnded[6];
	bool skipped[6];
	int currentPlayer;
	int currentBidder;
	int biddingFactory;
	int state;
	int winningBid;
	int nextBid;
	int currentWinner;
	bool step3drawn;

	void selectFactory(int index);
	void buy();
	void bid();
	void skip();
	void endTurn();
	void increaseBid();
	void decreaseBid();
	void exchangeFactory(int index);
	bool nextBidder();
	bool lastBidder();
	void winBid();
	void restockMarket();
	void endPhase();

};
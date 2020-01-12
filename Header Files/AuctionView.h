#pragma once

#include "View.h"
#include "Graphic.h"
#include "Text.h"
#include "Picture.h"
#include "Player.h"
#include "FactoryCard.h"

class AuctionView : public View {
public:
	AuctionView();
	~AuctionView();
	void update();
	void setFactory(FactoryCard* _factory);
	void setWinner(Player* player);
	void setCurrentBid(int bid);
	void setNextBid(int bid);
	int buttonClicked(int _x, int _y);
	void previewMode();
	void auctionMode();
private:
	FactoryCard* factory;
	Player* currentWinner;
	Text* winnerText;
	Text* currentBid;
	Text* nextBid;
	Picture* factoryPicture;
	Picture* increaseButton;
	Picture* decreaseButton;
	Picture* bidButton;
	Picture* skipButton;
};
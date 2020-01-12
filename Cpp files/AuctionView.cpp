#include "View.h"
#include "Graphic.h"
#include "Text.h"
#include "Picture.h"
#include "AuctionView.h"
#include "Player.h"
#include <vector>

// Auction View. Displays the current card being bid on, and allows players to bid higher. Also serves as Preview.
AuctionView::AuctionView() {
	factory = nullptr;
	currentWinner = nullptr;

	winnerText = new Text("winnerText", "Current winner: Placeholder", 20, 20);
	currentBid = new Text("currentBid", "Winning bid: 20 Elektro", 20, 55);
	nextBid = new Text("nextBid", "100 Elektro", 115, 460);
	increaseButton = new Picture("increase", "image\\UpArrow.png", 117, 440);
	decreaseButton = new Picture("decrease", "image\\DownArrow.png", 117, 500);
	bidButton = new Picture("bidButton", "image\\BidButton.png", 20, 450);
	skipButton = new Picture("skipButton", "image\\SkipButton.png", 230, 450);
	factoryPicture = new Picture("factory", "image\\3.png", 20, 100, 0.38);

	add_graphic(winnerText);
	add_graphic(currentBid);
	add_graphic(nextBid);
	add_graphic(increaseButton);
	add_graphic(decreaseButton);
	add_graphic(bidButton);
	add_graphic(skipButton);
	add_graphic(factoryPicture);
}

AuctionView::~AuctionView() {}

void AuctionView::update() {
	
}

// Sets the Factory which is bid on.
void AuctionView::setFactory(FactoryCard* _factory) {
	factory = _factory;
	if (factory != nullptr) {
		factoryPicture->changePicture("image\\" + std::to_string(factory->get_value()) + ".png");
	}
	else {
		factoryPicture->changePicture("");
	}
}

// Sets the current winner.
void AuctionView::setWinner(Player* player) {
	currentWinner = player;
	winnerText->set_text("Current winner: " + player->get_name());
}

// Sets the current winning bid.
void AuctionView::setCurrentBid(int bid) {
	currentBid->set_text("Winning bid: " + std::to_string(bid) + " Elektro");
}

// Sets the bid the current bidder wants to give.
void AuctionView::setNextBid(int bid) {
	nextBid->set_text(std::to_string(bid) + " Elektro");
}

// Returns a code for the button clicked. -1 = Nothing was clicked, 1 = Increase bid, 2 = Decrease bid, 3 = Bid, 4 = Skip.
int AuctionView::buttonClicked(int _x, int _y) {
	if (increaseButton->wasClicked(_x, _y)) {
		return 1;
	}
	else if (decreaseButton->wasClicked(_x, _y)) {
		return 2;
	}
	else if (bidButton->wasClicked(_x, _y)) {
		return 3;
	}
	else if (skipButton->wasClicked(_x, _y)) {
		return 4;
	}
	else {
		return -1;
	}
}

void AuctionView::previewMode() {
	winnerText->hide();
	currentBid->hide();
	increaseButton->hide();
	decreaseButton->hide();
	bidButton->hide();
	skipButton->hide();
}

void AuctionView::auctionMode() {
	winnerText->show();
	currentBid->show();
	increaseButton->show();
	decreaseButton->show();
	bidButton->show();
	skipButton->show();
}
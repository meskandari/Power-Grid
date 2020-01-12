#include "Phase2Controller.h"
#include "FactoryMarketView.h"
#include "Phase2View.h"
#include "PlayerFactoriesView.h"
#include "AuctionView.h"
#include "Model.h"
#include "Player.h"
#include <iostream>

// Called on game launch. Initializes all of its views and phase-specific variables.
Phase2Controller::Phase2Controller() :Controller() {

	endOfPhase = false;
	facMarketView = new FactoryMarketView();
	facMarketView->set_pos(100, 370);
	phase2view = new Phase2View();
	playerFactoriesView = new PlayerFactoriesView();
	playerFactoriesView->move(50, 170);
	auctionView = new AuctionView();
	auctionView->move(800, 100);

	for (int i = 0; i < 6; i++) {
		turnEnded[i] = false;
		skipped[i] = false;
	}
	biddingFactory = -1;
	state = 0;
	winningBid = 0;
	nextBid = 0;
	currentWinner = -1;
	currentPlayer = 0;
	currentBidder = 0;
	step3drawn = false;

	facMarketView->hide();
	phase2view->hide();
	playerFactoriesView->hide();
	auctionView->hide();
}

Phase2Controller::~Phase2Controller() {}

// Handles Click events. What is clickable depends on the current state of the Controller.
void Phase2Controller::onClick(int _x, int _y) {
	if (state == 0) { // Case: Choosing which factory to buy.
		int factory = facMarketView->factoryClicked(_x, _y);
		if (factory >= 0) selectFactory(factory);
		else if (phase2view->buyClicked(_x, _y)) {
			buy();
		}
		else if (phase2view->endTurnClicked(_x, _y)) {
			endTurn();
		}
	}
	else if (state == 1) { // Case: Auctioning the Factory.
		int button = auctionView->buttonClicked(_x, _y);
		if (button == -1) {
			return;
		}
		else if (button == 1) {
			increaseBid();
		}
		else if (button == 2) {
			decreaseBid();
		}
		else if (button == 3) {
			bid();
		}
		else if (button == 4) {
			skip();
		}
	}
	else if (state == 2) { // Case: Auction won, but needs to discard a Factory.
		int factory = playerFactoriesView->factoryClicked(_x, _y);
		if (factory >= 0) {
			exchangeFactory(factory);
		}
	}
}

// When becoming the active Controller. Shows and updates its Views, then reinitializes phase-specific variables.
void Phase2Controller::onLoad() {
	Model::set_currentPlayer(0);
	facMarketView->show();
	facMarketView->findAndAttach();
	phase2view->show();
	phase2view->findAndAttach();
	phase2view->showButtons();
	playerFactoriesView->show();
	playerFactoriesView->set_player(Model::get_currentPlayer());
	auctionView->hide();

	for (int i = 0; i < 6; i++) {
		turnEnded[i] = false;
		skipped[i] = false;
	}
	biddingFactory = -1;
	state = 0;
	phase2view->setBottomMessage("Select the Power Plant you want to buy. An auction with start with their value as minimum price.");
	winningBid = 0;
	nextBid = 0;
	currentWinner = -1;
	currentPlayer = 0;
	currentBidder = 0;
	step3drawn = false;

}

// Hides its views and declares the next phase.
void Phase2Controller::onUnload() {
	endOfPhase = false;
	facMarketView->hide();
	phase2view->hide();
	playerFactoriesView->hide();
	auctionView->hide();
	Model::set_phase(3);
}

// Tells the driver that it is ready to move on to the next phase.
bool Phase2Controller::phasedEnded() {
	return endOfPhase;
}

// Select a Factory to view. 
void Phase2Controller::selectFactory(int index) {
	FactoryMarket* facMarket = Model::get_factoryMarket();
	FactoryCard* factory = facMarket->getFactory(index);
	if (facMarket->canBuy(factory->get_value())) {
		auctionView->previewMode();
		auctionView->show();
		auctionView->setFactory(factory);
		biddingFactory = index;
		nextBid = factory->get_value();
		auctionView->setNextBid(nextBid);
	}
}

// Starts an auction with the selected Factory Card.
void Phase2Controller::buy() {
	if (biddingFactory == -1) { // No factory selected.
		return;
	}
	if (Model::get_currentPlayer()->get_money() >= nextBid) {
		phase2view->hideButtons();
		state = 1;
		phase2view->setBottomMessage("The Auction has started! Bid higher if you want the Factory Card for yourself.");
		winningBid = nextBid;
		currentWinner = currentBidder = currentPlayer;
		auctionView->setWinner(Model::get_currentPlayer());
		if (!lastBidder()) { // Case: at least one other player can bid against the buyer.
			nextBid++;
			auctionView->setCurrentBid(winningBid);
			auctionView->setNextBid(nextBid);
			nextBidder();
			playerFactoriesView->set_player(Model::get_currentPlayer());
			auctionView->auctionMode();
		}
		else { // Case: last player to purchase a Factory Plant
			winBid();
		}
	}
}

// Validates the current bid and become the current Winner.
void Phase2Controller::bid() {
	if (Model::get_currentPlayer()->get_money() >= nextBid) {
		winningBid = nextBid;
		nextBid++;
		currentWinner = currentBidder;
		auctionView->setCurrentBid(winningBid);
		auctionView->setWinner(Model::get_currentPlayer());
		auctionView->setNextBid(nextBid);
		nextBidder();
		playerFactoriesView->set_player(Model::get_currentPlayer());
	}
}

// Skip from the Auction. The bidding player is no longer able to bid on that Factory Card.
void Phase2Controller::skip() {
	skipped[currentBidder] = true;
	if (nextBidder() && !lastBidder()) {
		playerFactoriesView->set_player(Model::get_currentPlayer());
	}
	else {
		winBid();
	}
}

// Ends the turn and move on to the next player that hasn't bought a Factory.
void Phase2Controller::endTurn() {
	if (Model::get_currentPlayer()->getHighestValueFactory() == 0) { // Force a player to buy a first factory.
		return;
	}

	turnEnded[currentPlayer] = skipped[currentPlayer] = true;
	while (turnEnded[currentPlayer]) {
		if (Model::next_player()) {
			currentPlayer++;
		}
		else {
			endPhase();
			return;
		}
	}
	playerFactoriesView->set_player(Model::get_currentPlayer());
}

// Increases the bid, up to a maximum of the current bidder's money.
void Phase2Controller::increaseBid() {
	if (nextBid + 1 <= Model::get_currentPlayer()->get_money()) {
		nextBid++;
		auctionView->setNextBid(nextBid);
	}
}

// Decreases the bid, up to a minimum of the winning bid + 1.
void Phase2Controller::decreaseBid() {
	if (nextBid - 1 > winningBid) {
		nextBid--;
		auctionView->setNextBid(nextBid);
	}
}

// Exchanges the won factory with the selected factory.
void Phase2Controller::exchangeFactory(int index) {
	// Setting up accesses to Model and delete the factory card.
	Player* player = Model::get_currentPlayer();
	FactoryCard* factory = player->getFactories()[index];
	std::vector<Resource*> resources = factory->get_stock();
	player->removeFactory(factory->get_value());
	delete factory;
	factory = nullptr;

	// Add the won Factory to the player and update the market.
	FactoryMarket* facMarket = Model::get_factoryMarket();
	player->addFactory(facMarket->removeFactory(facMarket->getFactory(biddingFactory)->get_value()));
	restockMarket();

	// Get a list of the resources to attempt transferring.
	int resourceCounts[4] = { 0, 0, 0, 0 };
	for (int i = 0; i < resources.size(); i++) {
		if (resources[i] != nullptr) {
			resourceCounts[resources[i]->get_type()]++;
		}
	}


	// Transfer as many resources as possible to other cards.
	std::vector<FactoryCard*> factories = player->getFactories();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < factories.size() && resourceCounts[i] > 0; j++) {
			if (player->getFactories()[j] == nullptr) {
				continue;
			}
			resourceCounts[i] = resourceCounts[i] - player->addResource(factories[j]->get_value(), i, resourceCounts[i]);
			
		}
	}

	// Return those that couldn't be transferred to the Resource Market's reserve (lost to the player).
	for (int i = 0; i < 4; i++) {
		Model::get_resourceMarket()->addToReserve(i, resourceCounts[i]);
	}

	// Return turn to the player that started the bid, then skip if he was the winner.
	state = 0;
	phase2view->setBottomMessage("Select the Power Plant you want to buy. An auction with start with their value as minimum price.");
	phase2view->showButtons();
	Model::set_currentPlayer(currentPlayer);
	if (turnEnded[currentPlayer]) {
		endTurn();
	}
	else {
		auctionView->hide();
		playerFactoriesView->set_player(Model::get_currentPlayer());
	}

}

// Switches to the next available bidder. If there is only one bidder remaining, returns false, else returns true.
bool Phase2Controller::nextBidder() {
	int initiateBidder = currentBidder;
	do {
		if (Model::next_player()) {
			currentBidder++;
		}
		else {
			Model::set_currentPlayer(0);
			currentBidder = 0;
		}
		if (!turnEnded[currentBidder] && !skipped[currentBidder]) {
			return true;
		}
	} while (initiateBidder != currentBidder);
	return false;
}

// Returns true if there is only one remaining bidder.
bool Phase2Controller::lastBidder() {
	int nonSkipped = 0;
	for (int i = 0; i < Model::get_playerCount(); i++) {
		if (!skipped[i]) {
			nonSkipped++;
			if (nonSkipped > 1) {
				return false;
			}
		}
	}
	return true;
}

// Either sends the Factory Card directly to the player, or changes phase to allow the player to choose which Factory Card to discard.
void Phase2Controller::winBid() {
	// Returns turn to the player that won.
	Model::set_currentPlayer(currentWinner);
	turnEnded[currentWinner] = true;
	for (int i = 0; i < 6; i++) {
		skipped[i] = turnEnded[i];
	}
	
	// Spend the money.
	Model::get_currentPlayer()->spendMoney(winningBid);


	if (Model::get_currentPlayer()->factoriesFull()) { // Case: Factories full, let the player choose which factory to discard.
		auctionView->previewMode();
		state = 2;
		phase2view->setBottomMessage("Your factories are full. Select which Factory you wish to Discard. Resources will automatically be transferred");
		playerFactoriesView->set_player(Model::get_currentPlayer());
	}
	else { // Case: Still has space, buy directly.
		FactoryCard* wonFactory = Model::get_factoryMarket()->getFactory(biddingFactory);
		Model::get_currentPlayer()->addFactory(wonFactory);
		Model::get_factoryMarket()->removeFactory(wonFactory->get_value());

		restockMarket();

		state = 0;
		phase2view->setBottomMessage("Select the Power Plant you want to buy. An auction with start with their value as minimum price.");
		auctionView->previewMode();
		phase2view->showButtons();
		Model::set_currentPlayer(currentPlayer);
		if (turnEnded[currentPlayer]) {
			endTurn();
		}
		else {
			auctionView->hide();
			playerFactoriesView->set_player(Model::get_currentPlayer());
		}
	}
	
}

// Draw a Factory Card and adds it to the Market. Different behavior if the deck is empty or Step3 Card is drawn.
void Phase2Controller::restockMarket() {
	Card* card = Model::get_deck()->pull();
	
	if (card == nullptr) { // Case: Empty deck
		return;
	}
	else if (card->get_type() == "Step 3") { // Case: Step3 card was drawn. Effects applied at end of phase.
		step3drawn = true;
		delete card;
		card = nullptr;
	}
	else { // Case: Normal card drawn.
		Model::get_factoryMarket()->addFactory((FactoryCard*)card);
		card = nullptr;
	}

}

void Phase2Controller::endPhase() {
	if (step3drawn) {
		Model::set_step(3);
		Model::get_factoryMarket()->removeIndex(0);
		Model::get_factoryMarket()->setStep(3);
	}

	endOfPhase = true;
}
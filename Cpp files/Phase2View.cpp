#include "View.h"
#include "Graphic.h"
#include "Text.h"
#include "Picture.h"
#include "Phase2View.h"
#include "Model.h"
#include "Player.h"
#include <vector>

Phase2View::Phase2View() {
	add_graphic(new Text("phase2Title", "Phase 2: Auction Power Plants", 120, 20, 50));
	bottomMessage = new Text("instruction", "Select the Power Plant you want to buy. An auction with start with their value as minimum price.", 250, 650);
	add_graphic(bottomMessage);

	playerName = new Text("playerText", "Placeholder's turn", 470, 80, 35);
	endTurnButton = new Picture("endTurnButton", "image\\EndTurnButton.png", 650, 530);
	buyButton = new Picture("buyButton", "image\\BuyButton.png", 670, 430);
	playerHouses = new Text("playerHouses", "Player has 10 houses", 180, 120);
	playerElektro = new Text("playerHouses", "Player has 100 Elektro", 410, 120);
	strategyText = new Text("strategyText", "Placeholder strategy epsio lisum or whatever it was.", 635, 50, 20);

	add_graphic(buyButton);
	add_graphic(endTurnButton);
	add_graphic(playerName);
	add_graphic(playerHouses);
	add_graphic(playerElektro);
	add_graphic(strategyText);

	add_graphic(new Text("strategyHeader", "Strategy:", 700, 20));

	player = nullptr;
}

Phase2View::~Phase2View() {}

void Phase2View::update() {
	if (player != Model::get_currentPlayer()) {
		if (player != nullptr) player->detach(this);
		player = Model::get_currentPlayer();
		player->attach(this);
	}
	playerName->set_text(player->get_name() + "'s turn");
	playerHouses->set_text("Player has " + std::to_string(player->getHousesOwned()) + " houses");
	playerElektro->set_text("Player has " + std::to_string(player->get_money()) + " Elektro");
	strategyText->set_text(player->executeStrategy(2,
		Model::get_factoryMarket()->getBuyableFactories(), player->getFactories()));
}

bool Phase2View::buyClicked(int _x, int _y) {
	return buyButton->wasClicked(_x, _y);
}

bool Phase2View::endTurnClicked(int _x, int _y) {
	return endTurnButton->wasClicked(_x, _y);
}

void Phase2View::hideButtons() {
	endTurnButton->hide();
	buyButton->hide();
}

void Phase2View::showButtons() {
	endTurnButton->show();
	buyButton->show();
}

void Phase2View::setBottomMessage(std::string message) {
	bottomMessage->set_text(message);
}

void Phase2View::setStrategy(std::string strategy) {
	strategyText->set_text(strategy);
}

void Phase2View::findAndAttach() {
	if (Model::attachToModel(this)) {
		update();
	}
}
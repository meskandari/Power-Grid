#include "View.h"
#include "Graphic.h"
#include "Text.h"
#include "Picture.h"
#include "Phase3View.h"
#include "FactoryCard.h"
#include "Resource.h"
#include "Model.h"
#include "Player.h"
#include <vector>
#include <iostream>

// Creates the view. This View displays all information specific for the functionning of Phase 3.
Phase3View::Phase3View() {
	selectedResource = new Picture("resSelect", "image\\ResourceSelect.png", 443, 173);
	add_graphic(selectedResource);
	endTurnButton = new Picture();
	for (int i = 0; i < 4; i++) {
		resButtons[i] = new Picture(Resource::codeToName(i) + "button", "image\\" + Resource::codeToName(i) + ".png", 450 + i * 50, 180, 0.5);
		add_graphic(resButtons[i]);
	}
	
	countText = new Text("countText", "Buying:  0", 450, 270);
	priceText = new Text("priceText", ": 100 Elektro", 550, 270);
	curPlayer = new Text("playerText", "Placeholder's turn", 440, 100, 40);
	increaseButton = new Picture("increaseButton", "image\\UpArrow.png", 520, 250);
	decreaseButton = new Picture("decreaseButton", "image\\DownArrow.png", 520, 310);
	endTurnButton = new Picture("endTurnButton", "image\\EndTurnButton.png", 530, 350);
	buyButton = new Picture("buyButton", "image\\BuyButton.png", 675, 260);
	curElektroText = new Text("elektroText", "Player has 50 Elektro", 100, 325);
	curHousesText = new Text("houseText", "Player has 5 houses", 100, 375);
	add_graphic(countText);
	add_graphic(priceText);
	add_graphic(curPlayer);
	add_graphic(increaseButton);
	add_graphic(decreaseButton);
	add_graphic(endTurnButton);
	add_graphic(buyButton);
	add_graphic(curElektroText);
	add_graphic(curHousesText);
	add_graphic(new Text("phase3Title", "Phase 3: Resource Buying", 360, 20, 50));
	add_graphic(new Text("instruction", "Purchase the resources you want, then press End Turn.", 300, 650));
}

Phase3View::~Phase3View() {}

// Updates all the information according to the current player.
void Phase3View::update() {
	curPlayer->set_text(player->get_name() + "'s turn");
	curElektroText->set_text("Player has " + std::to_string(player->get_money()) + " Elektro");
	curHousesText->set_text("Player has " + std::to_string(player->getHousesOwned()) + " houses");
	std::cout << player->executeStrategy(3,
		Model::get_factoryMarket()->getBuyableFactories(), player->getFactories()) << "\n";
}

// Unused.
void Phase3View::set_player(Player* _player) {
	if (player != nullptr) player->detach(this);
	player = _player;
	player->attach(this);
	update();
}

// Sets the price for the player's intended purchase. 
void Phase3View::set_price(int price) {
	priceText->set_text(": " + std::to_string(price) + " Elektro");
}

// Sets the amount for the player's intended purchase.
void Phase3View::set_count(int count) {
	countText->set_text("Buying:  " + std::to_string(count));
}

// Sets the resource type for the player's intended purchase.
void Phase3View::set_currentResource(int type) {
	selectedResource->set_pos(443 + x + type * 50, 173 + y);
}

// Returns a code for the button clicked. -1 = Nothing, 0-3 = Resource choice, 
// 4 = Increase count, 5 = Decrease count, 6 = End turn, 7 = Purchase.
int Phase3View::buttonClicked(int _x, int _y) {
	for (int i = 0; i < 4; i++) {
		if (resButtons[i]->wasClicked(_x, _y)) {
			return i;
		}
	}
	if (increaseButton->wasClicked(_x, _y)) {
		return 4;
	}
	if (decreaseButton->wasClicked(_x, _y)) {
		return 5;
	}
	if (endTurnButton->wasClicked(_x, _y)) {
		return 6;
	}
	if (buyButton->wasClicked(_x, _y)) {
		return 7;
	}
	return -1;
}
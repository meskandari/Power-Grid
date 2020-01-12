#include "View.h"
#include "Graphic.h"
#include "Text.h"
#include "Picture.h"
#include "PlayerInfoView.h"
#include "FactoryCard.h"
#include "Resource.h"
#include "Model.h"
#include "Player.h"
#include <vector>
#include <iostream>

PlayerInfoView::PlayerInfoView() {
	player = nullptr;
	playerName = new Text("pinfoName", "Placeholder", 50, 0);
	playerElektro = new Text("pinfoElektro", "100 Elektro", 160, 80);
	playerHouse = new Text("pinfoHouse", "10 Houses", 160, 120);
	playerColor = new Picture("pinfoColor", "image\\Red.png", 0, 0, 0.35);

	add_graphic(playerName);
	add_graphic(playerElektro);
	add_graphic(playerHouse);
	add_graphic(playerColor);

	for (int i = 0; i < 4; i++) {
		factories[i] = new Picture("PlayerFactory" + std::to_string(i),
			"image\\3.png", (i%2) * 80, 40 + (int)(i/2)*80, 0.09);
		add_graphic(factories[i]);
		for (int j = 0; j < 6; j++) {
			resources[i][j] = new Picture("info" + std::to_string(i) + "Res" + std::to_string(j), "image\\Coal.png", 
				(i % 2) * 80 + (j % 3) * 20 + 8, 
				36 + (int)(i / 2) * 80 + (int)(j / 3) * 20 + 20, 0.2);
			add_graphic(resources[i][j]);
			resources[i][j]->hide();
		}
	}
	update();
}

PlayerInfoView::~PlayerInfoView() {}

void PlayerInfoView::set_player(Player* _player) {
	if (_player == nullptr) return;
	player = _player;
	player->attach(this);
	update();
}

void PlayerInfoView::update() {
	if (player == nullptr) {
		playerName->set_text("");
		playerElektro->set_text("");
		playerHouse->set_text("");
		playerColor->changePicture("");
		for (int i = 0; i < 4; i++) {
			factories[i]->changePicture("");
			for (int j = 0; j < 6; j++) {
				resources[i][j]->changePicture("");
			}
		}
		return;
	}

	playerName->set_text(player->get_name());
	playerElektro->set_text(std::to_string(player->get_money()) + " Elektro");
	playerHouse->set_text(std::to_string(player->getHousesOwned()) + " Houses");
	playerColor->changePicture("image\\" + player->get_color() + ".png");

	std::vector<FactoryCard*> curFactories = player->getFactories();
	for (int i = 0; i < 4; i++) {
		if (i < curFactories.size() && curFactories[i] != nullptr) {
			factories[i]->changePicture("image\\" + std::to_string(curFactories[i]->get_value()) + ".png");
			std::vector<Resource*> curResources = curFactories[i]->get_stock();
			for (int j = 0; j < 6; j++) {
				resources[i][j]->hide();
			}
			for (int j = 0; j < curResources.size(); j++) {
				int pos = j; // pos = display position. This differs according to the capacity of the factory.
				if (pos >= curFactories[i]->get_cost()) {
					pos = pos + 3 - curFactories[i]->get_cost();
				}
				if (curResources[j] != nullptr) {

					resources[i][pos]->changePicture("image\\" + Resource::codeToName(curResources[j]->get_type()) + ".png");
					resources[i][pos]->show();
				}
			}

		}
		else {
			factories[i]->changePicture("");
			for (int j = 0; j < 6; j++) {
				resources[i][j]->changePicture("");
			}
		}
	}
}

bool PlayerInfoView::isSet() {
	return player != nullptr;
}
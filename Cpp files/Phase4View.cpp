#pragma once

#include "View.h"
#include "Graphic.h"
#include "Text.h"
#include "Picture.h"
#include <string>
#include "Player.h"
#include "Phase4View.h"
#include "Model.h"
#include "Mymap.h"
#include <iostream>

Phase4View::Phase4View() {
	add_graphic(new Picture("map", "image\\Map.png", 0, 0));
	add_graphic(new Text("phase4Title", "Phase 4: Building", 850, 20, 50));
	add_graphic(new Text("instruction", "Select and buy cities, then end your turn.", 50, 610));

	buyButton = new Picture("buyButton", "image\\BuyButton.png", 215, 550);
	endTurnButton = new Picture("endTurnButton", "image\\EndTurnButton.png", 70, 550);
	for (int i = 0; i < 42; i++) {
		cities[i] = new Picture("city" + std::to_string(i), "image\\CityBox.png", cityCoords[i][0] - 23, cityCoords[i][1] - 23);
		add_graphic(cities[i]);
		for (int j = 0; j < 3; j++) {
			houses[i][j] = new Picture("house" + std::to_string(i) + "_" + std::to_string(j), "image\\Red.png",
				cityCoords[i][0] - 26 + ((j * 2 + 1) % 3) * 15,
				cityCoords[i][1] - 26 + (int)((j * 2 + 1) / 3) * 20, 0.25);
			add_graphic(houses[i][j]);
		}
	}

	cityName = new Text("cityName", "Washington", 330, 540);
	cost = new Text("cityCost", "35 Elektro", 330, 570);
	playerName = new Text("playerName", "Placeholder's turn", 870, 80, 40);
	add_graphic(buyButton);
	add_graphic(endTurnButton);
	add_graphic(cityName);
	add_graphic(cost);
	add_graphic(playerName);

}

Phase4View::~Phase4View() {}

void Phase4View::update() {
	for (int i = 0; i < 42; i++) {
		const std::string* owners = map->getOwners(cityNames[i]);
		for (int j = 0; j < 3; j++) {
			if (owners[j] == "") {
				houses[i][j]->changePicture("");
			}
			else {
				houses[i][j]->changePicture("image\\" + owners[j] + ".png");
				houses[i][j]->show();
			}
		}
	}
}
bool Phase4View::buyButtonClicked(int _x, int _y) {
	return buyButton->wasClicked(_x, _y);
}

bool Phase4View::endTurnButtonClicked(int _x, int _y) {
	return endTurnButton->wasClicked(_x, _y);
}

std::string Phase4View::cityClicked(int _x, int _y) {
	for (int i = 0; i < 42; i++) {
		if (cities[i]->wasClicked(_x, _y)) {
			return cityNames[i];
		}
	}
	return "";
}

void Phase4View::set_city(std::string name, int _cost) {
	cityName->set_text(name);
	cost->set_text(std::to_string(_cost) + " Elektro");
}

void Phase4View::findAndAttach() {
	if (Model::isInstanciated()) {
		map = Model::get_map();
		map->attach(this);
		update();
	}
}

void Phase4View::set_playerName(std::string name) {
	playerName->set_text(name + "'s turn");
}
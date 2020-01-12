#pragma once

#include "View.h"
#include "Graphic.h"
#include "Text.h"
#include "Picture.h"
#include <string>
#include "Player.h"
#include "MinimapView.h"
#include "Model.h"

MinimapView::MinimapView() {
	add_graphic(new Picture("map", "image\\Map.png", 0, 0, 0.5));

	for (int i = 0; i < 42; i++) {
		for (int j = 0; j < 3; j++) {
			houses[i][j] = new Picture("house" + std::to_string(i) + "_" + std::to_string(j), "image\\Red.png",
				(cityCoords[i][0] - 26 + ((j * 2 + 1) % 3) * 15)/2,
				(cityCoords[i][1] - 26 + (int)((j * 2 + 1) / 3) * 20)/2, 0.13);
			add_graphic(houses[i][j]);
		}
	}

	map = nullptr;
}

MinimapView::~MinimapView() {}

void MinimapView::update() {
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

void MinimapView::findAndAttach() {
	if (Model::isInstanciated()) {
		map = Model::get_map();
		if (map != nullptr) {
			map->attach(this);
			update();
		}
	}
}
#include "View.h"
#include "Graphic.h"
#include "Text.h"
#include "Picture.h"
#include "PlayerFactoriesView.h"
#include "FactoryCard.h"
#include "Resource.h"
#include "Model.h"
#include "Player.h"
#include <vector>
#include <iostream>

// Player Factories View. Shows the factories a player owns, as well as its resource stock.
PlayerFactoriesView::PlayerFactoriesView() {
	player = nullptr;
	for (int i = 0; i < 4; i++) {
		factories[i] = new Picture("PlayerFactory" + std::to_string(i),
			"image\\3.png", i * 180, 0, 0.2);
		add_graphic(factories[i]);
		for (int j = 0; j < 6; j++) {
			resources[i][j] = new Picture("PlayerFactory" + std::to_string(i) + "Res" + std::to_string(j),
				"image\\Coal.png", i * 180 + (j % 3) * 40 + 25, (int)(j / 3) * 40 + 40, 0.4);
			add_graphic(resources[i][j]);
			resources[i][j]->hide();
		}
	}
	draggedResource = new Picture("ResDrag", "", 0, 0, 0.4);
	add_graphic(draggedResource);
	draggedResourceSlot[0] = draggedResourceSlot[1] = draggedResourceSlot[2] = -1;
	draggedResourceType = -1;
}

// Unused constructor. Setting up the player immediately caused problems.
PlayerFactoriesView::PlayerFactoriesView(Player* _player) {
	player = _player;
	for (int i = 0; i < 4; i++) {
		factories[i] = new Picture("PlayerFactory" + std::to_string(i),
									"", i * 180, 0, 0.2);
		add_graphic(factories[i]);
		for (int j = 0; j < 6; j++) {
			resources[i][j] = new Picture("PlayerFactory" + std::to_string(i) + "Res" + std::to_string(j),
				"", i * 180 + (j%3)*40 + 25, (int)(j/3)*40 + 40, 0.4);
			add_graphic(resources[i][j]);
		}
	}
	draggedResource = new Picture(player->get_name() + "ResDrag", "", 0, 0, 0.4);
	add_graphic(draggedResource);
	draggedResourceSlot[0] = draggedResourceSlot[1] = draggedResourceSlot[2] = -1;
	draggedResourceType = -1;
	update();
}

PlayerFactoriesView::~PlayerFactoriesView() {}

// Sets the player to display.
void PlayerFactoriesView::set_player(Player* _player) {
	if (player != nullptr) player->detach(this);
	player = _player;
	player->attach(this);
	update();
}

// Updates the information according to the watched player.
void PlayerFactoriesView::update() {
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
				if (!(draggedResourceSlot[0] == i && draggedResourceSlot[1] == pos) && curResources[j] != nullptr) {
					
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

// Returns the index of the factory clicked. Returns -1 if nothing was clicked.
int PlayerFactoriesView::factoryClicked(int _x, int _y) {
	for (int i = 0; i < 4; i++) {
		if (factories[i]->wasClicked(_x, _y)) {
			return i;
		}
	}
	return -1;
}

// Starts resource dragging. Stores the information of the resource.
bool PlayerFactoriesView::startResourceDrag(int _x, int _y) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			if (!resources[i][j]->isHidden() && resources[i][j]->wasClicked(_x, _y)) {
				FactoryCard* factory = player->getFactories()[i];
				int pos = j;
				if (pos >= factory->get_cost()) {
					pos = pos - 3 + factory->get_cost();
				}
				int type = factory->get_stock()[pos]->get_type();
				draggedResource->changePicture("image\\" + Resource::codeToName(type) + ".png" );
				draggedResource->show();
				draggedResourceSlot[0] = i;
				draggedResourceSlot[1] = j;
				draggedResourceSlot[2] = pos;
				draggedResourceType = type;
				draggedResource->set_pos(_x, _y);
				update();
				return true;
			}
		}
	}
	return false;
}

// Keeps the dragged resource following the mouse (passed values)
void PlayerFactoriesView::updateResourceDrag(int _x, int _y) {
	draggedResource->set_pos(_x, _y);
}

// Returns the values: [Source factory index, Target factory index, Resource type code, Source resource position, upper(0) or lower(1)].
std::vector<int> PlayerFactoriesView::stopResourceDrag(int _x, int _y) {
	int facSource = draggedResourceSlot[0];
	int resSource = draggedResourceSlot[2];
	draggedResourceSlot[0] = draggedResourceSlot[1] = -1;
	update();

	std::vector<int> returnValues = { facSource, -1, draggedResourceType, resSource, -1 };
	if (draggedResource->isHidden()) {
		return returnValues;
	}
	for (int i = 0; i < 4; i++) {
		if (factories[i]->wasClicked(_x, _y)) {
			draggedResource->hide();
			returnValues[1] = i;
			if (_y < 80 + y) {
				returnValues[4] = 0;
			}
			else {
				returnValues[4] = 1;
			}
			
			return returnValues;
		}
	}
	draggedResource->hide();
	returnValues[0] = returnValues[2] = -1;
	return returnValues;
}
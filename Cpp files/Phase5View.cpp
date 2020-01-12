#pragma once

#include "View.h"
#include "Graphic.h"
#include "Text.h"
#include "Picture.h"
#include <string>
#include <algorithm>
#include "Player.h"
#include "PlayerFactoriesView.h"
#include "Phase5View.h"
#include "Model.h"

// View specific for Phase 5. Initializes its graphics.
Phase5View::Phase5View() {
	activeCities = 0;

	add_graphic(new Text("phase5Title", "Phase 5: Bureaucracy", 400, 20, 50));
	bottomText = new Text("instruction", "Select the Power Plants you want to activate.", 350, 650);
	add_graphic(bottomText);

	incomeSelect = new Picture("incomeSelect", "image\\IncomeSelect.png", 890, 51);
	add_graphic(incomeSelect);

	for (int i = 0; i < 4; i++) {
		activatedFactories[i] = new Picture("activeFactory" + std::to_string(i), "image\\FactorySelect.png", i * 180 + 61, 240);
		activateButtons[i] = new Picture("activateButton" + std::to_string(i), "image\\ActivateButton.png", i * 180 + 100, 450);
		add_graphic(activatedFactories[i]);
		add_graphic(activateButtons[i]);
		activatedFactories[i]->hide();
	}

	currentPlayer = new Text("playerText", "Placeholder's turn", 470, 80, 35);
	currentHouses = new Text("playerHouses", "0 / 10 powered cities", 300, 190);
	currentElektro = new Text("playerHouses", "Player has 100 Elektro", 300, 140);
	for (int i = 0; i < 22; i++) {
		incomeText[i] = new Text("incomeText" + std::to_string(i), 
						std::to_string(i) + " -> " + std::to_string(elektro[i]) + " Elektro", 900, 55 + 28 * i);
		add_graphic(incomeText[i]);
	}
	
	endTurnButton = new Picture("endTurnButton", "image\\EndTurnButton.png", 500, 560);

	add_graphic(currentPlayer);
	add_graphic(currentHouses);
	add_graphic(currentElektro);
	add_graphic(endTurnButton);
}

Phase5View::~Phase5View() {}

// Updates the graphics according to the Model.
void Phase5View::update() {
	Player* player = Model::get_currentPlayer();
	currentPlayer->set_text(player->get_name() + "'s turn");
	currentHouses->set_text(std::to_string(activeCities) + " / " + std::to_string(player->getHousesOwned()) + " powered cities");
	currentElektro->set_text("Player has " + std::to_string(player->get_money()) + " Elektro");
	std::vector<FactoryCard*> factories = Model::get_currentPlayer()->getFactories();
	for (int i = 0; i < 4; i++) {
		if (factories[i] == nullptr) {
			activateButtons[i]->hide();
		}
		else {
			activateButtons[i]->show();
		}
	}
}

// Returns -1 if nothing was clicked, 0-3 if Factory was clicked, 4 if End Turn button was clicked.
int Phase5View::buttonClicked(int _x, int _y) {
	if (endTurnButton->wasClicked(_x, _y)) {
		return 4;
	}
	else {
		for (int i = 0; i < 4; i++) {
			if (activateButtons[i]->wasClicked(_x, _y)) {
				return i;
			}
		}
	}
	return -1;
}

// Shows that the factory at the specified slot is activated.
void Phase5View::activateFactory(int pos) {
	activatedFactories[pos]->show();
}

// Stops showing that the factory at the specified slots is activated.
void Phase5View::deactivateFactory(int pos) {
	activatedFactories[pos]->hide();
}

// Points the reward for the amount of cities activated.
void Phase5View::set_activeCities(int count) {
	activeCities = count;
	currentHouses->set_text(std::to_string(activeCities) + " / " + std::to_string(Model::get_currentPlayer()->getHousesOwned()) + " powered cities");
	incomeSelect->set_pos(x + 890, y + 51 + 28 * std::min(std::min(21, activeCities), Model::get_currentPlayer()->getHousesOwned()));

}

// Hides or Show graphics according to the given state. State 0 = powering up Factories, State 1 = viewing market changes.
void Phase5View::set_state(int state) {
	if (state == 1) {
		for (int i = 0; i < 4; i++) {
			activatedFactories[i]->hide();
			activateButtons[i]->hide();
		}
		currentPlayer->hide();
		currentHouses->hide();
		currentElektro->hide();
		for (int i = 0; i < 22; i++) {
			incomeText[i]->hide();
		}
		bottomText->set_text("The Resource and Factory markets have been updated.");
		incomeSelect->hide();
		endTurnButton->changePicture("image\\ContinueButton.png");
	}
	else if (state == 0) {
		for (int i = 0; i < 4; i++) {
			activateButtons[i]->show();
		}
		currentPlayer->show();
		currentHouses->show();
		currentElektro->show();
		for (int i = 0; i < 22; i++) {
			incomeText[i]->show();
		}
		bottomText->set_text("Select the Power Plants you want to activate.");
		incomeSelect->show();
		endTurnButton->changePicture("image\\EndTurnButton.png");
	}
}

void Phase5View::findAndAttach() {
	if (Model::attachToModel(this)) {
		update();
	}
}
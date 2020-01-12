#pragma once

#include "View.h"
#include "Graphic.h"
#include "Text.h"
#include "Picture.h"
#include <string>
#include "Player.h"
#include "StartView.h"

StartView::StartView() {
	add_graphic(new Text("startTitle", "POWER GRID", 410, 20, 100));
	instructionText = new Text("instruction", "", 450, 650);
	add_graphic(instructionText);

	newGame = new Picture("newGameButton", "image\\NewGameButton.png", 550, 300);
	loadGame = new Picture("loadGameButton", "image\\LoadGameButton.png", 550, 400);
	continueButton = new Picture("continueButton", "image\\Continuebutton.png", 550, 570);
	add_graphic(newGame);
	add_graphic(loadGame);
	add_graphic(continueButton);

	for (int i = 0; i < 6; i++) {
		colors[i] = new Picture(colorNames[i], "image\\" + colorNames[i] + ".png", 250 + 120 * i, 300);
		add_graphic(colors[i]);
		chosenColor[i] = false;

		regions[i] = new Picture(regionColors[i] + "Region", "image\\" + regionColors[regionMapping[i]] + "Region.png", 490 + (i % 3) * 80, 420 + (int)(i / 3) * 80);
		selectedRegions[i] = new Picture(regionColors[i] + "RegionSelect", "image\\ResourceSelect.png", 490 + (i % 3) * 80, 420 + (int)(i / 3) * 80);
		add_graphic(selectedRegions[i]);
		add_graphic(regions[i]);
	}

	for (int i = 0; i < 5; i++) {
		playerCount[i] = new Text("playerCount" + std::to_string(i + 2), std::to_string(i + 2), 300 + 150 * i, 300, 75);
		add_graphic(playerCount[i]);
	}

	std::string names[3] = { "Aggressive", "Moderate", "Environmentalist" };
	for (int i = 0; i < 3; i++) {
		strategyButtons[i] = new Picture("strategy" + std::to_string(i), "image\\" + names[i] + ".png", 490, 300 + i * 100);
		add_graphic(strategyButtons[i]);
	}

	mapPreview = new Picture("mapPreview", "image\\Map.png", 360, 140, 0.4);
	nameInput = new Text("nameInput", "", 300, 300, 80);
	add_graphic(mapPreview);
	add_graphic(nameInput);
	regionCount = 0;
	newGameState();
}

StartView::~StartView() {}

void StartView::update() {}

void StartView::newGameState() {
	continueButton->hide();
	instructionText->hide();
	for (int i = 0; i < 5; i++) playerCount[i]->hide();
	for (int i = 0; i < 6; i++) {
		colors[i]->hide();
		regions[i]->hide();
		selectedRegions[i]->hide();
	}
	for (int i = 0; i < 3; i++) strategyButtons[i]->hide();
	nameInput->hide();
	mapPreview->hide();

	newGame->show();
	loadGame->show();

}

bool StartView::newGameClicked(int _x, int _y) {
	return newGame->wasClicked(_x, _y);
}
bool StartView::loadGameClicked(int _x, int _y) {
	return loadGame->wasClicked(_x, _y);
}

void StartView::playerCountState() {
	continueButton->hide();
	instructionText->show();
	instructionText->set_text("Select the amount of players.");
	for (int i = 0; i < 5; i++) playerCount[i]->show();
	for (int i = 0; i < 6; i++) {
		colors[i]->hide();
		regions[i]->hide();
		selectedRegions[i]->hide();
	}
	for (int i = 0; i < 3; i++) strategyButtons[i]->hide();
	nameInput->hide();
	mapPreview->hide();

	newGame->hide();
	loadGame->hide();
}

int StartView::playerCountClicked(int _x, int _y) {
	for (int i = 0; i < 5; i++) {
		if (playerCount[i]->wasClicked(_x, _y)) {
			return i + 2;
		}
	}
	return -1;
}

void StartView::colorChoiceState() {
	continueButton->hide();
	instructionText->show();
	instructionText->set_text("Select the player's color");
	for (int i = 0; i < 5; i++) playerCount[i]->hide();
	for (int i = 0; i < 6; i++) {
		colors[i]->show();
		regions[i]->hide();
		selectedRegions[i]->hide();
	}
	for (int i = 0; i < 3; i++) strategyButtons[i]->hide();
	nameInput->hide();
	mapPreview->hide();

	newGame->hide();
	loadGame->hide();
}

std::string StartView::colorClicked(int _x, int _y) {
	for (int i = 0; i < 6; i++) {
		if (colors[i]->wasClicked(_x, _y)) {
			return colorNames[i];
		}
	}
	return "";
}

void StartView::nameInputState() {
	continueButton->show();
	instructionText->show();
	instructionText->set_text("Input the name of the player.");
	for (int i = 0; i < 5; i++) playerCount[i]->hide();
	for (int i = 0; i < 6; i++) {
		colors[i]->hide();
		regions[i]->hide();
		selectedRegions[i]->hide();
	}
	for (int i = 0; i < 3; i++) strategyButtons[i]->hide();
	nameInput->show();
	mapPreview->hide();

	newGame->hide();
	loadGame->hide();
	nameInput->set_text("");
}

void StartView::nameAppend(std::string character) {
	nameInput->append_text(character);
}

void StartView::nameBackspace() {
	std::string newName = nameInput->get_name().substr(0, nameInput->get_name().size() - 1);
	nameInput->set_text(newName);
}

std::string StartView::getName() {
	return nameInput->get_name();
}

bool StartView::continueButtonclicked(int _x, int _y) {
	return continueButton->wasClicked(_x, _y);
}

void StartView::regionChoiceState(int _regionCount) {
	continueButton->show();
	regionCount = _regionCount;
	instructionText->show();
	instructionText->set_text("Select " + std::to_string(regionCount) + " adjacent regions");
	for (int i = 0; i < 5; i++) playerCount[i]->hide();
	for (int i = 0; i < 6; i++) {
		colors[i]->hide();
		regions[i]->show();
		selectedRegions[i]->hide();
	}
	for (int i = 0; i < 3; i++) strategyButtons[i]->hide();
	nameInput->hide();
	mapPreview->show();

	newGame->hide();
	loadGame->hide();
}

int StartView::regionClicked(int _x, int _y) {
	for (int i = 0; i < 6; i++) {
		if (regions[i]->wasClicked(_x, _y)) {
			if (selectedRegions[i]->isHidden()) selectedRegions[i]->show();
			else selectedRegions[i]->hide();
			return i;
		}
	}
	return -1;
}
bool* StartView::regionConfirmClicked(int _x, int _y) {
	if (!continueButton->wasClicked(_x, _y)) return nullptr;
	bool* selection = new bool[6];
	for (int i = 0; i < 6; i++) {
		selection[regionMapping[i]] = !selectedRegions[i]->isHidden();
	}
	return selection;
}

void StartView::strategyChoiceState() {
	continueButton->hide();
	instructionText->show();
	instructionText->set_text("Select the player's strategy.");
	for (int i = 0; i < 5; i++) playerCount[i]->hide();
	for (int i = 0; i < 6; i++) {
		colors[i]->hide();
		regions[i]->hide();
		selectedRegions[i]->hide();
	}
	for (int i = 0; i < 3; i++) strategyButtons[i]->show();
	nameInput->hide();
	mapPreview->hide();

	newGame->hide();
	loadGame->hide();
	nameInput->set_text("");
}

int StartView::strategyButtonClicked(int _x, int _y) {
	for (int i = 0; i < 3; i++) {
		if (strategyButtons[i]->wasClicked(_x, _y)) {
			return i;
		}
	}
	return -1;
}
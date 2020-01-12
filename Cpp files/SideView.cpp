#include "View.h"
#include "Graphic.h"
#include "Text.h"
#include "Picture.h"
#include <string>
#include "Player.h"
#include "SideView.h"
#include "Model.h"

SideView::SideView() {
	name = "SideView";
	add_graphic(new Picture("sideBackground", "image\\SideBackground.png"));

	playersButton = new Picture("playersButton", "image\\PlayersButton.png", 1, 1);
	mapButton = new Picture("mapButton", "image\\MapButton.png", 96, 1);
	playerOrderButton = new Picture("playerOrderButton", "image\\PlayerOrderButton.png", 164, 1);
	facMarketButton = new Picture("facMarketButton", "image\\FactoryMarketButton.png", 297, 1);
	resMarketButton = new Picture("resMarketButton", "image\\ResourceMarketButton.png", 464, 1);
	stepText = new Text("stepText", "Current Step: 1", 200, 58);

	add_graphic(playersButton);
	add_graphic(mapButton);
	add_graphic(playerOrderButton);
	add_graphic(facMarketButton);
	add_graphic(resMarketButton);
	add_graphic(stepText);
}
SideView::~SideView() {}

void SideView::update() {
	stepText->set_text("Current Step: " + std::to_string(Model::get_step()));
}

int SideView::buttonClicked(int _x, int _y) {
	if (playersButton->wasClicked(_x, _y)) {
		return 1;
	}
	else if (mapButton->wasClicked(_x, _y)) {
		return 2;
	}
	else if (playerOrderButton->wasClicked(_x, _y)) {
		return 3;
	}
	else if (facMarketButton->wasClicked(_x, _y)) {
		return 4;
	}
	else if (resMarketButton->wasClicked(_x, _y)) {
		return 5;
	}
	else {
		return -1;
	}
}

void SideView::findAndAttach() {
	if (Model::isInstanciated()) {
		Model::attachToModel(this);
		update();
	}
}
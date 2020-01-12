#include "View.h"
#include "Graphic.h"
#include "Text.h"
#include "Picture.h"
#include <string>
#include "Player.h"
#include "Model.h"
#include "PlayerOrderView.h"

PlayerOrderView::PlayerOrderView() {
	for (int i = 0; i < 6; i++) {
		playerColors[i] = new Picture("color" + std::to_string(i), "image\\Red.png", 0, 60 * i, 0.6);
		playerNames[i] = new Text("name" + std::to_string(i), "Placeholder", 80, 60 * i);
		add_graphic(playerColors[i]);
		add_graphic(playerNames[i]);
	}
}
PlayerOrderView::~PlayerOrderView() {}

void PlayerOrderView::update() {
	Player** players = Model::get_players();
	int count = Model::get_playerCount();
	for (int i = 0; i < 6; i++) {
		if (i < count) {
			playerColors[i]->changePicture("image\\" + players[i]->get_color() + ".png");
			playerColors[i]->show();
			playerNames[i]->set_text(players[i]->get_name());
			playerNames[i]->show();
		}
		else {
			playerColors[i]->hide();
			playerNames[i]->hide();
		}
	}
}

void PlayerOrderView::findAndAttach() {
	if (Model::isInstanciated()) {
		Model::attachToModel(this);
		update();
	}
}
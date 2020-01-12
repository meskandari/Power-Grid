#pragma once

#include "Controller.h"
#include <vector>
#include <iostream>
#include "Model.h"
#include "Player.h"
#include "PlayerOrderView.h"
#include "ResourceMarketView.h"
#include "FactoryMarketView.h"
#include "Picture.h"
#include "SideView.h"
#include "SideController.h"
#include "PlayerInfoView.h"

SideController::SideController() {
	sideView = new SideView();
	sideView->set_pos(1200, 0);

	minimapView = new MinimapView();
	minimapView->set_pos(1200, 200);
	minimapView->hide();

	playerOrderView = new PlayerOrderView();
	playerOrderView->set_pos(1300, 200);
	playerOrderView->hide();

	resMarketView = new ResourceMarketView();
	resMarketView->set_pos(1350, 175);
	resMarketView->hide();

	facMarketView = new FactoryMarketView();
	facMarketView->set_pos(1250, 250);
	facMarketView->hide();

	for (int i = 0; i < 6; i++) {
		playerViews[i] = new PlayerInfoView();
		playerViews[i]->set_pos(1225 + (i % 2) * 280, 100 + (int)((i / 2) * 200));
		playerViews[i]->hide();
	}

	state = 0;
}
SideController::~SideController() {
	
}

void SideController::onClick(int _x, int _y) {
	if (!Model::isInstanciated() || Model::get_phase() < 1) {
		return;
	}

	int buttonClicked = sideView->buttonClicked(_x, _y);
	if (buttonClicked == -1 || buttonClicked == state) {
		return;
	}
	
	playerOrderView->hide();
	resMarketView->hide();
	facMarketView->hide();
	minimapView->hide();
	for (int i = 0; i < 6; i++) playerViews[i]->hide();
	state = buttonClicked;

	switch (buttonClicked) {
	case 1: 
		for (int i = 0; i < 6; i++) {
			playerViews[i]->show();
			if (!playerViews[i]->isSet()) playerViews[i]->set_player(Model::get_players()[i]);
		}
		break;
	case 2: 
		minimapView->show();
		minimapView->findAndAttach();
		break;
	case 3:
		playerOrderView->show();
		playerOrderView->findAndAttach();
		break;
	case 4:
		facMarketView->show();
		facMarketView->findAndAttach();
		break;
	case 5:
		resMarketView->show();
		resMarketView->findAndAttach();
		break;
	}
}
void SideController::onLoad() {}
void SideController::onUnload() {}
bool SideController::phasedEnded() { return false; }
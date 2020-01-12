#include "Phase4Controller.h"
#include <iostream>
#include "Model.h"

Phase4Controller::Phase4Controller() :Controller() {
	phase4view = new Phase4View();
	phase4view->hide();
	curCity = "";
	endOfPhase = false;
}

Phase4Controller::~Phase4Controller() {}

void Phase4Controller::onClick(int _x, int _y) {
	if (phase4view->buyButtonClicked(_x, _y)) {
		std::cout<<Model::get_map()->buyCity(curCity, Model::get_currentPlayer()->get_color())<<"\n";
		Model::get_currentPlayer()->addHouses(1);
		if (Model::get_step() == 1 && Model::get_currentPlayer()->getHousesOwned() >= 7) {
			Model::set_step(2);
		}
	}
	else if (phase4view->endTurnButtonClicked(_x, _y)) {
		if (!Model::previous_player()) {
			endOfPhase = true;
		}
		else {
			phase4view->set_playerName(Model::get_currentPlayer()->get_name());
			std::cout << Model::get_currentPlayer()->executeStrategy(4,
				Model::get_factoryMarket()->getBuyableFactories(), 
				Model::get_currentPlayer()->getFactories()) << "\n";
		}
	}
	else {
		std::string city = phase4view->cityClicked(_x, _y);
		if (city != "") {
			curCity = city;
			phase4view->set_city(curCity, 10);
		}
	}
}

void Phase4Controller::onLoad() {
	phase4view->show();
	phase4view->findAndAttach();
	Model::set_currentPlayer(Model::get_playerCount() - 1);
	phase4view->set_playerName(Model::get_currentPlayer()->get_name());
	endOfPhase = false;
}
void Phase4Controller::onUnload() {
	phase4view->hide();
	endOfPhase = false;
	Model::set_phase(5);
}

bool Phase4Controller::phasedEnded() {
	return endOfPhase;
}
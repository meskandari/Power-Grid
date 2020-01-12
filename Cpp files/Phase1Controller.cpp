#include "Phase1Controller.h"
#include "Phase1View.h"
#include "PlayerOrderView.h"


Phase1Controller::Phase1Controller() :Controller() {
	phase1view = new Phase1View();
	playerOrderView = new PlayerOrderView();
	playerOrderView->move(400, 150);
	phase1view->hide();
	playerOrderView->hide();
	endOfPhase = false;
}

Phase1Controller::~Phase1Controller() {}

void Phase1Controller::onClick(int _x, int _y) {
	if (phase1view->continueClicked(_x, _y)) {
		endOfPhase = true;
	}
}

void Phase1Controller::onLoad() {
	phase1view->show();
	playerOrderView->show();
	endOfPhase = false;
	{
		Player** m_players = Model::get_players();
		int size = Model::get_playerCount();
		playersOrderIndex = new int[size];
		for (int i = 0; i < size; i++) {
			playersOrderIndex[i] = 0;
		}
		for (int i = 0; i < size - 1; i++) {
			for (int j = i + 1; j < size; j++) {
				int playerIhouses = m_players[i]->getHousesOwned();
				int playerJhouses = m_players[j]->getHousesOwned();
				if (playerIhouses < playerJhouses) {
					playersOrderIndex[j] = playersOrderIndex[j] + 1;
				}
				else {
					if (playerIhouses == playerJhouses) {
						int playerIFactory = m_players[i]->getHighestValueFactory();
						int playerJFactory = m_players[j]->getHighestValueFactory();
						if (playerIFactory < playerJFactory)
							playersOrderIndex[j] = playersOrderIndex[j] + 1;
						else
							playersOrderIndex[i] = playersOrderIndex[i] + 1;
					}
					else
						playersOrderIndex[i] = playersOrderIndex[i] + 1;
				}
			}
		}
		playersCurrentOrder = new Player*[size];
		for (int i = 0; i < size; i++) {
			playersCurrentOrder[playersOrderIndex[i]] = m_players[i];
		}
		Model::set_players(playersCurrentOrder);
	}
	playerOrderView->update();
}

void Phase1Controller::onUnload() {
	phase1view->hide();
	playerOrderView->hide();
	Model::set_phase(2);
}

bool Phase1Controller::phasedEnded() {
	return endOfPhase;
}
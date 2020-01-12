#include "Phase5Controller.h"
#include "PlayerFactoriesView.h"
#include "Phase5View.h"
#include "ResourceMarketView.h"
#include "FactoryMarketView.h"
#include "Model.h"
#include <string>
#include <iostream>
#include <algorithm>

// Called on boot-up. Initializes the Views and various phase-specific variables.
Phase5Controller::Phase5Controller() :Controller() {
	endOfPhase = false;

	phase5view = new Phase5View();
	phase5view->hide();

	factoriesView = new PlayerFactoriesView();
	factoriesView->hide();
	factoriesView->move(70, 250);

	resMarketView = new ResourceMarketView();
	resMarketView->hide();
	resMarketView->move(800, 170);

	facMarketView = new FactoryMarketView();
	facMarketView->hide();
	facMarketView->move(100, 170);

	dragging = false;
	state = 0;
	for (int i = 0; i < 4; i++) {
		activated[i] = false;
	}
}

Phase5Controller::~Phase5Controller() {}

// Handles mouse clicking.
void Phase5Controller::onClick(int _x, int _y) {
	if (state == 0) {
		if (factoriesView->startResourceDrag(_x, _y)) { // Case: Factory's resource clicked.
			dragging = true;
		}
		else {
			int choice = phase5view->buttonClicked(_x, _y);
			if (choice == 4) { // Case: End turn button clicked.
				endTurn();
			}
			else if (choice >= 0) { // Case: factory's Activate button clicked.
				toggleFactory(choice);
			}
		}
	}
	else if (state == 1) {
		if (phase5view->buttonClicked(_x, _y) == 4) {
			endPhase();
		}
	}
}

// When the controller becomes the active Controller. Unhides its Views and sets up some variables.
void Phase5Controller::onLoad() {
	Model::set_currentPlayer(0);
	phase5view->show();
	phase5view->findAndAttach();
	factoriesView->show();
	factoriesView->set_player(Model::get_currentPlayer());
	facMarketView->findAndAttach();
	resMarketView->findAndAttach();

	endOfPhase = false;
	state = 0;
	phase5view->set_state(0);

}

// When the controller is no longer the active Controller. Hides its Views and declares the next Phase.
void Phase5Controller::onUnload() {
	phase5view->hide();
	factoriesView->hide();
	facMarketView->hide();
	resMarketView->hide();
	Model::set_phase(1);
}

// Tells the Driver that the phase ended.
bool Phase5Controller::phasedEnded() {
	return endOfPhase;
}

// Handles mouse movement. Only used for resource dragging.
void Phase5Controller::onMouseMove(int _x, int _y) {
	if (dragging) {
		factoriesView->updateResourceDrag(_x, _y);
	}
}

// Handles Click release. Only used for resource dragging.
void Phase5Controller::onClickRelease(int _x, int _y) {
	if (dragging) {
		std::cout << "reached\n";
		dragging = false;
		std::vector<int> moveInfo = factoriesView->stopResourceDrag(_x, _y);
		if (moveInfo[1] == -1) { // Case: didn't release on a Factory, no change.
			return;
		}

		std::cout << "reached2\n";
		Player* player = Model::get_currentPlayer();
		if (moveInfo[0] == moveInfo[1]) { // Case: Source and Target factories are the same.

			if (player->getFactories()[moveInfo[0]]->get_resourceType() != 4) { // Case: Non-hybrid Factory (no move needed)
				return;
			}
			else {
				player->rearrangeResource(moveInfo[0], moveInfo[3], moveInfo[4] == 0);
			}
		}
		else { // Case: Transferring to another factory.
			std::vector<FactoryCard*> factories = player->getFactories();
			int count = player->addResource(factories[moveInfo[1]]->get_value(), moveInfo[2], 1);
			if (count > 0) {
				player->removeResource(factories[moveInfo[0]]->get_value(), moveInfo[2], 1);
			}
			factories = player->getFactories();
			for (int i = 0; i < 1; i++) {
				if (activated[moveInfo[i]] && !factories[moveInfo[i]]->canActivate()) toggleFactory(moveInfo[i]);
			}

		}
	}
}

// Sets the chosen factory to active or innactive.
void Phase5Controller::toggleFactory(int pos) {
	std::vector<FactoryCard*> factories = Model::get_currentPlayer()->getFactories();
	if (pos >= factories.size() || factories[pos] == nullptr) { // Case: No factory at selected slot.
		return;
	}
	if (activated[pos]) { // Case: Factory is activated, deactivate.
		activated[pos] = false;
		phase5view->deactivateFactory(pos);
	}
	else { // Case: Factory is deactivated, try to activate.
		if (factories[pos]->canActivate()) { // Case: Enough resources to activate.
			activated[pos] = true;
			phase5view->activateFactory(pos);
		}
		else return; // Case: Not enough resources to activate.
	}

	// If the operation wasn't cancelled, updates the various information.
	poweredCities = 0;
	for (int i = 0; i < 4; i++) {
		if (activated[i]) {
			poweredCities += factories[i]->get_energy();
		}
	}
	phase5view->set_activeCities(poweredCities);
}

// Ends the turn, spending the resources and claiming the Elektro income, then switches player or next phase.
void Phase5Controller::endTurn() {
	Player* player = Model::get_currentPlayer();
	std::vector<FactoryCard*> factories = player->getFactories();
	int toRestock[4] = { 0, 0, 0, 0 };
	player->powerCities(std::min(poweredCities, std::min(player->getHousesOwned(), 20)));

	// Removes the resources from the player's activated factories.
	for (int i = 0; i < 4; i++) {
		if (activated[i]) {
			std::vector<Resource*> resources = factories[i]->get_stock();
			for (int j = 0; j < factories[i]->get_cost(); j++) {
				if (resources[j] != nullptr) {
					toRestock[resources[j]->get_type()]++;
				}
			}
			player->activateFactory(i);
		}
	}

	// Readds the removed resources to the Market.
	for (int i = 0; i < 4; i++) {
		Model::get_resourceMarket()->addToReserve(i, toRestock[i]);
	}

	if (Model::next_player()) { // Case: Still more players.
		poweredCities = 0;
		for (int i = 0; i < 4; i++) {
			activated[i] = false;
			phase5view->deactivateFactory(i);
		}
		phase5view->set_activeCities(0);
		factoriesView->set_player(Model::get_currentPlayer());
	}
	else { // Case: All players have finished, display market replenishes
		state = 1;
		restockMarkets();
		phase5view->set_state(1);
		resMarketView->show();
		facMarketView->show();
		factoriesView->hide();
	}
}

void Phase5Controller::endPhase() {
	endOfPhase = true;
}

// End of turn Market changes: restock the resource Market and switch a card of the Factory Market.
void Phase5Controller::restockMarkets() {
	for (int i = 0; i < 4; i++) {
		Model::get_resourceMarket()->restockMarket(i, std::min(Model::get_resourceMarket()->get_reserveResource(i),
			resRestock[Model::get_playerCount() - 2][Model::get_step() - 1][i]));
		FactoryMarket* facMarket = Model::get_factoryMarket();
		if (Model::get_step() == 3) {
			if (facMarket->getFactory(0) != nullptr) {
				delete facMarket->removeIndex(0);
			}
		}
		else {
			Model::get_deck()->insert(facMarket->removeIndex(7));
		}

		Card* card = Model::get_deck()->pull();
		if (card == nullptr) { // Case: Deck is empty, nothing was drawn.
			return;
		}
		else if (card->get_type() == "Step 3") { // Case: Step 3 activated.
			delete card;
			card = nullptr;
			delete facMarket->removeIndex(0);
			Model::set_phase(3);
			Model::get_deck()->shuffle();
		}
		else { // Case: Normal draw.
			facMarket->addFactory((FactoryCard*)card);
		}

	}
}
#include "Phase3Controller.h"
#include "ResourceMarketView.h"
#include "Phase3View.h"
#include "PlayerFactoriesView.h"
#include "Model.h"
#include "Player.h"
#include <iostream>

// Start of controller, initialized upon opening the game.
Phase3Controller::Phase3Controller():Controller() {

	endOfPhase = false;
	resMarketView = new ResourceMarketView();
	resMarketView->move(800, 270);
	phase3view = new Phase3View();
	factoriesView = new PlayerFactoriesView();
	factoriesView->move(20, 450);

	resMarketView->hide();
	phase3view->hide();
	factoriesView->hide();

	dragging = false;
	currentResourceType = 0;
	count = 0;
	price = 0;
}

Phase3Controller::~Phase3Controller() {}

// Handles the clicking during the phase.
void Phase3Controller::onClick(int _x, int _y) {
	if (factoriesView->startResourceDrag(_x, _y)) {
		dragging = true;
	}
	else {
		int result = phase3view->buttonClicked(_x, _y);
		if (result < 0) return;
		else if (result < 4) changeResourceType(result);
		else if (result == 4) increaseCount();
		else if (result == 5) decreaseCount();
		else if (result == 6) endTurn();
		else if (result == 7) buy();
	}
}

// Handles mouse movement. Only used for resource Dragging.
void Phase3Controller::onMouseMove(int _x, int _y) {
	if (dragging) {
		factoriesView->updateResourceDrag(_x, _y);
	}
}

// Handles mouse release. Only used for resource Dragging.
void Phase3Controller::onClickRelease(int _x, int _y) {
	if (dragging) {
		dragging = false;
		std::vector<int> moveInfo = factoriesView->stopResourceDrag(_x, _y);
		if (moveInfo[1] == -1) { // Case: didn't release on a Factory, no change.
			return;
		}

		Player* player = Model::get_currentPlayer();
		if (moveInfo[0] == moveInfo[1]) { // Case: Source and Target factories are the same.
			
			if (player->getFactories()[moveInfo[0]]->get_resourceType() != 4) { // Case: Non-hybrid Factory (no move needed)
				return;
			}
			else {
				std::cout << moveInfo[2] << ", " << moveInfo[3] << "\n";
				player->rearrangeResource(moveInfo[0], moveInfo[3], moveInfo[4] == 0);
			}
		}
		else { // Case: Transferring to another factory.
			std::vector<FactoryCard*> factories = player->getFactories();
			int count = player->addResource(factories[moveInfo[1]]->get_value(), moveInfo[2], 1);
			if (count > 0) {
				player->removeResource(factories[moveInfo[0]]->get_value(), moveInfo[2], 1);
			}
			if (Model::get_currentPlayer()->getRemainingResourceSpace(currentResourceType) < count) {
				decreaseCount();
			}
		}
	}
}

// When the Controller becomes the active one. Unhides its Views and sets up specific data.
void Phase3Controller::onLoad() {
	resMarketView->show();
	phase3view->show();
	factoriesView->show();

	endOfPhase = false;
	count = 0;
	price = 0;
	currentResourceType = 0;

	Model::set_currentPlayer(Model::get_playerCount() - 1);
	resMarketView->findAndAttach();
	phase3view->set_count(0);
	phase3view->set_price(0);
	factoriesView->set_player(Model::get_currentPlayer());
	phase3view->set_player(Model::get_currentPlayer());
}

// When the controller becomes unactive. Hides its Views and declares the next phase.
void Phase3Controller::onUnload() {
	resMarketView->hide();
	phase3view->hide();
	factoriesView->hide();
	Model::set_phase(4);
}

// Tells the Driver when the phase ended.
bool Phase3Controller::phasedEnded() {
	return endOfPhase;
}

// Ended up unused.
void Phase3Controller::dragResourceStart(int factoryPos, int resourcePos) {

}

// Ended up unused.
void Phase3Controller::dragResourceEnd(int factorySource, int resourcePos, int factoryTarget, bool placeBefore) {

}

// Changes the active resource for buying. 
void Phase3Controller::changeResourceType(int type) {
	phase3view->set_currentResource(type);
	phase3view->set_count(0);
	phase3view->set_price(0);
	currentResourceType = type;
	count = 0;
	price = 0;
}

// Increases the amount that the player wants to buy.
void Phase3Controller::increaseCount() {
	int nextPrice = Model::get_resourceMarket()->getPrice(currentResourceType, count+1);
	if (nextPrice == -1) { 
		return; // Case: Market is out of resource.
	}
	else if (nextPrice > Model::get_currentPlayer()->get_money()) {
		return; // Case: Player does not have enough money.
	}
	else if (count + 1 > Model::get_currentPlayer()->getRemainingResourceSpace(currentResourceType)) {
		return; // Case: Player does not have enough storage space remaining.
	}
	else { // Case: Player can buy at least one more.
		count++;
		price = nextPrice;
		phase3view->set_count(count);
		phase3view->set_price(price);
	}
}

// Decreases the amount of resources the player wants to buy.
void Phase3Controller::decreaseCount() {
	if (count == 0) {
		return;
	}
	count--;
	price = Model::get_resourceMarket()->getPrice(currentResourceType, count);
	phase3view->set_count(count);
	phase3view->set_price(price);
}

// Purchases the desired amount of the desired resource.
void Phase3Controller::buy() {
	Player* player = Model::get_currentPlayer();
	player->spendMoney(price);
	price = 0;
	Model::get_resourceMarket()->removeResource(currentResourceType, count);
	std::vector<FactoryCard*> factories = player->getFactories();
	for (int i = 0; i < factories.size() && count > 0; i++) {
		if (factories[i] == nullptr) {
			continue;
		}
		count = count - player->addResource(factories[i]->get_value(), currentResourceType, count);
	}
	phase3view->set_count(0);
	phase3view->set_price(0);
}

// Ends the turn, either moving on to the next player or to the next phase.
void Phase3Controller::endTurn() {
	if (Model::previous_player()) { // Case: There's still more players that haven't played.
		count = 0;
		price = 0;
		currentResourceType = 0;
		phase3view->set_count(0);
		phase3view->set_price(0);
		phase3view->set_currentResource(0);
		factoriesView->set_player(Model::get_currentPlayer());
		phase3view->set_player(Model::get_currentPlayer());
	}
	else { // Case: No more player, go to next phase.
		endOfPhase = true;
	}
}
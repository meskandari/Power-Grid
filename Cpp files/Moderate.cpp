#include "Moderate.h"

string Moderate::execute(int phaseNumber, vector<FactoryCard*> _currentBuyabaleCards, vector<FactoryCard*> _playerFactories) {
	if (phaseNumber == 2) {
		const int sizeBuyableCard = (int)_currentBuyabaleCards.size();
		const int sizePlayerFCard = (int)_playerFactories.size();

		int fLowestCost = 1000;
		int playerLCostCard = 1000;
		int index = -1;

		for (int i = 0; i < sizeBuyableCard; i++) {
			if (fLowestCost > _currentBuyabaleCards[i]->get_value()) {
				fLowestCost = _currentBuyabaleCards[i]->get_value();
				index = i;
			}
		}

		for (int i = 0; i < sizePlayerFCard; i++) {
			if (_playerFactories[i]!=nullptr&& playerLCostCard > _playerFactories[i]->get_value()) {
				playerLCostCard = _playerFactories[i]->get_value();
			}
		}

		if (playerLCostCard < fLowestCost) {
			comment = "Moderate strategy: you already have the  most efficient power plant. Pass in this Auction";
			return comment;
		}
		else {
			comment = "Moderate strategy: choose Factory of price " +to_string( _currentBuyabaleCards[index]->get_value());
			return comment;
		}
	}
	else if (phaseNumber == 3) {
		comment = "Moderate strategy: choose resources efficiently depends on your powerplant cards capacity";
		return comment;

	}
	else if (phaseNumber == 4) {
		comment = "Moderate strategy: buy lowest price city";
		return comment;
	}
	else{
		comment = "Moderate strategy: nothing to do in this phase based on your strategy";
		return comment;
	}
}
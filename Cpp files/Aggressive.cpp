#include "Aggressive.h"
#include <vector>
#include "FactoryCard.h"
string Aggressive::execute(int phaseNumber, vector<FactoryCard*> _currentBuyabaleCards, vector<FactoryCard*> _playerFactories) {
	if (phaseNumber == 2) {
		const int sizeBuyableCard = (int)_currentBuyabaleCards.size();
		const int sizePlayerFCard = (int)_playerFactories.size();

		int fHighestEnergy = 0;
		int playerHEnergyCard = 0;
		int index=-1;

		for (int i = 0; i < sizeBuyableCard; i++) {
			if (fHighestEnergy < _currentBuyabaleCards[i]->get_energy()) {
				fHighestEnergy = _currentBuyabaleCards[i]->get_energy();
				index = i;
			}
		}
		
		for (int i = 0; i < sizePlayerFCard; i++) {
			if (_playerFactories[i]!=nullptr&&playerHEnergyCard < _playerFactories[i]->get_energy()) {
				playerHEnergyCard = _playerFactories[i]->get_energy();
			}
		}
		
		if (playerHEnergyCard > fHighestEnergy) {
			comment = "Aggressive strategy: you already have the most powerful plant. Pass in this Auction";
			return comment;
		}
		else {
			comment="Aggressive strategy: choose Factory of value " +to_string( _currentBuyabaleCards[index]->get_value());
			comment +=" to power Up " + to_string( _currentBuyabaleCards[index]->get_energy());
			comment+= " cities.";
			return comment;
		}
	}
	
	else {
		comment="Aggressive Strategy: nothing to do in this phase based on your strategy";
		return comment;
	}
}
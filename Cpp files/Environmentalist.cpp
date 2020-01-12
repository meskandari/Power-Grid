#include "Environmentalist.h"
#include "ResourceMarket.h"


string Environmentalist::execute(int phaseNumber, vector<FactoryCard*> _currentBuyabaleCards, vector<FactoryCard*> _playerFactories) {
	if (phaseNumber == 2) {
		const int sizeBuyableCard = (int)_currentBuyabaleCards.size();
		int index = -1;

		for (int i = 0; i < sizeBuyableCard; i++) {
			if ( _currentBuyabaleCards[i]->get_resourceType()==5) {
				index = i;
				break;
			}
			else if (_currentBuyabaleCards[i]->get_resourceType() == 4) {
				index = i;
				break;
			}
		}
		if (index>-1) {
			comment = "Environmentalist strategy: Buy the power plant of resource type "+ Resource::codeToName(_currentBuyabaleCards[index]->get_resourceType());
			return comment;
		}
		else {
			comment = "Environmentalist strategy: there is no Hybrid power plant. Pass in this Auction";
			return comment;
		}
	}

	else {
		comment = "Environmentalist strategy : nothing to do in this phase based on your strategy";
		return comment;
	}
 }
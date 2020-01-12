#pragma once
#include <string>
#include <iostream>
#include "Card.h"
#include "FactoryCard.h"
#include "Step3Card.h"

using namespace std;
class CardFactory {
public:
	static Card* Create(string type, int _value, int _resourceType, int _cost, int _energy) {
		if (type == "Factory")
			return new FactoryCard(_value, _resourceType, _cost, _energy);
		else if (type == "Step3")
			return new Step3Card();
		return nullptr;
	}

	static Card* Create(string type) {
		if (type == "Step3")
			return new Step3Card();
	}
private:
	CardFactory() {};
};

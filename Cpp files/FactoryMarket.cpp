#include "FactoryCard.h"
#include "FactoryMarket.h"
#include "CardFactory.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Creates the Factory Market, and initializes it for Step 1. Cards need to be added to it after creation.
FactoryMarket::FactoryMarket() {
	capacity = 8;
	currentMarket = 4;
	factoryCount = 0;
}

// Creates the Factory Market using the save file.
FactoryMarket::FactoryMarket(std::string file) {
	capacity = 8;
	currentMarket = 4;
	factoryCount = 0;
	std::ifstream iFile;
	iFile.open(file);
	if (iFile) {
		iFile >> capacity;
		iFile >> currentMarket;
		iFile >> factoryCount;
		for (int i = 0; i < factoryCount; i++) {
			int value, type, cost, energy;
			iFile >> value;
			iFile >> type;
			iFile >> cost;
			iFile >> energy;
			factories[i] = (FactoryCard*)CardFactory::Create("Factory",value, type, cost, energy);
		}
		iFile.close();
	}
}

FactoryMarket::~FactoryMarket() {
	for (int i = 0; i < factoryCount; i++) {
		delete factories[i];
	}
}

// Returns the factory at given index.
FactoryCard* FactoryMarket::getFactory(int index)
{
	return factories[index];
}

std::vector<FactoryCard*> FactoryMarket::getBuyableFactories() {
	std::vector<FactoryCard*> buyableFactories;
	for (int i = 0; i < currentMarket && i < factoryCount; i++) {
		buyableFactories.push_back(factories[i]);
	}
	return buyableFactories;
}

// Removes the Factory using its value. Returns the removed Factory Card.
FactoryCard* FactoryMarket::removeFactory(int value) {
	int index = search(value, true);
	return removeIndex(index);
}

// Removes the Factory using its index. Returns the removed Factory Card.
FactoryCard* FactoryMarket::removeIndex(int index) {
	if (index >= factoryCount || index < 0) {
		return nullptr;
	}
	FactoryCard* factory = factories[index];
	factories[index] = nullptr;
	for (int i = index; i < factoryCount - 1; i++) {
		factories[i] = factories[i + 1];
	}
	factoryCount--;
	factories[factoryCount] = nullptr;
	notify();
	return factory;
}

// Adds a Factory Card in the market. Returns False if the market is full. The Market is automatically reordered.
bool FactoryMarket::addFactory(FactoryCard* factory) {

	if (factoryCount >= capacity) {
		return false;
	}
	int index = search(factory->get_value(), false);
	for (int i = factoryCount; i > index; i--) {
		FactoryCard* temp = factories[i];
		factories[i] = factories[i - 1];
		factories[i - 1] = temp;
	}
	factories[index] = factory;
	factoryCount++;
	notify();
	return true;
}

// Sets the current Step of the game. Only changes with Step 3, though.
void FactoryMarket::setStep(int step) {
	if (step == 3) {
		capacity = 6;
		currentMarket = 6;
	}
	else {
		capacity = 8;
		currentMarket = 4;
	}
	notify();
}

// Returns the current capacity of the market.
int FactoryMarket::getCapacity() const {
	return capacity;
}

// Returns true if the selected Factory is in the current market, or false if it's in the future market.
bool FactoryMarket::canBuy(int value) const {
	int index = search(value, true);
	return (index != -1 && index < currentMarket);
}

// Searches for where the given value falls into the current market. 
// When exactValue == true, it returns the index location of the Factory, or -1 if it is not there.
// When exactValue == false, it returns the index location of the closest card with higher value.
int FactoryMarket::search(int value, bool exactValue) const {
	int min = 0;
	int max = factoryCount - 1;
	while (min <= max) {
		int current = int((min + max) / 2);
		int curValue = factories[current]->get_value();
		if (curValue == value) {
			return current;
		}
		else if (value < curValue) {
			max = current - 1;
		}
		else {
			min = current + 1;
		}
	}
	if (exactValue) {
		return -1;
	}
	else {
		return min;
	}

}

// Saves the Factory Market to a file.
void FactoryMarket::saveToFile() {
	std::ofstream file;
	file.open("facMarket.sav");
	if (file) {
		file << capacity << "\n";
		file << currentMarket << "\n";
		file << factoryCount << "\n";
		for (int i = 0; i < factoryCount; i++) {
			file << factories[i]->get_value() << "\n";
			file << factories[i]->get_resourceType() << "\n";
			file << factories[i]->get_cost() << "\n";
			file << factories[i]->get_energy() << "\n";
		}
		file.close();
	}
}

void FactoryMarket::print() const {
	std::cout << "The Market current has " << factoryCount << " factories in its market.\n";
	for (int i = 0; i < factoryCount; i++) {
		if (i == 0) {
			std::cout << "Current Market:\n";
		}
		else if (i == currentMarket) {
			std::cout << "Future Market:\n";
		}
		if (factories[i] != nullptr) {
			factories[i]->print();
		}
	}
}
#include <string>
#include <vector>
#include <algorithm>
#include "FactoryCard.h"
#include "Resource.h"
#include <iostream>

// Default constructor. Should not be used.
FactoryCard::FactoryCard() : Card("Factory") {
	value = 0;
	resourceType = 0;
	cost = 0;
	energy = 0;
	stock = std::vector<Resource*>(0);
	stockCount = 0;
}

// Resource type: 0 = Coal, 1 = Oil, 2 = Garbage, 3 = Uranium, 4 = Hybrid, 5 = None
FactoryCard::FactoryCard(int _value, int _resourceType, int _cost, int _energy) : Card("Factory") {
	value = _value;
	resourceType = _resourceType;
	cost = _cost;
	energy = _energy;
	capacity = cost * 2;
	stock = std::vector<Resource*>(capacity);
	stockCount = 0;
	if (_value < 10) {
		set_frontPicturePath("image\\0" + std::to_string(_value) + ".png");
	}
	else {
		set_frontPicturePath("image\\" + std::to_string(_value) + ".png");
	}
}

// Creates a deep copy of the passed Factory Card.
FactoryCard::FactoryCard(FactoryCard& card) {
	value = card.get_value();
	resourceType = card.get_resourceType();
	cost = card.get_cost();
	energy = card.get_energy();
	capacity = card.get_capacity();
	stock = std::vector<Resource*>(capacity);
	for (int i = 0; i < capacity; i++) {
		if (card.stock[i] != nullptr) {
			stock[i] = new Resource(card.stock[i]->get_type());
		}
	}
	stockCount = card.stockCount;
	set_frontPicturePath(card.get_frontPicturePath());
}

FactoryCard::~FactoryCard() {
	for (int i = 0; i < capacity; i++) {
		if (stock[i] == nullptr) {
			delete stock[i];
		}
	}
}

// Value number of the Factory card. This determines it's ranking amongst other Factories as well as its minimum cost.
int FactoryCard::get_value() const {
	return value;
}

// Cost for powering up the Factory. Varies between 0 and 5 (0 is only for None resourceType)
int FactoryCard::get_cost() const {
	return cost;
}

// Storage capacity of the Factory. Although it is always 2 times the cost, a function is used to get it.
int FactoryCard::get_capacity() const {
	return capacity;
}

// Returns the amount of Resource space that hasn't been filled yet.
int FactoryCard::get_remainingSpace() const {
	return capacity - stockCount;
}

// Type of resource the Factory needs, in int code.
int FactoryCard::get_resourceType() const {
	return resourceType;
}

// How many cities the Factory powers up when paying its power cost.
int FactoryCard::get_energy() const {
	return energy;
}

// Returns the amount that was successfully deposited.
int FactoryCard::addResource(int amount, int type) {
	if (stockCount >= capacity) {
		return 0;
	} else if (resourceType == 4 && (type > 1 || type < 0)) {
		return 0;
	} else if (resourceType != 4 && resourceType != type) {
		return 0;
	}

	int count = 0;
	for (int i = 0; i < capacity && count < amount; i++) {
		if (stock[i] == nullptr) {
			stock[i] = new Resource(type);
			count++;
			stockCount++;
		}
	}
	return count;
}

// Returns the amount that was sucessfully removed from the stock.
int FactoryCard::removeResource(int amount, int type) {
	if (resourceType == 4 && (type > 1 || type < 0)) {
		return 0;
	}
	else if (resourceType != 4 && resourceType != type) {
		return 0;
	}

	int count = 0;
	for (int i = 0; i < capacity && count < amount; i++) {
		if (stock[i] != nullptr && stock[i]->get_type() == type) {
			stock[i] = nullptr;
			stock.erase(stock.begin() + i);
			stock.push_back(nullptr);
			stockCount--;
			count++;
		}
	}
	
	return count;
}

// Takes a Resource by index and sends it either to the front or the back of the stock.
void FactoryCard::rearrangeResource(int resourceIndex, bool toFront) {
	if (resourceIndex >= stockCount) {
		return;
	}
	Resource* resource = stock[resourceIndex];
	stock.erase(stock.begin() + resourceIndex);
	if (toFront) {
		stock.insert(stock.begin(), resource);
	}
	else {
		stock.insert(stock.begin() + (stockCount - 1), resource);
	}
}

// Returns true if the Factory has enough resources to be activated.
bool FactoryCard::canActivate() {
	return stockCount >= cost;
}

// Spends the first half of the stock.
bool FactoryCard::activate() {
	if (stockCount < cost) return false;
	else {
		for (int i = 0; i < cost; i++) {
			stock.erase(stock.begin());
			stock.push_back(nullptr);
			stockCount--;
		}
	}
}

// Returns a copy of the stock of the Factory.
std::vector<Resource*> FactoryCard::get_stock() const {
	std::vector<Resource*> stockImage = std::vector<Resource*>(capacity);
	int j = 0;
	for (int i = 0; i < capacity; i++) {
		if (stock[i] != nullptr) {
			stockImage.at(i) = new Resource(stock[i]->get_type());
		}
	}
	return stockImage;
}

void FactoryCard::print() const {
	std::cout << "Factory of value " << value << ", type " << Resource::codeToName(resourceType) << ", costs " << cost << " to power up " << energy << " cities. ";
	if (resourceType == 4) {
		int coal = 0;
		int oil = 0;
		for (int i = 0; i < capacity; i++) {
			if (stock[i] != nullptr) {
				if (stock[i]->get_type() == 0) {
					coal++;
				}
				else {
					oil++;
				}
			}
		}
		std::cout << "It currently stocks " << coal << " Coal and " << oil << " Oil.\n";
	}
	else if (resourceType < 4) {
		int count = 0;
		for (int i = 0; i < capacity; i++) {
			if (stock[i] != nullptr) {
				count++;
			}
		}
		std::cout << "It current stocks " << count << " " << Resource::codeToName(resourceType) << ".\n";
	}
	else {
		std::cout << "It cannot stock any resource.\n";
	}
}
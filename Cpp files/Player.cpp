#include <string>
#include <vector>
#include "FactoryCard.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include "CardFactory.h"

// Initializes a player with no color or name. 
Player::Player() {
	name = "";
	color = "";
	money = 50;
	maxFactories = 3;
	factories = std::vector<FactoryCard*>(maxFactories);
	housesOwned = 0;
	highestValueFactory = 0;
	factoriesOwned = 0;
}

// Initializes a player using data from a save file. 
Player::Player(std::string file) {
	name = "";
	color = "";
	money = 50;
	maxFactories = 3;
	factories = std::vector<FactoryCard*>(maxFactories);
	housesOwned = 0;
	highestValueFactory = 0;
	factoriesOwned = 0;

	std::ifstream iFile;
	iFile.open(file);
	if (iFile) {
		iFile >> name;
		iFile >> color;
		iFile >> money;
		iFile >> factoriesOwned;
		iFile >> maxFactories;
		iFile >> housesOwned;
		iFile >> highestValueFactory;
		for (int i = 0; i < factoriesOwned; i++) {
			int value, type, cost, energy;
			iFile >> value;
			iFile >> type;
			iFile >> cost;
			iFile >> energy;
			factories[i] = (FactoryCard*)CardFactory::Create("Factory",value,type,cost,energy);

			int resources[4] = { 0, 0, 0, 0 };
			for (int j = 0; j < 4; j++) {
				iFile >> resources[j];
			}

			for (int j = 0; j < 4; j++) {
				if (resources[j] > 0) {
					factories[i]->addResource(resources[j], j);
				}
			}
		}
		iFile.close();
	}
}

// Creates a player with designed name, color and max factories.
Player::Player(std::string _name, std::string _color, int _maxFactories) {
	name = _name;
	color = _color;
	money = 50;
	maxFactories = _maxFactories;
	factories = std::vector<FactoryCard*>(maxFactories);
	housesOwned = 0;
	highestValueFactory = 0;
	factoriesOwned = 0;
}

Player::Player(std::string _name, std::string _color, int _maxFactories, Strategy* _initiStrategy) {
	name = _name;
	color = _color;
	money = 50;
	maxFactories = _maxFactories;
	factories = std::vector<FactoryCard*>(maxFactories);
	housesOwned = 0;
	highestValueFactory = 0;
	factoriesOwned = 0;
	_strategy = _initiStrategy;
}

Player::~Player() {
	for (int i = 0; i < maxFactories; i++) {
		if (factories[i] != nullptr) {
			delete factories[i];
		}
	}
}

// Get the name of the player. This property cannot be changed once set.
std::string Player::get_name() const {
	return name;
}

// Get the color of the player. This property cannot be changed once set.
std::string Player::get_color() const {
	return color;
}

// Get the amount of money the player has.
int Player::get_money() const {
	return money;
}

// Add money to the player.
void Player::addMoney(int value) {
	money += value;
	notify();
}

// Substract money from the player. Returns true if the operation was successful.
bool Player::spendMoney(int value) {
	if (money < value) {
		return false;
	}
	else {
		money -= value;
		notify();
		return true;
	}
}

// Set the money the player has.
void Player::setMoney(int value) {
	money = value;
	notify();
}

// Get a vector of al the factories the player has. These are copies, and changes to them do not reflect to the original.
std::vector<FactoryCard*> Player::getFactories() const {
	std::vector<FactoryCard*> copyFactories = std::vector<FactoryCard*>(maxFactories);
	for (int i = 0; i < maxFactories; i++) {
		if (factories[i] != nullptr) {
			copyFactories[i] = new FactoryCard(*factories[i]);
		}
	}
	return copyFactories;
}

// Remove a factory from the player's inventory, using value of the factory. Returns true if the player had that factory.
bool Player::removeFactory(int factoryValue) {
	if (factoriesOwned == 0) {
		return false;
	}
	for (int i = 0; i < maxFactories; i++) {
		if (factories[i]->get_value() == factoryValue) {
			delete factories[i];
			factories[i] = nullptr;
			factoriesOwned--;
			notify();
			return true;
		}
	}
	return false;
}

// Adds a factory to the player's inventory. Returns true if the player had space to add the factory.
bool Player::addFactory(FactoryCard* factory) {
	if (factoriesOwned == maxFactories) {
		return false;
	}
	for (int i = 0; i < maxFactories; i++) {
		if (factories[i] == nullptr) {
			factories[i] = factory;
			factoriesOwned++;
			notify();
			return true;
		}
	}
	return false;
}

// Returns true if the player has reached his or her maximum capacity of factories.
bool Player::factoriesFull() const {
	return (factoriesOwned == maxFactories);
}

// Returns the amount of houses the player has purchased and placed on the map.
int Player::getHousesOwned() const {
	return housesOwned;
}

// Adds to the count of houses owned by the player. The total cannot exceed 21. Returns true if it does not exceed.
bool Player::addHouses(int count) {
	if (housesOwned + count > 21) {
		return false;
	}
	else {
		housesOwned += count;
		notify();
		return true;
	}
}

// Get the value of the strongest factory in the player's inventory. Returns 0 if the player does not have a factory.
int Player::getHighestValueFactory() const {
	if (factoriesOwned == 0) {
		return 0;
	}
	int max = 0;
	for (int i = 0; i < maxFactories; i++) {
		if (factories[i]!=nullptr&&factories[i]->get_value() > max) {
			max = factories[i]->get_value();
		}
	}
	return max;
}

// Power up cities and gain Elektro back. Returns -1 if unsuccessful, else returns the amount of elektro gained.
int Player::powerCities(int cities) {
	if (cities < 0 || cities > housesOwned) {
		return -1;
	}
	else {
		int elektro[22] = { 10, 22, 33, 44, 54, 64, 73, 82, 90, 98, 105, 112, 118, 124, 129, 134, 138, 142, 145, 148, 150 };
		addMoney(elektro[cities]);
		notify();
		return elektro[cities];
	}
}

// Returns the amount that was successfully deposited.
int Player::addResource(int factoryValue, int resourceType, int quantity) {
	for (int i = 0; i < maxFactories; i++) {
		if (factories[i] != nullptr && factories[i]->get_value() == factoryValue) {
			int temp = factories[i]->addResource(quantity, resourceType);
			notify();
			return temp;
		}
	}
	return 0;
}

// Returns the amount that was sucessfully removed from the factory.
int Player::removeResource(int factoryValue, int resourceType, int quantity) {
	for (int i = 0; i < maxFactories; i++) {
		if (factories[i] != nullptr && factories[i]->get_value() == factoryValue) {
			int temp = factories[i]->removeResource(quantity, resourceType);
			notify();
			return temp;
		}
	}
	return 0;
}

// Spends the top half of the resources for the specified factory.
bool Player::activateFactory(int factoryIndex) {
	if (factoryIndex >= factoriesOwned) {
		return false;
	}
	else {
		bool temp = factories[factoryIndex]->activate();
		notify();
		return temp;
	}
}

// Sends the specified resource of the specified factory to either the front or back of its stock.
void Player::rearrangeResource(int factoryIndex, int resourceIndex, bool toFront) {
	if (factoryIndex >= factoriesOwned) {
		return;
	}
	factories[factoryIndex]->rearrangeResource(resourceIndex, toFront);
	notify();
}

// Returns the amount of resources the player can hold of the specified type.
int Player::getRemainingResourceSpace(int type) {
	int total = 0;
	for (int i = 0; i < factoriesOwned; i++) {
		if (factories[i]->get_resourceType() == 4 && type != 0 && type != 1) {
			continue;
		}
		else if (factories[i]->get_resourceType() != 4 && factories[i]->get_resourceType() != type) {
			continue;
		}
		total += factories[i]->get_remainingSpace();
	}
	return total;
}

// Saves the player to a file. Each player gets their own file.
void Player::saveToFile() const {
	std::ofstream file;
	file.open("player" + color + ".sav");
	if (file) {
		file << name << "\n";
		file << color << "\n";
		file << money << "\n";
		file << factoriesOwned << "\n";
		file << maxFactories << "\n";
		file << housesOwned << "\n";
		file << highestValueFactory << "\n";
		for (int i = 0; i < maxFactories; i++) {
			if (factories[i] != nullptr) {
				file << factories[i]->get_value() << "\n";
				file << factories[i]->get_resourceType() << "\n";
				file << factories[i]->get_cost() << "\n";
				file << factories[i]->get_energy() << "\n";
				int resources[4] = { 0, 0, 0, 0 };
				std::vector<Resource*> stockImage = factories[i]->get_stock();
				for (int i = 0; i < (int)stockImage.size(); i++) {
					if (stockImage.at(i) != nullptr) {
						resources[stockImage.at(i)->get_type()]++;
					}
				}
				for (int i = 0; i < 4; i++) {
					file << resources[i] << "\n";
				}
			}
		}
		file.close();
	}
}

void Player::print() const {
	std::cout << color << " player " << name << " has " << money << " Elektro, " << housesOwned << " houses owned, and " << factoriesOwned << " FactoryCards:\n";
	for (int i = 0; i < maxFactories; i++) {
		if (factories[i] != nullptr) {
			factories[i]->print();
		}
	}
}

// Returns true if the color is usable. They are Red, Blue, Black, Green, Purple and Orange.
bool Player::isValidColor(std::string color) {
	return (color.compare("Red") || color.compare("Blue") || color.compare("Black") || color.compare("Green") || color.compare("Purple") || color.compare("Orange"));
}

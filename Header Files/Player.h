#pragma once
#include <string>
#include <vector>
#include "FactoryCard.h"
#include "Subject.h"
#include "Strategy.h"

class Player : public Subject {
public:
	Player();
	Player(std::string _name, std::string _color, int _maxFactories);
	Player(std::string file);
	~Player();
	std::string get_name() const;
	std::string get_color() const;
	int get_money() const;
	void addMoney(int value);
	bool spendMoney(int value);
	void setMoney(int value);
	std::vector<FactoryCard*> getFactories() const;
	bool removeFactory(int factoryValue);
	bool addFactory(FactoryCard* factory);
	bool factoriesFull() const;
	int getHousesOwned() const;
	bool addHouses(int count);
	int getHighestValueFactory() const;
	void saveToFile() const;
	void print() const;
	int powerCities(int cities);
	int addResource(int factoryValue, int resourceType, int quantity);
	int removeResource(int factoryValue, int resourceType, int quantity);
	bool activateFactory(int factoryIndex);
	void rearrangeResource(int factoryIndex, int resourceIndex, bool toFront);
	int getRemainingResourceSpace(int type);
	static bool isValidColor(std::string color);

	Player(std::string _name, std::string _color, int _maxFactories, Strategy* _initiStrategy);
	void setStrategy(Strategy *newStrategy) { _strategy = newStrategy; }
	Strategy* getStrategy() const { return _strategy; }
	string executeStrategy(int phaseNumber, vector<FactoryCard*> _currentBuyabaleCards, vector<FactoryCard*> _playerFactories) {
		return this->_strategy->execute(phaseNumber, _currentBuyabaleCards, _playerFactories);
	};

private:
	std::string name;
	std::string color;
	int highestValueFactory;
	int money;
	std::vector<FactoryCard*> factories;
	int factoriesOwned;
	int maxFactories;
	int housesOwned;

	Strategy* _strategy;
};
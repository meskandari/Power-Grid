#pragma once
#include "FactoryCard.h"
#include <string>
#include "Subject.h"
#include <vector>

class FactoryMarket : public Subject {
public:
	FactoryMarket();
	FactoryMarket(std::string file);
	~FactoryMarket();
	FactoryCard* getFactory(int index);
	std::vector<FactoryCard*> getBuyableFactories();
	FactoryCard* removeFactory(int value);
	FactoryCard* removeIndex(int index);
	bool addFactory(FactoryCard* factory);
	void setStep(int phase);
	int getCapacity() const;
	bool canBuy(int value) const;
	void saveToFile();
	void print() const;
private:
	FactoryCard* factories[8];
	int capacity;
	int currentMarket;
	int factoryCount;
	int search(int value, bool exactValue) const;
};

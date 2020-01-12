#pragma once
#include <string>
#include <vector>
#include "Resource.h"
#include "Card.h"

class FactoryCard : public Card {
public:
	FactoryCard();
	FactoryCard(int _value, int _resourceType, int _cost, int _energy);
	FactoryCard(FactoryCard& card);
	int get_value() const;
	~FactoryCard();
	int get_resourceType() const;
	int get_cost() const;
	int get_capacity() const;
	int get_remainingSpace() const;
	int get_energy() const;
	int addResource(int amount, int type);
	int removeResource(int amount, int type);
	void rearrangeResource(int resourceIndex, bool toFront);
	bool canActivate();
	bool activate();
	std::vector<Resource*> get_stock() const;
	void print() const;

private:
	int value;
	int resourceType;
	int cost;
	int capacity;
	std::vector<Resource*> stock;
	int energy;
	int stockCount;
};

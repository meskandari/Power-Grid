#pragma once
#include <string>
#include "Card.h"
#include <cstdlib>
#include "CardFactory.h"

class Deck {
public:
	Deck();
	Deck(std::string file);
	~Deck();
	void initialize();
	void insert(Card* card);
	Card* pull();
	void shuffle();
	int getSize() const;
	bool isEmpty() const;
	void saveToFile() const;
private:
	const int CAPACITY = 44;
	Card* cards[44];
	int top;
	int bottom;
	int size;
};

#include "FactoryCard.h"
#include "Step3Card.h"
#include "Deck.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <iostream>

// Deck is implemented as a Queue, with the ability to shuffle.
Deck::Deck() {
	top = 0;
	bottom = 0;
	size = 0;
}

// Creates the Deck using a save file.
Deck::Deck(std::string file) {
	top = 0;
	bottom = 0;
	size = 0;
	std::ifstream iFile;
	iFile.open(file);
	if (iFile) {
		int savedSize;
		iFile >> savedSize;
		for (int i = 0; i < savedSize; i++) {
			std::string line;
			iFile >> line;
			if (line == "Step3") {\
				insert(CardFactory::Create("Step3", 0, 0, 0, 0));
			}
			else {
				int value = std::stoi(line, nullptr);
				int type, cost, energy;
				iFile >> type;
				iFile >> cost;
				iFile >> energy;
				insert(CardFactory::Create("Factory",value, type, cost, energy));
			}
		}
		iFile.close();
	}
}

Deck::~Deck() {
	for (int i = top; i == bottom; i = (i + 1) % CAPACITY) {
		delete cards[i];
	}
}

// Creates all cards of the game. For easier initializing of the game, Factories 3-10 and Step 3 cards are created first.
void Deck::initialize() {
	insert(CardFactory::Create("Factory", 3, 1, 2, 1));
	insert(CardFactory::Create("Factory",4, 0, 2, 1));
	insert(CardFactory::Create("Factory", 5, 4, 2, 1));
	insert(CardFactory::Create("Factory", 6, 2, 1, 1));
	insert(CardFactory::Create("Factory", 7, 1, 3, 2));
	insert(CardFactory::Create("Factory", 8, 0, 3, 2));
	insert(CardFactory::Create("Factory", 9, 1, 1, 1));
	insert(CardFactory::Create("Factory", 10, 0, 2, 2));
	insert(CardFactory::Create("Step3", 0,0,0,0));
	insert(CardFactory::Create("Factory", 11, 3, 1, 2));
	insert(CardFactory::Create("Factory",12, 4, 2, 2));
	insert(CardFactory::Create("Factory",13, 5, 0, 1));
	insert(CardFactory::Create("Factory", 14, 2, 2, 2));
	insert(CardFactory::Create("Factory",15, 0, 2, 3));
	insert(CardFactory::Create("Factory",16, 1, 2, 3));
	insert(CardFactory::Create("Factory",17, 3, 1, 2));
	insert(CardFactory::Create("Factory", 18, 5, 0, 2));
	insert(CardFactory::Create("Factory", 19, 2, 2, 3));
	insert(CardFactory::Create("Factory",20, 0, 3, 5));
	insert(CardFactory::Create("Factory", 21, 4, 2, 4));
	insert(CardFactory::Create("Factory",22, 5, 0, 2));
	insert(CardFactory::Create("Factory",23, 3, 1, 3));
	insert(CardFactory::Create("Factory",24, 2, 2, 4));
	insert(CardFactory::Create("Factory",25, 0, 2, 5));
	insert(CardFactory::Create("Factory",26, 1, 2, 5));
	insert(CardFactory::Create("Factory",27, 5, 0, 3));
	insert(CardFactory::Create("Factory",28, 3, 1, 4));
	insert(CardFactory::Create("Factory",29, 4, 1, 4));
	insert(CardFactory::Create("Factory",30, 2, 3, 6));
	insert(CardFactory::Create("Factory",31, 0, 3, 6));
	insert(CardFactory::Create("Factory",32, 1, 3, 6));
	insert(CardFactory::Create("Factory",33, 5, 0, 4));
	insert(CardFactory::Create("Factory",34, 3, 1, 5));
	insert(CardFactory::Create("Factory",35, 1, 1, 5));
	insert(CardFactory::Create("Factory",36, 0, 3, 7));
	insert(CardFactory::Create("Factory",37, 5, 0, 4));
	insert(CardFactory::Create("Factory",38, 2, 3, 7));
	insert(CardFactory::Create("Factory",39, 3, 1, 6));
	insert(CardFactory::Create("Factory",40, 1, 2, 6));
	insert(CardFactory::Create("Factory",42, 0, 2, 6));
	insert(CardFactory::Create("Factory",44, 5, 0, 5));
	insert(CardFactory::Create("Factory",46, 4, 3, 7));
	insert(CardFactory::Create("Factory",50, 5, 0, 6));
}

// Insert a card at its bottom. (Enqueue)
void Deck::insert(Card* card) {
	cards[bottom] = card;
	bottom = (bottom + 1) % CAPACITY;
	size++;
}

// Pull a card from the top. (Dequeue)
Card* Deck::pull() {
	if (getSize() == 0) {
		return nullptr;
	}
	Card* pulled = cards[top];
	cards[top] = nullptr;
	top = (top + 1) % CAPACITY;
	size--;
	return pulled;
}

// Shuffles what is currently in the deck.
void Deck::shuffle() {
	
	srand((unsigned int)time(NULL));
	int cur = 0;
	int j = (bottom - 1) % CAPACITY;
	j = (j < 0) ? j + CAPACITY : j;
	for (int i = top; i != j; i = (i+1)%CAPACITY) { // Start at the top of the deck, ends at its bottom
		int swapIndex = (i + std::rand() % (size-cur)) % CAPACITY; // Picks a random card that hasn't been picked yet.
		Card* temp = cards[i];
		cards[i] = cards[swapIndex];
		cards[swapIndex] = temp;
		cur++;
	}
}

// Returns the amount of cards remaining.
int Deck::getSize() const {
	return size;
}

bool Deck::isEmpty() const {
	return (getSize() == 0);
}

// Saves the current state of the deck as a save file.
void Deck::saveToFile() const {
	std::ofstream file;
	file.open("deck.sav");
	if (file) {
		file << size << "\n";
		for (int i = top; i != bottom; i = (i + 1) % CAPACITY) {
			if (cards[i]->get_type() == "Factory") {
				FactoryCard* curCard = (FactoryCard*)(cards[i]);
				file << curCard->get_value() << "\n";
				file << curCard->get_resourceType() << "\n";
				file << curCard->get_cost() << "\n";
				file << curCard->get_energy() << "\n";
			}
			else {
				file << "Step3\n";
			}

		}
		file.close();
	}
}
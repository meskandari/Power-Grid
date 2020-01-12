#include "Resource.h"
#include "ResourceMarket.h"
#include <iostream>
#include <fstream>
#include <string>

// Creates the Resource Market with no resource.
ResourceMarket::ResourceMarket() {
	for (int i = 0; i < 4; i++) {
		market[i] = 0;
		reserve[i] = 0;
	}
}

// Creates the Resource Market with resources saved from the save file.
ResourceMarket::ResourceMarket(std::string file) {
	for (int i = 0; i < 4; i++) {
		market[i] = 0;
		reserve[i] = 0;
	}
	std::ifstream iFile;
	iFile.open(file);
	if (iFile) {
		for (int i = 0; i < 4; i++) {
			iFile >> reserve[i];
			iFile >> market[i];
		}
		iFile.close();
	}
}

ResourceMarket::~ResourceMarket() {}

// Gets the price needed to purchase X quantity of a resource. Returns -1 if cannot buy.
int ResourceMarket::getPrice(int type, int quantity) const {
	if (type > 3 || type < 0 || market[type] < quantity) {
		return -1;
	}
	int price = 0;
	int div = 3;
	int base = 9;
	int cur = market[type];
	if (type == 3) {
		div = 1;
		base = 13;
	}
	for (int i = 0; i < quantity; i++) {
		int curPrice = base - (cur + div - 1) / div;
		if (curPrice > 8) {
			curPrice = curPrice * 2 - 8;
		}
		price+= curPrice;
		cur--;
	}
	return price;
}

// Removes X quantity of a resource from the market (purchased). Returns false if can't buy.
bool ResourceMarket::removeResource(int type, int quantity) {
	if (type > 3 || type < 0 || market[type] < quantity) {
		return false;
	}
	market[type] -= quantity;
	notify();
	return true;
}

// Moves X resources from the Reserve to the Market. Return false if can't do this operation.
bool ResourceMarket::restockMarket(int type, int quantity) {
	if (type > 3 || type < 0 || reserve[type] < quantity) {
		return false;
	}
	reserve[type] -= quantity;
	market[type] += quantity;
	notify();
	return true;
}

// Adds X quantity of a resource back into the reserve. It is not immediately restocked into the market.
void ResourceMarket::addToReserve(int type, int quantity) {
	reserve[type] += quantity;
	notify();
}

// Initializes the reserve. To use when starting the game.
void ResourceMarket::setReserve(int coal, int oil, int garbage, int uranium) {
	reserve[0] = coal;
	reserve[1] = oil;
	reserve[2] = garbage;
	reserve[3] = uranium;
	notify();
}

// Returns the amount of resources of the specified type currently in the market.
int ResourceMarket::get_marketResource(int i) const {
	return market[i];
}

// Returns the amount of resources of the specified type currently in the reserve.
int ResourceMarket::get_reserveResource(int i) const {
	return reserve[i];
}

// Saves the Market to a file.
void ResourceMarket::saveToFile() {
	std::ofstream file;
	file.open("resMarket.sav");
	if (file) {
		for (int i = 0; i < 4; i++) {
			file << reserve[i] << "\n";
			file << market[i] << "\n";
		}
		file.close();
	}
}

void ResourceMarket::print() const {
	std::cout << "Resource Market. Its stock is " << reserve[0] << " coal, " << reserve[1] << " oil, " << reserve[2] << " garbage and " << reserve[3] << " uranium.\n";
	std::cout << "Its market is " << market[0] << " coal, " << market[1] << " oil, " << market[2] << " garbage and " << market[3] << " uranium.\n";
}
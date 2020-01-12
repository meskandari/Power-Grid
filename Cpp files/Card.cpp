#include <string>
#include "Card.h"

// Creates a card. Should not be used.
Card::Card() {
	type = "undefined";
}

// Creates a card with given type. Should not be used.
Card::Card(std::string _type) {
	type = _type;
}

Card::~Card() {}

// Returns the type of the card.
std::string Card::get_type() const {
	return type;
}

// Returns the path to the picture on the front of the card.
std::string Card::get_frontPicturePath() const {
	return frontPicturePath;
}

// Sets the path to the picture on the front of the card. Only made available to children.
void Card::set_frontPicturePath(std::string _frontPicturePath) {
	frontPicturePath = _frontPicturePath;
}
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "Graphic.h"

// Default constructor. Sets coordinate to 0, empty name and non-hidden.
Graphic::Graphic() {
	x = 0;
	y = 0;
	name = "";
	hidden = false;
}

// Sets only the name, and the rest is default.
Graphic::Graphic(std::string _name) {
	x = 0;
	y = 0;
	name = _name;
	hidden = false;
}

// Full constructor. Sets the name and coordinates.
Graphic::Graphic(std::string _name, int _x, int _y) {
	x = _x;
	y = _y;
	name = _name;
	hidden = false;
}

Graphic::~Graphic() {
	
}

// Adds to the current coordinates.
void Graphic::move(int _x, int _y) {
	x += _x;
	y += _y;
}

// Sets the position of the graphic, regardless of current coordinates.
void Graphic::set_pos(int _x, int _y) {
	x = _x;
	y = _y;
}

// Hides the graphic, preventing it from being rendered.
void Graphic::hide() {
	hidden = true;
}

// Shows the graphic, allowing it from being rendered.
void Graphic::show() {
	hidden = false;
}

// Returns hidden property.
bool Graphic::isHidden() const {
	return hidden;
}

// Returns name.
std::string Graphic::get_name() {
	return name;
}

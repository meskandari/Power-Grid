
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include "Text.h"

// Default constructor
Text::Text(): Graphic() {
	text = "";
	x = 0;
	y = 0;
	font_size = 30;
	font_file = "font\\AGENCYR.ttf";
	font = al_load_ttf_font(font_file.c_str(), font_size, 0);
	r = 0;
	g = 0;
	b = 0;
}

// Sets the name and the text.
Text::Text(std::string _name, std::string _text) : Graphic(_name) {
	text = _text;
	x = 0;
	y = 0;
	font_size = 30;
	font_file = "font\\AGENCYR.ttf";
	font = al_load_ttf_font(font_file.c_str(), font_size, 0);
	r = 0;
	g = 0;
	b = 0;
}

// Sets the name, text and coordinates.
Text::Text(std::string _name, std::string _text, int _x, int _y) : Graphic(_name, _x, _y) {
	text = _text;
	x = _x;
	y = _y;
	font_size = 30;
	font_file = "font\\AGENCYR.ttf";
	font = al_load_ttf_font(font_file.c_str(), font_size, 0);
	r = 0;
	g = 0;
	b = 0;
}

// Full constructor. Sets the name, text, coordinates and font size.
Text::Text(std::string _name, std::string _text, int _x, int _y, int _size) : Graphic(_name, _x, _y) {
	text = _text;
	x = _x;
	y = _y;
	font_size = _size;
	font_file = "font\\AGENCYR.ttf";
	font = al_load_ttf_font(font_file.c_str(), font_size, 0);
	r = 0;
	g = 0;
	b = 0;
}

Text::~Text() {
	al_destroy_font(font);
	font = nullptr;
}

// Draws the text onto the display.
void Text::draw() {
	// std::cout << "font != nullptr: " << (font != nullptr) << "\n";
	if (!hidden && text != "" && font != nullptr) {
		al_draw_text(font, al_map_rgb(r, g, b), x, y, 0, text.c_str());
	}
}

// Returns true if the given Click coordinates correspond to the Text box.
bool Text::wasClicked(int _x, int _y) {
	int width = al_get_text_width(font, text.c_str());
	int height = al_get_font_line_height(font);

	return (_x >= x && _x <= x + width && _y >= y && _y <= y + height);
}

// Sets the text.
void Text::set_text(std::string _text) {
	text = _text;
}

// Returns the current text.
std::string Text::get_text() const {
	return text;
}

// Adds on top of the current text.
void Text::append_text(std::string _text) {
	text = text + _text;
}

// Sets the font of the text.
void Text::set_font(std::string file) {
	font = al_load_ttf_font(file.c_str(), font_size, 0);
}

// Sets the color of the text.
void Text::set_color(float _r, float _g, float _b) {
	r = _r;
	g = _g;
	b = _b;
}

// Sets the font size of the text.
void Text::set_size(int _size) {
	font_size = _size;
	font = al_load_ttf_font(font_file.c_str(), font_size, 0);
}
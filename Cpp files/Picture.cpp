#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "Picture.h"
#include <iostream>

// Default constructor. Doesn't build the picture yet.
Picture::Picture(): Graphic() {
	file = "";
	bitmap = nullptr;
	resize = 1;
}

// Sets the picture name and file name.
Picture::Picture(std::string _name, std::string _file): Graphic(_name) {
	file = _file;
	bitmap = al_load_bitmap(file.c_str());
	resize = 1;
}

// Sets the picture name and file name, as well as its coordinates. 
Picture::Picture(std::string _name, std::string _file, int _x, int _y): Graphic(_name, _x, _y) {
	file = _file;
	bitmap = al_load_bitmap(file.c_str());
	resize = 1;
}

// Full constructor. Sets picture name, file name, coordinates, and resize value.
Picture::Picture(std::string _name, std::string _file, int _x, int _y, float _resize) : Graphic(_name, _x, _y) {
	file = _file;
	bitmap = al_load_bitmap(file.c_str());
	resize = _resize;
}

Picture::~Picture() {
	al_destroy_bitmap(bitmap);
	bitmap = nullptr;
}

// Draws the picture onto the screen.
void Picture::draw() {
	if (!hidden && bitmap != nullptr) {
		al_draw_scaled_bitmap(bitmap, 0, 0, 
			al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),
			x, y, al_get_bitmap_width(bitmap)*resize, al_get_bitmap_height(bitmap)*resize, 0);
	}
}

// Returns true if the given Click coordinates collide with the picture.
bool Picture::wasClicked(int _x, int _y) {
	if (hidden) {
		return false;
	}
	int width = al_get_bitmap_width(bitmap) * resize;
	int height = al_get_bitmap_height(bitmap) * resize;

	return (_x >= x && _x <= x + width && _y >= y && _y <= y + height);
}

// Changes the picture to the given file name.
void Picture::changePicture(std::string _file) {
	if (file == _file) {
		return;
	}
	file = _file;
	bitmap = al_load_bitmap(file.c_str());
}

// Sets the resize of the picture. 1 = default scale (100%)
void Picture::set_resize(float _resize) {
	resize = _resize;
}

// Returns the current resize percentage of the picture.
float Picture::get_resize() const {
	return resize;
}
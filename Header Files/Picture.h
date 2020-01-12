#pragma once
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "Graphic.h"

class Picture: public Graphic {
public:
	Picture();
	Picture(std::string _name, std::string _file);
	Picture(std::string _name, std::string _file, int _x, int _y);
	Picture(std::string _name, std::string _file, int _x, int _y, float _resize);
	~Picture();
	void draw();
	bool wasClicked(int _x, int _y);
	void changePicture(std::string _file);
	void set_resize(float _resize);
	float get_resize() const;

private:
	float resize;
	std::string file;
	ALLEGRO_BITMAP* bitmap;
	
};
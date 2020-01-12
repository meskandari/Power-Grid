#pragma once
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class Graphic {
public:
	Graphic();
	Graphic(std::string _name);
	Graphic(std::string _nameint, int _x, int _y);
	virtual ~Graphic();
	void move(int _x, int _y);
	void set_pos(int _x, int _y);
	virtual void draw()=0;
	virtual bool wasClicked(int _x, int _y)=0;
	void hide();
	void show();
	bool isHidden() const;
	std::string get_name();

protected:
	int x;
	int y;
	bool hidden;
	std::string name;

};
#include "Graphic.h"
#include "View.h"
#include <string>
#include <vector>
#include <iostream>

// Default constructor. Sets all values to default, then adds itself to the list of views.
View::View() {
	x = 0;
	y = 0;
	hidden = false;
	layer = 0;
	name = "";
	add_view(this);
}

// Sets up the name, on top of the default values.
View::View(std::string _name) {
	x = 0;
	y = 0;
	hidden = false;
	layer = 0;
	name = name;
	add_view(this);
}

// Sets up the name as well as the coordinates.
View::View(std::string _name, int _x, int _y) {
	x = _x;
	y = _y;
	hidden = false;
	layer = 0;
	name = name;
	add_view(this);
}

// Deletes all of its graphics before deleting itself.
View::~View() {
	for (int i = 0; i < (int)graphics.size(); i++) {
		delete graphics[i];
		graphics[i] = nullptr;
	}
	graphics.empty();
	//remove_view(name);
}

// Draws all of its visible graphics.
void View::draw() {
	if (!hidden) {
		for (int i = 0; i < (int)graphics.size(); i++) {
			graphics[i]->draw();
		}
	}
}
	
// Moves itself (graphics included) by the specified ammounts.
void View::move(int _x, int _y) {
	for (int i = 0; i < (int)graphics.size(); i++) {
		graphics[i]->move(_x, _y);
	}
	x += _x;
	y += _y;
}

// Sets the position (graphics included) to the specified coordinates.
void View::set_pos(int _x, int _y) {
	int moveX = _x - x;
	int moveY = _y - y;
	move(moveX, moveY);
}

// Checks if any of its graphics was clicked. A custom function may be used instead.
bool View::wasClicked(int _x, int _y) {
	for (int i = 0; i < (int)graphics.size(); i++) {
		if (graphics[i]->wasClicked(_x, _y)) {
			return true;
		}
	}
	return false;
}

// Hides the View, preventing it from being rendered.
void View::hide() {
	hidden = true;
}

// Shows the View so it can be rendered.
void View::show() {
	hidden = false;
}

// Returns if it is hidden or not.
bool View::isHidden() const {
	return hidden;
}

// Sets the layer of the View. Although they are rendered in declared order, this allows to make sure one is rendered under or over another.
void View::set_layer(int _layer) {
	if (layer == _layer) {
		return;
	}
	int pos = -1;
	for (int i = 0; i < (int)views.size(); i++) {
		if (views[i] == this) {
			pos = i;
			break;
		}
	}

	views.erase(views.begin() + pos);
	layer = _layer;
	add_view(this);

}

// Returns the layer of the view.
int View::get_layer() const {
	return layer;
}

// Returns a list of all the graphics registered.
std::vector<Graphic*> View::get_graphics() {
	return std::vector<Graphic*>(graphics);
}

// Adds a graphic to the list.
void View::add_graphic(Graphic* graphic) {
	graphics.push_back(graphic);
}

// Removes a graphic to the list, using its name.
void View::remove_graphic(std::string _name) {
	for (int i = 0; i < (int)graphics.size(); i++) {
		if (graphics[i]->get_name() == _name) {
			delete graphics[i];
			graphics[i] = nullptr;
			graphics.erase(graphics.begin() + i);
		}
	}
}

// Static function. Searches for a view with a specific name.
View* View::get_view(std::string _name) {
	for (int i = 0; i < (int)views.size(); i++) {
		std::cout << views[i]->name << "\n";
		if (views[i]->name == _name) {
			return views[i];
		}
	}
	return nullptr;
}

// Static function. Adds a view to the list of Views.
void View::add_view(View* view) {
	for (int i = 0; i < (int)views.size(); i++) {
		if (views[i]->get_layer() < view->get_layer()) {
			views.insert(views.begin() + i, view);
			return;
		}
	}
	views.insert(views.begin() + views.size(), view);
}

// Static function. Removes a view from the list, using its name. Bugged for some reason.
bool View::remove_view(std::string _name) {
	for (int i = 0; i < (int)views.size(); i++) {
		if (views[i]->name == _name) {
			delete views[i];
			views[i] = nullptr;
			views.erase(views.begin() + i);
			return true;
		}
	}
	return false;
}

// Draws all the registered Views onto the display.
void View::drawAll() {
	for (int i = 0; i < (int)views.size(); i++) {
		views[i]->draw();
	}
}

// Calls the destructor for all registered Views.
void View::deleteAll() {
	while (views.size() > 0) {
		std::cout << views.size() << "\n";
		delete views[0];
		views[0] = nullptr;
		views.erase(views.begin());
	}
}

// List of registered Views. The driver uses these for rendering all Views onto the screen.
std::vector<View*> View::views;
#pragma once
#include <allegro5\allegro.h>

// Controller Parent class. Every Controller of the game must inherit from this.

class Controller {
public:
	
	// Default constructor. The parent one is empty; implementation of each controller will be different.
	Controller();
	virtual ~Controller();

	// Called on every frame. Default implementation is no functionality.
	virtual void onUpdate();

	// Called whenever a mouse button is pressed, with coordinates passed. As it is a click-based game, all Controllers must implement this.
	virtual void onClick(int _x, int _y) = 0;

	// Called whenever a mouse button is released, with coordinates passed.
	virtual void onClickRelease(int _x, int _y);

	// Called whenever the mouse moves within the window, with coordinates passed.
	virtual void onMouseMove(int _x, int _y);

	// Called whenever a keyboard button is pressed. An int corresponding to the key is passed:
	// See the Allegro documentation for more information.
	virtual void onKeyPress(int keyState);

	// Called when the Controller becomes the active controller. This is the time to unhide views and set things up.
	virtual void onLoad() = 0;

	// Called when the Controller becomes unactive (Ending the phase). This is where to hide views and declare the next phase.
	virtual void onUnload() = 0;

	// Called every frame. If it returns true, onUnload is called and the game moves to the next Phase.
	virtual bool phasedEnded() = 0;

};
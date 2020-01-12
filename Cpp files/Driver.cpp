#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include "FactoryCard.h"
#include "FactoryMarket.h"
#include "Resource.h"
#include "ResourceMarket.h"
#include "Step3Card.h"
#include "Controller.h"
#include "Model.h"
#include "View.h"
#include "Phase1Controller.h"
#include "Phase2Controller.h"
#include "Phase3Controller.h"
#include "Phase4Controller.h"
#include "Phase5Controller.h"
#include "StartController.h"
#include "SideController.h"
#include <iostream>
#include "Aggressive.h"
#include "Moderate.h"

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

int setupTestModel() {
	// Set the number of the phase you wish to test here. 3 for Phase 3, etc.
	int testPhase = -1;
	// If -1, executes the program correctly.
	if (testPhase == -1) return -1;

	new Model();
	Model::add_player(new Player("Bob", "Red", 4));
	Model::set_currentPlayer("Red");
	Model::get_currentPlayer()->setStrategy(new Aggressive());
	Model::get_currentPlayer()->addFactory((FactoryCard*)Model::get_deck()->pull());
	Model::get_currentPlayer()->addFactory((FactoryCard*)Model::get_deck()->pull());
	Model::get_currentPlayer()->addFactory((FactoryCard*)Model::get_deck()->pull());
	Model::get_currentPlayer()->addFactory((FactoryCard*)Model::get_deck()->pull());
	for (int i = 0; i < Model::get_currentPlayer()->getFactories().size(); i++) {
		FactoryCard* factory = Model::get_currentPlayer()->getFactories()[i];
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 4; k++) {
				Model::get_currentPlayer()->addResource(factory->get_value(), k, 1);
			}
		}
	}

	Model::add_player(new Player("Jack", "Blue", 4));
	Model::set_currentPlayer("Blue");
	Model::get_currentPlayer()->setStrategy(new Moderate());
	Model::get_currentPlayer()->addFactory((FactoryCard*)Model::get_deck()->pull());
	Model::get_currentPlayer()->addFactory((FactoryCard*)Model::get_deck()->pull());
	Model::get_currentPlayer()->addFactory((FactoryCard*)Model::get_deck()->pull());
	Model::get_currentPlayer()->addFactory((FactoryCard*)Model::get_deck()->pull());
	for (int i = 0; i < Model::get_currentPlayer()->getFactories().size(); i++) {
		FactoryCard* factory = Model::get_currentPlayer()->getFactories()[i];
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 4; k++) {
				Model::get_currentPlayer()->addResource(factory->get_value(), k, 1);
			}
		}
	}
	Model::set_phase(testPhase);

	return testPhase;
}

int main() {
	// Allegro specific initialization.
	ALLEGRO_DISPLAY * display;
	ALLEGRO_EVENT_QUEUE *queue;

	al_init();
	display = al_create_display(1800, 700);
	queue = al_create_event_queue();

	al_install_keyboard();
	al_install_mouse();

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_mouse_event_source());

	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	bool running = true;

	int testPhase = setupTestModel();

	Controller* controllers[5];
	controllers[0] = new Phase1Controller();
	controllers[1] = new Phase2Controller();
	controllers[2] = new Phase3Controller();
	controllers[3] = new Phase4Controller();
	controllers[4] = new Phase5Controller();
	Controller* startController = new StartController();
	Controller* activeController = nullptr;
	SideController* sideController = new SideController();
	if (testPhase == -1) { 
		activeController = startController;
	}
	else { 
		activeController = controllers[testPhase - 1]; 
		startController->onUnload();
		SideView* sideView = (SideView*)View::get_view("SideView");
		sideView->findAndAttach();
		sideView = nullptr;
	}

	activeController->onLoad();


	// Game loop.
	while (running) {
		// Draw the screen, as well as all created Views.
		al_clear_to_color(al_map_rgba_f(0.5, 0.5, 0.5, 1));
		View::drawAll();
		al_flip_display();

		// Event handling. Events are only sent to the Active controller.
		ALLEGRO_EVENT event;

		activeController->onUpdate();

		if (!al_is_event_queue_empty(queue)) {
			al_wait_for_event(queue, &event);

			switch (event.type) {
			case ALLEGRO_EVENT_DISPLAY_CLOSE: 
				running = false;
				break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				activeController->onClick(event.mouse.x, event.mouse.y);
				sideController->onClick(event.mouse.x, event.mouse.y);
				break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				activeController->onClickRelease(event.mouse.x, event.mouse.y);
				break;
			case ALLEGRO_EVENT_MOUSE_AXES:
				activeController->onMouseMove(event.mouse.x, event.mouse.y);
				break;
			case ALLEGRO_EVENT_KEY_DOWN:
				activeController->onKeyPress(event.keyboard.keycode);
				break;
			}
		}

		// Check if the active Controller has ended its phase. If so, sets the next Controller as Active.
		if (activeController->phasedEnded()) {
			activeController->onUnload();
			activeController = controllers[Model::get_phase() - 1];
			activeController->onLoad();
		}

	}

	// After closing the game, destroy all objects.
	al_destroy_display(display);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	View::deleteAll();
	Model::remove();
	for (int i = 0; i < 5; i++) {
		delete controllers[i];
		controllers[i] = nullptr;
	}
	delete startController;
	startController = nullptr;
	activeController = nullptr;

	return 0;
}
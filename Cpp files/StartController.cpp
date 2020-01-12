#include "StartController.h"
#include "View.h"
#include "Sideview.h"

StartController::StartController() :Controller() {
	startView = new StartView();
	endOfPhase = false;
	state = 0;
}

StartController::~StartController() {

}

void StartController::onClick(int _x, int _y) {
		if (state == 0) { // Start or New Game state
		if (startView->newGameClicked(_x, _y)) {
			new Model();
			PowerGridLoader = Model::get_mapLoader();
			startView->playerCountState();
			state = 1;
		}
		else if (startView->loadGameClicked(_x, _y)) {
			endOfPhase = true;
		}
	}
	else if (state == 1) { // Select Player count state.
		playercount = startView->playerCountClicked(_x, _y);
		counter = playercount;
		if (startView->playerCountClicked(_x, _y) > 0) {
			startView->regionChoiceState(playercount);
			state = 2;
		}
	}
	else if (state == 2) { // Select Region areas state.
		selection = startView->regionConfirmClicked(_x, _y);
		if (selection != nullptr) {
			// Insert the code to check if the selection is valid here.
			int selectedAreas = 0;;
			for (int i = 0; i < 6; i++) {
				if (selection[i] == true)
					selectedAreas++;
			}
			if (selectedAreas != playercount) {
				cout << "the areas are selected is not match with player number\n";
				return;
			}
			if (playercount < 5)
				if (PowerGridLoader->checkAdjacentArea(selection, 6) == true) {
					PowerGridLoader->setActiveArea(selection, 6);
					startView->colorChoiceState();
					state = 3;
				}
				else
					cout << "the areas are ot adjacent.select again:\n";
			else {
				PowerGridLoader->setActiveArea(selection, 6);
				startView->colorChoiceState();
				state = 3;
			}
		}
		else {
			startView->regionClicked(_x, _y);
		}
	}
	else if (state == 3) { // Select player color state.
			 
			 if (playercount > 2)
					_maxFactory = 3;
			 else
					_maxFactory = 4;
			
			_color = startView->colorClicked(_x, _y);
		if (_color != "") {
			startView->nameInputState();
			state = 4;
		}
	}
	else if (state == 4) { // Select player name state.
			cout << "give me a name:\n";
			cin >> _name;
		if (startView->continueButtonclicked(_x, _y)) {
			startView->strategyChoiceState();
			state = 5;
		}
	}
	else if (state == 5) { // Select player strategy state.
		int strategy = startView->strategyButtonClicked(_x, _y);
		if (strategy >= 0) {
			Player* _player=new Player(_name, _color, _maxFactory);
			switch (strategy){
			case 0:
				_player->setStrategy(new Aggressive());
				break;
			case 1:
				_player->setStrategy(new Moderate());
				break;
			case 2:
				_player->setStrategy(new Environmentalist());
				break;
			}
			Model::add_player(_player);
			counter--;
			if (counter >0) {
				startView->colorChoiceState();
				state = 3;
			}
			else
				endOfPhase = true;

		}
	}
}

void StartController::onLoad() {
	endOfPhase = false;
}
void StartController::onUnload() {
	startView->hide();
	Model::set_phase(1);
	SideView* sideView = (SideView*)View::get_view("SideView");
	sideView->findAndAttach();
	sideView = nullptr;
}

bool StartController::phasedEnded() {
	return endOfPhase;
}
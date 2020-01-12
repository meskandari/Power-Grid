#pragma once

#include "View.h"
#include "Graphic.h"
#include "Text.h"
#include "Picture.h"
#include <string>
#include "Player.h"

class Phase5View : public View {
public:
	Phase5View();
	~Phase5View();
	void update();
	int buttonClicked(int _x, int _y);
	void activateFactory(int pos);
	void deactivateFactory(int pos);
	void set_activeCities(int count);
	void set_state(int state);
	void findAndAttach();

private:
	Picture* activatedFactories[4];
	Picture* activateButtons[4];
	Text* currentPlayer;
	Text* currentHouses;
	Text* currentElektro;
	Text* incomeText[22];
	Text* bottomText;
	Picture* incomeSelect;
	Picture* endTurnButton;
	int activeCities;
	const int elektro[22] = { 10, 22, 33, 44, 54, 64, 73, 82, 90, 98, 105, 112, 118, 124, 129, 134, 138, 142, 145, 148, 150, 150 };
};
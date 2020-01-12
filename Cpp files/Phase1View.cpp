#include "View.h"
#include "Graphic.h"
#include "Text.h"
#include "Picture.h"
#include <string>
#include "Player.h"
#include "Phase1View.h"

Phase1View::Phase1View() {
	add_graphic(new Text("phase1Title", "Phase 1: Player Turn Order", 360, 20, 50));
	add_graphic(new Text("instruction", "The player turn order has been decided.", 400, 650));

	continueButton = new Picture("continueButton", "image\\ContinueButton.png", 525, 550);
	add_graphic(continueButton);
}
Phase1View::~Phase1View() {}

void Phase1View::update() {}

bool Phase1View::continueClicked(int _x, int _y) {
	return continueButton->wasClicked(_x, _y);
}

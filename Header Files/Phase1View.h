#pragma once

#include "View.h"
#include "Graphic.h"
#include "Text.h"
#include "Picture.h"
#include <string>
#include "Player.h"

class Phase1View : public View {
public:
	Phase1View();
	~Phase1View();
	void update();
	bool continueClicked(int _x, int _y);
private:
	Picture* continueButton;
};
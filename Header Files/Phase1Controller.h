#pragma once

#include "Controller.h"
#include <vector>
#include <iostream>
#include "Model.h"
#include "Player.h"
#include "Phase1View.h"
#include "PlayerOrderView.h"

class Phase1Controller : public Controller {
public:
	Phase1Controller();
	~Phase1Controller();
	void onClick(int _x, int _y);
	void onLoad();
	void onUnload();
	bool phasedEnded();
private:
	bool endOfPhase;
	int* playersOrderIndex;
	Player** playersCurrentOrder;
	Phase1View* phase1view;
	PlayerOrderView* playerOrderView;
	
};
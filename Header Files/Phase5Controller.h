#pragma once

#include "Controller.h"
#include "Phase5View.h"
#include "PlayerFactoriesView.h"
#include "ResourceMarketView.h"
#include "FactoryMarketView.h"

class Phase5Controller : public Controller {
public:
	Phase5Controller();
	~Phase5Controller();
	void onClick(int _x, int _y);
	void onLoad();
	void onUnload();
	bool phasedEnded();
	void onMouseMove(int _x, int _y);
	void onClickRelease(int _x, int _y);
private:
	bool endOfPhase;
	Phase5View* phase5view;
	PlayerFactoriesView* factoriesView;
	ResourceMarketView* resMarketView;
	FactoryMarketView* facMarketView;
	

	bool dragging;
	bool activated[4];
	int poweredCities;
	int state;

	void toggleFactory(int pos);
	void endTurn();
	void endPhase();
	void restockMarkets();

	// [playerCount-2][step-1][resourceType]
	const int resRestock[5][3][4] = { {{3, 2, 1, 1}, {4, 2, 2, 1}, {3, 4, 3, 1}},
									  {{4, 2, 1, 1}, {5, 3, 2, 1}, {3, 4, 3, 1}},
									  {{5, 3, 2, 1}, {6, 4, 3, 2}, {4, 5, 4, 2}},
									  {{5, 4, 3, 2}, {7, 5, 3, 3}, {5, 6, 5, 2}},
									  {{7, 5, 3, 2}, {9, 6, 5, 3}, {6, 7, 6, 3}}};
};
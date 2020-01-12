#pragma once

#include "Controller.h"
#include "ResourceMarketView.h"
#include "Phase3View.h"
#include "PlayerFactoriesView.h"
#include <string>

class Phase3Controller : public Controller {
public:
	Phase3Controller();
	~Phase3Controller();
	void onClick(int _x, int _y);
	void onMouseMove(int _x, int _y);
	void onClickRelease(int _x, int _y);
	void onLoad();
	void onUnload();
	bool phasedEnded();
private:
	bool endOfPhase;
	ResourceMarketView* resMarketView;
	Phase3View* phase3view;
	PlayerFactoriesView* factoriesView;

	bool dragging;
	int currentResourceType;
	int count;
	int price;

	void dragResourceStart(int factoryPos, int resourcePos);
	void dragResourceEnd(int factorySource, int resourcePos, int factoryTarget, bool placeBefore);
	void changeResourceType(int type);
	void increaseCount();
	void decreaseCount();
	void buy();
	void endTurn();
};
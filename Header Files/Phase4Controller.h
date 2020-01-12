#pragma once

#include "Controller.h"
#include "Phase4View.h"

class Phase4Controller : public Controller {
public:
	Phase4Controller();
	~Phase4Controller();
	void onClick(int _x, int _y);
	void onLoad();
	void onUnload();
	bool phasedEnded();
private:
	Phase4View* phase4view;
	std::string curCity;
	bool endOfPhase;
};
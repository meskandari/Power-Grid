#pragma once

#include "View.h"
#include "Graphic.h"
#include "Text.h"
#include "Picture.h"
#include <string>
#include "FactoryMarket.h"

class FactoryMarketView : public View {
public:
	FactoryMarketView();
	~FactoryMarketView();
	void update();
	int factoryClicked(int _x, int _y);
	void findAndAttach();
private:
	Picture* factories[8];
	FactoryMarket* facMarket;
};
#pragma once

#include "View.h"
#include "Graphic.h"
#include "Text.h"
#include "Picture.h"
#include <string>
#include "FactoryMarketView.h"
#include "FactoryMarket.h"
#include "Model.h"

// Factory Market View. Shows all the factory cards on the Factory market.
FactoryMarketView::FactoryMarketView() {
	facMarket = nullptr;
	for (int i = 0; i < 8; i++) {
		factories[i] = new Picture("FacMarket" + std::to_string(i), "", (i % 4) * 130, (int)(i / 4) * 130, 0.15);
		add_graphic(factories[i]);
	}
}

FactoryMarketView::~FactoryMarketView() {

}

// Updates the data of the factory market.
void FactoryMarketView::update() {
	facMarket->print();
	for (int i = 0; i < 8; i++) {
		FactoryCard* factory = facMarket->getFactory(i);
		if (factory != nullptr) {
			factories[i]->changePicture("image\\" + std::to_string(factory->get_value()) + ".png");
			factories[i]->show();
		}
		else {
			factories[i]->hide();
		}
	}
}

// Returns the index of the factory that was clicked. If none was clicked, returns -1.
int FactoryMarketView::factoryClicked(int _x, int _y) {
	for (int i = 0; i < 8; i++) {
		if (factories[i]->wasClicked(_x, _y)) {
			return i;
		}
	}
	return -1;
}

void FactoryMarketView::findAndAttach() {
	if (facMarket == nullptr) {
		facMarket = Model::get_factoryMarket();
		if (facMarket != nullptr) {
			facMarket->attach(this);
			update();
		}
	}
}
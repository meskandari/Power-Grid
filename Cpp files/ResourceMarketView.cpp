#include "ResourceMarketView.h"
#include "Picture.h"
#include "Text.h"
#include <string>
#include "Resource.h"
#include "ResourceMarket.h"
#include "Model.h"

// Resource Market View. Displays the current state of the Resource Market.
ResourceMarketView::ResourceMarketView() : View("Resource Market") {
	add_graphic(new Picture("CoalRM", "image\\CoalRM.png", 000, 000, 0.8));
	add_graphic(new Picture("OilRM", "image\\OilRM.png", 000, 100, 0.8));
	add_graphic(new Picture("GarbageRM", "image\\GarbageRM.png", 000, 200, 0.8));
	add_graphic(new Picture("UraniumRM", "image\\UraniumRM.png", 000, 300, 0.8));
	for (int i = 0; i < 4; i++) {
		std::string type = Resource::codeToName(i);
		costs[i] = new Text((type + "Cost").c_str(), "10", 170, i * 100 + 10);
		remainings[i] = new Text((type + "Remaining").c_str(), "+10", 210, i * 100 + 40);
		stock[i] = new Text((type + "Stock").c_str(), "(10)", 260, i * 100 + 40);
		add_graphic(costs[i]);
		add_graphic(remainings[i]);
		add_graphic(stock[i]);
		for (int j = 0; j < 3; j++) {
			resources[i][j] = new Picture((type + std::to_string(j)), ("image\\" + type + ".png"), 10 + j * 55, 050 + 100 * i, 0.45);
			add_graphic(resources[i][j]);
		}
		
	}
	resources[3][0]->hide();
	resources[3][1]->hide();

	market = nullptr;
}

ResourceMarketView::~ResourceMarketView() {}

// Updates the View according to the current state of the Market.
void ResourceMarketView::update() {
	int toShow[4] = { 0, 0, 0, 0 }; // How many resources should be displayed for each type.
	for (int i = 0; i < 4; i++) {
		if (market->getPrice(i, 1) >= 1) {
			costs[i]->set_text(std::to_string(market->getPrice(i, 1)));
		}
		else {
			costs[i]->set_text("X");
		}
		stock[i]->set_text("(" + std::to_string(market->get_reserveResource(i)) + ")");
		toShow[i] = market->get_marketResource(i) % 3;
		if (toShow[i] == 0 && market->get_marketResource(i) > 0) {
			toShow[i] = 3;
		}
	}
	// Specific case for Uranium: Only 1 can be shown at most.
	if (market->get_marketResource(3) > 0) {
		toShow[3] = 1;
	}
	else {
		toShow[3] = 0;
	}

	// Shows or hides the specified amount, with visibles starting from the right.
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (j >= 3 - toShow[i]) {
				resources[i][j]->show();
			}
			else {
				resources[i][j]->hide();
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		remainings[i]->set_text("+" + std::to_string(market->get_marketResource(i)-toShow[i]));
	}

}

void ResourceMarketView::findAndAttach() {
	if (market == nullptr) {
		market = Model::get_resourceMarket();
		if (market != nullptr) {
			market->attach(this);
			update();
		}
	}
}
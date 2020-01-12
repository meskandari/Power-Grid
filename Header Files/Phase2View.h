#pragma once

#include "View.h"
#include "Graphic.h"
#include "Text.h"
#include "Picture.h"
#include <string>
#include "Player.h"
#include "Model.h"

class Phase2View : public View {
public:
	Phase2View();
	~Phase2View();
	void update();
	bool buyClicked(int _x, int _y);
	bool endTurnClicked(int _x, int _y);
	void hideButtons();
	void showButtons();
	void setBottomMessage(std::string message);
	void setStrategy(std::string strategy);
	void findAndAttach();
private:
	Picture* endTurnButton;
	Picture* buyButton;
	Text* playerName;
	Text* playerHouses;
	Text* playerElektro;
	Text* bottomMessage;
	Text* strategyText;
	Player* player;
};
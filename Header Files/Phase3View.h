#pragma once

#include "View.h"
#include "Graphic.h"
#include "Text.h"
#include "Picture.h"
#include <string>
#include "Player.h"

class Phase3View : public View {
public:
	Phase3View();
	~Phase3View();
	void update();
	void set_player(Player* _player);
	void set_price(int price);
	void set_count(int count);
	void set_currentResource(int type);
	int buttonClicked(int _x, int _y);
private:
	Picture* endTurnButton;
	Picture* resButtons[4];
	Picture* selectedResource;
	Text* countText;
	Text* priceText;
	Text* curPlayer;
	Text* curElektroText;
	Text* curHousesText;
	Picture* increaseButton;
	Picture* decreaseButton;
	Picture* buyButton;
	Player* player;
};
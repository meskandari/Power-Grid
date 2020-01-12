#pragma once

#include "View.h"
#include "Graphic.h"
#include "Text.h"
#include "Picture.h"
#include "Player.h"

class PlayerInfoView : public View {
public:
	PlayerInfoView();
	~PlayerInfoView();
	void set_player(Player* _player);
	bool isSet();
	void update();
private:
	Picture* resources[4][6];
	Picture* factories[4];
	Text* playerName;
	Text* playerHouse;
	Text* playerElektro;
	Picture* playerColor;
	Player* player;
};
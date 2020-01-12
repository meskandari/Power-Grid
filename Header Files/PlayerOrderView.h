#pragma once

#include "View.h"
#include "Graphic.h"
#include "Text.h"
#include "Picture.h"
#include <string>
#include "Player.h"

class PlayerOrderView : public View {
public:
	PlayerOrderView();
	~PlayerOrderView();
	void update();
	void findAndAttach();
private:
	Picture* playerColors[6];
	Text* playerNames[6];
};
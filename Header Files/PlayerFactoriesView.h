#pragma once

#include "View.h"
#include "Graphic.h"
#include "Text.h"
#include "Picture.h"
#include "Player.h"

class PlayerFactoriesView : public View {
public:
	PlayerFactoriesView();
	PlayerFactoriesView(Player* _player);
	~PlayerFactoriesView();
	void set_player(Player* _player);
	void update();
	int factoryClicked(int _x, int _y);
	bool startResourceDrag(int _x, int _y);
	void updateResourceDrag(int _x, int _y);
	std::vector<int> stopResourceDrag(int _x, int _y);
private:
	Picture* resources[4][6];
	Picture* factories[4];
	Picture* draggedResource;
	int draggedResourceType;
	int draggedResourceSlot[3]; // [ Factory Slot, Resource Picture slot, Resource Data slot ]
	Player* player;
};
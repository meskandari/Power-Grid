#pragma once
#include "Deck.h"
#include "FactoryMarket.h"
#include "ResourceMarket.h"
#include "Player.h"
#include <string>
#include "Subject.h"
#include "mapLoader.h"
#include "Mymap.h"
#include "Strategy.h"
#include "Aggressive.h"
#include "Moderate.h"
#include "Environmentalist.h"

class Model : public Subject {
public:
	Model();
	Model(std::string file);
	~Model();

	static Deck* get_deck();
	static FactoryMarket* get_factoryMarket();
	static ResourceMarket* get_resourceMarket();
	static Mymap* get_map();
	static MapLoader* get_mapLoader();
	static void set_map(Mymap* _map);
	static void set_mapLoader(MapLoader* _mapLoader);
	static int get_step();
	static void set_step(int _step);
	static int get_phase();
	static void set_phase(int _phase);
	static void add_player(Player* player);
	static Player* get_currentPlayer();
	static void set_currentPlayer(std::string color);
	static void set_currentPlayer(int pos);
	static bool next_player();
	static bool previous_player();
	static int get_playerCount();
	static Player* get_player(std::string color);
	static Player** get_players();
	static void set_players(Player** _players);
	static bool isInstanciated();
	static void initialize();
	static void save();
	static void remove();
	static bool attachToModel(Observer* o);

private:
	Deck* deck;
	FactoryMarket* factoryMarket;
	ResourceMarket* resourceMarket;
	Player* players[6];
	Mymap* map;
	MapLoader* maploader;

	int playerCount;
	int currentPlayer;
	int step;
	int phase;

	static Model* model;

};
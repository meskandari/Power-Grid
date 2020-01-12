#pragma once
#include "Deck.h"
#include "FactoryMarket.h"
#include "ResourceMarket.h"
#include "Player.h"
#include <string>
#include <iostream>
#include <fstream>
#include "Model.h"
#include "mapLoader.h"
#include "Mymap.h"

// Default constructor. For new games.
Model::Model() {
	deck = new Deck();
	factoryMarket = new FactoryMarket();
	resourceMarket = new ResourceMarket();
	
	maploader = new MapLoader("PowerGridMap.txt");
	map = maploader->getPowerGridMap();

	playerCount = 0;
	currentPlayer = 0;
	step = 1;
	phase = 0;

	model = this;
	initialize();
}

// Save file constructor. Loads the game using the various Save files.
Model::Model(std::string file) {
	deck = new Deck("deck.sav");
	factoryMarket = new FactoryMarket("facMarket.sav");
	resourceMarket = new ResourceMarket("resMarket.sav");

	MapLoader* maploader = new MapLoader("PowerGridMap.txt");
	map = maploader->getPowerGridMap();

	std::ifstream iFile;
	iFile.open(file);
	if (iFile) {
		iFile >> playerCount;
		iFile >> currentPlayer;
		iFile >> step;
		iFile >> phase;
		for (int i = 0; i < playerCount; i++) {
			std::string color;
			iFile >> color;
			add_player(new Player("player" + color + ".sav"));
		}
		iFile.close();
	}

	model = this;
}

// Destructor. Also deletes all of the classes used in the game.
Model::~Model() {
	delete deck;
	deck = nullptr;
	delete factoryMarket;
	factoryMarket = nullptr;
	delete resourceMarket;
	resourceMarket = nullptr;
	for (int i = 0; i < playerCount; i++) {
		delete players[i];
		players[i] = nullptr;
	}
}

// Gives access to the deck of the game.
Deck* Model::get_deck() {
	return model->deck;
}

// Gives access to the Factory Market of the game.
FactoryMarket* Model::get_factoryMarket() {
	return model->factoryMarket;
}

// Gives access to the Resource Market of the game.
ResourceMarket* Model::get_resourceMarket() {
	return model->resourceMarket;
}

Mymap* Model::get_map() {
	return model->map;
}

 MapLoader* Model::get_mapLoader() {
	 return model->maploader;
}

void Model::set_map(Mymap* _map) {
	model->map = _map;
}

void Model::set_mapLoader(MapLoader* _mapLoader) {
	model->maploader = _mapLoader;

}

// Returns the current Step of the game (1, 2 or 3)
int Model::get_step() {
	return model->step;
}

// Sets the current step of the game. This only changes the value, effects on other game components must be done in the Controller.
void Model::set_step(int _step) {
	model->step = _step;
	model->notify();
}

// Returns the current phase of the game. 
int Model::get_phase() {
	return model->phase;
}

// Sets the current phase of the game. Should be set in the Controller's onUnload() function.
void Model::set_phase(int _phase) {
	model->phase = _phase;
}

// Adds a new Player to the game. 
void Model::add_player(Player* player) {
	if (model->playerCount >= 6) {
		return;
	}
	model->players[model->playerCount] = player;
	model->playerCount++;
}

// Returns the active player of the game.
Player* Model::get_currentPlayer() {
	return model->players[model->currentPlayer];
}

// Moves to the next player. Returns false if it was the last player.
bool Model::next_player() {
	if (model->currentPlayer == model->playerCount - 1) {
		return false;
	}
	model->currentPlayer++;
	model->notify();
	return true;
}

// Moves to the previous player. Returns false if it was the first player.
bool Model::previous_player() {
	if (model->currentPlayer == 0) {
		return false;
	}
	model->currentPlayer--;
	model->notify();
	return true;
}

// Returns the amount of players.
int Model::get_playerCount() {
	return model->playerCount;
}

// Returns a Player by his or her color.
Player* Model::get_player(std::string color) {
	for (int i = 0; i < model->playerCount; i++) {
		if (model->players[i]->get_color() == color) {
			return model->players[i];
		}
	}
	return nullptr;
}

// Returns all players. For more precise management of the game.
Player** Model::get_players() {
	return model->players;
}

// Sets the players using the given array of Players. For when reordering the order is needed.
void Model::set_players(Player** _players) {
	for (int i = 0; i < model->playerCount; i++) {
		model->players[i] = _players[i];
	}
	model->notify();
}

// Sets the current player, using the player's color.
void Model::set_currentPlayer(std::string color) {
	for (int i = 0; i < model->playerCount; i++) {
		if (model->players[i]->get_color() == color) {
			model->currentPlayer = i;
		}
	}
	model->notify();
}
	
// Sets the current player, using the player's position in the current player order.
void Model::set_currentPlayer(int pos) {
	model->currentPlayer = pos;
	model->notify();
}

bool Model::isInstanciated() {
	return (model != nullptr);
}

// Initializes various classes of the Model for a New game.
void Model::initialize() {
	model->deck->initialize();
	for (int i = 0; i < 8; i++) {
		model->factoryMarket->addFactory((FactoryCard*)model->deck->pull());
	}
	Card* step3card = model->deck->pull();
	model->deck->shuffle();
	model->deck->insert(step3card);
	step3card = nullptr;
	model->resourceMarket->setReserve(24, 24, 24, 12);
	model->resourceMarket->restockMarket(0, 24);
	model->resourceMarket->restockMarket(1, 18);
	model->resourceMarket->restockMarket(2, 6);
	model->resourceMarket->restockMarket(3, 2);
}

// Saves the full game state.
void Model::save() {
	model->deck->saveToFile();
	model->resourceMarket->saveToFile();
	model->factoryMarket->saveToFile();
	for (int i = 0; i < model->playerCount; i++) {
		model->players[i]->saveToFile();
	}

	std::ofstream file;
	file.open("game.sav");
	if (file) {
		file << model->playerCount << "\n";
		file << model->currentPlayer << "\n";
		file << model->step << "\n";
		file << model->phase << "\n";
		for (int i = 0; i < model->playerCount; i++) {
			model->players[i]->saveToFile();
			file << model->players[i]->get_color() << "\n";
		}
		file.close();
	}
}

// Calls the destructor on the Model instance.
void Model::remove() {
	delete model;
	model = nullptr;
}

bool Model::attachToModel(Observer* o) {
	if (model == nullptr) {
		return false;
	}
	else {
		model->attach(o);
		return true;
	}
}

// Model pointer, making the data available from anywhere.
Model* Model::model = nullptr;
#pragma once
#include "Mymap.h"
#include "City.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
enum string_code {
	AddEdge,
	AddCity,
	DefaultVal
};
class MapLoader {
private:
	Mymap* powerGridMap;
	int activeArea[6];
	bool adjacentArea[6][6] = { {0,1,0,0,0,1},{1,0,1,0,0,1},{0,1,0,1,1,1},{0,0,1,0,1,0},{0,0,1,1,0,1},{1,1,1,0,1,0} };

public:
	MapLoader();
	MapLoader(string);
	MapLoader(const MapLoader&);
	~MapLoader();
	MapLoader& operator=(const MapLoader&);
	Mymap* getPowerGridMap()const;
	int* getActiveArea() { return activeArea; }
	string_code hashit(std::string const&);
	void printAreas();
	void printActiveAreas();
	void setActiveArea(bool[], int);
	bool checkAdjacentArea(bool[], int);
};

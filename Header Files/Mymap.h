#pragma once
#include <vector>
#include <iostream>
#include "City.h"
#include <fstream>
#include <string>
#include "Subject.h"

using namespace std;
class Mymap : public Subject {
private:
	const int MaxCap = 42;
	vector<City> cities;
	string areasColor[6] = { "Brown","Green","Red","Blue","Purple","Yellow" };


public:

	Mymap();
	Mymap(int n);
	Mymap(const Mymap&);
	Mymap(Mymap*);
	~Mymap();

	Mymap& operator=(const Mymap&);
	vector<City> getCities()const;
	string* getAreasColor();
	int** getAdjMatrix()const;
	const string* getOwners(string cityname);
	bool addEdge(string, string, unsigned int);
	void addCity(const char*, const char*);
	void addCity(string, string);
	bool checkDuplicate(const char*);
	bool checkDuplicate(string);
	void printMap();
	bool checkAdjCity(string, string);
	bool compare(string, string);
	int getCityPrice(string, string);
	bool buyCity(string, string);
	void floydWarshall();
	int adjMatrix[42][42];

};

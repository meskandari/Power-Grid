#include "Mymap.h"

Mymap::Mymap() {
	cities.reserve(MaxCap);
	/*adjMatrix = new int*[MaxCap];
	for (int i = 0; i < MaxCap; i++) {
	adjMatrix[i] = new int(MaxCap);
	}*/
	//adjMatrix = new int*[MaxCap];
	for (int i = 0; i < MaxCap; i++) {
		//adjMatrix[i] = new int[MaxCap];
		for (int j = 0; j < MaxCap; j++)
			adjMatrix[i][j] = -1;
	}
}
Mymap::Mymap(int n) {
	cities.reserve(n);
	for (int i = 0; i < MaxCap; i++) {
		for (int j = 0; j < MaxCap; j++)
			adjMatrix[i][j] = -1;
	}
}

Mymap::Mymap(const Mymap &CopyMap) {
	cities = CopyMap.getCities();
	for (int i = 0; i < MaxCap; i++) {
		for (int j = 0; j < MaxCap; j++)
			adjMatrix[i][j] = CopyMap.adjMatrix[i][j];
	}
	for (int i = 0; i < 6; i++) {
		areasColor[i] = CopyMap.areasColor[i];
	}
}

Mymap::Mymap(Mymap* CopyMap) {
	cities = CopyMap->getCities();
	for (int i = 0; i < MaxCap; i++) {
		for (int j = 0; j < MaxCap; j++)
			adjMatrix[i][j] = -1;
	}
	for (int i = 0; i < MaxCap; i++) {
		for (int j = 0; j < MaxCap; j++)
			adjMatrix[i][j] = CopyMap->adjMatrix[i][j];
	}
	for (int i = 0; i < 6; i++) {
		areasColor[i] = CopyMap->areasColor[i];
	}
}
Mymap::~Mymap() {

	for (unsigned int i = 0; i < cities.size(); i++)
		cities[i]->~City();
	cities.clear();

}

Mymap& Mymap::operator=(const Mymap &map) {
	if (&map != this) {
		/*for (int i = 0; i < cities.size(); i++)
		delete adjMatrix[i];*/
		//delete adjMatrix;
		for (unsigned int i = 0; i < cities.size(); i++)
			cities[i]->~City();
		cities.clear();
		cities = map.getCities();
		int** _adjMatrix = map.getAdjMatrix();
		for (int i = 0; i < MaxCap; i++) {
			for (int j = 0; j < MaxCap; j++)
				adjMatrix[i][j] = _adjMatrix[i][j];
		}
		for (int i = 0; i < 6; i++) {
			areasColor[i] = map.areasColor[i];
		}
	}
	return *this;
}

vector<City> Mymap::getCities()const {
	vector<City> citiesGetBack;
	for (int i = 0; i < cities.size(); i++) {
		citiesGetBack.emplace_back(cities[i]);
	}
	return citiesGetBack;
}


int** Mymap::getAdjMatrix()const {
	int** _adjMatrix = new int*[MaxCap];
	for (int i = 0; i < MaxCap; i++) {
		_adjMatrix[i] = new int(MaxCap);
	}

	for (int i = 0; i < MaxCap; i++) {
		for (int j = 0; j < MaxCap; j++)
			_adjMatrix[i][j] = adjMatrix[i][j];
	}
	return _adjMatrix;
}

string* Mymap::getAreasColor() {
	string area1, area2;
	int counter = 0;
	area1 = cities[counter].getAreaName();
	areasColor[counter] = area1;
	int n = (int)cities.size();
	for (int i = 0; i < n - 1; i++) {
		area1 = cities[i].getAreaName();
		area2 = cities[i + 1].getAreaName();
		if (area1.compare(area2) != 0)
			areasColor[++counter] = area2;
	}
	return areasColor;
}

const string* Mymap::getOwners(string cityname) {
	const string* ownersColor = new string[3];
	for (int i = 0; i < cities.size(); i++) {
		if (compare(cities[i]->getCityName(), cityname)) {

			ownersColor = cities[i].getOwnersColor();
			break;
		}
	}
	return ownersColor;
}

bool Mymap::addEdge(string resCity, string destCity, unsigned int weight) {
	int resID = -1, destID = -1;
	for (int i = 0; i < MaxCap; i++) {
		if (compare(cities[i]->getCityName(), resCity))
			resID = i;
		else if (compare(cities[i]->getCityName(), destCity))
			destID = i;
		//if (resID != -1 && destID != -1)
		//break;
	}
	if (resID == -1 || destID == -1)
		return false;
	else {
		adjMatrix[resID][destID] = weight;
		adjMatrix[destID][resID] = weight;
	}
	return true;
}

void Mymap::addCity(const char* cityName, const char* areaName) {
	if (checkDuplicate(cityName)) {
		City *city;
		city = new City(cityName, areaName);
		cities.push_back(*city);
	}
}
void Mymap::addCity(string cityName, string areaName) {
	if (checkDuplicate(cityName)) {
		City *city;
		city = new City(cityName, areaName);
		cities.push_back(*city);
	}
}

bool Mymap::checkDuplicate(const char* cityName) {
	for (unsigned int i = 0; i < cities.size(); i++) {
		if (cities[i]->getCityName() == cityName)
			return false;
	}
	return true;
}
bool Mymap::checkDuplicate(string cityName) {
	for (unsigned int i = 0; i < cities.size(); i++) {
		if (cities[i]->getCityName() == cityName)
			return false;
	}
	return true;
}

void Mymap::printMap() {
	ofstream out_file;
	out_file.exceptions(ifstream::badbit); // No need to check failbit
	try {
		out_file.open("./map.txt");
		for (int i = 0; i < MaxCap; i++) {
			for (int j = 0; j < (i + 1); j++) {
				if (adjMatrix[i][j] != -1)
					out_file << "(" << cities[i].getCityName() << ": " << cities[i].getAreaName() <<
					"; " << cities[j].getCityName() << ": " << cities[j].getAreaName() << "=" << adjMatrix[i][j] << ")" << endl;
			}
		}
	}
	catch (const exception e) {
		cout << "Exception opening/reading file" << e.what
		();
	}
	out_file.close();

}


bool Mymap::compare(string NewCityName, string resStr) {
	if (resStr.size() != NewCityName.size())
		return false;
	else
		if (NewCityName.compare(resStr) != 0)
			return false;
	return true;
}


bool Mymap::checkAdjCity(string city1, string city2) {
	if (!checkDuplicate(city1) && !checkDuplicate(city2)) {
		int resID = -1, destID = -1;
		for (int i = 0; i < cities.size(); i++) {
			if (compare(cities[i]->getCityName(), city1.c_str()))
				resID = i;
			else if (compare(cities[i]->getCityName(), city2.c_str()))
				destID = i;
			if (resID != -1 || destID != -1)
				break;
		}
		if (resID == -1 || destID == -1)
			return false;
		else if (adjMatrix[resID][destID] != 0)
			return true;

		return false;
	}
	return false;

}

int Mymap::getCityPrice(string cityName, string playerColor) {
	int Id = -1;
	int Ownerflag = -3;
	int price = 0;
	int minRout = 10000;
	for (int i = 0; i < MaxCap; i++) {
		if (compare(cities[i]->getCityName(), cityName))
			Id = i;
	}
	//if the city not found return -1
	if (Id == -1) {
		return Id;
	}
	if (cities[Id].isAvailableCity()) {
		price = cities[Id].CityPrice() + minRout;
		return price;
	}
	else
		//if the city is not available to buy return -2
		return -2;
	/*if (cities[Id].isAvailableCity()) {
		for (int i = 0; i < MaxCap; i++) {
			if (adjMatrix[Id][i] != -1) {
				if (cities[i].isHeOwner(playerColor)) {
					Ownerflag = 0;
					if (adjMatrix[Id][i] < minRout) {
						minRout = adjMatrix[Id][i];
					}
				}
			}
			else {
				if (Ownerflag == -3)
					return Ownerflag;//return -3 if the city is not adjacent with other cities owned by current player
			}
		}
		//total price calc
		price = cities[Id].CityPrice() + minRout;
		return price;
	}
	else
		//if the city is not available to buy return -2
		return -2;*/
}

bool Mymap::buyCity(string cityName, string playerColor) {
	int Id = -1;
	for (int i = 0; i < MaxCap; i++) {
		if (compare(cities[i]->getCityName(), cityName))
			Id = i;
	}
	if (Id == -1) {
		return false;
	}
	if (this->getCityPrice(cityName, playerColor) >= 0) {
		bool temp = cities[Id].setOwnersColor(playerColor);
		notify();
		return temp;

	}

	return false;
}



void  Mymap::floydWarshall()
{
	/* dist[][] will be the output matrix that will finally have the shortest
	distances between every pair of vertices */
	int V = 5;
	int dist[5][5], i, j, k;

	/* Initialize the solution matrix same as input graph matrix. Or
	we can say the initial values of shortest distances are based
	on shortest paths considering no intermediate vertex. */
	for (i = 0; i < 5; i++)
		for (j = 0; j < V; j++)
			dist[i][j] = adjMatrix[i][j];

	/* Add all vertices one by one to the set of intermediate vertices.
	---> Before start of an iteration, we have shortest distances between all
	pairs of vertices such that the shortest distances consider only the
	vertices in set {0, 1, 2, .. k-1} as intermediate vertices.
	----> After the end of an iteration, vertex no. k is added to the set of
	intermediate vertices and the set becomes {0, 1, 2, .. k} */
	for (k = 0; k < 5; k++)
	{
		// Pick all vertices as source one by one 
		for (i = 0; i < 5; i++)
		{
			// Pick all vertices as destination for the 
			// above picked source 
			for (j = 0; j < 5; j++)
			{
				// If vertex k is on the shortest path from 
				// i to j, then update the value of dist[i][j] 
				if (dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}

	// Print the shortest distance matrix 
	//printSolution(dist);
}


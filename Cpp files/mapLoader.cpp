#include "mapLoader.h"
MapLoader::MapLoader() {
	powerGridMap = new Mymap();
	for (int i = 0; i < 6; i++)
		activeArea[i] = 0;
}

MapLoader::MapLoader(string filepath) {
	string strInput;
	bool flagEdge = false;
	ifstream infile;
	infile.exceptions(ifstream::badbit); // No need to check failbit
	try {

		infile.open(filepath);
		getline(infile, strInput);
		int n = std::stoi(strInput);
		powerGridMap = new Mymap(42);
		while (infile.good()) {
			getline(infile, strInput);
			switch (hashit(strInput)) {
			case AddEdge:
				flagEdge = true;
				break;
			case AddCity:
				flagEdge = false;
				break;
			case DefaultVal:
				if (flagEdge == true) {
					string str1 = strInput;
					getline(infile, strInput);

					string str2 = strInput;
					getline(infile, strInput);
					unsigned int weight = std::stoi(strInput);
					powerGridMap->addEdge(str1, str2, weight);

				}
				else {
					string str1 = strInput;
					//strcpy(str1, strInput.c_str());
					getline(infile, strInput);
					string str2 = strInput;
					//strcpy(str2, strInput.c_str());
					powerGridMap->addCity(str1, str2);

				}
				break;
			}
		}

	}
	catch (const exception e) {
		cout << "Exception opening/reading file";
	}
	infile.close();
	for (int i = 0; i < 6; i++) {
		activeArea[i] = 0;
	}
	powerGridMap->printMap();
}

MapLoader::MapLoader(const MapLoader& CopyMapLoader) {
	powerGridMap = CopyMapLoader.getPowerGridMap();
	for (int i = 0; i < 6; i++)
		activeArea[i] = CopyMapLoader.activeArea[i];

}

MapLoader::~MapLoader() {
	powerGridMap->~Mymap();
	//delete powerGridMap;
}


MapLoader& MapLoader::operator=(const MapLoader& CopyMapLoader) {
	powerGridMap = CopyMapLoader.getPowerGridMap();
	for (int i = 0; i < 6; i++)
		activeArea[i] = CopyMapLoader.activeArea[i];
	return *this;

}


Mymap* MapLoader::getPowerGridMap()const {
	Mymap* powerGridMapGetBack = new Mymap(powerGridMap);
	return powerGridMapGetBack;
}

string_code MapLoader::hashit(std::string const& inString) {
	if (inString == "edges:") return AddEdge;
	if (inString == "cities:") return AddCity;
	else return DefaultVal;
}

void MapLoader::setActiveArea(bool areaCode[], int size) {
	for (int i = 0; i < size; i++) {
		activeArea[i] = areaCode[i];
	}
}


void  MapLoader::printAreas() {
	string* areas = powerGridMap->getAreasColor();
	for (int i = 0; i < 6; i++) {
		cout << "\n" << (i + 1) << "-: ";
		cout << *(areas + i) << endl;
	}

}

void  MapLoader::printActiveAreas() {
	cout << "selected areas are:\n";
	for (int i = 0; i < 6; i++) {
		if (activeArea[i] == 1) {
			switch (i) {
			case 0:
				cout << "Brown area" << "\n";
				break;
			case 1:
				cout << "Green area" << "\n";
				break;
			case 2:
				cout << "Red area" << "\n";
				break;
			case 3:
				cout << "Blue area" << "\n";
				break;
			case 4:
				cout << "Purple area" << "\n";
				break;
			case 5:
				cout << "Yellow area" << "\n";
				break;
			}
		}
	}
}
bool MapLoader::checkAdjacentArea(bool areaCode[], int size) {
	bool flagNotAdjacent = true;
	for (int i = 0; i < size; i++) {
		flagNotAdjacent = true;
		if (areaCode[i] == 1) {
			for (int j = 0; j < size; j++) {
				if (adjacentArea[i][j] == 1)
					if (areaCode[j] == 1) {
						flagNotAdjacent = false;
						break;
					}
			}
			if (flagNotAdjacent == true)
				return !flagNotAdjacent;
		}
	}
	if (flagNotAdjacent == false)
		setActiveArea(areaCode, size);
	return !flagNotAdjacent;
}




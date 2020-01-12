#include "City.h"

using namespace std;
City::City() {
	city_name = "";
	area_name = "";
	ownersColor[0] = "";
	ownersColor[1] = "";
	ownersColor[2] = "";
}

City::City(const char* cityName, const char* areaName) {
	city_name = cityName;
	area_name = areaName;
	ownersColor[0] = "";
	ownersColor[1] = "";
	ownersColor[2] = "";
}
City::City(string cityName, string areaName) {
	city_name = cityName;
	area_name = areaName;
	ownersColor[0] = "";
	ownersColor[1] = "";
	ownersColor[2] = "";
}

City::City(const City &Copycity) {
	this->city_name = Copycity.getCityName();
	this->area_name = Copycity.area_name;
	for (int i = 0; i < ownersColor->size(); i++) {
		ownersColor[i] = Copycity.ownersColor[i];
	}
}

City::~City() {
	//do not need to do anything

}

City& City::operator=(const City &city) {
	this->city_name = city.getCityName();
	this->area_name = city.area_name;
	for (int i = 0; i < ownersColor->size(); i++) {
		ownersColor[i] = city.ownersColor[i];
	}
	return *this;
}

const City* const City::operator->()const {
	return this;
}

string City::getCityName() const {

	return city_name;
}
string City::getCityName() {

	return city_name;
}

string City::getAreaName()const {

	return area_name;
}
string City::getAreaName() {

	return area_name;
}


const string* const City::getOwnersColor()const {
	return ownersColor;
}
void City::setCityName(string cityName) {
	city_name = cityName;
}

void City::setRegionName(string  regionName) {
	area_name = regionName;
}

bool City::setOwnersColor(string playerColor) {
	if (ownersColor[0].compare("") == 0) {
		ownersColor[0] = playerColor;
		return true;
	}
	else if (ownersColor[1].compare("") == 0) {
		ownersColor[1] = playerColor;
		return true;
	}
	else if (ownersColor[2].compare("") == 0) {
		ownersColor[2] = playerColor;
		return true;
	}
	else
		return false;
}

const int City::CityPrice() {
	if (ownersColor[0].compare("") == 0) {
		return firstPlaceOwner;
	}
	else if (ownersColor[1].compare("") == 0) {
		return secondPlaceOwner;
	}
	else if (ownersColor[2].compare("") == 0) {
		return thirdPlaceOwner;
	}
	else
		return -1;
}

bool City::isAvailableCity() {
	if ((ownersColor[0].compare("") != 0) && (ownersColor[1].compare("") != 0) && (ownersColor[2].compare("") != 0)) {
		return false;
	}
	return true;
}

bool City::isHeOwner(string playerColor) {
	for (int i = 0; i < 3; i++) {
		if (ownersColor->compare(playerColor) == 0)
			return true;
	}
	return false;
}

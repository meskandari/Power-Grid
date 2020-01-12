#pragma once
#include<iostream>
#include <string>
using namespace std;

class City {
private:
	string city_name;
	string area_name;
	string ownersColor[3];
	const int firstPlaceOwner = 10; const int secondPlaceOwner = 15; const int thirdPlaceOwner = 20;
protected:

public:
	City();
	City(const char*, const char*);
	City(string, string);
	City(const City&);
	~City();

	City& operator=(const City&);
	const  City* const operator->()const;
	string getCityName() const;
	string getCityName();
	string getAreaName()const;
	string getAreaName();
	const string* const getOwnersColor()const;
	void setCityName(string);
	bool isAvailableCity();
	bool isHeOwner(string);
	void setRegionName(string);
	bool setOwnersColor(string);
	const int CityPrice();

};

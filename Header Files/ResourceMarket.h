#pragma once
#include "Resource.h"
#include <string>
#include "Subject.h"

class ResourceMarket : public Subject {
public:
	ResourceMarket();
	ResourceMarket(std::string file);
	~ResourceMarket();
	int getPrice(int type, int quantity) const;
	bool removeResource(int type, int quantity);
	bool restockMarket(int type, int quantity);
	void addToReserve(int type, int quantity);
	void setReserve(int coal, int oil, int garbage, int uranium);
	void saveToFile();
	int get_marketResource(int i) const;
	int get_reserveResource(int i) const;
	void print() const;
private:
	int market[4];
	int reserve[4];
};
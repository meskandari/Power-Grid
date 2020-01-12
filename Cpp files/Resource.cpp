#include "Resource.h"
#include <string>

// Default constructor. Defaults to 0 (Coal)
Resource::Resource() {
	type = 0;
}

// Parameterized constructor. Sets the type of the resource.
Resource::Resource(int _type) {
	type = _type;
}

Resource::~Resource() {}

// Returns the type in number of the resource.
int Resource::get_type() const {
	return type;
}

// Returns the corresponding number for the resource name.
int Resource::nameToCode(std::string name) {
	std::string names[] = { "Coal", "Oil", "Garbage", "Uranium", "Hybrid", "None" };
	for (int i = 0; i < 6; i++) {
		if (name == names[i]) {
			return i;
		}
	}
	return -1;
}

// Returns the corresponding name for the resource code.
std::string Resource::codeToName(int type) {
	if (type < 0 || type > 5) {
		return "Invalid";
	}
	std::string names[] = { "Coal", "Oil", "Garbage", "Uranium", "Hybrid", "None" };
	return names[type];
	
}

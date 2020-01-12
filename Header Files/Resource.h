#pragma once
#include <string>

class Resource {
public:
	static int nameToCode(std::string name);
	static std::string codeToName(int type);
	
	Resource();
	Resource(int type);
	~Resource();
	int get_type() const;

private:
	int type;
};

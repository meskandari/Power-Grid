#pragma once

#include <string>

class Card {
public:
	Card();
	Card(std::string _type);
	~Card();
	std::string get_type() const;
	std::string get_frontPicturePath() const;

private:
	std::string type;
	std::string frontPicturePath;

protected:
	void set_frontPicturePath(std::string _frontPicturePath);
};
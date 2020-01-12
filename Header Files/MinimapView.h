#pragma once

#include "View.h"
#include "Graphic.h"
#include "Text.h"
#include "Picture.h"
#include <string>
#include "Mymap.h"

class MinimapView : public View {
public:
	MinimapView();
	~MinimapView();
	void update();
	void findAndAttach();

private:
	Picture* houses[42][3];
	Mymap* map;

	const int cityCoords[42][2] = { {76, 27}, {44, 105}, {202, 168}, {380, 114}, {454, 224}, {444, 281}, {626, 239},
									{48, 337}, {128, 432}, {222, 374}, {178, 488}, {293, 457}, {294, 265}, {417, 397},
									{654, 309}, {614, 398}, {629, 464}, {636, 543}, {748, 403}, {752, 532}, {821, 448},
									{611, 86}, {702, 64}, {687, 129}, {791, 222}, {751, 312}, {876, 294}, {883, 378},
									{887, 202}, {1007, 182}, {976, 257}, {1033, 304}, {1092, 272}, {1118, 231}, {1171, 181},
									{1075, 354}, {1017, 391}, {888, 447}, {964, 472}, {962, 526}, {914, 594}, {985, 652} };



	const std::string cityNames[42] = { "Seattle", "Portland", "Boise", "Billings", "Cheyenne", "Denver", "Omaha",
										"SanFrancisco", "LosAngeles", "LasVegas", "SanDiego", "Phoenix", "SaltLakeCity", "Santa",
										"KansasCity", "OklahomaCity", "Dallas", "Houston", "Memphis", "NewOrleans", "Birmincham",
										"Fargo", "Duluth", "Minneapolis", "Chicago", "STLouis", "Cincinnati", "Knoxville",
										"Detroit", "Buffalo", "Pittsburgh", "WashingtonDC", "Philedelphia", "NewYork", "Boston",
										"Norfolk", "Raleigh", "Atlanta", "Savannah", "Jacksonville", "Tampa", "Miami" };
};
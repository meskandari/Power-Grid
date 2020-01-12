#include <string>
#include "Card.h"
#include "Step3Card.h"

// Simple Card, nothing special.
Step3Card::Step3Card() : Card("Step 3") {
	set_frontPicturePath("image\\Step3.png");
}
Step3Card::~Step3Card() {}
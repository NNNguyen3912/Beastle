#include "Score.h"

Score::Score() : point(0) {
}

void Score::increase(int value) {
	point += value;
	std::cout << "Current Score: " << point << std::endl;
}

int Score::getPoints() const {
	return point;
}
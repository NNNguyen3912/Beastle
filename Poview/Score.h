#ifndef SCORE_H
#define SCORE_H

#include <iostream>

class Score {
private:
	int point;
public:
	Score();
	void increase(int value);
	int getPoints() const;
};


#endif;
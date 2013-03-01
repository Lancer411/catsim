/*
 * random.h
 *
 *  Created on: Nov 10, 2012
 *      Author: ngh
 */

#ifndef RANDOM_H_
#define RANDOM_H_
#include "define/cadef.h"

class random
{
public:
	static float std_random(int offset, int top)
	{
		return std::rand()%top + offset;
	};

	static float std_random()
	{
		return (std::rand()%100+1)/100.;
	};

	static relative_direction random_direction()
	{
		int dir = std::rand()%2;
		if(dir == 0)
			return DIRECTION_LEFT;
		if(dir == 1)
			return DIRECTION_RIGHT;
		if(dir == 2)
			return DIRECTION_STRAIGHT;
		return DIRECTION_STRAIGHT;
	};
};

#endif /* RANDOM_H_ */

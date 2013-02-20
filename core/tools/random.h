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
};

#endif /* RANDOM_H_ */

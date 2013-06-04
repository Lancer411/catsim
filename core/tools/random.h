/*
	random.h

	Catsim source code
	Copyright (C) 2012-2013  naghtarr

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef RANDOM_H_
#define RANDOM_H_
#include <ctime>
#include "core/data_structures/data.h"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/poisson_distribution.hpp>
#include <boost/random/triangle_distribution.hpp>

class random
{
	// random generator
	static boost::random::mt19937 gen;
	// distributions
	static boost::random::uniform_int_distribution<> uniform_int_dist;
	static boost::random::poisson_distribution<int> poisson_int_dist;
	static boost::random::triangle_distribution<> triangle_int_dist;
public:
	static void initialize()
	{
		std::srand(std::time(0));
	};

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

	static int next_int_uniform();
	static int next_int_poisson();
	static int next_int_triangle();

	static void init_int_uniform(unsigned int min, unsigned int max);
	static void init_int_poisson(unsigned int mean);
	static void init_int_trianle(unsigned int lower, unsigned int mode, unsigned int upper);
	static void seed(const unsigned int & seed);

};


#endif /* RANDOM_H_ */

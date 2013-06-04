/*
 	random.cpp - <description>

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
#include "random.h"

boost::random::mt19937 random::gen(std::time(0));
boost::random::uniform_int_distribution<> random::uniform_int_dist(0, 10);

int random::next_int_uniform()
{
	return random::uniform_int_dist(random::gen);
}

void random::init_int_uniform(int max)
{
	boost::random::uniform_int_distribution<> new_uniform(0, max);
	random::uniform_int_dist = new_uniform;
}

void random::seed(const unsigned int & seed)
{
	random::gen.seed(seed);
}


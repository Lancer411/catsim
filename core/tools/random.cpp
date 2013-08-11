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
boost::random::poisson_distribution<int> random::poisson_int_dist(5);
boost::random::triangle_distribution<> random::triangle_int_dist(1,5,10);

int random::next_int_uniform()
{
	return random::uniform_int_dist(random::gen);
}

int random::next_int_uniform(boost::random::uniform_int_distribution<> distrib)
{
	return distrib(random::gen);
}

int random::next_int_poisson()
{
	return random::poisson_int_dist(random::gen);
}

int random::next_int_poisson(boost::random::poisson_distribution<int> distrib)
{
	return distrib(random::gen);
}

int random::next_int_triangle()
{
	return random::triangle_int_dist(random::gen);
}

int random::next_int_triangle(boost::random::triangle_distribution<> distrib)
{
	return distrib(random::gen);
}

void random::init_int_uniform(unsigned int min, unsigned int max)
{
	boost::random::uniform_int_distribution<> new_uniform(min, max);
	random::uniform_int_dist = new_uniform;
}

void random::init_int_poisson(unsigned int mean)
{
	boost::random::poisson_distribution<int> new_poisson(mean);
	random::poisson_int_dist = new_poisson;
}

void random::init_int_trianle(unsigned int lower, unsigned int mode, unsigned int upper)
{
	boost::random::triangle_distribution<> new_triangle(lower, mode, upper);
	random::triangle_int_dist = new_triangle;
}

void random::seed(const unsigned int & seed)
{
	random::gen.seed(seed);
}


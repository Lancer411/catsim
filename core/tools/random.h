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
#include "define/cadef.h"

class random
{
public:
	static void initialize()
		{
			std::srand(std::time(0));
		}

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

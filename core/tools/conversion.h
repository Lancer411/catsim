/*
	conversion.h

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

#ifndef CONVERSION_H_
#define CONVERSION_H_
#include "define/cadef.h"

class conversion
{
public:
	static int16 convert_to_cell_velocity(int16 kmh_velocity)
	{
		return std::floor(kmh_velocity/3.6/DEFAULT_CELL_LENGTH);
	};

	static int16 convert_to_kmh_velocity(int16 cell_velocity)
	{
		return std::ceil(cell_velocity*3.6*DEFAULT_CELL_LENGTH);
	};

	static short get_car_length()
	{
		return std::ceil(5/DEFAULT_CELL_LENGTH);
	};

	static short get_light_truck_length()
	{
		return std::ceil(5.5/DEFAULT_CELL_LENGTH);
	};

	static short get_truck_length()
	{
		return std::ceil(6/DEFAULT_CELL_LENGTH);
	};

	static short get_bus_length()
	{
		return std::ceil(11/DEFAULT_CELL_LENGTH);
	};

// проверка координат на выход за границы i и j и их поправка
	static void check_coord (COORD &coord, int16 i, int16 j)
	{
		coord.x = (coord.x >= i) ? i-1:coord.x;
		coord.y = (coord.y >= j) ? j-1:coord.y;
		coord.x = (coord.x < 0) ? 0:coord.x;
		coord.y = (coord.y < 0) ? 0:coord.y;

	};

	static int get_output_road_position (int position, relative_direction direction)
	{
		int pos;
		switch(direction)
		{
			case DIRECTION_LEFT:
				pos = get_left_road_position(position);
				break;
			case DIRECTION_RIGHT:
				pos = get_right_road_position(position);
				break;
			case DIRECTION_ANY:
			case DIRECTION_STRAIGHT:
				pos =  get_straight_road_position(position);
				break;
		}
		return pos;
	}

	static int get_left_road_position(int position)
	{
		return fix_position (position + 1);
	};

	static int get_straight_road_position(int position)
	{
		return fix_position (position + 2);
	};

	static int get_right_road_position(int position)
	{
		return fix_position (position - 1);
	};

	static int fix_position(int position)
	{
		if(position > ROAD_COUNT - 1)
			return position - ROAD_COUNT;
		if(position < 0)
			return ROAD_COUNT + position;
		return position;
	};

};

#endif /* CONVERSION_H_ */

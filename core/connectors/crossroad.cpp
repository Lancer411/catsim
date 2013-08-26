/*
	crossroad.cpp - represents crossroad, intersection between roads

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

#include "crossroad.h"
#include "core/entities/road.h"
#include "define/cadef.h"

crossroad::crossroad()
{
	for (int i = 0; i < cadef::road_count; ++i)
		for (int j = 0; j < cadef::road_count; ++j)
			(i != j) ?
			road_mtx[i][j] = ROAD_NONE :
			road_mtx[i][j] = ROAD_ABLE;
}

bool crossroad::transfer(std::string from_road_id, road_ptr to_road, vehicle_ptr veh, short passed_distance)
{
	COORD coord;
	int from = get_road_position(from_road_id);
	int to = get_road_position(to_road->get_id());
	bool road_able = (get_status(from, to) == ROAD_ABLE);
	bool road_free = to_road->has_free_space(veh->get_length(), veh->get_cell_velocity() - passed_distance + 1, &coord);
	if(road_free && road_able)
	{
//		short vel = passed_distance + coord.y + 1;
//		veh->set_cell_velocity(vel);
		veh->set_cell_velocity(veh->get_cell_velocity() - passed_distance + 1);
		veh->reset_time_counter();
		to_road->move_vehicle(veh, coord);
		to_road->stat_data->inc_current_vehicles_num(veh->get_length());
//		road->push_vehicle(veh);
		return true;
	}
	return false;
}

bool crossroad::add_first_road(road_ptr road)
{
	if(road_mtx[0][1] != ROAD_NONE)
		return false;
	roads_direct[0] = road;
	set_road_status (0, ROAD_UNABLE);
	return true;
}

bool crossroad::connect(road_ptr road, std::string road_id, relative_direction direction)
{
	int x = get_road_position(road_id);
	if(x == NO_ROAD)
		return false;
	int y = conversion::get_road_position(x, direction);
	if(get_status(x, y) != ROAD_NONE)
	{
		set_status (x, y, ROAD_ABLE);
		switch(direction)
		{
			case DIRECTION_RIGHT:
			case DIRECTION_STRAIGHT:
				roads_direct[y] = road;
				break;
			case DIRECTION_LEFT:
				roads_opposite[y] = road;
				break;
			case DIRECTION_ANY:
				break;
		}
	}
	return false;
}

road_ptr crossroad::get_next_road(std::string road_id, relative_direction direction)
{
	road_ptr null_ptr;
	int position = get_road_position(road_id);
	if(position == NO_ROAD)
		return null_ptr;
	if(direction == DIRECTION_ANY)
	{
		direction = get_any_available_direction(position);
	}
	int pos = conversion::get_road_position(position, direction);
	switch(direction)
	{
		case DIRECTION_RIGHT:
		case DIRECTION_STRAIGHT:
			return roads_direct[pos];
		case DIRECTION_LEFT:
			return roads_opposite[pos];
		case DIRECTION_ANY:
			return null_ptr;
	}
}

int crossroad::get_road_position(std::string road_id)
{
	road_ptr null_ptr;
	for (int i = 0; i < cadef::road_count; ++i)
	{
		if(roads_direct[i] != null_ptr)
		if(boost::algorithm::equals(road_id, roads_direct[i]->get_id()))
			return i;
		if(roads_opposite[i] != null_ptr)
		if(boost::algorithm::equals(road_id, roads_opposite[i]->get_id()))
			return i;
	}
	return NO_ROAD;
}

relative_direction crossroad::get_any_available_direction(int position)
{
	short dir = 0;
	int left = conversion::get_left_road_position(position);
	int right = conversion::get_right_road_position(position);
	int straight = conversion::get_straight_road_position(position);
	if(get_status(position, left) == ROAD_ABLE)
		dir += DIRECTION_LEFT;
	if(get_status(position, right) == ROAD_ABLE)
		dir += DIRECTION_RIGHT;
	if(get_status(position, straight) == ROAD_ABLE)
		dir += DIRECTION_STRAIGHT;
	switch (dir)
	{
		case 1:
			return DIRECTION_LEFT;
		case 2:
			return DIRECTION_STRAIGHT;
		case 4:
			return DIRECTION_RIGHT;
		case 5:
			return (random::std_random(0,2) == 0 ? DIRECTION_LEFT : DIRECTION_RIGHT);
		case 6:
			return (random::std_random(0,2) == 0 ? DIRECTION_STRAIGHT : DIRECTION_RIGHT);
		case 3:
			return (random::std_random(0,2) == 0 ? DIRECTION_LEFT : DIRECTION_STRAIGHT);
		case 7:
			return (random::std_random(0,2) == 0 ?
					DIRECTION_RIGHT :
					(random::std_random(0,2) == 0) ? DIRECTION_LEFT : DIRECTION_STRAIGHT);
		default:
			break;
	}
}

road_status crossroad::get_status(int pos_x, int pos_y)
{
	return (road_status)road_mtx[pos_x][pos_y];
}

void crossroad::set_status(int pos_x, int pos_y, road_status status)
{
	set_direction_status (pos_x, pos_y, status);
	set_direction_status (pos_y, pos_x, status);
}

void crossroad::set_road_status(int position, road_status status)
{
	int x = position,
		y = conversion::get_left_road_position(position);
	set_status(x, y, status);
	y = conversion::get_straight_road_position(position);
	set_status(x, y, status);
	y = conversion::get_right_road_position(position);
	set_status(x, y, status);
}

void crossroad::set_direction_status(int pos_x, int pos_y, road_status status)
{
	road_mtx[pos_x][pos_y] = status;
}

crossroad::~crossroad()
{

}

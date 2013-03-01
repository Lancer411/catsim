/*
 * crossroad.cpp
 *
 *  Created on: Nov 18, 2012
 *      Author: ngh
 */

#include "crossroad.h"
#include "core/entities/road.h"

crossroad::crossroad()
{
	for (int i = 0; i < ROAD_COUNT; ++i)
		for (int j = 0; j < ROAD_COUNT; ++j)
			road_mtx[i][j] = ROAD_NONE;
}

bool crossroad::transfer(road_ptr road, vehicle_ptr veh, short passed_distance)
{
	COORD coord;
	bool road_free = road->has_free_space(veh->get_length(), veh->get_cell_velocity() - passed_distance + 1, &coord);
	if(road_free)
	{
//		short vel = passed_distance + coord.y + 1;
//		veh->set_cell_velocity(vel);
		veh->set_cell_velocity(veh->get_cell_velocity() - passed_distance + 1);
		veh->reset_time_counter();
		road->move_vehicle(veh, coord);
		road->stat_data->inc_current_vehicles_num(veh->get_length());
//		road->push_vehicle(veh);
		return true;
	}
	return false;
}

bool crossroad::add_first_road(road_ptr road)
{
	if(road_mtx[0][1] != ROAD_NONE)
		return false;
	roads[0] = road;
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
		roads[y] = road;
		set_road_status (x, ROAD_ABLE);
		set_road_status (y, ROAD_ABLE);
	}
	return false;
}

road_ptr crossroad::get_next_road(std::string road_id, relative_direction direction)
{
	road_ptr null_ptr;
	int position = get_road_position(road_id);
	if(position == NO_ROAD)
		return null_ptr;
	int pos = conversion::get_road_position(position, direction);
	return roads[pos];
}

int crossroad::get_road_position(std::string road_id)
{
	for (int i = 0; i < ROAD_COUNT; ++i)
	{
		if(road_id.compare(roads[i]->get_id())==0)
			return i;
	}
	return NO_ROAD;
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

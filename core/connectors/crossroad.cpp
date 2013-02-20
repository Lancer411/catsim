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

}

//bool crossroad::road_available(short length, short velocity, COORD *coord)
//{
	// проверить оба состояния и переехать в координаты
//	COORD next, temp;
//	bool next_free = road_output->has_free_space(length, velocity, &next);
//	bool temp_free = road_output->has_free_space_temp(length, velocity, &temp);
//	coord->x = next.x;
//	coord->y = next.y;
//	return next_free && temp_free;

//	return road_output->has_free_space_temp(length, velocity, coord);
//	return false;
//}

bool crossroad::transfer(road_ptr road, vehicle_ptr veh, short passed_distance)
{
	COORD coord;
	bool road_free = road->has_free_space_temp(veh->get_length(), veh->get_cell_velocity() - passed_distance + 1, &coord);
	if(road_free)
	{
//		short vel = passed_distance + coord.y + 1;
//		veh->set_cell_velocity(vel);
		veh->set_cell_velocity(veh->get_cell_velocity() - passed_distance + 1);
		veh->reset_time_counter();
		road->move_vehicle(veh, coord);
		road->stat_data->inc_current_vehicles_num();
//		road->push_vehicle(veh);
		return true;
	}
	return false;
}

crossroad::~crossroad()
{

}

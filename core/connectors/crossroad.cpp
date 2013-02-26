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

crossroad::~crossroad()
{

}

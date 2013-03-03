/*
	vehicle.cpp - represents vehicle various types

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

#include "vehicle.h"

vehicle::vehicle()
{
	init(DEFAULT_MAX_VEH_VELOCITY, 0, Car);
}

vehicle::vehicle(int16 max_velocity, int16 start_velocity)
{
	init(max_velocity, start_velocity, Car);
}

vehicle::vehicle(int16 max_velocity, int16 start_velocity, vehicle_type type)
{
	init(max_velocity, start_velocity, type);
}

vehicle::vehicle(const vehicle &veh)
{
	this->current_cell_velocity = veh.current_cell_velocity;
	this->max_cell_velocity = veh.max_cell_velocity;
	this->current_kmh_velocity = veh.current_kmh_velocity;
	this->max_kmh_velocity = veh.max_kmh_velocity;
	this->type = veh.type;
	this->length = veh.length;
//	this->updated = veh.updated;
}

void vehicle::init(int16 max_velocity, int16 start_velocity, vehicle_type type)
{
	current_kmh_velocity = start_velocity;
	current_cell_velocity = conversion::convert_to_cell_velocity(start_velocity);
	max_kmh_velocity = max_velocity;
	max_cell_velocity = conversion::convert_to_cell_velocity(max_velocity);
	set_type(type);
	reset_time_counter();
}

void vehicle::set_type(vehicle_type t)
{
	type = t;
	switch(t)
	{
		case Car:
			length = conversion::get_car_length();
			break;
		case LightTruck:
			length = conversion::get_light_truck_length();
			break;
		case Truck:
			length = conversion::get_truck_length();
			break;
		case Bus:
			length = conversion::get_bus_length();
			break;
		default:
			length = 1;
			break;
	}
}

int16 vehicle::update_velocity(short limit)
{
	time_on_road++;
	if(random::std_random() > DEFAULT_PROB_SLOWDOWN) // Случайное торможение
	{
		// Движение / ускорение, превышение скорости
		current_cell_velocity = std::min(current_cell_velocity + 1, (int)max_cell_velocity);
		// Ограничение скорости по дороге
		if(random::std_random() > DEFAULT_PROB_SPEEDING)
			current_cell_velocity = std::min((int)current_cell_velocity, (int)limit);
	}
	else
	{
		// Случайное возмущение
		if (current_cell_velocity > 1)						//Если скорость минимальная, то нельзя случайно остановиться
			current_cell_velocity = std::max(current_cell_velocity - 1, 0);
	}
	current_kmh_velocity = conversion::convert_to_kmh_velocity(current_cell_velocity);
	return current_cell_velocity;
}

vehicle::~vehicle()
{

}

/*
 vehicle_feeder.cpp - connector which aim is to fill roads with
 vehicles with some density

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

#include "vehicle_feeder.h"

vehicle_feeder::vehicle_feeder(vehicle_factory_ptr veh_factory)
{
//	this->veh_factory = vehicle_factory::get();
	this->veh_factory = veh_factory;
}

bool vehicle_feeder::transfer(std::string from_road_id, road_ptr to_road, vehicle_ptr veh, short passed_distance)
{
	COORD coord;
	bool road_free = to_road->has_free_space(veh->get_length(), veh->get_cell_velocity() - passed_distance + 1, &coord);
	if(road_free)
	{
		veh->set_cell_velocity(veh->get_cell_velocity() - passed_distance + 1);
		veh->reset_time_counter();
		to_road->move_vehicle(veh, coord);
		to_road->stat_data->inc_current_vehicles_num(veh->get_length());
		return true;
	}
	return false;
}

road_ptr vehicle_feeder::get_next_road(std::string road_id, relative_direction direction)
{
	road_map::iterator it;
	road_ptr null_ptr;
	for (it = deadend_roads.begin(); it != deadend_roads.end();++it)
	{
		std::string next_road_id = it->first;
		std::string dead_road_id = it->second->get_id();
		if(boost::algorithm::equals(dead_road_id, road_id))
		{
			return feeding_roads[next_road_id];
		}
	}
	return null_ptr;
}

bool vehicle_feeder::connect_feeding_road(road_ptr road, feeder_params params)
{
	if(!feeding_roads.count(road->get_id()))
	{
		feeding_roads[road->get_id()] = road;
		update_road_params(road->get_id(), params);
		return true;
	}
	return false;
}

bool vehicle_feeder::connect_deadend_road(road_ptr road, std::string feeding_road_id)
{
	if(feeding_roads.count(feeding_road_id) && !deadend_roads.count(feeding_road_id))
	{
		deadend_roads[feeding_road_id] = road;
		return true;
	}
	return false;
}

void vehicle_feeder::feed_roads()
{
	road_map::iterator it;
	for (it = feeding_roads.begin(); it != feeding_roads.end();++it)
	{
		std::string road_id = it->first;
		road_ptr road = it->second;
		feeder_params params = feeding_roads_params[road_id];
		switch (params.get_mode())
		{
			case INITIAL:
				fill_road_to_density(road, params);
				break;
			case CONTINUOUS:
				feed_road_continuously(road, params);
				break;
			case DISTRIBUTIVE:
				feed_road_by_distribution(road, params);
				break;
			default:
				break;
		}
	}
}

void vehicle_feeder::fill_road_to_density(road_ptr road, feeder_params params)
{
	// fill road with vehicles to density
	float dens = 0;
	int16 created_veh_length = 0;
	int16 road_length = road->get_lane_length();
	int16 lanes_num = road->get_lane_count();
	while (dens < params.density)
	{
		int16 init_speed = params.init_speed, max_speed = params.max_speed;
		vehicle_ptr veh = create_vehicle_by_params(params);
		created_veh_length += veh->get_length();
		dens = created_veh_length/(float)(road_length * lanes_num);
		road->push_vehicle(veh);
	}
}

vehicle_ptr vehicle_feeder::create_vehicle_by_params(feeder_params params)
{
	vehicle_type veh_type = Car;
	float typerand = random::std_random();
	if (typerand < params.car_prob)
		veh_type = Car;
	else
		if (typerand < params.car_prob + params.bus_prob)
			veh_type = Bus;
		else
			veh_type = Truck;
	return veh_factory->create_vehicle(max_speed, init_speed, veh_type);
}

void vehicle_feeder::feed_road_initially(road_ptr road, feeder_params params)
{
	if(params.road_fed())
		return;
	fill_road_to_density(road, params);
	params.set_fed();
	update_road_params(road->get_id(), params);
}

void vehicle_feeder::feed_road_continuously(road_ptr road, feeder_params params)
{
	float density_delta = params.density - road->get_current_density();
	if(density_delta > 0)
	{
		feeder_params update_params = params;
		update_params.density = density_delta;
		fill_road_to_density(road, update_params);
	}
}

void vehicle_feeder::feed_road_by_distribution(road_ptr road, feeder_params params)
{
	distribution dist_type = params.get_distribution();
	switch(dist_type)
	{
		case NORMAL:
			if(params.need_to_distribute())
			{
				vehicle_ptr veh = create_vehicle_by_params(params);
				road->push_vehicle(veh);
				int next_timer = random::next_int_uniform();
				params.set_distribution_timer(next_timer);
			}
			else
			{
				params.tick_distribution_timer();
			}
			break;
		case PUASSON:
			break;
		case TRIANGLE:
			break;
		default:
			break;
	}
	update_road_params(road->get_id(), params);
}

void vehicle_feeder::update_road_params(std::string id, feeder_params params)
{
	feeding_roads_params[id] = params;
}

vehicle_feeder::~vehicle_feeder()
{
	feeding_roads.clear();
	feeding_roads_params.clear();
	deadend_roads.clear();
	veh_factory.reset();
}

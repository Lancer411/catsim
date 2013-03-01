/*
 * vehicle_factory.cpp
 *
 *  Created on: Oct 31, 2012
 *      Author: ngh
 */

#include "vehicle_factory.h"

vehicle_factory::vehicle_factory()
{
	id_counter = 0;
}

vehicle_ptr vehicle_factory::create_vehicle(int16 max_velocity,
											int16 start_velocity,
											vehicle_type type)
{
	vehicle_ptr p(new vehicle(max_velocity, start_velocity, type));
	std::string id = "VEH_" + boost::lexical_cast<std::string> (id_counter++);
	p->set_id(id);
	vehicles[id] = p;
	return p;
}

void vehicle_factory::delete_vehicle(std::string id)
{
	vehicles[id].reset();
	vehicles.erase(id);
}

vehicle_ptr vehicle_factory::get_vehicle(std::string id)
{
	return vehicles[id];
}

size_t vehicle_factory::count()
{
	return vehicles.size();
}

void vehicle_factory::delete_all_vehicles()
{
	vehicles.clear();
}

vehicle_factory::~vehicle_factory()
{
//	std::map<std::string, vehicle_ptr>::iterator it;
//	for (it = vehicles.begin(); it != vehicles.end();++it)
//	{
//		it->second.reset();
////		it = vehicles.erase(it);
//	}
	delete_all_vehicles();
}

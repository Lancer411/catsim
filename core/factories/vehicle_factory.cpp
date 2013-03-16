/*
	vehicle_factory.cpp

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

#include "vehicle_factory.h"

vehicle_factory::vehicle_factory()
{
	id_counter = 0;
}

//boost::shared_ptr<vehicle_factory> vehicle_factory::get()
//{
//	if (!instance)
//	{
//		instance = new vehicle_factory();
//	}
//	return boost::shared_ptr<vehicle_factory>(instance);
//}

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
//	instance = NULL;
}

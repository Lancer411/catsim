/*
	vehicle_factory.h

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

#ifndef VEHICLE_FACTORY_H_
#define VEHICLE_FACTORY_H_
#include "define/cadef.h"
//#include "factory.h"
#include "core/entities/vehicle.h"

//typedef std::map<std::string, vehicle_ptr> factory_container;

class vehicle_factory //: factory<vehicle_ptr>
{
	std::map<std::string, vehicle_ptr> vehicles;
	long id_counter;
//	static vehicle_factory* instance;
public:
//	static boost::shared_ptr<vehicle_factory> get();
	vehicle_factory();
	vehicle_ptr create_vehicle(int16 max_velocity, int16 start_velocity, vehicle_type type);
	void delete_vehicle(std::string id);
	vehicle_ptr get_vehicle(std::string id);
	size_t count();
	void delete_all_vehicles();
	virtual ~vehicle_factory();
private:
//	vehicle_factory();
};

typedef boost::shared_ptr<vehicle_factory> vehicle_factory_ptr;

#endif /* VEHICLE_FACTORY_H_ */

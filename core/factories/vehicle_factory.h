/*
 * vehicle_factory.h
 *
 *  Created on: Oct 31, 2012
 *      Author: ngh
 */

#ifndef VEHICLE_FACTORY_H_
#define VEHICLE_FACTORY_H_
#include "define/cadef.h"
//#include "factory.h"
#include "core/entities/vehicle.h"
#include <map>

//typedef std::map<std::string, vehicle_ptr> factory_container;

class vehicle_factory //: factory<vehicle_ptr>
{
	std::map<std::string, vehicle_ptr> vehicles;
	long id_counter;
public:
	vehicle_factory();
	vehicle_ptr create_vehicle(int16 max_velocity, int16 start_velocity, vehicle_type type);
	void delete_vehicle(std::string id);
	vehicle_ptr get_vehicle(std::string id);
	size_t count();
	void delete_all_vehicles();
	virtual ~vehicle_factory();
};

#endif /* VEHICLE_FACTORY_H_ */

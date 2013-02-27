/*
 * test_vehicle_factory.h
 *
 *  Created on: Oct 31, 2012
 *      Author: ngh
 */

#ifndef TEST_VEHICLE_PTR_H_
#define TEST_VEHICLE_PTR_H_
#include "test.h"
#include "core/base/cell.h"
#include "core/entities/vehicle.h"
#include "core/factories/vehicle_factory.h"

class test_vehicle_ptr : public test
{
public:
	test_vehicle_ptr(){};
	virtual ~test_vehicle_ptr(){};
	void runtest()
	{
		cell cell;
		vehicle_factory factory;
		vehicle_ptr veh = factory.create_vehicle(100,60,Car);
		cell.set_vehicle(veh);
		std::cout << veh.use_count() << std::endl;
		factory.delete_all_vehicles();
		std::cout << veh.use_count() << std::endl;
		cell.clear();
		std::cout << veh.use_count() << std::endl;
		{
			vehicle_ptr vehc = veh;
			std::cout << veh.use_count() << std::endl;
		}
		std::cout << veh.use_count() << std::endl;
		f(veh);
		std::cout << veh.use_count() << std::endl;
		veh.reset();
		std::cout << veh.use_count() << std::endl;
	};

	void f (vehicle_ptr veh)
	{
		std::cout << veh.use_count() << std::endl;
		g(veh);
	}

	void g (vehicle_ptr veh)
	{
		std::cout << veh.use_count() << std::endl;
	}
};

#endif /* TEST_VEHICLE_PTR_H_ */

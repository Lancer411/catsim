/*
 * test_vehicle.h
 *
 *  Created on: Oct 31, 2012
 *      Author: ngh
 */

#ifndef TEST_VEHICLE_H_
#define TEST_VEHICLE_H_
#include "test.h"
#include "core/entities/vehicle.h"

class test_vehicle : public test
{
public:
	test_vehicle(){};
	virtual ~test_vehicle(){};
	void runtest()
	{
		vehicle veh(100,60,Car);
		std::cout<<"- vehicle_test:"<<std::endl;
		assert_equals(veh.get_cell_velocity(), 3);
		assert_equals(veh.get_length(), 1);
		assert_equals(veh.get_max_cell_velocity(), 5);
		veh.set_cell_velocity(2);
		assert_equals(veh.get_kmh_velocity(), 40);
		veh.set_type(Bus);
		assert_equals(veh.get_length(), 2);
	};
};

#endif /* TEST_VEHICLE_H_ */

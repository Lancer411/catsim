/*
 * test_vehicle_factory.h
 *
 *  Created on: Oct 31, 2012
 *      Author: ngh
 */

#ifndef TEST_VEHICLE_FACTORY_H_
#define TEST_VEHICLE_FACTORY_H_
#include "test.h"
#include "core/base/cell.h"
#include "core/entities/vehicle.h"
#include "core/factories/vehicle_factory.h"

class test_vehicle_factory : public test
{
public:
	test_vehicle_factory(){};
	virtual ~test_vehicle_factory(){};
	void runtest()
	{
		cell cell;
		vehicle_factory factory;
		cell.set_vehicle(factory.create_vehicle(100,60,Car));
		factory.create_vehicle(100,60,Car);
		std::cout<<"- vehicle_factory_test:"<<std::endl;
		std::string id = cell.get_vehicle()->get_id();
		assert_expression(cell.get_vehicle()==factory.get_vehicle(id));
		assert_equals(factory.count(),2);
		cell.clear();
		assert_expression(factory.get_vehicle(id)!=NULL);
		assert_expression(cell.get_vehicle()==NULL);
		assert_equals(factory.count(),2);
		factory.delete_vehicle(id);
		assert_equals(factory.count(),1);
		assert_expression(factory.get_vehicle(id)==NULL);
	};
};

#endif /* TEST_VEHICLE_FACTORY_H_ */

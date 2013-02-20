/*
 * test_cell.h
 *
 *  Created on: Oct 31, 2012
 *      Author: ngh
 */

#ifndef TEST_CELL_H_
#define TEST_CELL_H_
#include "test.h"
#include "core/base/cell.h"
#include "core/entities/vehicle.h"

class test_cell : public test
{
public:
	test_cell(){};
	virtual ~test_cell(){};
	void runtest()
	{
		vehicle_ptr veh(new vehicle(100,60,Car));
		cell cell;
		std::cout<<"- cell_test:"<<std::endl;
		cell.set_vehicle(veh);
		assert_expression(veh==cell.get_vehicle());
		assert_expression(cell.is_occupied()^!true);
		veh.reset();
		assert_expression(veh==NULL);
		assert_expression(cell.get_vehicle()!=NULL);
		cell.clear();
		assert_expression(cell.get_vehicle()==NULL);
		assert_expression(cell.is_occupied()^!false);
	};
};

#endif /* TEST_CELL_H_ */

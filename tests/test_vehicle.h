/*
	test_vehicle.h

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

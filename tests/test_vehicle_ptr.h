/*
	test_vehicle_ptr.h

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
		cell.set_object(veh);
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

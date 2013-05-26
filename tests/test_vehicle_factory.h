/*
	test_vehicle_factory.h

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
		cell.set_object(factory.create_vehicle(100,60,Car));
		factory.create_vehicle(100,60,Car);
		std::cout<<"- vehicle_factory_test:"<<std::endl;
		object_ptr obj = cell.get_object();
		vehicle_ptr veh = boost::shared_polymorphic_downcast<vehicle>(obj);
		std::string id = veh->get_id();
		assert_expression(cell.get_object()==factory.get_vehicle(id));
		assert_equals(factory.count(),2);
		cell.clear();
		assert_expression(factory.get_vehicle(id)!=NULL);
		assert_expression(cell.get_object()==NULL);
		assert_equals(factory.count(),2);
		factory.delete_vehicle(id);
		assert_equals(factory.count(),1);
		assert_expression(factory.get_vehicle(id)==NULL);
	};
};

#endif /* TEST_VEHICLE_FACTORY_H_ */

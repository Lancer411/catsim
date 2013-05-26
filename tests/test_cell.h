/*
	test_cell.h

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
		cell.set_object(veh);
		assert_expression(veh==cell.get_object());
		assert_expression(cell.is_occupied()^!true);
		veh.reset();
		assert_expression(veh==NULL);
		assert_expression(cell.get_object()!=NULL);
		cell.clear();
		assert_expression(cell.get_object()==NULL);
		assert_expression(cell.is_occupied()^!false);
	};
};

#endif /* TEST_CELL_H_ */

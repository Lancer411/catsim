/*
	testrunner.h

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

#ifndef TESTRUNNER_H_
#define TESTRUNNER_H_
#include "test_vehicle.h"
#include "test_cell.h"
#include "test_vehicle_factory.h"
#include "test_vehicle_ptr.h"
#include "test_vehicle_behaviour.h"
#include "test_one_road_simulation.h"
#include "test_road_infinity.h"
#include "test_crossroad.h"
#include "test_vehicle_feeder.h"
#include "test_poisson_flow.h"

void runtests()
{
//	test_vehicle vehtest;
//	vehtest.runtest();
//	test_cell celltest;
//	celltest.runtest();
//	test_vehicle_factory vehfactorytest;
//	vehfactorytest.runtest();
//	test_vehicle_behaviour behtest;
//	behtest.runtest();
//	test_one_road_simulation roadtest;
//	roadtest.runtest();
//	test_vehicle_ptr vehptrtest;
//	vehptrtest.runtest();
//	test_road_infinity inftest;
//	inftest.runtest();
//	test_crossroad crosstest;
//	crosstest.runtest();
//	test_vehicle_feeder feedertest;
//	feedertest.runtest();
	test_poisson_flow flowtest;
	flowtest.runtest();
}
#endif /* TESTRUNNER_H_ */

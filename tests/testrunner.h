/*
 * testrunner.h
 *
 *  Created on: Oct 31, 2012
 *      Author: ngh
 */

#ifndef TESTRUNNER_H_
#define TESTRUNNER_H_
#include "test_vehicle.h"
#include "test_cell.h"
#include "test_vehicle_factory.h"
#include "test_vehicle_ptr.h"
#include "test_vehicle_behaviour.h"
#include "test_one_road_simulation.h"
#include "test_vehicle_generation.h"
#include "test_vehicle_puasson_generation.h"
#include "test_road_infinity.h"

void runtests()
{
//	test_vehicle vehtest;
//	vehtest.runtest();
//	test_cell celltest;
//	celltest.runtest();
//	test_vehicle_factory vehfactorytest;
//	vehfactorytest.runtest();
	test_vehicle_behaviour behtest;
	behtest.runtest();
//	test_one_road_simulation roadtest;
//	roadtest.runtest();
//	test_vehicle_generation gentest;
//	gentest.runtest();
//	test_vehicle_puasson_generation puastest;
//	puastest.runtest();
//	test_vehicle_ptr vehptrtest;
//	vehptrtest.runtest();
//	test_road_infinity inftest;
//	inftest.runtest();
}
#endif /* TESTRUNNER_H_ */

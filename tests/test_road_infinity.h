/*
	test_road_infinity.h

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

#ifndef TEST_ROAD_INFINITY_H_
#define TEST_ROAD_INFINITY_H_
#include "test.h"
#include "core/factories/road_factory.h"
#include "core/factories/vehicle_factory.h"

class test_road_infinity : public test
{
public:
	void runtest()
	{
		int iteration_num = 200;
		int road_length = 800;
		int lane_num = 8;
		float car_prob = 0.75,
			  truck_prob = 0.2;
		road_factory roadf;
		vehicle_factory vehf;
		road_ptr road = roadf.create_road(lane_num, road_length);
		roadf.get_road_statistics(road->get_id())->set_stat_accumulation_time(iteration_num/2);
		crossroad_ptr cross = roadf.get_crossroad(road->get_id());
//		cross->set_road_output(road);

		// initiation parameters
		float density = 0.75;
		// fill road with vehicles to density
		float dens = 0;
		int16 created_veh_length = 0;
		while (dens < density)
		{
			int16 init_speed = 20, max_speed = 80;
			vehicle_type veh_type = Car;
//			float typerand = random::std_random();
//			if (typerand < car_prob)
//				veh_type = Car;
//			else
//				if (typerand < car_prob + truck_prob)
//					veh_type = Truck;
//				else
//					veh_type = Bus;
			vehicle_ptr veh = vehf.create_vehicle(max_speed, init_speed, veh_type);
			created_veh_length += veh->get_length();
			dens = created_veh_length/(float)(road_length*lane_num);
			road->push_vehicle(veh);
		}
		std::cout << "Vehicles created" << std::endl;

		std::cout << "Loop started..." << std::endl;
		while(true)
		{
			roadf.iterate();
		}
	};
};

#endif /* TEST_ROAD_INFINITY_H_ */

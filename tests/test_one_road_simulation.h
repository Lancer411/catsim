/*
	test_one_road_simulation.h

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

#ifndef TEST_ONE_ROAD_SIMULATION_H_
#define TEST_ONE_ROAD_SIMULATION_H_
#include "test.h"
#include "core/factories/road_factory.h"
#include "core/factories/vehicle_factory.h"


class test_one_road_simulation : public test
{
public:
	test_one_road_simulation(){};
	virtual ~test_one_road_simulation(){};
	void runtest()
	{
		// init parameters
		float init_density = 0.01;
		float step = 0.01;
		int iteration_num = 900;
		int road_length = 200;
		int lanes_num = 2;
		float car_prob = 0.75,
			  truck_prob = 0.2;


		// start model
		while(init_density <= 1)
		{
			// entity factories
			road_factory roadf;
			vehicle_factory vehf;
			road_ptr road = roadf.create_road(lanes_num, road_length);
			// init road loop
			crossroad_ptr cross = roadf.get_crossroad(road->get_id());
			cross->connect(road, road->get_id(), DIRECTION_LEFT);

			// set accumulation time
			roadf.get_road_statistics(road->get_id())->set_stat_accumulation_time(iteration_num/4);
			// initiation parameters
			float density = init_density;
			// fill road with vehicles to density
			float dens = 0;
			int16 created_veh_length = 0;
			while (dens < density)
			{
				int16 init_speed = 20, max_speed = 80;
				vehicle_type veh_type = Car;
//				float typerand = random::std_random();
//				if (typerand < car_prob)
//					veh_type = Car;
//				else
//					if (typerand < car_prob + truck_prob)
//						veh_type = Truck;
//					else
//						veh_type = Bus;
				vehicle_ptr veh = vehf.create_vehicle(max_speed, init_speed, veh_type);
				created_veh_length += veh->get_length();
				dens = created_veh_length/(float)(road_length * lanes_num);
				road->push_vehicle(veh);
			}

			// iteration process start
			int k = 0;

			while(k < iteration_num)
			{
//				std::cout<<"iter "<<k<<std::endl;
				k++;
//				std::cout<<road;
				roadf.iterate();
			}

			// statistic data
			road_stat_data_ptr  stat = roadf.get_road_statistics(road->get_id());
			std::cout.precision(5);
			std::cout<<stat->get_current_road_density()<<"|"
				<<stat->get_avg_road_density()<<"|"
				<<stat->get_avg_road_speed_total()<<"|"
				<<stat->get_road_flow()<<"|"
				<<stat->get_passed_vehicles_number()<<"|"
				<<stat->get_current_vehicles_number()<<"|"
				<<stat->get_avg_road_passage_time()<<"|"
				<<std::endl;


			init_density += step;
//			road->clear();
//			vehf.delete_all_vehicles();
//			stat->reset();
		}
	};
};

#endif /* TEST_ONE_ROAD_SIMULATION_H_ */

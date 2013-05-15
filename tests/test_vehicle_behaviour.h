/*
	test_vehicle_behaviour.h

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

#ifndef TEST_VEHICLE_BEHAVIOUR_H_
#define TEST_VEHICLE_BEHAVIOUR_H_
#include "test.h"
#include "core/factories/road_factory.h"
#include "core/factories/vehicle_factory.h"

class test_vehicle_behaviour : public test
{
public:
	void runtest()
	{
		int iteration_num = 200;
		int road_length = 50;
		int lane_num = 1;
		float car_prob = 1,
			  truck_prob = 0;
		road_factory roadf;
		vehicle_factory vehf;
		road_ptr road = roadf.create_road(lane_num, road_length);
		roadf.get_road_statistics(road->get_id())->set_stat_accumulation_time(iteration_num/2);
		crossroad_ptr cross = roadf.get_crossroad(road->get_id());
		cross->connect(road, road->get_id(), DIRECTION_STRAIGHT);

		// initiation parameters
		float density = 0.5;
		// fill road with vehicles to density
		float dens = 0;
		float prob  = random::std_random();
		int16 created_veh_length = 0;

		// statistic data
		road_stat_data_ptr  stat = roadf.get_road_statistics(road->get_id());
		int k = 0;
		while(k < iteration_num)
//		while(true)
		{
			if (prob < density)
					{
						int16 init_speed = 20, max_speed = 80;
						vehicle_type veh_type = Car;
						float typerand = random::std_random();
						if (typerand < car_prob)
							veh_type = Car;
						else
							if (typerand < car_prob + truck_prob)
								veh_type = Truck;
							else
								veh_type = Bus;
						vehicle_ptr veh = vehf.create_vehicle(max_speed, init_speed, veh_type);
						created_veh_length += veh->get_length();
						//dens = created_veh_length/(float)(road_length*lane_num);
						road->push_vehicle(veh);
					}

			if(k==18)
				std::cout<<75<<std::endl;
			k++;
			std::cout<<"iter "<<k<<std::endl;
			roadf.iterate();

			std::cout<<road;

			std::cout<<" source: "<<road->get_source_size()
			<<" runoff: "<<road->get_runoff_size()<<std::endl;
			std::cout<<"Current Vehicles: "<<stat->get_current_vehicles_number()<<std::endl<<std::endl;

//			cross->transfer();
//			vehicle_ptr veh = road->pop_vehicle();
//			while(veh!=NULL)
//			{
//				road->push_vehicle(veh);
//				veh = road->pop_vehicle();
//			}
		}


		std::cout<<"Current Density: "<<stat->get_current_road_density()<<std::endl;
		std::cout<<"Average Density: "<<stat->get_avg_road_density()<<std::endl;
		std::cout<<"Average Road Speed: "<<stat->get_avg_road_speed()<<std::endl;
		std::cout<<"Average Total Road Speed: "<<stat->get_avg_road_speed_total()<<std::endl;
		std::cout<<"Road Flow: "<<stat->get_road_flow()<<std::endl;
		std::cout<<"Passed Vehicles: "<<stat->get_passed_vehicles_number()<<std::endl;
		std::cout<<"Current Vehicles: "<<stat->get_current_vehicles_number()<<std::endl<<std::endl;
		std::cout<<"Avegare Passage Time: "<<stat->get_avg_road_passage_time()<<std::endl<<std::endl;

	};
};

#endif /* TEST_VEHICLE_BEHAVIOUR_H_ */

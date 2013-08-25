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
#include "core/connectors/vehicle_feeder.h"

class test_vehicle_behaviour : public test
{
public:
	void runtest()
	{
		int iteration_num = 200;
		int road_length = 50;
		int lane_num = 1;
		float density = 0.1;
		road_factory roadf;
		vehicle_factory_ptr vehf_p(new vehicle_factory());
		road_ptr road = roadf.create_road(lane_num, road_length);
		roadf.get_road_statistics(road->get_id())->set_stat_accumulation_time(iteration_num/2);
		vehicle_feeder_ptr feeder_p(new vehicle_feeder(vehf_p));

		feeder_params_ptr params (new feeder_params(density, 20, 80, 1, 0));
		params->mode = DISTRIBUTIVE;
		params->distribution_type = TRIANGLE;
		random::init_int_trianle(0,1,2);
		feeder_p->connect_feeding_road(road, params);

		crossroad_ptr cross = roadf.get_crossroad(road->get_id());
		cross->connect(road, road->get_id(), DIRECTION_STRAIGHT);

		// set accumulation time
		roadf.get_road_statistics(road->get_id())->set_stat_accumulation_time(iteration_num/4);
		// iteration process start
		int k = 0;

		while(k < iteration_num)
		{
			std::cout<<"iter "<<k<<std::endl;
			k++;
			feeder_p->feed_roads();
			std::cout<<road;
			roadf.iterate();
		}

		// statistic data
		road_stat_data_ptr  stat = roadf.get_road_statistics(road->get_id());
		std::cout.precision(5);
		std::cout<<"Current Density: "<<stat->get_current_road_density()<<std::endl;
		std::cout<<"Average Density: "<<stat->get_avg_road_density()<<std::endl;
		std::cout<<"Average Road Speed: "<<stat->get_avg_road_speed()<<std::endl;
		std::cout<<"Average Total Road Speed: "<<stat->get_avg_road_speed_total()<<std::endl;
		std::cout<<"Road Flow: "<<stat->get_road_flow()<<std::endl;
		std::cout<<"Passed Vehicles: "<<stat->get_passed_vehicles_number()<<std::endl;
		std::cout<<"Current Vehicles: "<<stat->get_current_vehicles_number()<<std::endl;
		std::cout<<"Avegare Passage Time: "<<stat->get_avg_road_passage_time()<<std::endl;

	};
};

#endif /* TEST_VEHICLE_BEHAVIOUR_H_ */

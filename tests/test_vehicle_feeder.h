/*
 test_vehicle_feeder.h - <description>

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

#ifndef TEST_VEHICLE_FEEDER_H_
#define TEST_VEHICLE_FEEDER_H_
#include "test.h"
#include "core/factories/road_factory.h"
#include "core/factories/vehicle_factory.h"
#include "core/connectors/vehicle_feeder.h"
/*
 *
 */
class test_vehicle_feeder : public test
{
public:
	test_vehicle_feeder(){};
	~test_vehicle_feeder(){};
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
			vehicle_factory_ptr vehf_p(new vehicle_factory());
			road_ptr road1 = roadf.create_road(lanes_num, road_length);
			road_ptr road2 = roadf.create_road(lanes_num, road_length);
			// init road loop
			vehicle_feeder_ptr feeder_p(new vehicle_feeder(vehf_p));
			feeder_params params(init_density);
			feeder_p->connect_feeding_road(road1, params);
			feeder_p->connect_feeding_road(road2, params);
			feeder_p->connect_deadend_road(road1, road2->get_id());
			feeder_p->connect_deadend_road(road2, road1->get_id());
			road1->set_connector(feeder_p);
			road2->set_connector(feeder_p);
			// set accumulation time
			roadf.get_road_statistics(road1->get_id())->set_stat_accumulation_time(iteration_num/4);
			roadf.get_road_statistics(road2->get_id())->set_stat_accumulation_time(iteration_num/4);
			// init feeder
			feeder_p->feed_roads();
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
			road_stat_data_ptr  stat = roadf.get_road_statistics(road1->get_id());
			std::cout.precision(5);
			std::cout<<stat->get_current_road_density()<<"|"
				<<stat->get_avg_road_density()<<"|"
				<<stat->get_avg_road_speed_total()<<"|"
				<<stat->get_road_flow()<<"|"
				<<stat->get_passed_vehicles_number()<<"|"
				<<stat->get_current_vehicles_number()<<"|"
				<<stat->get_avg_road_passage_time();
			std::cout<<"|||";
			stat = roadf.get_road_statistics(road2->get_id());
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
		}
	};
};

#endif /* TEST_VEHICLE_FEEDER_H_ */

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

#ifndef TEST_DIRECT_ROAD_SIMULATION_H_
#define TEST_DIRECT_ROAD_SIMULATION_H_
#include "test.h"
#include "core/factories/road_factory.h"
#include "core/factories/vehicle_factory.h"
#include "core/connectors/vehicle_feeder.h"
#include <boost/program_options.hpp>

class test_direct_road_simulation : public test
{
public:
	test_direct_road_simulation(){};
	~test_direct_road_simulation(){};
	void runtest()
	{
		// init parameters
		float init_density = 0.01;
		float step = 0.01;
		int iteration_num = 3600;
		int road_length = 800;
		int lanes_num = 1;
		random::initialize();
		// start model
		while(init_density <= 1)
		{
			// entity factories
			road_factory roadf;
			vehicle_factory_ptr vehf_p(new vehicle_factory());
			road_ptr road = roadf.create_road(lanes_num, road_length);
			// init road loop
			vehicle_feeder_ptr feeder_p(new vehicle_feeder(vehf_p));
			feeder_params params(init_density, 20, 80, 1, 0);
			feeder_p->connect_feeding_road(road, params);

			//crossroad_ptr cross = roadf.get_crossroad(road->get_id());
			//cross->connect(road, road->get_id(), DIRECTION_STRAIGHT);

			// set accumulation time
			roadf.get_road_statistics(road->get_id())->set_stat_accumulation_time(iteration_num/4);
			// initiation parameters
			feeder_p->feed_roads();
			// iteration process start
			int k = 0;

			while(k < iteration_num)
			{
				k++;
				std::cout<<"iter "<<k<<std::endl;
				roadf.iterate();

				std::cout<<road;

				std::cout<<" source: "<<road->get_source_size()
				<<" runoff: "<<road->get_runoff_size()<<std::endl;
				std::cout<<"Current Vehicles: "<<stat->get_current_vehicles_number()<<std::endl<<std::endl;
			}

			// statistic data
			road_stat_data_ptr  stat = roadf.get_road_statistics(road->get_id());
			std::cout.precision(5);
			std::cout<<stat->get_current_road_density()<<"|"
				<<stat->get_avg_road_density()<<"|"
				<<stat->get_avg_road_speed_total()<<"|"
				<<stat->get_road_flow()<<"|"
				<<stat->get_flow()<<"|"
				<<stat->get_passed_vehicles_number()<<"|"
				<<stat->get_current_vehicles_number()<<"|"
				<<stat->get_avg_road_passage_time()<<"|"
				<<std::endl;


			init_density += step;
		}
	};
};

#endif /* TEST_ONE_ROAD_SIMULATION_H_ */

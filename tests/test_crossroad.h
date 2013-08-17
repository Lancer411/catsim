/*
	test_crossroad.h

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

#ifndef TEST_CROSSROAD_H_
#define TEST_CROSSROAD_H_
#include "test.h"
#include "core/factories/road_factory.h"
#include "core/factories/vehicle_factory.h"
#include "core/connectors/vehicle_feeder.h"
#include "core/factories/lightsignal_factory.h"

class test_crossroad : public test
{
public:
	test_crossroad(){};
	virtual ~test_crossroad(){};
	void runtest()
	{
		// init parameters
		float init_density = 0.01;
		float step = 0.01;
		int iteration_num = 500;
		int road_length = 100;
		int lanes_num = 1;
		random::initialize();


		// start model
		while(init_density <= 1)
		{
			// entity factories
			road_factory roadf;
			vehicle_factory_ptr vehf_p(new vehicle_factory());
			lightsignal_factory lightsignalf;

			road_ptr road0 = roadf.create_road(lanes_num, road_length);
			road_ptr road1 = roadf.create_road(lanes_num, road_length);
			road_ptr road2 = roadf.create_road(lanes_num, road_length);
			road_ptr road3 = roadf.create_road(lanes_num, road_length);
			road_ptr road4 = roadf.create_road(lanes_num, 1000);
			road_ptr road5 = roadf.create_road(lanes_num, 1000);
			road_ptr road6 = roadf.create_road(lanes_num, 1000);
			road_ptr road7 = roadf.create_road(lanes_num, 1000);
			vehicle_feeder_ptr feeder_p(new vehicle_feeder(vehf_p));
			feeder_params_ptr params (new feeder_params(init_density, 20, 80, 1, 0));
			feeder_p->connect_feeding_road(road0, params);
	//		feeder_p->connect_feeding_road(road1, params);
	//		feeder_p->connect_feeding_road(road2, params);
	//		feeder_p->connect_feeding_road(road3, params);

			// init road loop
			crossroad_ptr cross = roadf.get_crossroad(road0->get_id());
			lightsignal_ptr lightsignal = lightsignalf.create_lightsignal(10,2,10,Green);

			road1->set_connector(cross);
			road2->set_connector(cross);
			road3->set_connector(cross);

			cross->connect(road6, road0->get_id(), DIRECTION_STRAIGHT);
			cross->connect(road5, road0->get_id(), DIRECTION_LEFT);
			cross->connect(road7, road0->get_id(), DIRECTION_RIGHT);

			cross->connect(road7, road1->get_id(), DIRECTION_STRAIGHT);
			cross->connect(road6, road1->get_id(), DIRECTION_LEFT);
			cross->connect(road4, road1->get_id(), DIRECTION_RIGHT);

			cross->connect(road4, road2->get_id(), DIRECTION_STRAIGHT);
			cross->connect(road7, road2->get_id(), DIRECTION_LEFT);
			cross->connect(road5, road2->get_id(), DIRECTION_RIGHT);

			cross->connect(road5, road3->get_id(), DIRECTION_STRAIGHT);
			cross->connect(road4, road3->get_id(), DIRECTION_LEFT);
			cross->connect(road6, road3->get_id(), DIRECTION_RIGHT);


			// set accumulation time
			roadf.get_road_statistics(road0->get_id())->set_stat_accumulation_time(iteration_num/4);
	//		roadf.get_road_statistics(road1->get_id())->set_stat_accumulation_time(iteration_num/4);
	//		roadf.get_road_statistics(road2->get_id())->set_stat_accumulation_time(iteration_num/4);
	//		roadf.get_road_statistics(road3->get_id())->set_stat_accumulation_time(iteration_num/4);

			// iteration process start
			int k = 0;

			while(k < iteration_num)
			{
		//		std::cout<<"iter "<<k<<std::endl;
				k++;
				feeder_p->feed_roads();

		//		cross->print_crossroad(road0->get_id());
		/*		std::cout<<""<<std::endl;
				std::cout<<road0;
				std::cout<<road1;
				std::cout<<road2;
				std::cout<<road3;
				std::cout<<road4;
				std::cout<<road5;
				std::cout<<road6;
				std::cout<<road7;*/
				roadf.iterate();
				lightsignalf.tick();

			}

			// statistic data
			road_stat_data_ptr  stat = roadf.get_road_statistics(road0->get_id());
			std::cout.precision(5);
			std::cout<<stat->get_current_road_density()<<"|"
				<<stat->get_avg_road_density()<<"|"
				<<stat->get_current_vehicles_number()<<"|"
				<<stat->get_avg_queue()<<"|"
				<<stat->get_max_queue()<<"|"
			<<std::endl;
	/*		stat = roadf.get_road_statistics(road1->get_id());
			std::cout.precision(5);
			std::cout<<stat->get_current_road_density()<<"|"
					<<stat->get_avg_road_density()<<"|"
					<<stat->get_current_vehicles_number()<<"|"
					<<stat->get_avg_queue()<<"|"
					<<stat->get_max_queue()<<"|";
					std::cout<<"  |||  ";
			stat = roadf.get_road_statistics(road2->get_id());
			std::cout.precision(5);
			std::cout<<stat->get_current_road_density()<<"|"
					<<stat->get_avg_road_density()<<"|"
					<<stat->get_current_vehicles_number()<<"|"
					<<stat->get_avg_queue()<<"|"
					<<stat->get_max_queue()<<"|";
					std::cout<<"  |||  ";
			stat = roadf.get_road_statistics(road3->get_id());
			std::cout.precision(5);
			std::cout<<stat->get_current_road_density()<<"|"
					<<stat->get_avg_road_density()<<"|"
					<<stat->get_current_vehicles_number()<<"|"
					<<stat->get_avg_queue()<<"|"
					<<stat->get_max_queue()<<"|"
				<<std::endl;*/
			init_density += step;
		}
	};
};

#endif /* TEST_CROSSROAD_H_ */

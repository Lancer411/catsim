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
		float init_density = 0.1;
		float step = 0.1;
		int iteration_num = 10800;
		int road_length = 100;
		int lanes_num = 2;
		random::initialize();


		// start model
		while(init_density <= 1)
		{
			int16 init_speed = 20, max_speed = 80;
			float speed_rand = random::std_random();
			if (speed_rand<0.5)
			   max_speed= (20 + sqrt(400 - 800 * (0.5 - speed_rand)));
			else max_speed= (60 - (sqrt(3600 - 800 * (3.5 +  speed_rand))));

			// entity factories
			road_factory roadf;
			vehicle_factory_ptr vehf_p(new vehicle_factory());
			lightsignal_factory lightsignalf;

			road_ptr road0 = roadf.create_road(lanes_num, road_length);
			road_ptr road1 = roadf.create_road(lanes_num, road_length);
			road_ptr road2 = roadf.create_road(lanes_num, road_length);
			road_ptr road3 = roadf.create_road(lanes_num, road_length);
			road_ptr road4 = roadf.create_road(lanes_num, road_length);
			road_ptr road5 = roadf.create_road(lanes_num, road_length);
			road_ptr road6 = roadf.create_road(lanes_num, road_length);
			road_ptr road7 = roadf.create_road(lanes_num, road_length);
			road_ptr road8 = roadf.create_road(lanes_num, road_length);
			road_ptr road9 = roadf.create_road(lanes_num, road_length);
			road_ptr road10 = roadf.create_road(lanes_num, road_length);
			road_ptr road11 = roadf.create_road(lanes_num, road_length);

			vehicle_feeder_ptr feeder_p(new vehicle_feeder(vehf_p));
			vehicle_feeder_ptr feeder_p5(new vehicle_feeder(vehf_p));
			vehicle_feeder_ptr feeder_p6(new vehicle_feeder(vehf_p));
			vehicle_feeder_ptr feeder_p7(new vehicle_feeder(vehf_p));
			feeder_params_ptr params (new feeder_params(init_density, init_speed, max_speed, 1, 0));
			params->mode = DISTRIBUTIVE;
			params->distribution_type = POISSON;

			feeder_params_ptr params1 (new feeder_params(0, 0, 0, 0, 0));


	/*		feeder_params_ptr params2 (new feeder_params(init_density, init_speed, max_speed, 1, 0));
			params2->mode = DISTRIBUTIVE;
			params2->distribution_type = POISSON;
			random::init_int_poisson(1);*/

//			feeder_p->connect_feeding_road(road0, params);
//			feeder_p->connect_feeding_road(road1, params);
//			feeder_p->connect_feeding_road(road2, params);
//			feeder_p->connect_feeding_road(road3, params);
			feeder_p->connect_feeding_road(road8, params);
			feeder_p->connect_feeding_road(road9, params);
			feeder_p->connect_feeding_road(road10, params);
			feeder_p->connect_feeding_road(road11, params);

			feeder_p5->connect_feeding_road(road5,params1);
			feeder_p5->connect_deadend_road(road5,road5->get_id());
			road5->set_connector(feeder_p5);
			feeder_p5->set_transfer_mode(DELETING);

			feeder_p6->connect_feeding_road(road6,params1);
			feeder_p6->connect_deadend_road(road6,road6->get_id());
			road6->set_connector(feeder_p6);
			feeder_p6->set_transfer_mode(DELETING);

			feeder_p7->connect_feeding_road(road7,params1);
			feeder_p7->connect_deadend_road(road7,road7->get_id());
			road7->set_connector(feeder_p7);
			feeder_p7->set_transfer_mode(DELETING);

			// init road loop
			crossroad_ptr cross = roadf.get_crossroad(road0->get_id());
			crossroad_ptr cross1 = roadf.get_crossroad(road8->get_id());
			crossroad_ptr cross2 = roadf.get_crossroad(road9->get_id());
			crossroad_ptr cross3 = roadf.get_crossroad(road10->get_id());
			crossroad_ptr cross4 = roadf.get_crossroad(road11->get_id());
			lightsignal_ptr lightsignal = lightsignalf.create_lightsignal(25,3,32,Green);
			lightsignal_ptr lightsignal8 = lightsignalf.create_lightsignal(25,3,32,Green);
			lightsignal_ptr lightsignal9 = lightsignalf.create_lightsignal(25,3,32,Red);
			lightsignal_ptr lightsignal10 = lightsignalf.create_lightsignal(43,3,78,Green);
			lightsignal_ptr lightsignal11 = lightsignalf.create_lightsignal(25,3,32,Red);
			road1->set_connector(cross);
			road2->set_connector(cross);
			road3->set_connector(cross);
			cross->connect_in(road1);
			cross->connect_in(road2);
			cross->connect_in(road3);


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

			cross1->connect(road0, road8->get_id(),DIRECTION_STRAIGHT);
			cross2->connect(road1, road9->get_id(),DIRECTION_STRAIGHT);
			cross3->connect(road2, road10->get_id(),DIRECTION_STRAIGHT);
			cross4->connect(road3, road11->get_id(),DIRECTION_STRAIGHT);

			cross->add_light_signal(lightsignal, ADAPTIVE);
			cross1->add_light_signal(lightsignal8,FIXED);
			cross2->add_light_signal(lightsignal9,FIXED);
			cross3->add_light_signal(lightsignal10,FIXED);
			cross4->add_light_signal(lightsignal11,FIXED);

			// set accumulation time
			roadf.get_road_statistics(road0->get_id())->set_stat_accumulation_time(iteration_num/4);
			roadf.get_road_statistics(road1->get_id())->set_stat_accumulation_time(iteration_num/4);
			roadf.get_road_statistics(road2->get_id())->set_stat_accumulation_time(iteration_num/4);
			roadf.get_road_statistics(road3->get_id())->set_stat_accumulation_time(iteration_num/4);

			// iteration process start
			int k = 0;

			while(k < iteration_num)
			{
	//			std::cout<<"iter "<<k<<std::endl;
				k++;
				feeder_p->feed_roads();

				//		cross->print_crossroad(road0->get_id());
/*		//		std::cout<<""<<std::endl;
		//		std::cout<<road8;
				std::cout<<road0;
		//		std::cout<<road5;
		//		std::cout<<road6;
		//		std::cout<<road7;
				std::cout<<""<<std::endl;
		//		std::cout<<road9;
				std::cout<<road1;
				std::cout<<""<<std::endl;
				std::cout<<road2;
				std::cout<<""<<std::endl;
				std::cout<<road3;
		//		std::cout<<road4;*/



		//		std::cout<<road10;
		//		std::cout<<road11;
				roadf.iterate();
				lightsignalf.tick();

			}

			// statistic data
			road_stat_data_ptr  stat = roadf.get_road_statistics(road0->get_id());
			std::cout.precision(5);
			std::cout<<stat->get_current_road_density()<<"|"
				<<stat->get_avg_road_density()<<"|"
				<<stat->get_road_flow_as_speeddensity()<<"|"
				<<stat->get_passed_vehicles_number()<<"|"
				<<stat->get_current_vehicles_number()<<"|"
				<<stat->get_avg_road_passage_time()<<"|"
				<<stat->get_avg_queue()<<"|"
				<<stat->get_max_queue()<<"|";
			std::cout<<"  |||  ";
			stat = roadf.get_road_statistics(road1->get_id());
			std::cout.precision(5);
			std::cout<<stat->get_current_road_density()<<"|"
					<<stat->get_avg_road_density()<<"|"
					<<stat->get_road_flow_as_speeddensity()<<"|"
					<<stat->get_passed_vehicles_number()<<"|"
					<<stat->get_current_vehicles_number()<<"|"
					<<stat->get_avg_road_passage_time()<<"|"
					<<stat->get_avg_queue()<<"|"
					<<stat->get_max_queue()<<"|";
			std::cout<<"  |||  ";
			stat = roadf.get_road_statistics(road2->get_id());
			std::cout.precision(5);
			std::cout<<stat->get_current_road_density()<<"|"
					<<stat->get_avg_road_density()<<"|"
					<<stat->get_road_flow_as_speeddensity()<<"|"
					<<stat->get_passed_vehicles_number()<<"|"
					<<stat->get_current_vehicles_number()<<"|"
					<<stat->get_avg_road_passage_time()<<"|"
					<<stat->get_avg_queue()<<"|"
					<<stat->get_max_queue()<<"|";
				std::cout<<"  |||  ";
			stat = roadf.get_road_statistics(road3->get_id());
			std::cout.precision(5);
			std::cout<<stat->get_current_road_density()<<"|"
					<<stat->get_avg_road_density()<<"|"
					<<stat->get_road_flow_as_speeddensity()<<"|"
					<<stat->get_passed_vehicles_number()<<"|"
					<<stat->get_current_vehicles_number()<<"|"
					<<stat->get_avg_road_passage_time()<<"|"
					<<stat->get_avg_queue()<<"|"
					<<stat->get_max_queue()<<"|";
			std::cout<<std::endl;
			init_density += step;
		}
	};
};

#endif /* TEST_CROSSROAD_H_ */

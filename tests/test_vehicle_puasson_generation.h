/*
 * test_vehicle_generation.h
 *
 *  Created on: Nov 18, 2012
 *      Author: ngh
 *
 */

#ifndef TEST_VEHICLE_PUASSON_GENERATION_H_
#define TEST_VEHICLE_PUASSON_GENERATION_H_
#include "test.h"
#include "core/factories/road_factory.h"
#include "core/factories/vehicle_factory.h"


class test_vehicle_puasson_generation : public test
{
public:
	test_vehicle_puasson_generation(){};
	virtual ~test_vehicle_puasson_generation(){};
	void runtest()
	{
		float init_density = 0.01;
		int iteration_num = 3600;
		int road_length = 400;
		int lanes_num = 1;
		float car_prob = 0.75,
			  truck_prob = 0.1;
		road_factory roadf;
		vehicle_factory vehf;
		road_ptr road = roadf.create_road(lanes_num, road_length);
		roadf.get_road_statistics(road->get_id())->set_stat_accumulation_time(iteration_num/2);
		crossroad_ptr cross = roadf.get_crossroad(road->get_id());
		cross->set_road_output(road);
		while(init_density <= 1)
		{
			// initiation parameters
			float density = init_density;

			// iteration process start
			int k = 0;

			while(k < iteration_num)
			{
				if(random::std_random() < density)
				{
					int16 init_speed = 20, max_speed = 80;
					float speed_rand = random::std_random();
					if (speed_rand<0.5)
						max_speed= (20 + sqrt(400 - 800 * (0.5 - speed_rand)));
					else max_speed= (60 - (sqrt(3600 - 800 * (3.5 +  speed_rand))));
					vehicle_type veh_type = Car;
					vehicle_ptr veh = vehf.create_vehicle(max_speed, init_speed, veh_type);
					road->push_vehicle(veh);
				}
	//			cout<<"iter "<<k<<std::endl;
				k++;
	//			cout<<road;
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
//				<<stat->get_avg_road_passage_time()<<"|"
				<<std::endl;


			init_density += 0.01;
			road->clear();
			vehf.delete_all_vehicles();
			stat->reset();
		}
	};
};

#endif /* TEST_VEHICLE_PUASSON_GENERATION_H_ */

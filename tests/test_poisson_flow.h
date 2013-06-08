/*
 * test_poisson_flow.h
 *
 *  Created on: Jun 8, 2013
 *      Author: naghtarr
 */

#ifndef TEST_POISSON_FLOW_H_
#define TEST_POISSON_FLOW_H_
#include "test.h"
#include "core/factories/road_factory.h"
#include "core/factories/vehicle_factory.h"
#include "core/connectors/vehicle_feeder.h"

class test_poisson_flow : public test
{
public:
	test_poisson_flow(){};
	~test_poisson_flow(){};
	void runtest()
	{
		int iteration_num = 10000;
		int road_length = 100;
		int lane_num = 1;
		float density = 0.5;
		road_factory roadf;
		vehicle_factory_ptr vehf_p(new vehicle_factory());
		road_ptr road = roadf.create_road(lane_num, road_length);
		roadf.get_road_statistics(road->get_id())->set_stat_accumulation_time(iteration_num/2);
		vehicle_feeder_ptr feeder_p(new vehicle_feeder(vehf_p));

		feeder_params_ptr params (new feeder_params(density, 20, 60, 1, 0));
		params->mode = DISTRIBUTIVE;
		params->distribution_type = TRIANGLE;
		random::init_int_trianle(1,2,2);
		feeder_p->connect_feeding_road(road, params);
		feeder_p->connect_deadend_road(road, road->get_id());
		road->set_connector(feeder_p);
		feeder_p->set_transfer_mode(DELETING);

		// set accumulation time
		roadf.get_road_statistics(road->get_id())->set_stat_accumulation_time(iteration_num/4);
		// iteration process start
		int k = 0;

		while(k < iteration_num)
		{
//			std::cout<<"iter "<<k<<std::endl;
			k++;
			feeder_p->feed_roads();
//			std::cout<<road;
			roadf.iterate();
		}

		// statistic data
		road_stat_data_ptr  stat = roadf.get_road_statistics(road->get_id());
		std::cout.precision(5);
		std::cout<<"Current Density: "<<stat->get_current_road_density()<<std::endl;
		std::cout<<"Average Density: "<<stat->get_avg_road_density()<<std::endl;
		std::cout<<"Average Road Speed: "<<stat->get_avg_road_speed()<<std::endl;
		std::cout<<"Average Total Road Speed: "<<stat->get_avg_road_speed_total()<<std::endl;
		std::cout<<"Road Flow: "<<stat->get_road_flow_as_speeddensity()<<std::endl;
		std::cout<<"Passed Vehicles: "<<stat->get_passed_vehicles_number()<<std::endl;
		std::cout<<"Current Vehicles: "<<stat->get_current_vehicles_number()<<std::endl;
		std::cout<<"Average Passage Time: "<<stat->get_avg_road_passage_time()<<std::endl;

		time_density_histogram hist = stat->get_time_density_histogram();

		double total = 0.0;

		for( int i = 0; i < hist.size(); i++ )
		{
			std::cout << "Bin lower bound: " << hist[i].first << ", Value: " << hist[i].second << std::endl;
			total += hist[i].second;
		}

		std::cout << "Total: " << total << std::endl;
	};
};

#endif /* TEST_POISSON_FLOW_H_ */

/*
 * test_read_network.h
 *
 *  Created on: Aug 17, 2013
 *      Author: naghtarr
 */

#ifndef TEST_READ_NETWORK_H_
#define TEST_READ_NETWORK_H_
#include "test.h"
#include "io/road_network_json_reader.h"
#include "model/roadnetworkmodel.h"
#include "model/simulationmodel.h"
#include "model/statisticsmodel.h"

class test_read_network : public test
{
public:
	test_read_network(){};
	virtual ~test_read_network(){};
	void runtest()
	{
		int iterations = 800;
		road_network_data_ptr network_data = road_network_json_reader::read("test_models/one_road_test.json");
		road_network_model_ptr network_model(new roadnetwork_model());
		network_model->build_network(network_data);
		simulation_model_ptr sim_model(new simulation_model(iterations));
		statistics_model_ptr stat_model(new statistics_model());
		stat_model->set_data_accumulation_time(iterations/4);
		stat_model->add_data_param(ROAD_DENSITY);
		stat_model->add_data_param(SPEED);
		stat_model->add_data_param(FLOW);
		stat_model->add_data_param(VEHICLES);
		stat_model->add_data_param(PASSAGE_TIME);
		stat_model->add_data_param(ROAD_QUEUE);
		stat_model->add_stat_param(MEAN);

		sim_model->launch_simulation(network_model, stat_model);
	};
};



#endif /* TEST_READ_NETWORK_H_ */

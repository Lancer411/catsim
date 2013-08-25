/*
 * simulationmodel.h
 *
 *  Created on: Aug 17, 2013
 *      Author: naghtarr
 */

#ifndef SIMULATIONMODEL_H_
#define SIMULATIONMODEL_H_
#include "core/tools/random.h"
#include "roadnetworkmodel.h"
#include "statisticsmodel.h"

const float DEFAULT_INITIAL_DENSITY = 0.01;
const float DEFAULT_DENSITY_STEP = 0.01;

class simulation_model
{
	float initial_density;
	float simulation_density_step;
	int iterations_number;
public:

	simulation_model(int iterations_number)
	{
		this->iterations_number = iterations_number;
		this->initial_density = DEFAULT_INITIAL_DENSITY;
		this->simulation_density_step = DEFAULT_DENSITY_STEP;
		random::initialize();
	};
	virtual ~simulation_model(){};

	int get_iterations_number() const {return this->iterations_number;};
	float get_initial_density() const {return this->initial_density;};
	float get_density_step() const {return this->simulation_density_step;};

	void set_iterations_number(const int number) {this->iterations_number = number;};
	void set_initial_density(const float density)
	{
		if(density >=1 || density < 0)
			return;
		this->initial_density = density;
	};

	void set_simulation_density_step(const float step)
	{
		if(step >=1 || step < 0)
			return;
		this->simulation_density_step = step;
	};

	void launch_simulation(road_network_model_ptr network_model, statistics_model_ptr statistics_model)
	{
		while(initial_density <= 1)
		{
//			std::cout << initial_density << std::endl;
			network_model->reset_to_density(initial_density);
			network_model->set_stat_data_accumulation_time(statistics_model->get_data_accumulation_time());
			int iteration = 0;
			while(iteration < iterations_number)
			{
				iteration++;
				network_model->iterate();
			}
			network_model->print();
			initial_density += simulation_density_step;
		}
	}

 };

typedef boost::shared_ptr<simulation_model> simulation_model_ptr;

#endif /* SIMULATIONMODEL_H_ */

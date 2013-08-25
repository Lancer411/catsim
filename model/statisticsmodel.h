/*
 * statisticsmodel.h
 *
 *  Created on: Aug 17, 2013
 *      Author: naghtarr
 */

#ifndef STATISTICSMODEL_H_
#define STATISTICSMODEL_H_
#include "roadnetworkmodel.h"
#include <fstream>
#include <boost/container/set.hpp>

const char *TOOL_NAME = "CATSim";
const char *TOOL_DESCRIPTION = "Cellular Automata Traffic Simulator";
const char *TOOL_VERSION = "0.1b";

enum DATA_PARAMS
{
	ROAD_DENSITY,
	SPEED,
	FLOW,
	VEHICLES,
	PASSAGE_TIME,
	ROAD_QUEUE
};

enum STAT_PARAMS
{
	MEAN,
	MEDIAN,
	KURTOSIS,
	MAX,
	MIN,
	SUM,
	VARIANCE,
	DEVIATION
};

class statistics_model {
	long data_accumulation_time;
	boost::container::set<DATA_PARAMS> data_params;
	boost::container::set<STAT_PARAMS> stat_params;
	std::string output_filename;
	std::ofstream out;
public:
	statistics_model(std::string filename) :
		output_filename(filename),
		out(filename.data(), std::ofstream::out)
	{
		out.precision(5);
		data_accumulation_time = 0;
	};

	virtual ~statistics_model()
	{
		out.close();
	};

	void set_data_accumulation_time(const long t) {this->data_accumulation_time = t;};
	long get_data_accumulation_time() const{return this->data_accumulation_time;}

	void add_data_param(DATA_PARAMS param)
	{
		data_params.insert(param);
	}

	void add_stat_param(STAT_PARAMS param)
	{
		stat_params.insert(param);
	}

	void print_model_data(int iterations, float initial_density, float final_density, float density_step, road_network_model_ptr network)
	{
		out << "===================   CATSIM INFORMATION   ===================" << std::endl;
		out << TOOL_NAME << " - " << TOOL_DESCRIPTION << std::endl;
		out << "Version: " << TOOL_VERSION << std::endl;
		out << "=================== ROAD NETWORK SIMULATION ===================" << std::endl;
		out << "Iterations number: " << iterations << std::endl;
		out << "Initial road density: " << initial_density << std::endl;
		out << "Final road density: " << final_density << std::endl;
		out << "Density Step: " << density_step << std::endl;
		out << "Data accumulation time: " << data_accumulation_time << " iterations" << std::endl;
		out << "Roads count: " << network->roads_factory->count();
	};

	void print_simulation_data(road_network_model_ptr network)
	{

	};
};

typedef boost::shared_ptr<statistics_model> statistics_model_ptr;

#endif /* STATISTICSMODEL_H_ */

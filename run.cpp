/*
	run.cpp

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

#include "tests/testrunner.h"
#include "define/cadef.h"
#include "command_line.h"

int main(int ac, char* av[])
{

//	runtests();
	command_line cl;
	cl.parser(ac, av);
	int iterations = cl.iterations;
	road_network_data_ptr network_data = road_network_json_reader::read(cl.input_path);
	road_network_model_ptr network_model(new roadnetwork_model());
	network_model->build_network(network_data);
	simulation_model_ptr sim_model(new simulation_model(iterations));
	statistics_model_ptr stat_model(new statistics_model(cl.output_path));

	stat_model->set_data_accumulation_time(cadef::stat_accumulation_time);

	stat_model->add_data_param(ROAD_DENSITY);
	stat_model->add_data_param(SPEED);
	stat_model->add_data_param(FLOW);
	stat_model->add_data_param(VEHICLES);
	stat_model->add_data_param(PASSAGE_TIME);
	stat_model->add_data_param(ROAD_QUEUE);

	stat_model->add_stat_param(MIN);
	stat_model->add_stat_param(MAX);
	stat_model->add_stat_param(SUM);
	stat_model->add_stat_param(MEAN);
	stat_model->add_stat_param(MEDIAN);
	stat_model->add_stat_param(DEVIATION);
	stat_model->add_stat_param(VARIANCE);
	stat_model->add_stat_param(KURTOSIS);

	sim_model->launch_simulation(network_model, stat_model);
	return 0;
}

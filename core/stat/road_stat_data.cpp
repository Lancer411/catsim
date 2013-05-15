/*
	road_stat_data.cpp

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

#include "road_stat_data.h"

road_stat_data::road_stat_data(int16 linesnum, int16 length)
{
	road_length = length;
	road_lanes_count = linesnum;
	reset();
}

void road_stat_data::update_parameters()
{
	stat_timer++;

	current_road_density = current_vehicles_length/(float)(road_length*road_lanes_count);
	density_accumulator(current_road_density);

	avg_road_speed = boost::accumulators::mean(avg_speed_accumulator);
	total_speed_accumulator(avg_road_speed);

	passed_veh_acc((float)passed_vehicles_number_iter);
	if(stat_timer == stat_accumulation_time)
	{
		avg_road_density = boost::accumulators::mean(density_accumulator);
		avg_road_passage_time = boost::accumulators::mean(passage_time_accumulator);
		avg_road_speed_total = boost::accumulators::mean(total_speed_accumulator);
		road_flow = avg_road_density * avg_road_speed_total*road_lanes_count;
		flow = boost::accumulators::mean(passed_veh_acc);
		reset_timer();
	}
	passed_vehicles_number_iter = 0;
}

void road_stat_data::inc_passed_vehicles_num(int16 time)
{
	passed_vehicles_number++;
	passage_time_accumulator(time);
	passed_vehicles_number_iter ++;
}

void road_stat_data::update_avg_speed(short speed)
{
	avg_speed_accumulator((float)speed);
}

void road_stat_data::reset_timer()
{
	stat_timer = 0;
	density_accumulator = float_acc();
	avg_speed_accumulator = float_acc();
	total_speed_accumulator = float_acc();
	passage_time_accumulator = long_acc();
	passed_veh_acc = float_acc();
}

void road_stat_data::reset()
{
	passed_vehicles_number_iter =
	passed_vehicles_number = current_vehicles_number =
	current_vehicles_length =
	current_road_density = avg_road_density =
	avg_road_speed = avg_road_speed_total =
	avg_road_passage_time = road_flow = flow = 0;
	stat_accumulation_time = DEFAULT_STAT_ACCUMULATION_TIME;
	reset_timer();
}

void road_stat_data::inc_current_vehicles_num(short veh_length)
{
	current_vehicles_number++;
	current_vehicles_length += veh_length;
}

void road_stat_data::dec_current_vehicles_num(short veh_length)
{
	current_vehicles_number--;
	current_vehicles_length -= veh_length;
}

road_stat_data::~road_stat_data()
{

}

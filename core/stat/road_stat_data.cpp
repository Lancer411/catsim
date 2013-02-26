/*
 * road_stat_data.cpp
 *
 *  Created on: Nov 12, 2012
 *      Author: ngh
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
	density_accumulator += current_road_density;

	avg_road_speed = avg_speed_accumulator/current_vehicles_number;
	total_speed_accumulator += avg_road_speed;
	avg_speed_accumulator = 0;

	if(stat_timer == stat_accumulation_time)
	{
		avg_road_density = density_accumulator/stat_accumulation_time;
		avg_road_passage_time = (float)passage_time_accumulator/ (float)passed_vehicles_number;
		avg_road_speed_total = total_speed_accumulator/stat_accumulation_time;
		road_flow = avg_road_density * avg_road_speed_total;
		reset_timer();
	}
}

void road_stat_data::inc_passed_vehicles_num(int16 time)
{
	passed_vehicles_number++;
	passage_time_accumulator += time;
}
void road_stat_data::reset_timer()
{
	stat_timer = 0;
	density_accumulator = passage_time_accumulator =
	total_speed_accumulator = 0;
//	passed_vehicles_number = 0;
}

void road_stat_data::reset()
{
	passed_vehicles_number = current_vehicles_number =
	current_vehicles_length =
	current_road_density = avg_road_density =
	avg_road_speed = avg_road_speed_total =
	avg_road_passage_time = road_flow = 0;
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

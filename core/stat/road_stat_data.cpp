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

int_dens_acc road_stat_data::dens_acc (stat_density::num_bins = 40, stat_density::cache_size = 20);

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
	queue_accumulator (current_queue);

	update_stat_data_params_float(speed, avg_speed_accumulator);
	total_speed_accumulator(speed.mean);

	passed_veh_acc((float)passed_vehicles_number_iter);
	if(stat_timer == stat_accumulation_time)
	{
		update_stat_data_params_float(density, density_accumulator);
		update_stat_data_params_long(passage_time, passage_time_accumulator);
		update_stat_data_params_float(queue, queue_accumulator);
		update_stat_data_params_float(speed_total, total_speed_accumulator);
		update_stat_data_params_float(passed_vehicles, passed_veh_acc);
		reset_timer();
	}
	passed_vehicles_number_iter = 0;

	typedef boost::container::vector<road_marker_ptr>::value_type marker_item;
	BOOST_FOREACH(marker_item item, markers_list)
	{
		int position = item->get_position();
		if(item->is_triggered())
		{
			markers_time_intervals[position](item->get_time_interval_prev());
			road_stat_data::dens_acc(item->get_time_interval_prev());
		}

		item->iterate();
	}
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
	density_accumulator = accumulator<float>::type();
	avg_speed_accumulator = accumulator<float>::type();
	total_speed_accumulator = accumulator<float>::type();
	passage_time_accumulator = accumulator<long>::type();
	passed_veh_acc = accumulator<float>::type();
	queue_accumulator = accumulator<float>::type();
	markers_time_intervals.clear();
}

void road_stat_data::reset()
{
	passed_vehicles_number_iter =
	passed_vehicles_number = current_vehicles_number =
	current_queue = current_vehicles_length = current_road_density = 0;

	density.reset();
	speed.reset();
	passed_vehicles.reset();
	passage_time.reset();
	queue.reset();

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

void road_stat_data::inc_queue_vehicles_num()
{
	current_queue++;
}

void road_stat_data::reset_queue_vehicles_num()
{
	if (current_queue > queue.max)
		queue.max = current_queue;
	current_queue=0;
}


void road_stat_data::add_marker(const road_marker_ptr marker)
{
	boost::container::vector<road_marker_ptr>::iterator it = markers_list.end();
	markers_list.insert(it, marker);
}

time_density_histogram road_stat_data::get_time_density_histogram()
{
	time_density_histogram hist = boost::accumulators::density(road_stat_data::dens_acc);
	return hist;
}

road_stat_data::~road_stat_data()
{
	markers_list.clear();
}

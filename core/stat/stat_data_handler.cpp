/*
 * stat_data_handler.cpp
 *
 *  Created on: Nov 13, 2012
 *      Author: ngh
 */

#include "stat_data_handler.h"

stat_data_handler::stat_data_handler()
{
	// TODO Auto-generated constructor stub

}

road_stat_data_ptr stat_data_handler::register_data(std::string road_id, int16 lanes, int16 len)
{
	road_stat_data_ptr p(new road_stat_data(lanes, len));
	data[road_id] = p;
	return p;
}

road_stat_data_ptr stat_data_handler::get_road_data(std::string road_id)
{
	return data[road_id];
}

void stat_data_handler::delete_data(std::string road_id)
{
	data[road_id].reset();
	data.erase(road_id);
}

stat_data_handler::~stat_data_handler()
{
	// TODO Auto-generated destructor stub
}

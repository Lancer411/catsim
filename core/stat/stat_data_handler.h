/*
 * stat_data_handler.h
 *
 *  Created on: Nov 13, 2012
 *      Author: ngh
 */

#ifndef STAT_DATA_HANDLER_H_
#define STAT_DATA_HANDLER_H_
#include "define/cadef.h"
#include "core/entities/road.h"
#include "core/stat/road_stat_data.h"
#include <map>

typedef std::map<std::string, road_stat_data_ptr> road_stat_data_map;

class stat_data_handler
{
	road_stat_data_map data;
public:
	stat_data_handler();
	road_stat_data_ptr register_data(std::string road_id, int16 lanes, int16 len);
	road_stat_data_ptr get_road_data(std::string road_id);
	void delete_data(std::string road_id);
	virtual ~stat_data_handler();
};

#endif /* STAT_DATA_HANDLER_H_ */

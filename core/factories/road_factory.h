/*
 * road_factory.h
 *
 *  Created on: Nov 13, 2012
 *      Author: ngh
 */

#ifndef ROAD_FACTORY_H_
#define ROAD_FACTORY_H_
#include "define/cadef.h"
//#include "factory.h"
#include "core/entities/road.h"
#include "core/connectors/crossroad.h"
#include "core/stat/stat_data_handler.h"
#include <map>

//typedef std::map<std::string, road_ptr> factory_container;

class road_factory //: factory<road_ptr>
{
	std::map<std::string, road_ptr>  roads;
	std::map<std::string, crossroad_ptr> crossroads;
	long id_counter;
	stat_data_handler stat_data;
public:
	road_factory();
	road_ptr create_road(int16 linesnum, int16 length);
	road_ptr create_road(int16 linesnum, int16 length, short velocity_limit);
	void delete_road(std::string id);
	const road_ptr get_road(std::string id);
	const road_stat_data_ptr get_road_statistics(std::string id);
	const stat_data_handler& get_stat_data_handler(){return stat_data;};
	crossroad_ptr get_crossroad(std::string road_id);
	size_t count();
	void iterate();
	virtual ~road_factory();
};


#endif /* ROAD_FACTORY_H_ */

/*
 * road_factory.cpp
 *
 *  Created on: Nov 13, 2012
 *      Author: ngh
 */

#include "road_factory.h"

road_factory::road_factory()
{
	id_counter = 0;
}

road_ptr road_factory::create_road(int16 linesnum, int16 length)
{
	road_ptr p(new road(linesnum, length));
	std::string id = "ROAD_"+id_counter++;
	p->set_id(id);
	road_stat_data_ptr data = stat_data.register_data(id, linesnum, length);
	p->set_road_stat_data(data);
	roads[id] = p;
	crossroad_ptr cross(new crossroad());
	cross->set_road_input(p);
	p->set_crossroad(cross);
	crossroads[id] = cross;
	return p;
}

road_ptr road_factory::create_road(int16 linesnum, int16 length, short velocity_limit)
{
	road_ptr p(new road(linesnum, length, velocity_limit));
	std::string id = "ROAD_"+id_counter++;
	p->set_id(id);
	road_stat_data_ptr data = stat_data.register_data(id, linesnum, length);
	p->set_road_stat_data(data);
	roads[id] = p;
	crossroad_ptr cross(new crossroad());
	cross->set_road_input(p);
	p->set_crossroad(cross);
	crossroads[id] = cross;
	return p;
}

void road_factory::delete_road(std::string id)
{
	roads[id].reset();
	roads.erase(id);
	stat_data.delete_data(id);
}

const road_ptr road_factory::get_road(std::string id)
{
	return roads[id];
}

size_t road_factory::count()
{
	return roads.size();
}

void road_factory::iterate()
{
	std::map<std::string, road_ptr>::iterator it;
	for (it = roads.begin(); it != roads.end();++it)
	{
		it->second->iterate();
	}
}

crossroad_ptr road_factory::get_crossroad(std::string road_id)
{
	return crossroads[road_id];
}

const road_stat_data_ptr road_factory::get_road_statistics(std::string id)
{
	return stat_data.get_road_data(id);
}

road_factory::~road_factory()
{
	roads.clear();
	crossroads.clear();
}

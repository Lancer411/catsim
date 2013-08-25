/*
	road_factory.cpp

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

#include "road_factory.h"

road_factory::road_factory()
{
	id_counter = 0;
}

road_ptr road_factory::create_road(int16 linesnum, int16 length)
{
	road_ptr p(new road(linesnum, length));
	std::string id = "ROAD_" + boost::lexical_cast<std::string> (id_counter++);
	p->set_id(id);
	road_stat_data_ptr data = stat_data.register_data(id, linesnum, length);
	p->set_road_stat_data(data);
	roads[id] = p;

	road_marker_ptr marker(new road_marker(ROAD_MARKER_SPECIAL_POSITION));
	data->add_marker(marker);

	p->add_marker(marker);

	crossroad_ptr cross(new crossroad());
	cross->add_first_road(p);
	p->set_connector(cross);
	crossroads[id] = cross;
	return p;
}

road_ptr road_factory::create_road(int16 linesnum, int16 length, short velocity_limit)
{
	road_ptr p(new road(linesnum, length, velocity_limit));
	std::string id = "ROAD_" + boost::lexical_cast<std::string> (id_counter++);
	p->set_id(id);
	road_stat_data_ptr data = stat_data.register_data(id, linesnum, length);
	p->set_road_stat_data(data);
	roads[id] = p;
	crossroad_ptr cross(new crossroad());
	cross->add_first_road(p);
	p->set_connector(cross);
	crossroads[id] = cross;
	return p;
}

road_ptr road_factory::create_road(int16 linesnum, int16 length, short velocity_limit, std::string id)
{
	road_ptr p(new road(linesnum, length, velocity_limit));
	p->set_id(id);
	road_stat_data_ptr data = stat_data.register_data(id, linesnum, length);
	p->set_road_stat_data(data);
	roads[id] = p;
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
	road_map::iterator it;
	for (it = roads.begin(); it != roads.end();++it)
	{
		it->second->iterate();
	}
}

crossroad_ptr road_factory::get_crossroad(std::string road_id)
{
	return crossroads[road_id];
}

void road_factory::put_crossroad(crossroad_ptr crossroad, const std::string road_id)
{
	crossroads[road_id] = crossroad;
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

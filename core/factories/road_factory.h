/*
	road_factory.h

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

#ifndef ROAD_FACTORY_H_
#define ROAD_FACTORY_H_
#include "define/cadef.h"
#include "core/entities/road.h"
#include "core/connectors/crossroad.h"
#include "core/stat/stat_data_handler.h"

typedef boost::container::map<std::string, road_ptr> road_map;
typedef boost::container::map<std::string, crossroad_ptr> crossroad_map;

class road_factory
{
	road_map roads;
	crossroad_map crossroads;
	long id_counter;
	stat_data_handler stat_data;
public:
	road_factory();
	road_ptr create_road(int16 linesnum, int16 length);
	road_ptr create_road(int16 linesnum, int16 length, short velocity_limit);
	road_ptr create_road(int16 linesnum, int16 length, short velocity_limit, std::string id);
	void delete_road(std::string id);
	const road_ptr get_road(std::string id);
	const road_stat_data_ptr get_road_statistics(std::string id);
	const stat_data_handler& get_stat_data_handler(){return stat_data;};
	crossroad_ptr get_crossroad(std::string road_id);
	void put_crossroad(crossroad_ptr crossroad, const std::string road_id);
	size_t count();
	void iterate();
	virtual ~road_factory();
};

typedef boost::shared_ptr<road_factory> road_factory_ptr;

#endif /* ROAD_FACTORY_H_ */

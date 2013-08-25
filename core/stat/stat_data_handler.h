/*
	stat_data_handler.h

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

#ifndef STAT_DATA_HANDLER_H_
#define STAT_DATA_HANDLER_H_
#include "define/cadef.h"
#include "core/entities/road.h"
#include "core/stat/road_stat_data.h"

typedef boost::container::map<std::string, road_stat_data_ptr> road_stat_data_map;

class stat_data_handler
{
	road_stat_data_map data;
public:
	stat_data_handler();
	road_stat_data_ptr register_data(std::string road_id, int16 lanes, int16 len);
	road_stat_data_ptr get_road_data(std::string road_id);
	road_stat_data_map get_data_map() const{return data;};
	void delete_data(std::string road_id);
	virtual ~stat_data_handler();
};

#endif /* STAT_DATA_HANDLER_H_ */

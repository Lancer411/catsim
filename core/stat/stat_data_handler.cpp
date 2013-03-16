/*
	stat_data_handler.cpp

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

#include "stat_data_handler.h"

stat_data_handler::stat_data_handler()
{

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

}

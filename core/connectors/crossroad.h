/*
	crossroad.h - represents crossroad, intersection between roads

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

#ifndef CROSSROAD_H_
#define CROSSROAD_H_
#include "core/connectors/connector.h"
#include "core/tools/conversion.h"

class crossroad : public connector
{
	const static int NO_ROAD = -1;
	road_ptr roads_direct[ROAD_COUNT];
	road_ptr roads_opposite[ROAD_COUNT];
	short road_mtx[ROAD_COUNT][ROAD_COUNT];
public:
	crossroad();
	virtual ~crossroad();
	bool add_first_road(road_ptr road);
	bool connect(road_ptr road, std::string road_id, relative_direction direction);
	bool transfer(std::string from_road_id, road_ptr to_road, vehicle_ptr veh, short passed_distance);
	road_ptr get_next_road(std::string road_id, relative_direction direction);
private:
	int get_road_position(std::string road_id);
	road_status get_status(int pos_x, int pos_y);
	void set_status(int pos_x, int pos_y, road_status status);
	void set_road_status(int position, road_status status);
	void set_direction_status(int pos_x, int pos_y, road_status status);
};

typedef boost::shared_ptr<crossroad> crossroad_ptr;
typedef boost::weak_ptr<crossroad> crossroad_ptr_weak;

#endif /* CROSSROAD_H_ */

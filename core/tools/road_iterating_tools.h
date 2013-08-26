/*
	road_iterating_tools.h

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

#ifndef ROAD_ITERATING_TOOLS_H_
#define ROAD_ITERATING_TOOLS_H_
#include "define/cadef.h"
#include "core/base/cell.h"
#include "core/entities/vehicle.h"

class road_iterating_tools
{
public:

// поиск автомобиля впереди в интервале от start до end.y на полосе start.x
// найденная машина front_vehicle находится по координате end
	static bool find_front_vehicle(cell** &cells, CA_COORD start,
							CA_COORD &end, vehicle_ptr& front_vehicle)
	{
		for (int16 k = start.y; k <= end.y; k++)
			if(cells[start.x][k].is_occupied())
				{
	//				end.y = k-start.y;	//*--* (Дистанция=3) *-*(Дистанция=2) ** (Дистанция=1)
					end.x = start.x;
					end.y = k;
					object_ptr obj = cells[start.x][k].get_object();
					if(obj->is_dynamic())
						front_vehicle = boost::shared_polymorphic_downcast<vehicle>(obj);
					else
						obj->react();
					return true;
				}
		return false;
	};
// есть ли машина впереди в интервале от start.y до end.y (start.y < end.y)
	static bool vehicle_exists(cell** &cells, CA_COORD start, CA_COORD end)
	{
		for (int16 k = start.y; k <= end.y; k++)
			if(cells[start.x][k].is_occupied())
				return true;
		return false;
	};
// проверка на необходимость смены полосы
	static bool lane_changing_required(short vehicle_velocity,
								short front_vehicle_velocity,
								int16 distance_to_front_vehicle)
	{
		if (distance_to_front_vehicle <= vehicle_velocity
			&& front_vehicle_velocity <= vehicle_velocity)
			return true;
		return false;
	};

};

#endif /* ROAD_ITERATING_TOOLS_H_ */

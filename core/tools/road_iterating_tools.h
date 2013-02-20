/*
 * road_iterating_tools.h
 *
 *  Created on: Nov 13, 2012
 *      Author: ngh
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
	static bool find_front_vehicle(cell** &cells, COORD start,
							COORD &end, vehicle_ptr& front_vehicle)
	{
		for (int16 k = start.y; k <= end.y; k++)
			if(cells[start.x][k].is_occupied())
				{
	//				end.y = k-start.y;	//*--* (Дистанция=3) *-*(Дистанция=2) ** (Дистанция=1)
					end.x = start.x;
					end.y = k;
					front_vehicle = cells[start.x][k].get_vehicle();
					return true;
				}
		return false;
	};
// есть ли машина впереди в интервале от start.y до end.y (start.y < end.y)
	static bool vehicle_exists(cell** &cells, COORD start, COORD end)
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

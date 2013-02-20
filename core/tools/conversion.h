/*
 * conversion.h
 *
 *  Created on: Nov 10, 2012
 *      Author: ngh
 */

#ifndef CONVERSION_H_
#define CONVERSION_H_
#include "define/cadef.h"

class conversion
{
public:
	static int16 convert_to_cell_velocity(int16 kmh_velocity)
	{
		return std::floor(kmh_velocity/3.6/DEFAULT_CELL_LENGTH);
	};

	static int16 convert_to_kmh_velocity(int16 cell_velocity)
	{
		return std::ceil(cell_velocity*3.6*DEFAULT_CELL_LENGTH);
	};

	static short get_car_length()
	{
		return std::ceil(5/DEFAULT_CELL_LENGTH);
	};

	static short get_light_truck_length()
	{
		return std::ceil(5.5/DEFAULT_CELL_LENGTH);
	};

	static short get_truck_length()
	{
		return std::ceil(6/DEFAULT_CELL_LENGTH);
	};

	static short get_bus_length()
	{
		return std::ceil(11/DEFAULT_CELL_LENGTH);
	};

// проверка координат на выход за границы i и j и их поправка
	static void check_coord (COORD &coord, int16 i, int16 j)
	{
		coord.x = (coord.x >= i) ? i-1:coord.x;
		coord.y = (coord.y >= j) ? j-1:coord.y;
		coord.x = (coord.x < 0) ? 0:coord.x;
		coord.y = (coord.y < 0) ? 0:coord.y;

	};
};

#endif /* CONVERSION_H_ */

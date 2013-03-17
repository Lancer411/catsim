/*
	cadef.h

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

#ifndef CADEF_H_
#define CADEF_H_

#include <cstddef>
#include <iostream>
#include <ctime>
#include <cstring>
//#include <map>
#include <boost/container/map.hpp>
#include <boost/cstdlib.hpp>
#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/lexical_cast.hpp>


const float DEFAULT_CELL_LENGTH = 5.5;					// Размер ячейки в метрах по умолчанию
const short DEFAULT_MAX_VEH_VELOCITY = 100;				// Максимальная скорость ТС п.у.
const short DEFAULT_VELOCITY_LIMIT = 60;				// Ограничение скорости п.у.
const float DEFAULT_PROB_SLOWDOWN = 0.01; 				// Вероятность случайного замедления
const float DEFAULT_PROB_LANE_CHANGE = 0.01; 			// Вероятность смены полосы
const float DEFAULT_PROB_SLOW_TO_START = 0.1; 			// Вероятность медленного старта
const float DEFAULT_PROB_FWD_ANTICIPATION = 0.9; 		// Вероятность срабатывания пространственного упреждения
const float DEFAULT_PROB_SPEEDING = 0.7;				// Вероятность превышения скорости
const short MIN_POSSIBLE_DISTANCE = 1; 					// Дистанция, которая нужна для начала старта
const short DEFAULT_BLINK_DURATION = 3;					// Время мигания зеленого сигнала светофора
const short DEFAULT_GET_READY_DURATION = 2;				// Продолжительность сигнала готовности светофора
const long DEFAULT_STAT_ACCUMULATION_TIME = 60;			// Время накопления статистическаз данных п.у. (время итерации подсчета) = 1 мин.
const static short ROAD_COUNT = 4;

const float DEFAULT_FEEDER_DENSITY = 0.2;
const short DEFAULT_FEEDER_INIT_SPEED = 20;
const short DEFAULT_FEEDER_MAX_SPEED = 80;
const float DEFAULT_FEEDER_CAR_PROB = 0.7;
const float DEFAULT_FEEDER_BUS_PROB = 0.25;
const float DEFAULT_FEEDER_TRUCK_PROB = 0.05;

typedef uint16_t int16;

enum direction
{
	NORTH = 0,
	EAST = 1,
	SOUTH = 2,
	WEST = 3
};

enum relative_direction
{
	DIRECTION_LEFT = 0,
	DIRECTION_STRAIGHT = 1,
	DIRECTION_RIGHT = 2
};

enum road_status
{
	ROAD_ABLE = 1,
	ROAD_UNABLE = 0,
	ROAD_NONE = -1
};

enum vehicle_type
{
	Car = 1,
	LightTruck = 2,
	Truck = 3,
	Bus = 4,
};

typedef struct
{
	int x;
	int y;
} COORD;

enum light_signal_state
{
	Green = 0,
	GreenBlink = 1,
	Yellow = 2,
	Red = 3,
	GetReady = 4,
	Broken = 5
};

#endif /* CADEF_H_ */

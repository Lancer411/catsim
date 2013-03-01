/*
 * cadef.h
 *
 *  Created on: 09.10.2012
 *      Author: NGH
 */

#ifndef CADEF_H_
#define CADEF_H_

#include <cstddef>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include <vector>
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

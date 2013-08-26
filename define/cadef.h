/*
 * cafef1.h
 *
 *  Created on: 25.08.2013
 *      Author: ekaterina
 */

#ifndef CADEF_H_
#define CADEF_H_
#include <cstring>
#include <boost/pending/cstddef.hpp>
#include <boost/container/map.hpp>
#include <boost/cstdlib.hpp>
#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include "core/data_structures/data.h"
class cadef {
public:
	cadef();
	virtual ~cadef();
	static float cell_lenght;					// Размер ячейки в метрах по умолчанию
	static short max_veh_velocity;			// Максимальная скорость ТС п.у.
	static short velocity_limit;				// Ограничение скорости п.у.
	static float prob_showdown; 				// Вероятность случайного замедления
	static float prob_lane_change; 			// Вероятность смены полосы
	static float prob_slow_to_start; 			// Вероятность медленного старта
	static float prob_fwd_anticipation; 		// Вероятность срабатывания пространственного упреждения
	static float prob_speeding;				// Вероятность превышения скорости
	static short min_possible_distance; 		// Дистанция, которая нужна для начала старта
	static short blink_duration;				// Время мигания зеленого сигнала светофора
	static short get_ready_duration;			// Продолжительность сигнала готовности светофора
	static long stat_accumulation_time;		// Время накопления статистических данных п.у. (время итерации подсчета) = 1 мин.
	const static short road_count = 4;
	static int init(bool config_file);

};

typedef uint16_t int16;
#endif /* CADEF_H_ */

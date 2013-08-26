/*
 * cafef1.cpp
 *
 *  Created on: 25.08.2013
 *      Author: ekaterina
 */

#include "cadef.h"

float cadef::cell_lenght;
short cadef::max_veh_velocity;
short cadef::velocity_limit;
float cadef::prob_showdown;
float cadef::prob_lane_change;
float cadef::prob_slow_to_start;
float cadef::prob_fwd_anticipation;
float cadef::prob_speeding;
short cadef::min_possible_distance;
short cadef::blink_duration;
short cadef::get_ready_duration;
long cadef::stat_accumulation_time;


cadef::cadef() {
	// TODO Auto-generated constructor stub

}

cadef::~cadef() {
	// TODO Auto-generated destructor stub
}
int cadef::init(bool config_file)
{

	if (config_file)
	{
		//Проверка правильности значений установленных параметров
		if (prob_showdown<0||prob_lane_change<0||prob_slow_to_start<0||prob_fwd_anticipation<0||prob_speeding<0||prob_showdown>1||prob_lane_change>1||prob_slow_to_start>1||prob_fwd_anticipation>1||prob_speeding>1)
			{
			std::cout<<"probability value in config file should lie within the range of 0 to 1"<<std::endl;
			return 0;
			}
		if(cell_lenght<0||max_veh_velocity<0||velocity_limit<0||min_possible_distance<0||blink_duration<0||get_ready_duration<0||stat_accumulation_time<0||road_count<0)
			{
			std::cout<<"All parameters in config file must be positive"<<std::endl;
			return 0;
			}
	}
	else
	{
		cell_lenght = 5.5;					// Размер ячейки в метрах по умолчанию
		max_veh_velocity = 100;				// Максимальная скорость ТС п.у.
		velocity_limit = 60;					// Ограничение скорости п.у.
		prob_showdown = 0.01; 				// Вероятность случайного замедления
		prob_lane_change = 0.01; 			// Вероятность смены полосы
		prob_slow_to_start = 0.1; 			// Вероятность медленного старта
		prob_fwd_anticipation = 0.9; 		// Вероятность срабатывания пространственного упреждения
		prob_speeding = 0.7;					// Вероятность превышения скорости
		min_possible_distance = 1; 			// Дистанция, которая нужна для начала старта
		blink_duration = 3;					// Время мигания зеленого сигнала светофора
		get_ready_duration = 2;				// Продолжительность сигнала готовности светофора
		stat_accumulation_time = 60;			// Время накопления статистических данных п.у. (время итерации подсчета) = 1 мин.
	}
	return 1;
}

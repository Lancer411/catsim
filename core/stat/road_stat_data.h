/*
 * road_stat_data.h
 *
 *  Created on: Nov 12, 2012
 *      Author: ngh
 */

#ifndef ROAD_STAT_DATA_H_
#define ROAD_STAT_DATA_H_
#include "define/cadef.h"
#include <boost/shared_ptr.hpp>

class road_stat_data
{
	int16 road_length;					// длина дороги
	int16 road_lanes_count;				// число полос
	int16 passed_vehicles_number;		// число машин, прошедших дорогу
	int16 current_vehicles_number;		// текущее число машин
	int16 current_vehicles_length;		// длина машин на дороге
	float current_road_density;			// текущая плотность на дороге
	float avg_road_density;				// средняя плотность
	float avg_road_speed;				// средняя скорость за итерацию
	float avg_road_speed_total;			// средняя скорость за время итерации подсчета
	float avg_road_passage_time;		// среднее время проезда
	float road_flow;					// поток (ср плотность*ср скорость)
	double density_accumulator;			// накопитель для подсчета avg_road_density
	double avg_speed_accumulator;		// накопитель для подсчета avg_road_speed
	double total_speed_accumulator;		// накопитель для подсчета avg_road_speed_total
	long passage_time_accumulator;	// накопитель для подсчета avg_road_passage_time

	long stat_accumulation_time;		// время итерации подсчета
	long stat_timer;					// таймер итераций подсчета
public:
	road_stat_data(int16 linesnum, int16 length);
	virtual ~road_stat_data();

	// вызывать когда ТС проезжает дорогу, передается время проезда дороги
	void inc_passed_vehicles_num(int16 time);
	// вызывать когда ТС заезжает на дорогу
	void inc_current_vehicles_num(short veh_length);
	// вызывать когда ТС проезжает дорогу
	void dec_current_vehicles_num(short veh_length);
	// вызывать для каждого ТС на дороге
	void update_avg_speed(short speed){avg_speed_accumulator += speed;};

	int16 get_passed_vehicles_number() const{return passed_vehicles_number;};
	int16 get_current_vehicles_number() const{return current_vehicles_number;};
	float get_current_road_density() const{return current_road_density;};
	float get_avg_road_density() const{return avg_road_density;};
	float get_avg_road_speed() const{return avg_road_speed;};
	float get_avg_road_speed_total() const{return avg_road_speed_total;};
	float get_avg_road_passage_time() const{return avg_road_passage_time;};
	float get_road_flow() const{return road_flow;};
	// подсчет параметров, вызывается раз в итерацию
	void update_parameters();

	void set_stat_accumulation_time(long time){stat_accumulation_time = time;};
	void reset();
private:
	void reset_timer();
};

typedef boost::shared_ptr<road_stat_data> road_stat_data_ptr;

#endif /* ROAD_STAT_DATA_H_ */

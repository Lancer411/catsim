/*
	road_stat_data.h

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

#ifndef ROAD_STAT_DATA_H_
#define ROAD_STAT_DATA_H_
#include "define/cadef.h"
#include "core/entities/road_marker.h"
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/accumulators/accumulators.hpp>

#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/median.hpp>
#include <boost/accumulators/statistics/covariance.hpp>
#include <boost/accumulators/statistics/density.hpp>
#include <boost/accumulators/statistics/kurtosis.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/moment.hpp>
#include <boost/accumulators/statistics/sum.hpp>
#include <boost/accumulators/statistics/variance.hpp>

#include <boost/container/vector.hpp>
#include <boost/container/map.hpp>

typedef boost::accumulators::tag::mean stat_mean;
typedef boost::accumulators::tag::median stat_median;
typedef boost::accumulators::tag::density stat_density;
typedef boost::accumulators::tag::kurtosis stat_kurtosis;
typedef boost::accumulators::tag::max stat_max;
typedef boost::accumulators::tag::min stat_min;
typedef boost::accumulators::tag::sum stat_sum;
typedef boost::accumulators::tag::variance stat_variance;

template <typename T>
struct accumulator
{
	typedef boost::accumulators::accumulator_set<T,
						boost::accumulators::stats<stat_mean, stat_median, stat_kurtosis, stat_max, stat_min, stat_sum, stat_variance> >
						type;
};


typedef boost::accumulators::accumulator_set<int,
						boost::accumulators::features<stat_density> >
						int_dens_acc;

typedef accumulator<int>::type int_acc;

typedef boost::container::map<int, int_acc> position_time_interval_map;

typedef boost::iterator_range<std::vector<std::pair<double, double> >::iterator > time_density_histogram;

struct stat_data_params
{
	float max;
	float min;
	float sum;
	float mean;
	float median;
	float variance;
	float deviation;
	float kurtosis;

	void reset()
	{
		max = min = sum = mean = median = variance = deviation = kurtosis = 0;
	};
};

class road_stat_data
{
	int16 road_length;					// длина дороги
	int16 road_lanes_count;				// число полос
	int16 passed_vehicles_number;		// число машин, прошедших дорогу
	int16 current_vehicles_number;		// текущее число машин
	int16 current_vehicles_length;		// длина машин на дороге
	int16 passed_vehicles_number_iter;  // число прошедших машин за итерацию

	stat_data_params density;
	stat_data_params speed;
	stat_data_params speed_total;
	stat_data_params passed_vehicles;
	stat_data_params passage_time;
	stat_data_params queue;

	int16 current_queue;				// длина очереди (в ячейках) перед перекрестком
	float current_road_density;			// текущая плотность на дороге

	accumulator<float>::type density_accumulator;		// накопитель для подсчета avg_road_density
	accumulator<float>::type avg_speed_accumulator;	// накопитель для подсчета avg_road_speed
	accumulator<float>::type total_speed_accumulator;	// накопитель для подсчета avg_road_speed_total
	accumulator<float>::type passed_veh_acc;			// накопитель для подсчета числа прошедших машин
	accumulator<float>::type queue_accumulator;		// накопитель для подсчета avg_queue
	accumulator<long>::type passage_time_accumulator;	// накопитель для подсчета avg_road_passage_time

	long stat_accumulation_time;		// время итерации подсчета
	long stat_timer;					// таймер итераций подсчета

	boost::container::vector<road_marker_ptr> markers_list;

	position_time_interval_map markers_time_intervals;
	static int_dens_acc dens_acc;
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
	void update_avg_speed(short speed);

	// вызывать когда проверяется очередь перед перекрестком
	void inc_queue_vehicles_num();
	// вызывать при проверке очереди перекрестка (обнуление очереди)
	void reset_queue_vehicles_num();

	int16 get_passed_vehicles_number() const{return passed_vehicles_number;};
	int16 get_current_vehicles_number() const{return current_vehicles_number;};
	int16 get_current_queue() const{return current_queue;};
	int16 get_max_queue() const{return queue.max;};
	float get_avg_queue()const{return queue.mean;};
	float get_current_road_density() const{return current_road_density;};
	float get_avg_road_density() const{return density.mean;};
	float get_avg_road_speed() const{return speed.mean;};
	float get_avg_road_speed_total() const{return speed_total.mean;};
	float get_avg_road_passage_time() const{return passage_time.mean;};
	float get_road_flow () const {return passed_vehicles.mean;};

	stat_data_params get_density() const {return density;};
	stat_data_params get_speed() const {return speed;};
	stat_data_params get_total_speed() const {return speed_total;};
	stat_data_params get_passage_time() const {return passage_time;};
	stat_data_params get_passed_vehicles() const {return passed_vehicles;};
	stat_data_params get_queue() const {return queue;};

	position_time_interval_map get_time_intervals() const {return markers_time_intervals;};
	// подсчет параметров, вызывается раз в итерацию
	void update_parameters();

	void set_stat_accumulation_time(long time){stat_accumulation_time = time;};
	void reset();


	void add_marker(const road_marker_ptr marker);

	time_density_histogram get_time_density_histogram();
private:
	void update_stat_data_params_float(stat_data_params &params, accumulator<float>::type acc)
	{
		params.max = boost::accumulators::max(acc);
		params.min = boost::accumulators::min(acc);
		params.sum = boost::accumulators::sum(acc);
		params.mean = boost::accumulators::mean(acc);
		params.median = boost::accumulators::median(acc);
		params.variance = boost::accumulators::variance(acc);
		params.deviation = std::sqrt(params.variance);
		params.kurtosis = boost::accumulators::kurtosis(acc);
	};

	void update_stat_data_params_long(stat_data_params &params, accumulator<long>::type acc)
	{
		params.max = boost::accumulators::max(acc);
		params.min = boost::accumulators::min(acc);
		params.sum = boost::accumulators::sum(acc);
		params.mean = boost::accumulators::mean(acc);
		params.median = boost::accumulators::median(acc);
		params.variance = boost::accumulators::variance(acc);
		params.deviation = std::sqrt(params.variance);
		params.kurtosis = boost::accumulators::kurtosis(acc);
	};

	void reset_timer();
};

typedef boost::shared_ptr<road_stat_data> road_stat_data_ptr;

#endif /* ROAD_STAT_DATA_H_ */

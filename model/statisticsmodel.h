/*
 * statisticsmodel.h
 *
 *  Created on: Aug 17, 2013
 *      Author: naghtarr
 */

#ifndef STATISTICSMODEL_H_
#define STATISTICSMODEL_H_
#include <boost/container/set.hpp>

enum DATA_PARAMS
{
	ROAD_DENSITY,
	SPEED,
	FLOW,
	VEHICLES,
	PASSAGE_TIME,
	ROAD_QUEUE
};

enum STAT_PARAMS
{
	MEAN,
	MEDIAN,
	COVARIANCE,
	DENSITY,
	KURTOSIS,
	MAX,
	MIN,
	MOMENT,
	SUM,
	VARIANCE
};

class statistics_model {
	long data_accumulation_time;
	boost::container::set<DATA_PARAMS> data_params;
	boost::container::set<STAT_PARAMS> stat_params;
public:
	statistics_model()
	{
		data_accumulation_time = 0;
	};

	virtual ~statistics_model(){};

	void set_data_accumulation_time(const long t) {this->data_accumulation_time = t;};
	long get_data_accumulation_time() const{return this->data_accumulation_time;}

	void add_data_param(DATA_PARAMS param)
	{
		data_params.insert(param);
	}

	void add_stat_param(STAT_PARAMS param)
	{
		stat_params.insert(param);
	}
};

typedef boost::shared_ptr<statistics_model> statistics_model_ptr;

#endif /* STATISTICSMODEL_H_ */

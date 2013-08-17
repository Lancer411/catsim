/*
 * road_network_data.h
 *
 *  Created on: Aug 17, 2013
 *      Author: naghtarr
 */

#ifndef ROAD_NETWORK_DATA_H_
#define ROAD_NETWORK_DATA_H_
#include "define/cadef.h"
#include "ptree_helper.h"
#include <boost/container/list.hpp>
#include <boost/property_tree/ptree.hpp>

const char * EMPTY_PROPERTY = "";

const char * RN_ROADS = "roads";
const char * RN_ROAD_ID = "road_id";
const char * RN_ROAD_LENGTH = "length";
const char * RN_ROAD_LANES = "lanes";
const char * RN_ROAD_NAME = "name";
const char * RN_ROAD_VELOCITY_LIMIT = "velocity_limit";

const char * RN_CROSSROADS = "crossroads";
const char * RN_CROSSROAD_ID = "crossroad_id";
const char * RN_CROSSROAD_ROADS_IN = "roads_in";
const char * RN_CROSSROAD_ROADS_OUT = "roads_out";
const char * RN_CROSSROAD_ROAD_NONE = "none";

const char * RN_FEEDERS = "vehicle_feeders";
const char * RN_FEEDER_ID = "feeder_id";
const char * RN_FEEDING_ROADS = "feeding_roads";
const char * RN_DEADEND_ROADS = "deadend_roads";
const char * RN_FEEDER_PARAMS = "params";
const char * RN_FEEDER_PARAM_ROAD_ID = "road_id";
const char * RN_FEEDER_PARAM_MODE = "mode";
const char * RN_FEEDER_PARAM_DENSITY = "density";
const char * RN_FEEDER_PARAM_INIT_SPEED = "init_speed";
const char * RN_FEEDER_PARAM_MAX_SPEED = "max_speed";
const char * RN_FEEDER_PARAM_CAR_PROB = "car_prob";
const char * RN_FEEDER_PARAM_BUS_PROB = "bus_prob";


struct road_raw
{
	std::string id;
	int length;
	int lanes;
	std::string name;
	int velocity_limit;
};

struct crossroad_raw
{
	std::string id;
	std::string roads_in[4];
	std::string roads_out[4];
};

struct vehicle_feeder_params
{
	std::string road_id;
	std::string mode;
	float density;
	int init_speed;
	int max_speed;
	float car_prob;
	float bus_prob;
};

struct vehicle_feeder_raw
{
	std::string id;
	boost::container::list<std::string> feeding_roads;
	boost::container::list<std::string> deadend_roads;
	boost::container::list<vehicle_feeder_params> params;
};

typedef boost::container::list<road_raw> raw_roads_list;
typedef boost::container::list<crossroad_raw> raw_crossroads_list;
typedef boost::container::list<vehicle_feeder_raw> raw_feeder_list;

class road_network_data {
	raw_roads_list roads_raw;
	raw_crossroads_list crossroads_raw;
	raw_feeder_list feeders_raw;
public:
	road_network_data(){};
	~road_network_data()
	{
		roads_raw.clear();
	};

	raw_roads_list get_roads() const
	{
		return roads_raw;
	};

	raw_crossroads_list get_crossroads() const
	{
		return crossroads_raw;
	};

	void parse_road(const boost::property_tree::ptree ptree)
	{
		road_raw road;
		road.id = ptree_get<std::string>(ptree, RN_ROAD_ID);
		road.length = ptree_get<int>(ptree, RN_ROAD_LENGTH);
		road.lanes = ptree_get<int>(ptree, RN_ROAD_LANES);
		road.name = ptree_get<std::string>(ptree, RN_ROAD_NAME);
		road.velocity_limit = ptree_get<int>(ptree, RN_ROAD_VELOCITY_LIMIT);
		roads_raw.push_front(road);
	};

	void parse_crossroad(const boost::property_tree::ptree ptree)
	{
		crossroad_raw crossroad;
		crossroad.id = ptree_get<std::string>(ptree, RN_CROSSROAD_ID);
		boost::property_tree::ptree roads_in = ptree.get_child(RN_CROSSROAD_ROADS_IN);
		boost::property_tree::ptree roads_out = ptree.get_child(RN_CROSSROAD_ROADS_OUT);
		ptree_fill_array<std::string>(roads_in, EMPTY_PROPERTY, crossroad.roads_in, 4);
		ptree_fill_array<std::string>(roads_out, EMPTY_PROPERTY, crossroad.roads_out, 4);
	}

	void parse_feeder(boost::property_tree::ptree ptree)
	{
		vehicle_feeder_raw feeder;
		feeder.id = ptree_get<std::string>(ptree, RN_FEEDER_ID);
		ptree_fill_list<std::string>(ptree.get_child(RN_FEEDING_ROADS), EMPTY_PROPERTY, feeder.feeding_roads);
		ptree_fill_list<std::string>(ptree.get_child(RN_DEADEND_ROADS), EMPTY_PROPERTY, feeder.deadend_roads);
		BOOST_FOREACH(ptree_value &val, ptree.get_child(RN_FEEDER_PARAMS))
		{
			feeder.params.push_front(parse_feeder_params(val.second));
		}
		feeders_raw.push_front(feeder);
	}

	vehicle_feeder_params parse_feeder_params(const boost::property_tree::ptree ptree)
	{
		vehicle_feeder_params params;
		params.road_id = ptree_get<std::string>(ptree, RN_FEEDER_PARAM_ROAD_ID);
		params.mode = ptree_get<std::string>(ptree, RN_FEEDER_PARAM_MODE);
		params.density = ptree_get<float>(ptree, RN_FEEDER_PARAM_DENSITY);
		params.init_speed = ptree_get<int>(ptree, RN_FEEDER_PARAM_INIT_SPEED);
		params.max_speed = ptree_get<int>(ptree, RN_FEEDER_PARAM_MAX_SPEED);
		params.car_prob = ptree_get<float>(ptree, RN_FEEDER_PARAM_CAR_PROB);
		params.bus_prob = ptree_get<float>(ptree, RN_FEEDER_PARAM_BUS_PROB);
		return params;
	}

};

#endif /* ROAD_NETWORK_DATA_H_ */

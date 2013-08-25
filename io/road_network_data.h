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
const char * RN_CONNECTIONS = "road_connections";
const char * RN_CONNECTION_INPUT_ROAD = "input_road_id";
const char * RN_CONNECTION_OUPUT_ROAD = "output_road_id";
const char * RN_CONNECTION_DIRECTION = "direction";
const char * RN_CONNECTION_DIRECTION_STRAIGHT = "straight";
const char * RN_CONNECTION_DIRECTION_LEFT = "left";
const char * RN_CONNECTION_DIRECTION_RIGHT = "right";

const char * RN_PARAM_NONE = "none";

const char * RN_FEEDERS = "vehicle_feeders";
const char * RN_FEEDER_ID = "feeder_id";
const char * RN_FEEDER_ROADS = "feeder_roads";
const char * RN_PAIR_FEEDING_ROAD = "feeding_road";
const char * RN_PAIR_DEADEND_ROAD = "deadend_road";
const char * RN_FEEDER_MODE = "feeder_mode";
const char * RN_FEEDER_MODE_SAVING = "saving";
const char * RN_FEEDER_MODE_DELETING = "deleting";
const char * RN_FEEDER_PARAMS = "params";
const char * RN_FEEDER_PARAM_ROAD_ID = "road_id";
const char * RN_FEEDER_PARAM_MODE = "mode";
const char * RN_FEEDER_PARAM_MODE_INITIAL = "initial";
const char * RN_FEEDER_PARAM_MODE_CONTINUOUS = "continuous";
const char * RN_FEEDER_PARAM_MODE_DISTRIBUTIVE = "distributive";
const char * RN_FEEDER_PARAM_DISTRIBUTION = "distribution";
const char * RN_FEEDER_PARAM_DISTRIBUTION_UNIFORM = "uniform";
const char * RN_FEEDER_PARAM_DISTRIBUTION_POISSON = "poisson";
const char * RN_FEEDER_PARAM_DISTRIBUTION_TRIANGLE = "triangle";
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

struct roads_connection
{
	std::string input_road_id;
	std::string output_road_id;
	std::string direction;
};

struct crossroad_raw
{
	std::string id;
	boost::container::list<roads_connection> road_connections;
};

struct vehicle_feeder_params
{
	std::string road_id;
	std::string mode;
	std::string distribution;
	float density;
	int init_speed;
	int max_speed;
	float car_prob;
	float bus_prob;
};

struct roads_pair
{
	std::string feeding_road;
	std::string deadend_road;
};

struct vehicle_feeder_raw
{
	std::string id;
	boost::container::list<roads_pair> roads;
	std::string feeder_mode;
	boost::container::list<vehicle_feeder_params> params;
};


typedef boost::container::list<road_raw> raw_roads_list;
typedef boost::container::list<crossroad_raw> raw_crossroads_list;
typedef boost::container::list<vehicle_feeder_raw> raw_feeders_list;

class road_network_data {
	raw_roads_list roads_raw;
	raw_crossroads_list crossroads_raw;
	raw_feeders_list feeders_raw;
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

	raw_feeders_list get_feeders() const
	{
		return feeders_raw;
	};

	void parse_road(const boost::property_tree::ptree ptree)
	{
		road_raw road;
		road.id = ptree_get<std::string>(ptree, RN_ROAD_ID);
		road.length = ptree_get<int>(ptree, RN_ROAD_LENGTH);
		road.lanes = ptree_get<int>(ptree, RN_ROAD_LANES);
		road.name = ptree_get<std::string>(ptree, RN_ROAD_NAME);
		road.velocity_limit = ptree_get<int>(ptree, RN_ROAD_VELOCITY_LIMIT);
		raw_roads_list::iterator it = roads_raw.end();
		roads_raw.insert(it, road);
	};

	void parse_crossroad(boost::property_tree::ptree ptree)
	{
		crossroad_raw crossroad;
		crossroad.id = ptree_get<std::string>(ptree, RN_CROSSROAD_ID);
		BOOST_FOREACH(ptree_value &val, ptree.get_child(RN_CONNECTIONS))
		{
			boost::container::list<roads_connection>::iterator iter = crossroad.road_connections.end();
			crossroad.road_connections.insert(iter, parse_road_connection(val.second));
		}
		raw_crossroads_list::iterator it = crossroads_raw.end();
		crossroads_raw.insert(it, crossroad);
	}

	roads_connection parse_road_connection(const boost::property_tree::ptree ptree)
	{
		roads_connection conn;
		conn.input_road_id = ptree_get<std::string>(ptree, RN_CONNECTION_INPUT_ROAD);
		conn.output_road_id = ptree_get<std::string>(ptree, RN_CONNECTION_OUPUT_ROAD);
		conn.direction = ptree_get<std::string>(ptree, RN_CONNECTION_DIRECTION);
		return conn;
	}

	void parse_feeder(boost::property_tree::ptree ptree)
	{
		vehicle_feeder_raw feeder;
		feeder.id = ptree_get<std::string>(ptree, RN_FEEDER_ID);
		BOOST_FOREACH(ptree_value &val, ptree.get_child(RN_FEEDER_ROADS))
		{
			boost::container::list<roads_pair>::iterator iter = feeder.roads.end();
			feeder.roads.insert(iter, parse_road_pair(val.second));
		}

		feeder.feeder_mode = ptree_get<std::string>(ptree, RN_FEEDER_MODE);

		BOOST_FOREACH(ptree_value &val, ptree.get_child(RN_FEEDER_PARAMS))
		{
			boost::container::list<vehicle_feeder_params>::iterator iter = feeder.params.end();
			feeder.params.insert(iter, parse_feeder_params(val.second));
		}
		raw_feeders_list::iterator it = feeders_raw.end();
		feeders_raw.insert(it, feeder);
	}

	roads_pair parse_road_pair(const boost::property_tree::ptree ptree)
	{
		roads_pair pair;
		pair.feeding_road = ptree_get<std::string>(ptree, RN_PAIR_FEEDING_ROAD);
		pair.deadend_road = ptree_get<std::string>(ptree, RN_PAIR_DEADEND_ROAD);
		return pair;
	}

	vehicle_feeder_params parse_feeder_params(const boost::property_tree::ptree ptree)
	{
		vehicle_feeder_params params;
		params.road_id = ptree_get<std::string>(ptree, RN_FEEDER_PARAM_ROAD_ID);
		params.mode = ptree_get<std::string>(ptree, RN_FEEDER_PARAM_MODE);
		params.distribution = ptree_get<std::string>(ptree, RN_FEEDER_PARAM_DISTRIBUTION);
		params.density = ptree_get<float>(ptree, RN_FEEDER_PARAM_DENSITY);
		params.init_speed = ptree_get<int>(ptree, RN_FEEDER_PARAM_INIT_SPEED);
		params.max_speed = ptree_get<int>(ptree, RN_FEEDER_PARAM_MAX_SPEED);
		params.car_prob = ptree_get<float>(ptree, RN_FEEDER_PARAM_CAR_PROB);
		params.bus_prob = ptree_get<float>(ptree, RN_FEEDER_PARAM_BUS_PROB);
		return params;
	}

};

typedef boost::shared_ptr<road_network_data> road_network_data_ptr;

#endif /* ROAD_NETWORK_DATA_H_ */

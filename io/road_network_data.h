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

typedef boost::container::list<road_raw> raw_roads_list;
typedef boost::container::list<crossroad_raw> raw_crossroads_list;

class road_network_data {
	raw_roads_list roads_raw;
	raw_crossroads_list crossroads_raw;
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
		road.id = ptree_get_string(ptree, RN_ROAD_ID);
		road.length = ptree_get_int(ptree, RN_ROAD_LENGTH);
		road.lanes = ptree_get_int(ptree, RN_ROAD_LANES);
		road.name = ptree_get_string(ptree, RN_ROAD_NAME);
		road.velocity_limit = ptree_get_int(ptree, RN_ROAD_VELOCITY_LIMIT);
		roads_raw.push_front(road);
	};

	void parse_crossroad(const boost::property_tree::ptree ptree)
	{
		crossroad_raw crossroad;
		crossroad.id = ptree_get_string(ptree, RN_CROSSROAD_ID);
		boost::property_tree::ptree roads_in = ptree.get_child(RN_CROSSROAD_ROADS_IN);
		boost::property_tree::ptree roads_out = ptree.get_child(RN_CROSSROAD_ROADS_OUT);
		ptree_fill_string_array(roads_in, EMPTY_PROPERTY, crossroad.roads_in, 4);
		ptree_fill_string_array(roads_out, EMPTY_PROPERTY, crossroad.roads_out, 4);
	}

};

#endif /* ROAD_NETWORK_DATA_H_ */

/*
 * roadnetworkjsonreader.h
 *
 *  Created on: Aug 17, 2013
 *      Author: naghtarr
 */

#ifndef ROADNETWORKJSONREADER_H_
#define ROADNETWORKJSONREADER_H_
#include "define/cadef.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "road_network_data.h"

typedef boost::property_tree::ptree ptree;
class road_network_json_reader
{
public:
	road_network_json_reader(){};
	virtual ~road_network_json_reader(){};

	static road_network_data_ptr read(const std::string filename)
	{
		ptree network_tree;
		road_network_data_ptr data(new road_network_data());
		try
		{
			boost::property_tree::read_json(filename, network_tree);
			typedef ptree::value_type tree_value;

			BOOST_FOREACH(tree_value &v, network_tree.get_child(RN_ROADS))
			{
				ptree road = v.second;
				data->parse_road(road);
			}

			BOOST_FOREACH(tree_value &v, network_tree.get_child(RN_CROSSROADS))
			{
				ptree crossroad = v.second;
				data->parse_crossroad(crossroad);
			}

			BOOST_FOREACH(tree_value &v, network_tree.get_child(RN_FEEDERS))
			{
				ptree feeder = v.second;
				data->parse_feeder(feeder);
			}
		} catch (std::exception const& e) {
			std::cerr << e.what() << std::endl;
		}

		return data;
	};
};

#endif /* ROADNETWORKJSONREADER_H_ */

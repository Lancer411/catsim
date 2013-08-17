/*
 * roadnetworkjsonreader.h
 *
 *  Created on: Aug 17, 2013
 *      Author: naghtarr
 */

#ifndef ROADNETWORKJSONREADER_H_
#define ROADNETWORKJSONREADER_H_
#include "define/cadef.h"
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class road_network_json_reader
{
	boost::property_tree::ptree network_tree;
public:
	road_network_json_reader(){};
	virtual ~road_network_json_reader(){};

	void read(const std::string filename)
	{
		try
		{
			boost::property_tree::read_json(filename, network_tree);
			typedef boost::property_tree::ptree::value_type tree_value;

			boost::property_tree::write_json(std::cout, network_tree);

		} catch (std::exception const& e) {
			std::cerr << e.what() << std::endl;
		}
	};
};

#endif /* ROADNETWORKJSONREADER_H_ */

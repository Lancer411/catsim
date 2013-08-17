/*
 * ptree_helper.h
 *
 *  Created on: Aug 17, 2013
 *      Author: naghtarr
 */

#ifndef PTREE_HELPER_H_
#define PTREE_HELPER_H_
#include "define/cadef.h"
#include <boost/property_tree/ptree.hpp>

std::string ptree_get_string(const boost::property_tree::ptree ptree, const char * property)
{
	return ptree.get<std::string>(property);
}

int ptree_get_int(const boost::property_tree::ptree ptree, const char * property)
{
	return ptree.get<int>(property);
}

void ptree_fill_string_array(boost::property_tree::ptree ptree, const char * property,
						std::string array[], const int size)
{
	typedef boost::property_tree::ptree::value_type tree_value;

	int index = 0;
	BOOST_FOREACH(tree_value &val, ptree.get_child(property))
	{
		if(index >= size)
			break;

		array[index] = ptree_get_string(val.second, property);;
		index++;
	}
}


#endif /* PTREE_HELPER_H_ */

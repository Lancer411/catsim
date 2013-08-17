/*
 * ptree_helper.h
 *
 *  Created on: Aug 17, 2013
 *      Author: naghtarr
 */

#ifndef PTREE_HELPER_H_
#define PTREE_HELPER_H_
#include "define/cadef.h"
#include <boost/container/list.hpp>
#include <boost/property_tree/ptree.hpp>

typedef boost::property_tree::ptree::value_type ptree_value;

template <class T>
T ptree_get(const boost::property_tree::ptree ptree, const char * property)
{
	return ptree.get<T>(property);
}

template <class T>
void ptree_fill_array(boost::property_tree::ptree ptree, const char * property,
						T array[], const int size)
{
	int index = 0;
	BOOST_FOREACH(ptree_value &val, ptree.get_child(property))
	{
		if(index >= size)
			break;

		array[index] = ptree_get<T>(val.second, property);
		index++;
	}
}

template <class T>
void ptree_fill_list(boost::property_tree::ptree ptree, const char * property,
		boost::container::list<T> list)
{
	BOOST_FOREACH(ptree_value &val, ptree.get_child(property))
	{
		T obj = ptree_get<T>(val.second, property);
		list.push_front(obj);
	}
}


#endif /* PTREE_HELPER_H_ */

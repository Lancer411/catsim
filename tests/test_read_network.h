/*
 * test_read_network.h
 *
 *  Created on: Aug 17, 2013
 *      Author: naghtarr
 */

#ifndef TEST_READ_NETWORK_H_
#define TEST_READ_NETWORK_H_
#include "test.h"
#include "io/road_network_json_reader.h"

class test_read_network : public test
{
public:
	test_read_network(){};
	virtual ~test_read_network(){};
	void runtest()
	{
		road_network_json_reader::read("test_models/one_road_test.json");
	};
};



#endif /* TEST_READ_NETWORK_H_ */

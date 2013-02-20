/*
 * test.h
 *
 *  Created on: Oct 31, 2012
 *      Author: ngh
 */

#ifndef TEST_H_
#define TEST_H_
#include <iostream>
#include <cstring>
class test
{
public:
	test();
	virtual ~test();
	virtual void runtest() = 0;
	void assert_expression (bool expr)
	{
		if(expr)
			std::cout<<"\tsuccess"<<std::endl;
		else
			std::cout<<"\tfailed"<<std::endl;
	};
	void assert_equals(int a, int b);
	void assert_equals(std::string a, std::string b);
};

#endif /* TEST_H_ */

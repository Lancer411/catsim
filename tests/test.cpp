/*
 * test.cpp
 *
 *  Created on: Oct 31, 2012
 *      Author: ngh
 */

#include "test.h"

test::test()
{
	// TODO Auto-generated constructor stub

}

test::~test()
{
	// TODO Auto-generated destructor stub
}

void test::assert_equals(int a, int b)
{
	if(a==b)
		std::cout<<"\tsuccess"<<std::endl;
	else
		std::cout<<"\tfailed: "<<a<<"!="<<b<<std::endl;
}

void test::assert_equals(std::string a, std::string b)
{
	if(a==b)
		std::cout<<"\tsuccess"<<std::endl;
	else
		std::cout<<"\tfailed: "<<a<<"!="<<b<<std::endl;
}

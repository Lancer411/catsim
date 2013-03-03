/*
	test.h

	Catsim source code
	Copyright (C) 2012-2013  naghtarr

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

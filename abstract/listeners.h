/*
 	listeners.h - set of interfaces for different listeners (handlers)

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

#ifndef LISTENERS_H_
#define LISTENERS_H_
#include <cstring>
#include <boost/shared_ptr.hpp>

class ilistener_void
{
public:
	virtual void handle() = 0;
};
typedef boost::shared_ptr<ilistener_void> listener_void;

class ilistener_int
{
public:
	virtual void handle(int value) = 0;
};
typedef boost::shared_ptr<ilistener_int> listener_int;

class ilistener_float
{
public:
	virtual void handle(float value) = 0;
};
typedef boost::shared_ptr<ilistener_float> listener_float;

class ilistener_long
{
public:
	virtual void handle(long value) = 0;
};
typedef boost::shared_ptr<ilistener_long> listener_long;

class ilistener_string
{
public:
	virtual void handle(std::string value) = 0;
};
typedef boost::shared_ptr<ilistener_string> listener_string;

#endif /* LISTENERS_H_ */

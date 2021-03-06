/*
 	observer.h - observer pattern interface

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

#ifndef OBSERVER_H_
#define OBSERVER_H_
#include "define/cadef.h"

class observer
{
public:
	virtual void handle_event() = 0;
};

typedef boost::shared_ptr<observer> observer_ptr;

class iobservable
{
public:
	virtual void add_observer(const observer_ptr observer) = 0;
	virtual void remove_observer(const observer_ptr observer) = 0;
	virtual void notify_observers() = 0;
};


#endif /* OBSERVER_H_ */

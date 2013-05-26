/*
 	iobject.h - <description>

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

#ifndef IOBJECT_H_
#define IOBJECT_H_
#include "define/cadef.h"

class iobject
{
public:
	virtual bool is_dynamic() = 0;
	virtual void react() = 0;
protected:
	bool is_static(){return !this->is_dynamic();};
};

typedef boost::shared_ptr<iobject> object_ptr;

#endif /* IOBJECT_H_ */

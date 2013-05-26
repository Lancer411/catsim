/*
	cell.h - class represents a cell of cellular automata

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

#ifndef CELL_H_
#define CELL_H_
#include "define/cadef.h"
#include "core/base/iobject.h"

class cell
{
	object_ptr object;
	bool occupied;
public:
	cell();
	cell(const cell &cell);
	~cell();

	bool is_occupied() const{return this->occupied;};
	object_ptr get_object() const {return this->object;};

	void clear();
	void set_object(object_ptr object);

	friend std::ostream& operator <<( std::ostream &stream, const cell &cell)
	{
		if(cell.is_occupied())
			if(cell.object->is_dynamic())
				stream<<"*";
			else
				stream<<'|';
		else
			stream<<'-';
		return stream;
	}
};

#endif /* CELL_H_ */

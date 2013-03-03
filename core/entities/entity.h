/*
	entity.h - basic class for entities

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

#ifndef ENTITY_H_
#define ENTITY_H_
#include "define/cadef.h"

class entity
{
	std::string id;
public:
	std::string get_id() const {return id;};
	void set_id(std::string id){this->id = id;};
};

#endif /* ENTITY_H_ */

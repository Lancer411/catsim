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

#include "cell.h"

cell::cell()
{
	this->occupied = false;
}

cell::cell(const cell &cell)
{
	this->occupied = cell.occupied;
	this->vehicle = cell.vehicle;
}

void cell::set_vehicle(vehicle_ptr vehicle)
{
	this->vehicle = vehicle;
	occupied = true;
}

void cell::clear()
{
	occupied = false;
	vehicle.reset();
}

cell::~cell()
{
	vehicle.reset();
}

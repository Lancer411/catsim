/*
 * cell.cpp
 *
 *  Created on: Oct 30, 2012
 *      Author: ngh
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

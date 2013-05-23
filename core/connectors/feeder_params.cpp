/*
 feeder_params.cpp -  parameter for road's vehicle generation

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

#include "feeder_params.h"

feeder_params::feeder_params()
{
	this->init_params(DEFAULT_FEEDER_DENSITY,
						DEFAULT_FEEDER_MODE,
						DEFAULT_FEEDER_INIT_SPEED,
						DEFAULT_FEEDER_MAX_SPEED,
						DEFAULT_FEEDER_CAR_PROB,
						DEFAULT_FEEDER_BUS_PROB,
						DEFAULT_FEEDER_TRUCK_PROB);
}

feeder_params::feeder_params(float density)
{
	this->init_params(density,
						DEFAULT_FEEDER_MODE,
						DEFAULT_FEEDER_INIT_SPEED,
						DEFAULT_FEEDER_MAX_SPEED,
						DEFAULT_FEEDER_CAR_PROB,
						DEFAULT_FEEDER_BUS_PROB,
						DEFAULT_FEEDER_TRUCK_PROB);
}

feeder_params::feeder_params(float density, int16 init_speed, int16 max_speed)
{
	this->init_params(density,
						DEFAULT_FEEDER_MODE,
						init_speed,
						max_speed,
						DEFAULT_FEEDER_CAR_PROB,
						DEFAULT_FEEDER_BUS_PROB,
						DEFAULT_FEEDER_TRUCK_PROB);
}

feeder_params::feeder_params(float density, int16 init_speed, int16 max_speed,
							float car_prob,
							float bus_prob)
{
	this->init_params(density,
						DEFAULT_FEEDER_MODE,
						init_speed,
						max_speed,
						car_prob,
						bus_prob,
						100 - (car_prob + bus_prob));
}

void feeder_params::init_params(float density, feeder_mode mode,
								int16 init_speed,
								int16 max_speed, float car_prob,
								float bus_prob, float truck_prob)
{
	this->density = density;
	this->mode = mode;
	this->distrib = DEFAULT_FEEDER_DISTRIBUTION;
	this->init_speed = init_speed;
	this->max_speed = max_speed;
	this->car_prob = car_prob;
	this->bus_prob = bus_prob;
	this->truck_prob = truck_prob;
	this->road_is_fed = false;
}

feeder_params::~feeder_params()
{

}

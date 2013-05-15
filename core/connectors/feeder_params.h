/*
feeder_params.h - parameter for road's vehicle generation

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

#ifndef FEEDER_PARAMS_H_
#define FEEDER_PARAMS_H_
#include "define/cadef.h"
/*
 *
 */
class feeder_params
{
public:
	feeder_params();
	feeder_params(float density);
	feeder_params(float density, int16 init_speed, int16 max_speed);
	feeder_params(float density, int16 init_speed, int16 max_speed,
					float car_prob,
					float bus_prob);
	~feeder_params();

	float density;		// density of filled road
	int16 init_speed;	// initial speed of vehicles to generate
	int16 max_speed;	// maximum spped of vehicles to generate
	float car_prob;		// probability of generating Cars
	float bus_prob;		// probability of generating Buses
	float truck_prob;	// probability of generating Trucks
private:
	void init_params(float density, int16 init_speed,
					int16 max_speed, float car_prob,
					float bus_prob, float truck_prob);
};

#endif /* FEEDER_PARAMS_H_ */

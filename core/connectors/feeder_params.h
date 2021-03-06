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

const float DEFAULT_FEEDER_DENSITY = 0.2;
const short DEFAULT_FEEDER_INIT_SPEED = 20;
const short DEFAULT_FEEDER_MAX_SPEED = 80;
const float DEFAULT_FEEDER_CAR_PROB = 0.7;
const float DEFAULT_FEEDER_BUS_PROB = 0.25;
const float DEFAULT_FEEDER_TRUCK_PROB = 0.05;
const distribution DEFAULT_FEEDER_DISTRIBUTION = UNIFORM;

enum feeder_mode
{
	INITIAL,			// road is fed to density at start
	CONTINUOUS,			// road is fed to keep required density
	DISTRIBUTIVE,		// vehicles appear according to distribution
};

const feeder_mode DEFAULT_FEEDER_MODE = INITIAL;
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

	feeder_mode mode;	// a mode of feeding
	distribution distribution_type; // distribution that is used in DISTRIBUTIVE mode

	bool road_fed() const {return road_is_fed;};
	void set_fed() {road_is_fed = true;};
	void set_not_fed(){road_is_fed = false;};
	bool need_to_distribute() const{return need_distribute;};
	void set_distribution_timer(int time)
	{
		this->distribution_timer = time;
		need_distribute = false;
	};
	void tick_distribution_timer();
private:
	bool road_is_fed;	// indicator for initial distribution
	bool need_distribute;	// indicator of road's need to be distributed
	int distribution_timer;

	void init_params(float density, feeder_mode mode, int16 init_speed,
					int16 max_speed, float car_prob,
					float bus_prob, float truck_prob);

};

typedef boost::shared_ptr<feeder_params> feeder_params_ptr;

#endif /* FEEDER_PARAMS_H_ */

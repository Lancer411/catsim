/*
	connector.h - an interface that provides road connector's functionality

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

#ifndef CONNECTOR_H_
#define CONNECTOR_H_
#include "define/cadef.h"
#include "core/entities/road.h"

class road;
typedef boost::shared_ptr<road> road_ptr;

class connector
{
public:
	/**
	 * Transfers vehicle from one road to another
	 *
	 * \param	from_road_id	Identifier of road which vehicle comes from
	 * \param	to_road			Pointer to road which vehicle comes to
	 * \param	veh				Vehicle for transfer
	 * \param	passed_distance	Distance (in cells) that vehicle has already passed on previous road
	 *
	 * \return	true	- if transfering possible
	 * 			false	- if transfering impossible (e.g. next road is busy)
	 */
	virtual bool transfer(std::string from_road_id, road_ptr to_road, vehicle_ptr veh, short passed_distance) = 0;

	/**
	 * Determines the appropriate road to transfer depending
	 * on its relative direction to previous road (left, right,
	 * straight) and returns it.
	 *
	 * \param	road_id		Identifier of previous road
	 * \param	direction	Relative direction of next road to previous one
	 *
	 * \return	road_ptr	- appropriate pointer to road
	 * 			null_ptr	- if no appropriate road exists
	 */
	virtual road_ptr get_next_road(std::string road_id, relative_direction direction) = 0;
};

#endif /* CONNECTOR_H_ */

/*
	crossroad.h - represents crossroad, intersection between roads

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

#ifndef CROSSROAD_H_
#define CROSSROAD_H_
#include "core/connectors/connector.h"
#include "core/tools/conversion.h"
#include "boost/algorithm/string/predicate.hpp"
#include "core/entities/lightsignal.h"
enum lightsignal_mode
{
	FIXED,
	ADAPTIVE,
};
class crossroad : public connector
{
	const static int NO_ROAD = -1;
	//array inputs roads
	road_ptr roads_in [ROAD_COUNT];
	// array of roads which are direct inputs for crossroad
	road_ptr roads_direct[ROAD_COUNT][ROAD_COUNT];
	// array of roads which are opposite to direct ones
	road_ptr roads_opposite[ROAD_COUNT][ROAD_COUNT];
	// matrix represents road to road state (ABLE, UNABLE, NONE)
	short road_mtx[ROAD_COUNT][ROAD_COUNT];

	bool controlled;
	lightsignal_ptr ls;
	lightsignal_mode ls_mode;
public:
	crossroad();
	virtual ~crossroad();
	/**
	 * Method for adding the first road to crossroad. Other roads
	 * must be added to crossroad using method connect, relatively
	 * to existing roads.
	 *
	 * \param	road	a road to add
	 * \return	true	- if road added
	 * 			false	- if first road already been added
	 */
	bool add_first_road(road_ptr road);

	/**
	 * Method to establish connection between existing road in crossroad
	 * and newly added using relative direction between them.
	 *
	 * \param	road		new road to connect
	 * \param	road_id		identifier of the road which already connected to crossroad
	 * \param	direction	relative direction of \p road to road with \p road_id
	 * 						(e.g. road_1 is left (DIRECTION_LEFT) to road with id 2)
	 *
	 * \return	true		- if connected successfully
	 * 			false		- if road with road_id is not connected to crossroad
	 * 						or connection in that direction already exists
	 **/
	bool connect(road_ptr road, std::string road_id, relative_direction direction);
	bool connect_in(road_ptr inpit_road);
	bool transfer(std::string from_road_id, road_ptr to_road, vehicle_ptr veh, short passed_distance);
	road_ptr get_next_road(std::string road_id, relative_direction direction);

	void add_light_signal(lightsignal_ptr lightsignal, lightsignal_mode mode);
	lightsignal_ptr get_light_signal();

	void print_crossroad(std::string road_id);

	/**
	 * Implements an adaptive control method
	 */
	void iterate();

private:
	/**
	 * Finds position of road in one of road arrays (direct and opposite)
	 *
	 * \param	road_id		identifier of road to find
	 *
	 * \return	position 	- if road found
	 * 			ROAD_NONE	- if road not found
	 */
	int get_input_road_position(std::string road_id);
	int get_output_road_position(std::string road_id, int x);
	/**
	 * Returns the status of path availavility between roads
	 * with positions pos_x and pos_y
	 *
	 * \param	pos_x		position of first road
	 * \param	pos_y		position of second road
	 *
	 * \return	road_status	ROAD_ABLE, ROAD_UNABLE, or ROAD_NONE for no connection
	 */
	road_status get_status(int pos_x, int pos_y);

	/**
	 * Sets the same status for both directions
	 */
	void set_status(int pos_x, int pos_y, road_status status);

	/**
	 * Sets status for road in position, for all of other roads
	 * in both directions
	 */
	void set_road_status(int position, road_status status);
	/**
	 * Sets status for road in position, for all of other roads
	 * in one directions
	 */
	void set_direction_road_status(int position, road_status status);
	/**
	 * Sets status in one direction between road with \p pos_x
	 * and road with \p pos_y
	 */
	void set_direction_status(int pos_x, int pos_y, road_status status);

	/**
	 * Determines all available directions for road in \p position
	 * and return a random of them.
	 */
	relative_direction get_any_available_direction(int position);



};

typedef boost::shared_ptr<crossroad> crossroad_ptr;
typedef boost::weak_ptr<crossroad> crossroad_ptr_weak;

#endif /* CROSSROAD_H_ */

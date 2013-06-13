/*
 vehicle_feeder.h - connector which aim is to fill roads with
 vehicles with some density and transfer input vehicles from
 deadend roads to feeding

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

#ifndef VEHICLE_FEEDER_H_
#define VEHICLE_FEEDER_H_
#include "core/connectors/connector.h"
#include "core/connectors/feeder_params.h"
#include "core/factories/vehicle_factory.h"
#include "core/entities/vehicle.h"
#include <boost/algorithm/string/predicate.hpp>

typedef boost::container::map<std::string, road_ptr> road_map;
typedef boost::container::map<std::string, feeder_params_ptr> params_map;

enum feeder_trasfer_mode
{
  SAVING,
  DELETING,
};
class vehicle_feeder : public connector
{
	// a map of roads to feed
	road_map feeding_roads;
	// a map of roads' feeding params
	params_map feeding_roads_params;
	// a map of deadend roads
	road_map deadend_roads;
	// pointer to existing vehicle factory
	vehicle_factory_ptr veh_factory;
	// transfer mode
	feeder_trasfer_mode transfer_mode;
public:
	/**
	 * Constructor of vehicle feeder with vehicle factory as parameter
	 */
	vehicle_feeder(vehicle_factory_ptr veh_factory);
	~vehicle_feeder();

	bool transfer(std::string from_road_id, road_ptr to_road, vehicle_ptr veh, short passed_distance);
	road_ptr get_next_road(std::string road_id, relative_direction direction);

	/**
	 * Adds road to feed with feeding \p params
	 *
	 * \return	true	- if successfully added
	 * 			false	- if road already been added
	 */
	bool connect_feeding_road(road_ptr road, feeder_params_ptr params);

	/**
	 * Add road which is input to feeder
	 *
	 * \param	road				a road to add
	 * \param	feeding_road_id		identifier of feeding road. added road
	 * 								will be transfered to this feeding road
	 *
	 * \return	true	- if successfully added
	 * 			false	- if road already been added or feeding road is not exist
	 */
	bool connect_deadend_road(road_ptr road, std::string feeding_road_id);

	/**
	 * Feeds all the roads with their params
	 */
	void feed_roads();
	void set_transfer_mode(feeder_trasfer_mode mode){this->transfer_mode = mode;};
private:
	/**
	 * Fills specified road with params
	 */
	void fill_road_to_density(road_ptr road, feeder_params_ptr params);
	void feed_road_initially(road_ptr road, feeder_params_ptr params);
	void feed_road_continuously(road_ptr road, feeder_params_ptr params);
	void feed_road_by_distribution(road_ptr road, feeder_params_ptr params);

	vehicle_ptr create_vehicle_by_params(feeder_params_ptr params);
	void update_road_params(std::string id, feeder_params_ptr params);

};

typedef boost::shared_ptr<vehicle_feeder> vehicle_feeder_ptr;
typedef boost::weak_ptr<vehicle_feeder> vehicle_feeder_ptr_weak;

#endif /* VEHICLE_FEEDER_H_ */

/*
 vehicle_feeder.h - connector which aim is to fill roads with
 vehicles with some density

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
#include "core/tools/random.h"
#include "boost/algorithm/string/predicate.hpp"

typedef boost::container::map<std::string, road_ptr> road_map;
typedef boost::container::map<std::string, feeder_params> params_map;
/*
 *
 */
class vehicle_feeder : public connector
{
	road_map feeding_roads;
	params_map feeding_roads_params;
	road_map deadend_roads;
	vehicle_factory_ptr veh_factory;
public:
	vehicle_feeder(vehicle_factory_ptr veh_factory);
	~vehicle_feeder();

	bool transfer(std::string from_road_id, road_ptr to_road, vehicle_ptr veh, short passed_distance);
	road_ptr get_next_road(std::string road_id, relative_direction direction);

	bool connect_feeding_road(road_ptr road, feeder_params params);
	bool connect_deadend_road(road_ptr road, std::string feeding_road_id);

	void feed_roads();
	void feed_direct_roads();
private:
	void fill_road_to_density(road_ptr road, feeder_params params);
	void fill_direct_road_to_density (road_ptr road, feeder_params params);
};

typedef boost::shared_ptr<vehicle_feeder> vehicle_feeder_ptr;
typedef boost::weak_ptr<vehicle_feeder> vehicle_feeder_ptr_weak;

#endif /* VEHICLE_FEEDER_H_ */

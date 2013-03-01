/*
 * connector.h
 *
 *  Created on: Feb 28, 2013
 *      Author: ngh
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
	virtual bool transfer(std::string from_road_id, road_ptr to_road, vehicle_ptr veh, short passed_distance) = 0;
	virtual road_ptr get_next_road(std::string road_id, relative_direction direction) = 0;
};

#endif /* CONNECTOR_H_ */

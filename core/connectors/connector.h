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
	virtual bool transfer(road_ptr road, vehicle_ptr veh, short passed_distance) = 0;
	virtual road_ptr get_next_road() = 0;
};

#endif /* CONNECTOR_H_ */

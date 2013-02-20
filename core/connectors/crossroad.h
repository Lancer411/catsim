/*
 * crossroad.h
 *
 *  Created on: Nov 18, 2012
 *      Author: ngh
 */

#ifndef CROSSROAD_H_
#define CROSSROAD_H_
#include "define/cadef.h"
#include "core/entities/road.h"

//class road;
//typedef boost::shared_ptr<road> road_ptr;

class crossroad
{
	road_ptr road_input;
	road_ptr road_output;
public:
	crossroad();
	virtual ~crossroad();
	void set_road_input(road_ptr road) {road_input = road;};
	void set_road_output(road_ptr road) {road_output = road;};
	bool transfer(road_ptr road, vehicle_ptr veh, short passed_distance);
	road_ptr get_next_road(){return road_output;};
};

typedef boost::shared_ptr<crossroad> crossroad_ptr;
typedef boost::weak_ptr<crossroad> crossroad_ptr_weak;

#endif /* CROSSROAD_H_ */

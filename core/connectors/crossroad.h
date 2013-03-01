/*
 * crossroad.h
 *
 *  Created on: Nov 18, 2012
 *      Author: ngh
 */

#ifndef CROSSROAD_H_
#define CROSSROAD_H_
#include "core/connectors/connector.h"
#include "core/tools/conversion.h"

class crossroad : public connector
{
	const static int NO_ROAD = -1;
	road_ptr roads[ROAD_COUNT];
	short road_mtx[ROAD_COUNT][ROAD_COUNT];
public:
	crossroad();
	virtual ~crossroad();
	bool add_first_road(road_ptr road);
	bool connect(road_ptr road, std::string road_id, relative_direction direction);
	bool transfer(road_ptr road, vehicle_ptr veh, short passed_distance);
	road_ptr get_next_road(std::string road_id, relative_direction direction);
private:
	int get_road_position(std::string road_id);
	road_status get_status(int pos_x, int pos_y);
	void set_status(int pos_x, int pos_y, road_status status);
	void set_road_status(int position, road_status status);
	void set_direction_status(int pos_x, int pos_y, road_status status);
};

typedef boost::shared_ptr<crossroad> crossroad_ptr;
typedef boost::weak_ptr<crossroad> crossroad_ptr_weak;

#endif /* CROSSROAD_H_ */

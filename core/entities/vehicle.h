/*
 * vehicle.h
 *
 *  Created on: Oct 30, 2012
 *      Author: ngh
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_
#include "entity.h"
#include "core/tools/conversion.h"
#include "core/tools/random.h"

class vehicle : public entity
{
	int16 current_kmh_velocity;
	int16 max_kmh_velocity;
	int16 current_cell_velocity;
	int16 max_cell_velocity;
	vehicle_type type;
	short length;
	int16 time_on_road;
public:
	vehicle();
	vehicle(int16 max_velocity, int16 start_velocity);
	vehicle(int16 max_velocity, int16 start_velocity, vehicle_type type);
	vehicle(const vehicle &veh);
	~vehicle();

	int16 get_kmh_velocity() const {return current_kmh_velocity;};
	int16 get_cell_velocity() const {return current_cell_velocity;};
	int16 get_max_kmh_velocity() const {return max_kmh_velocity;};
	int16 get_max_cell_velocity() const {return max_cell_velocity;};
	vehicle_type get_type() const {return type;};
	short get_length() const {return length;};
	int16 get_time_on_road() const {return time_on_road;};
	void set_current_velocity(int16 kmh_velocity)
	{
		current_kmh_velocity = kmh_velocity;
		current_cell_velocity = conversion::convert_to_cell_velocity(kmh_velocity);
	};
	void set_cell_velocity (int16 cell_velocity)
	{
		current_cell_velocity = cell_velocity;
		current_kmh_velocity = conversion::convert_to_kmh_velocity(cell_velocity);
	};
	void set_max_kmh_velocity(int16 kmh_velocity){max_kmh_velocity = kmh_velocity;};
	void set_max_cell_velocity(int16 cell_velocity){max_cell_velocity = cell_velocity;};
	void set_type(vehicle_type t);
//	void set_length(int16 lenth){this->length = length;};

	int16 update_velocity (short limit);
	void reset_time_counter(){time_on_road = 0;};
private:
	void init(int16 max_velocity, int16 start_velocity, vehicle_type type);
};

typedef boost::shared_ptr<vehicle> vehicle_ptr;
#endif /* VEHICLE_H_ */

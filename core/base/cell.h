/*
 * cell.h
 *
 *  Created on: Oct 30, 2012
 *      Author: ngh
 */

#ifndef CELL_H_
#define CELL_H_
#include "define/cadef.h"
#include "core/entities/vehicle.h"

class cell
{
	vehicle_ptr vehicle;
	bool occupied;
public:
	cell();
	cell(const cell &cell);
	virtual ~cell();

	bool is_occupied() const{return this->occupied;};
	vehicle_ptr get_vehicle() const {return this->vehicle;};

	void clear();
	void set_vehicle(vehicle_ptr vehicle);

	friend std::ostream& operator <<( std::ostream &stream, const cell &cell)
	{
		if(cell.is_occupied())
			stream<<"*";
		else
			stream<<'-';
		return stream;
	}
};

#endif /* CELL_H_ */

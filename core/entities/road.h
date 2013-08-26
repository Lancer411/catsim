/*
	road.h - represents simple one direction road

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

#ifndef ROAD_H_
#define ROAD_H_
#include "entity.h"
#include "define/cadef.h"
#include "core/base/iautomat.h"
#include "core/base/cell.h"
#include "core/tools/conversion.h"
#include "core/tools/random.h"
#include "core/entities/vehicle.h"
#include "core/stat/road_stat_data.h"
#include "core/stat/stat_data_handler.h"
#include "core/tools/road_iterating_tools.h"
#include "core/entities/road_marker.h"
#include <boost/pending/queue.hpp>
#include <boost/container/set.hpp>

typedef boost::queue<vehicle_ptr> vehicle_queue;
typedef boost::container::set<vehicle_ptr> vehicle_set;

class connector;
typedef boost::shared_ptr<connector> connector_ptr;
typedef boost::weak_ptr<connector> connector_ptr_weak;

class road;
typedef boost::shared_ptr<road> road_ptr;
class road : public entity, public iautomat, public imarkable
{
	cell **roaddata;
	cell **temp_roaddata;
	int16 rl, rw;
	short velocity_limit;
	vehicle_queue vehicles_source;			// источник машин
	vehicle_queue vehicles_runoff;			// сток машин; машина попадает в сток когда выезжает с дороги
	road_stat_data_ptr stat_data;			// статистические данные с дороги
	connector_ptr_weak front_crossroad;

	bool free;
public:
	road(int16 linesnum, int16 length);
	road(int16 linesnum, int16 length, short velocity_limit);
	virtual ~road();
	void iterate();
	void clear();
	int16 get_lane_count() const {return rw;};
	int16 get_lane_length() const {return rl;};
	short get_velocity_limit() const {return velocity_limit;};
	float get_current_density() const {return stat_data->get_current_road_density();};
	void set_velocity_limit(short limit){velocity_limit = limit;};
	void set_connector(connector_ptr cross){ front_crossroad = cross; };
	void push_vehicle(vehicle_ptr veh);
	vehicle_ptr pop_vehicle();
	int get_source_size(){return vehicles_source.size();};
	int get_runoff_size(){return vehicles_runoff.size();};
	friend std::ostream& operator <<( std::ostream &stream, const road_ptr &road)
	{
		for(int i = 0; i<road->rw; i++)
		{
			for(int j = 0; j<road->rl; j++)
				stream<<road->roaddata[i][j];
			stream<<std::endl;
		}
		return stream;
	};


	void set_road_stat_data (road_stat_data_ptr data){stat_data = data;};
private:
	// осуществить переезд машиной
	void drive(vehicle_ptr veh, int i, int j);
	// установить машину. l - координата хвоста машины
	void put_vehicle(vehicle_ptr veh, int16 w, int16 l);
	// установить  машину. l - координата носа машины
	void put_vehicle2(vehicle_ptr veh, int16 w, int16 l);
	void init (int16 linesnum, int16 length, short limit);
	// свободное место в начале дороги
	bool has_free_space(short len, short velocity, CA_COORD *coord);
	bool has_free_space_at_lane(cell** &data, int lane, short len, short velocity, CA_COORD *coord);
	// выпустить машины в очереди на дорогу (кол-во машин = кол-во полос)
	void release_vehicles_source();
	// переместить машину veh со start на end
	// start, end - координаты старой и новой позиции носа машины
	void move_vehicle(vehicle_ptr veh, CA_COORD end);
	// затормозить машину
	void slow_down_vehicle(vehicle_ptr veh, vehicle_ptr front_veh, short distance, CA_COORD end);
	// проверка доступности полосы в интервале
	bool lane_accessible(vehicle_ptr veh, int i, int j);
	// попытаться пройти перекресток или затормозить
	void try_crossroad(vehicle_ptr veh, int i, int j);
	// попытатся сменить полосу
	bool change_lanes(vehicle_ptr veh, int i, int j, CA_COORD &coord);
	// скопировать дорогу из временной.
	void copy_roads();
	// освободить временный массив
	void free_temp_road();
	// освободить сток и исток
	void free_queues();

	friend class crossroad;
	friend class vehicle_feeder;
};


#endif /* ROAD_H_ */

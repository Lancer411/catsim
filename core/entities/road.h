/*
 * road.h
 *
 *  Created on: Oct 31, 2012
 *      Author: ngh
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
//#include "core/connectors/crossroad.h"
#include "core/stat/road_stat_data.h"
#include "core/stat/stat_data_handler.h"
#include "core/tools/road_iterating_tools.h"
#include <queue>
#include <set>

typedef std::queue<vehicle_ptr> vehicle_queue;
typedef std::set<vehicle_ptr> vehicle_set;

class crossroad;
typedef boost::shared_ptr<crossroad> crossroad_ptr;
typedef boost::weak_ptr<crossroad> crossroad_ptr_weak;

class road;
typedef boost::shared_ptr<road> road_ptr;
class road : public entity, iautomat
{
	cell **roaddata;
	cell **temp_roaddata;
	int16 rl, rw;
	short velocity_limit;
	vehicle_queue vehicles_source;			// источник машин
	vehicle_queue vehicles_runoff;			// сток машин; машина попадает в сток когда выезжает с дороги
	road_stat_data_ptr stat_data;			// статистические данные с дороги
	crossroad_ptr_weak crossroad;
public:
	road(int16 linesnum, int16 length);
	road(int16 linesnum, int16 length, short velocity_limit);
	virtual ~road();
	void iterate();
	void clear();
	int16 get_lane_count() const {return rw;};
	int16 get_lane_length() const {return rl;};
	short get_velocity_limit() const {return velocity_limit;};
	void set_velocity_limit(short limit){velocity_limit = limit;};
	void set_crossroad(crossroad_ptr cross){ crossroad = cross; };
	void push_vehicle(vehicle_ptr veh);
	vehicle_ptr pop_vehicle();
	int get_source_size(){return vehicles_source.size();};
	int get_runoff_size(){return vehicles_runoff.size();};
	friend std::ostream& operator <<( std::ostream &stream, const road_ptr &road)
	{
		stream<<"current"<<std::endl;
		for(int i = 0; i<road->rw; i++)
		{
			for(int j = 0; j<road->rl; j++)
				stream<<road->roaddata[i][j];
			stream<<std::endl;
		}

		stream<<"temp"<<std::endl;
		for(int i = 0; i<road->rw; i++)
		{
			for(int j = 0; j<road->rl; j++)
				stream<<road->temp_roaddata[i][j];
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
	bool has_free_space_temp(short len, short velocity, COORD *coord);
	bool has_free_space(short len, short velocity, COORD *coord);
	bool has_free_space_at_lane(cell** &data, int lane, short len, short velocity, COORD *coord);
	// выпустить машины в очереди на дорогу (кол-во машин = кол-во полос)
	void release_vehicles_source();
	// переместить машину veh со start на end
	// start, end - координаты старой и новой позиции носа машины
	void move_vehicle(vehicle_ptr veh, COORD end);
	// затормозить машину
	void slow_down_vehicle(vehicle_ptr veh, vehicle_ptr front_veh, short distance, COORD end);
	// проверка доступности полосы в интервале
	bool lane_accessible(vehicle_ptr veh, int i, int j);
	// попытаться пройти перекресток или затормозить
	void try_crossroad(vehicle_ptr veh, int i, int j);
	// попытатся сменить полосу
	bool change_lanes(vehicle_ptr veh, int i, int j, COORD &coord);
	// скопировать дорогу из временной.
	void copy_roads();
	// освободить временный массив
	void free_temp_road();

	friend class crossroad;
};


#endif /* ROAD_H_ */

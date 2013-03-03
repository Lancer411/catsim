/*
	road.cpp - represents simple one direction road

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

#include "road.h"
#include "core/connectors/crossroad.h"

road::road(int16 linesnum, int16 length)
{
	init(linesnum, length, DEFAULT_VELOCITY_LIMIT);
}

road::road(int16 linesnum, int16 length, short limit)
{
	init(linesnum, length, limit);
}

void road::init(int16 linesnum, int16 length, short limit)
{
	rw = linesnum; rl = length;
	velocity_limit = conversion::convert_to_cell_velocity(limit);
	roaddata = new cell*[rw];
	temp_roaddata = new cell*[rw];
	for(int i = 0; i < rw; i++)
	{
		roaddata[i] = new cell[rl];
		temp_roaddata[i] = new cell[rl];
	}
}

void road::copy_roads()
{
	for(int i = 0; i < rw; i++)
	{
		for(int j = 0; j < rl; j++)
		{
			temp_roaddata[i][j] = roaddata[i][j] ;
			roaddata[i][j].clear();
		}
	}
}

void road::free_temp_road()
{
	for(int i = 0; i < rw; i++)
	{
		delete[] temp_roaddata[i];
		temp_roaddata[i] = new cell[rl];
	}
}

void road::iterate()
{
	// распределить машины из источника
	release_vehicles_source();
	// скопировать дороги
	copy_roads();
	// итерировать все машины
	for(int i = 0; i < rw; i++)
		for(int j = 0; j < rl;)
		{
			if(temp_roaddata[i][j].is_occupied()) // если ячейка занята
			{
				vehicle_ptr veh = temp_roaddata[i][j].get_vehicle();
				stat_data->update_avg_speed(veh->get_kmh_velocity());
				veh->update_velocity(velocity_limit);
				drive(veh, i, j);
				j += veh->get_length();
//				j -= veh->get_length();
			}
			else j++;
//			else j--;
		}

	// обновить статистические данные
	stat_data->update_parameters();
	// cбросить обновившиеся машины
	free_temp_road();
}

void road::drive(vehicle_ptr veh, int i, int j)
{
	// вычислить следующую позицию
	short veh_length = veh->get_length();
	COORD start, end;
	start.x = i; end.x = i;
	start.y = j + veh_length; // нос машины + 1
//	start.y = j + 1; // нос машины + 1
	// проверить текущую позицию
	if(start.y >= rl)
	{
		// если последняя ячейка то переехать/не двигатся
		try_crossroad(veh, i, start.y - 1);
		return;
	}
	// следующая возможная координата
	int next_coord_y = start.y + veh->get_cell_velocity() - 1;
	end.y = next_coord_y;
	vehicle_ptr front_vehicle;
	conversion::check_coord(start, rw, rl);
	conversion::check_coord(end, rw, rl);
	// если впереди есть машина
	bool front_veh_exist = road_iterating_tools::
			find_front_vehicle(temp_roaddata, start, end, front_vehicle);
	if(!front_veh_exist)
	{
		// проверить следующую координату
		if(next_coord_y >= rl)
			try_crossroad(veh, i, start.y - 1);// либо переехать/затормозить
		else
			move_vehicle(veh, end);// либо ехать дальше
		return;
	}
	// сменить полосу
	bool lane_changed = change_lanes(veh, i, start.y - 1, end);
	// если не сменили
	if(!lane_changed)
	{
		//	тормозить
		start.y = start.y - 1;
		short distance_to_front_vehicle = end.y - start.y;
		end.y = start.y + distance_to_front_vehicle - 1;
		conversion::check_coord(end, rw, rl);
		slow_down_vehicle(veh, front_vehicle, distance_to_front_vehicle - 1, end);
		return;
	}
	// ехать прямо
	move_vehicle(veh, end);

}

bool road::change_lanes(vehicle_ptr veh, int i, int j, COORD &coord)
{
	int16 next_coord_x = i;
	if(lane_accessible(veh, i+1, j))
		next_coord_x = i+1;
	else
	{
		if(lane_accessible(veh, i-1, j))
			next_coord_x = i-1;
	}

	if(next_coord_x!=i)
	{
		coord.x = next_coord_x;
		return true;
	}
	return false;
}


void road::try_crossroad(vehicle_ptr veh, int i, int j)
{
	crossroad_ptr cr = boost::shared_polymorphic_downcast<crossroad>(front_crossroad.lock());
//	short velocity_decceleration = veh->get_cell_velocity() - (rl-j-1);
	if(cr)
	{
		COORD coord;
		road_ptr null_ptr;
		// выбрать следующую дорогу
		road_ptr next_road = cr->get_next_road(this->get_id(), DIRECTION_STRAIGHT);
		// если дороги нет
		if(next_road == null_ptr)
		{
			// тормозить в конце дороги
			coord.x = i;
			coord.y = rl - 1;
			conversion::check_coord(coord,rw,rl);
			vehicle_ptr front_vehicle;
			slow_down_vehicle(veh, front_vehicle, 0, coord);
			return;
		}

		// если дорога свободна переехать
		int16 time_on_road = veh->get_time_on_road();
		bool transfered = cr->transfer(this->get_id(), next_road, veh, (rl-j-1));
		if(!transfered)
		{
			// иначе затормозить в конце дороги
			coord.x = i;
			coord.y = rl - 1;
			conversion::check_coord(coord,rw,rl);
			vehicle_ptr front_vehicle;
			slow_down_vehicle(veh, front_vehicle, 0, coord);
			return;
		}
		stat_data->inc_passed_vehicles_num(time_on_road);
		stat_data->dec_current_vehicles_num(veh->get_length());
	}
}

bool road::lane_accessible(vehicle_ptr veh, int i, int j)
{
	if(i >= rw || i < 0)
		return false;
		// проверить промежуток на соседней полосе, спереди и сзади от тек машины
	COORD start, end;
	start.x = end.x = i;
	start.y = j - veh->get_length() - velocity_limit;
	end.y = j + veh->get_cell_velocity();
	conversion::check_coord(start, rw, rl);
	conversion::check_coord(end, rw, rl);
	return !road_iterating_tools::vehicle_exists(temp_roaddata, start, end);
}

void road::move_vehicle(vehicle_ptr veh, COORD end)
{
//	remove_vehicle2(veh, start.x, start.y);
	put_vehicle2(veh, end.x, end.y);
//	put_vehicle(veh, end.x, end.y);
}

void road::slow_down_vehicle(vehicle_ptr veh, vehicle_ptr front_veh, short distance, COORD end)
{
	// если торможение не перед машиной
	if(front_veh==NULL)
	{
		veh->set_cell_velocity(distance);
		move_vehicle(veh, end);
	}
	else
	// Торможение
	// Если оба авто движутся и скорость тек авто > расстояния
	// до впереди идущего то тек скорость = расст
	if(random::std_random() < DEFAULT_PROB_FWD_ANTICIPATION ||
	(veh->get_cell_velocity() > 0
	&& front_veh->get_cell_velocity() >= 0
	/*&& veh->get_cell_velocity() >= distance*/))
	{
		// снизить скорость
		veh->set_cell_velocity(distance);
		move_vehicle(veh, end);
	}
	// Медленный старт
	else
	{
		if(random::std_random()<DEFAULT_PROB_SLOW_TO_START ||
		(veh->get_cell_velocity() == 0
		/*&&	distance <= MIN_POSSIBLE_DISTANCE*/))
		{
			veh->set_cell_velocity(0);
		}
	}
}

void road::clear()
{
	for (int i = 0; i < rw; i++)
	{
		for (int j = 0; j < rl; j++)
		{
			roaddata[i][j].clear();
			temp_roaddata[i][j].clear();
		}
	}
	free_queues();
}

void road::put_vehicle(vehicle_ptr veh, int16 w, int16 l)
{
	short len = veh->get_length();
	while(len)
	{
		len--;
		roaddata[w][l+len].set_vehicle(veh);
	}
}

void road::put_vehicle2(vehicle_ptr veh, int16 w, int16 l)
{
	put_vehicle(veh, w, l - veh->get_length() + 1);
}

void road::push_vehicle(vehicle_ptr veh)
{
	COORD coord;
	if(has_free_space(veh->get_length(), veh->get_cell_velocity(), &coord))
	{
		put_vehicle2(veh, coord.x, coord.y);
		stat_data->inc_current_vehicles_num(veh->get_length());
	}
	else
		vehicles_source.push(veh);
}

vehicle_ptr road::pop_vehicle()
{
	vehicle_ptr veh;
	if(!vehicles_runoff.empty())
	{
		veh = vehicles_runoff.front();
		veh->reset_time_counter();
		vehicles_runoff.pop();
	}
	return veh;
}

void road::release_vehicles_source()
{
	if(vehicles_source.empty())
		return;
	vehicle_ptr veh = vehicles_source.front();
	for(int i = 0; i < rw; i++)
	{
		COORD coord;
		while(has_free_space_at_lane(roaddata, i, veh->get_length(), veh->get_cell_velocity(), &coord))
		{
			put_vehicle2(veh, coord.x, coord.y);
			stat_data->inc_current_vehicles_num(veh->get_length());
			vehicles_source.pop();
			if(vehicles_source.empty())
				return;
			veh = vehicles_source.front();
		}
	}
}

bool road::has_free_space(short len, short velocity, COORD *coord)
{
	bool source_empty = vehicles_source.empty();
		for(int i = 0; i < rw; i++)
			if(has_free_space_at_lane(temp_roaddata ,i, len, velocity, coord))
				return true && source_empty;
		return false && source_empty;
}

bool road::has_free_space_at_lane(cell** &data, int lane, short len, short velocity, COORD *coord)
{
	for(int j = 0; j <= len && j < rl - velocity; j++)
	{
		if(!data[lane][j].is_occupied())
		{
			if(j >= len - 1)
			{
				short vel_t = 0;
				while(vel_t <= velocity)
				{
					if(!data[lane][j+vel_t].is_occupied())
					{
						coord->y = j+vel_t;
						coord->x = lane;
					}
					else
					{
						bool already_occupied = roaddata[lane][coord->y].is_occupied()
								||  roaddata[lane][j].is_occupied();
						return !already_occupied;
					}

					vel_t++;
				}
				bool already_occupied = roaddata[lane][coord->y].is_occupied()
												||  roaddata[lane][j].is_occupied();
				return !already_occupied;
			}
		}
		else
			return false;
	}
	return false;
}

void road::free_queues()
{
	vehicle_queue empty;
	std::swap(vehicles_source, empty);
	std::swap(vehicles_runoff, empty);
}

road::~road()
{
	for(int i = 0; i < rw; i++)
	{
	   delete[] roaddata[i];
	   delete[] temp_roaddata[i];
	}
	delete[] roaddata;
	delete[] temp_roaddata;
	free_queues();
}

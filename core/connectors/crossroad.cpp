/*
	crossroad.cpp - represents crossroad, intersection between roads

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

#include "crossroad.h"
#include "core/entities/road.h"
#include "define/cadef.h"

crossroad::crossroad()
{
	for (int i = 0; i < cadef::road_count; ++i)
		for (int j = 0; j < cadef::road_count; ++j)
			(i != j) ?
			road_mtx[i][j] = ROAD_UNABLE:
			road_mtx[i][j] = ROAD_ABLE;
	controlled = false;
}

bool crossroad::transfer(std::string from_road_id, road_ptr to_road, vehicle_ptr veh, short passed_distance)
{
	COORD coord;
	int from = get_input_road_position(from_road_id);
	int to = get_output_road_position(to_road->get_id(),from);
	bool road_able = (get_status(from, to) == ROAD_ABLE);
	bool road_free = to_road->has_free_space(veh->get_length(), veh->get_cell_velocity() - passed_distance + 1, &coord);
//	std::cout<<"from "<<from<<" to "<<to+4<<std::endl;
	if(road_free && road_able)
	{
//		short vel = passed_distance + coord.y + 1;
//		veh->set_cell_velocity(vel);
		veh->set_cell_velocity(veh->get_cell_velocity() - passed_distance + 1);
		veh->reset_time_counter();
		to_road->move_vehicle(veh, coord);
		to_road->stat_data->inc_current_vehicles_num(veh->get_length());
//		road->push_vehicle(veh);
		return true;
	}
	return false;
}

bool crossroad::add_first_road(road_ptr road)
{
	if(road_mtx[0][1] != ROAD_UNABLE)
		return false;
	roads_direct[0][0] = road;
	roads_in[0] = road;
	set_direction_road_status (0, ROAD_UNABLE);
	return true;
}

bool crossroad::connect(road_ptr road, std::string road_id, relative_direction direction)
{
	int x = get_input_road_position(road_id);
	if(x == NO_ROAD)
		return false;
	int y = conversion::get_output_road_position(x, direction);
	if(get_status(x, y) != ROAD_NONE)
	{
		set_direction_status (x, y, ROAD_ABLE);
		switch(direction)
		{
			case DIRECTION_RIGHT:
			case DIRECTION_STRAIGHT:
				roads_direct[x][y] = road;
				break;
			case DIRECTION_LEFT:
				roads_opposite[x][y] = road;
				break;
			case DIRECTION_ANY:
				break;
		}
	}
	return false;
}

bool crossroad::connect_in(road_ptr input_road)
{
	road_ptr null_ptr;
	for (int i=0; i<cadef::road_count;i++)
		if (roads_in[i]==null_ptr)
		{
			roads_direct[i][0] = input_road;
			set_direction_road_status(i, ROAD_UNABLE);
			roads_in[i]=input_road;
			return true;
		}
	return false;
}

road_ptr crossroad::get_next_road(std::string road_id, relative_direction direction)
{
	road_ptr null_ptr;
	int position = get_input_road_position(road_id);
	if(position == NO_ROAD)
		return null_ptr;
	if(direction == DIRECTION_ANY)
	{
		direction = get_any_available_direction(position);

	}
	int pos = conversion::get_output_road_position(position, direction);
	switch(direction)
	{
		case DIRECTION_RIGHT:
		case DIRECTION_STRAIGHT:
			return roads_direct[position][pos];
		case DIRECTION_LEFT:
			return roads_opposite[position][pos];
		case DIRECTION_ANY:
			return null_ptr;
	}
}

int crossroad::get_input_road_position(std::string road_id)
{
	road_ptr null_ptr;
	for (int i = 0; i < cadef::road_count; ++i)
	{
		if (roads_in[i]!= null_ptr)
			if(boost::algorithm::equals(road_id, roads_in[i]->get_id()))
				return i;
	}
	return NO_ROAD;
}

int crossroad::get_output_road_position(std::string road_id, int x)
{
	road_ptr null_ptr;
	for (int i = 0; i < cadef::road_count; ++i)
	{
		if(roads_direct[x][i] != null_ptr)
		if(boost::algorithm::equals(road_id, roads_direct[x][i]->get_id()))
			return i;
		if(roads_opposite[x][i] != null_ptr)
		if(boost::algorithm::equals(road_id, roads_opposite[x][i]->get_id()))
			return i;
	}
	return NO_ROAD;
}
relative_direction crossroad::get_any_available_direction(int position)
{
	short dir = 0;
	int left = conversion::get_left_road_position(position);
	int right = conversion::get_right_road_position(position);
	int straight = conversion::get_straight_road_position(position);


	if(get_status(position, left) == ROAD_ABLE)
		dir += DIRECTION_LEFT;
	if(get_status(position, right) == ROAD_ABLE)
		dir += DIRECTION_RIGHT;
	if(get_status(position, straight) == ROAD_ABLE)
		dir += DIRECTION_STRAIGHT;
	switch (dir)
	{
		case 0:
			return DIRECTION_ANY;
		case 1:
			return DIRECTION_LEFT;
		case 2:
			return DIRECTION_STRAIGHT;
		case 4:
			return DIRECTION_RIGHT;
		case 5:
			return (random::std_random(0,2) == 0 ? DIRECTION_LEFT : DIRECTION_RIGHT);
		case 6:
			return (random::std_random(0,2) == 0 ? DIRECTION_STRAIGHT : DIRECTION_RIGHT);
		case 3:
			return (random::std_random(0,2) == 0 ? DIRECTION_LEFT : DIRECTION_STRAIGHT);
		case 7:
			return (random::std_random(0,2) == 0 ?
					DIRECTION_RIGHT :
					(random::std_random(0,2) == 0) ? DIRECTION_LEFT : DIRECTION_STRAIGHT);;
		default:
			break;

	}
}

road_status crossroad::get_status(int pos_x, int pos_y)
{
	return (road_status)road_mtx[pos_x][pos_y];
}

void crossroad::set_status(int pos_x, int pos_y, road_status status)
{
	set_direction_status (pos_x, pos_y, status);
	set_direction_status (pos_y, pos_x, status);
}

void crossroad::set_road_status(int position, road_status status)
{
	int x = position,
	y = conversion::get_left_road_position(position);
	set_status(x, y, status);
	y = conversion::get_straight_road_position(position);
	set_status(x, y, status);
	y = conversion::get_right_road_position(position);
	set_status(x, y, status);
}



void crossroad::set_direction_status(int pos_x, int pos_y, road_status status)
{

	road_mtx[pos_x][pos_y] = status;
}
void crossroad::print_crossroad(std::string road_id)
{
	for (int i=0;i<4;i++)
		{
		for (int j=0;j<4;j++)
			std::cout<< get_status(i,j)<<" ";
			std::cout<<" "<<std::endl;
		}

	std::cout<<get_input_road_position(road_id)<<" "<<std::endl;

}

void crossroad::set_direction_road_status(int position, road_status status)
{
	int x = position,
	y = conversion::get_left_road_position(position);
	if (get_status(x,y) != ROAD_NONE)
		set_direction_status(x, y, status);
	y = conversion::get_straight_road_position(position);
	if (get_status(x,y) != ROAD_NONE)
		set_direction_status(x, y, status);
	y = conversion::get_right_road_position(position);
	if (get_status(x,y) != ROAD_NONE)
		set_direction_status(x, y, status);
}
void crossroad::add_light_signal(lightsignal_ptr lightsignal, lightsignal_mode mode)
{
	ls = lightsignal;
	controlled = true;
	//Green
	set_direction_road_status(0,ROAD_ABLE);
	set_direction_road_status(2,ROAD_ABLE);
	//Red
	set_direction_road_status(1,ROAD_UNABLE);
	set_direction_road_status(3,ROAD_UNABLE);
	this->ls_mode = mode;

}
void crossroad::iterate()
{
	if (controlled)
	{
	if (ls->getSignal()==Green)
	{
		//std::cout<<"Зеленый"<<std::endl;
		//Green
		set_direction_road_status(0,ROAD_ABLE);
		set_direction_road_status(2,ROAD_ABLE);
		//Red
		set_direction_road_status(1,ROAD_UNABLE);
		set_direction_road_status(3,ROAD_UNABLE);
	}

	if (ls->getSignal()==GreenBlink)
	{//std::cout<<"ЗЕЛЕНЫЙМИГАЮЩИЙ"<<std::endl;

	if (ls_mode==FIXED)
	{
		//Red
		set_direction_road_status(0,ROAD_UNABLE);
		set_direction_road_status(2,ROAD_UNABLE);
		//Green
		set_direction_road_status(1,ROAD_ABLE);
		set_direction_road_status(3,ROAD_ABLE);
	}
	else
	{
		road_ptr null_ptr;
		bool left_exist=false;
		bool right_exist=false;
		bool left_free=false;
		bool right_free=false;
		bool reset=false;

		if(roads_in[1]!=null_ptr)
		{
			left_exist=true;
			if (roads_in[1]->free)
				left_free=true;

		if(roads_in[3]!=null_ptr)
		{
			right_exist=true;
			if (roads_in[3]->free)
				right_free=true;
		}

		if (left_exist && right_exist)
			if (left_free && right_free)
			{
				reset=true;
			}

		if (left_exist)
			{
			if (!right_exist)
				if (left_free)
					reset=true;
			}
		else
			if (right_exist)
				if (right_free)
					reset=true;

		if (reset)
		{
//			std::cout<<"aDAPTIVE1"<<std::endl;
			ls->setSignal(Green);
			ls->resetCounter();//включить заново
		}
		else
		{
			//Red
			set_direction_road_status(0,ROAD_UNABLE);
			set_direction_road_status(2,ROAD_UNABLE);
			//Green
			set_direction_road_status(1,ROAD_ABLE);
			set_direction_road_status(3,ROAD_ABLE);
		}

		}
	}
	}
	if (ls->getSignal()==Yellow)
		{//	std::cout<<"Желтый"<<std::endl;
		//Green
		set_direction_road_status(0,ROAD_UNABLE);
		set_direction_road_status(2,ROAD_UNABLE);
		//Red
		set_direction_road_status(1,ROAD_ABLE);
		set_direction_road_status(3,ROAD_ABLE);
		}
	if (ls->getSignal()==Red)
		{	//std::cout<<"Красный"<<std::endl;
			//Green
		set_direction_road_status(0,ROAD_UNABLE);
		set_direction_road_status(2,ROAD_UNABLE);
			//Red
		set_direction_road_status(1,ROAD_ABLE);
		set_direction_road_status(3,ROAD_ABLE);
		}
	if (ls->getSignal()==GetReady)
		{//	std::cout<<"Предупреждающий"<<std::endl;
	if (ls_mode==FIXED)
	{
		//Green
	set_direction_road_status(0,ROAD_UNABLE);
	set_direction_road_status(2,ROAD_UNABLE);
		//Red
	set_direction_road_status(1,ROAD_UNABLE);
	set_direction_road_status(3,ROAD_UNABLE);
	}
	else
	{
		road_ptr null_ptr;
		bool left_exist=false;
		bool right_exist=false;
		bool left_free=false;
		bool right_free=false;
		bool reset=false;

		if(roads_in[0]!=null_ptr)
		{
			left_exist=true;
			if (roads_in[0]->free)
				left_free=true;

		if(roads_in[2]!=null_ptr)
		{
			right_exist=true;
			if (roads_in[2]->free)
				right_free=true;
		}

		if (left_exist && right_exist)
			if (left_free && right_free)
			{
				reset=true;
			}

		if (left_exist)
			{
			if (!right_exist)
				if (left_free)
					reset=true;
			}
		else
			if (right_exist)
				if (right_free)
					reset=true;

		if (reset)
		{
//			std::cout<<"aDAPTIVE"<<std::endl;
			ls->setSignal(Red);
			ls->resetCounter();//включить заново
		}
		else
		{
			//Green
		set_direction_road_status(0,ROAD_UNABLE);
		set_direction_road_status(2,ROAD_UNABLE);
			//Red
		set_direction_road_status(1,ROAD_UNABLE);
		set_direction_road_status(3,ROAD_UNABLE);
		}

		}
	}



		}
	if (ls->getSignal()==Broken)
	{}	//std::cout<<"СЛоман"<<std::endl;
	}

}
lightsignal_ptr crossroad::get_light_signal()
{
	return ls;
}
crossroad::~crossroad()
{

}

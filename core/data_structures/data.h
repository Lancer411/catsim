/*
 	data.h - <description>

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

#ifndef DATA_H_
#define DATA_H_

enum relative_direction
{
	DIRECTION_LEFT = 1,
	DIRECTION_STRAIGHT = 2,
	DIRECTION_RIGHT = 4,
	DIRECTION_ANY = 8,
};

enum road_status
{
	ROAD_ABLE = 1,
	ROAD_UNABLE = 0,
	ROAD_NONE = -1,
};

enum vehicle_type
{
	Car = 1,
	LightTruck = 2,
	Truck = 3,
	Bus = 4,
};

typedef struct
{
	int x;
	int y;
} COORD;

enum light_signal_state
{
	Green = 0,
	GreenBlink = 1,
	Yellow = 2,
	Red = 3,
	GetReady = 4,
	Broken = 5,
};

enum distribution
{
	NORMAL,
	PUASSON,
	TRIANGLE,
};

#endif /* DATA_H_ */

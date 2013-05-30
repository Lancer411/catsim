/*
 road_marker.h - road marker class and interface to mark a road

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

#ifndef ROAD_MARKER_H_
#define ROAD_MARKER_H_
#include "abstract/observer.h"
#include "core/base/iautomat.h"
#include "core/entities/entity.h"
#include "abstract/listeners.h"

class road_marker: public observer, public entity, public iautomat
{
	int position;
	int time_interval;
	listener_void handler;
public:
	road_marker(int position, const listener_void handler)
	{
		this->position = position;
		this->handler = handler;
		this->time_interval = 0;
	};

	int get_position() const {return position;};
	int get_time_interval() const {return time_interval;};

	void handle_event()
	{
		handler->handle();
		time_interval = 0;
	};

	void iterate()
	{
		time_interval++;
	};

	~road_marker()
	{
		handler.reset();
	};
};

typedef boost::shared_ptr<road_marker> road_marker_ptr;
typedef boost::container::map<int, road_marker_ptr> marker_map;

class imarkable : private iobservable
{
	marker_map markers;
public:
	void add_marker(const road_marker_ptr marker)
	{
		markers[marker->get_position()] = marker;
	};

	void remove_marker(const road_marker_ptr marker)
	{
		int pos = marker->get_position();
		markers[pos].reset();
		markers.erase(pos);
	};

	void notify_marker(int position)
	{
		markers[position]->handle_event();
	};

	void notify_markers()
	{
		typedef marker_map::value_type marker_item;
		BOOST_FOREACH(marker_item iter, markers)
		{
			iter.second->handle_event();
		}
	};
private:
	void add_observer(const observer_ptr observer){};
	void remove_observer(const observer_ptr observer){};

	bool marker_exists(int position)
	{
		return (markers.find(position) != markers.end());
	};
};


#endif /* ROAD_MARKER_H_ */

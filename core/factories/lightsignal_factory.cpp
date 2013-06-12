/*
 * lightsignal_factory.cpp
 *
 *  Created on: 04.06.2013
 *      Author: ekaterina
 */

#include "lightsignal_factory.h"

lightsignal_factory::lightsignal_factory()
{
	id_counter = 0;
}

lightsignal_ptr lightsignal_factory:: create_lightsignal(int durationGreen, int durationYellow, int durationRed, light_signal_state currentSignal)
{
	lightsignal_ptr p(new lightsignal(durationGreen, durationYellow, durationRed, currentSignal));
	std::string id = "LIGHTSIGNAL_" + boost::lexical_cast<std::string> (id_counter++);
	p->set_id(id);
	lightsignals[id] = p;
	return p;
}
void lightsignal_factory::delete_lightsignal(std::string id)
{
	lightsignals[id].reset();
	lightsignals.erase(id);
}
lightsignal_ptr lightsignal_factory::getLightSignal(std::string id)
{
	return lightsignals[id];
}
size_t lightsignal_factory::count()
{
	return lightsignals.size();
}
void lightsignal_factory::tick()
{
	lightsignal_map::iterator it;
	for (it = lightsignals.begin(); it != lightsignals.end();++it)
	{
		it->second->tick();
	}
}
lightsignal_factory::~lightsignal_factory()
{
	lightsignals.clear();
}

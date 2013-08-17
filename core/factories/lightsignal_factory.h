/*
 * lightsignal_factory.h
 *
 *  Created on: 04.06.2013
 *      Author: ekaterina
 */

#ifndef LIGHTSIGNAL_FACTORY_H_
#define LIGHTSIGNAL_FACTORY_H_
#include "define/cadef.h"
#include "core/entities/lightsignal.h"


typedef boost::container::map<std::string, lightsignal_ptr> lightsignal_map;

class lightsignal_factory
{
	lightsignal_map lightsignals;
	long id_counter;
public:
	lightsignal_factory();
	lightsignal_ptr create_lightsignal(int durationGreen, int durationYellow, int durationRed, light_signal_state currentSignal);
	void delete_lightsignal(std::string id);
	lightsignal_ptr getLightSignal (std::string id);
	size_t count();

	void tick();
	virtual ~lightsignal_factory();
};

typedef boost::shared_ptr<lightsignal_factory> lightsignal_factory_ptr;

#endif /* LIGHTSIGNAL_FACTORY_H_ */

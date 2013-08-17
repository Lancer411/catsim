/*
 * roadnetworkmodel.h
 *
 *  Created on: Aug 17, 2013
 *      Author: naghtarr
 */

#ifndef ROADNETWORKMODEL_H_
#define ROADNETWORKMODEL_H_
#include "core/factories/road_factory.h"
#include "core/factories/vehicle_factory.h"
#include "core/factories/lightsignal_factory.h"
#include "core/connectors/vehicle_feeder.h";

class roadnetwork_model {
	road_factory_ptr roads_factory;
	vehicle_factory_ptr vehicles_factory;
	lightsignal_factory_ptr lightsignals_factory;
	vehicle_feeder_ptr vehicles_feeder;

public:
	roadnetwork_model()
	{
		roads_factory = new road_factory_ptr(new road_factory());
		vehicles_factory = new vehicle_factory_ptr(new vehicle_factory());
		lightsignals_factory = new lightsignal_factory_ptr(new lightsignal_factory);
		vehicles_feeder = new vehicle_feeder_ptr(new vehicle_feeder(vehicles_factory));
	};

	~roadnetwork_model()
	{
		roads_factory.reset();
		vehicles_factory.reset();
		lightsignals_factory.reset();
		vehicles_feeder.reset();
	};
};

#endif /* ROADNETWORKMODEL_H_ */

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
#include "core/connectors/feeder_params.h";
#include "io/road_network_data.h"

class roadnetwork_model {
	road_factory_ptr roads_factory;
	vehicle_factory_ptr vehicles_factory;
	lightsignal_factory_ptr lightsignals_factory;
	vehicle_feeder_ptr vehicles_feeder;

public:
	roadnetwork_model() :
		roads_factory(new road_factory()),
		vehicles_factory(new vehicle_factory()),
		lightsignals_factory(new lightsignal_factory()),
		vehicles_feeder(new vehicle_feeder(vehicles_factory))
	{
	};

	void build_network(road_network_data_ptr network)
	{
		raw_roads_list roads = network->get_roads();
		raw_crossroads_list crossroads = network->get_crossroads();
		raw_feeders_list feeders = network->get_feeders();
		int roads_count = roads.size();
		int crossroads_count = crossroads.size();
		int feeders_count = feeders.size();
		std::cout<<roads_count << "|" << crossroads_count<< "|" <<feeders_count <<std::endl;

		BOOST_FOREACH(raw_roads_list::value_type road, roads)
		{
			std::cout << road.id << std::endl;
			roads_factory->create_road(road.lanes, road.length, road.velocity_limit, road.id);
		}

		BOOST_FOREACH(raw_crossroads_list::value_type raw_crossroad, crossroads)
		{
			std::cout << raw_crossroad.id << std::endl;
			crossroad_ptr crossroad_p(new crossroad());
			crossroad_p->set_id(raw_crossroad.id);
			int pos = 0;
			BOOST_FOREACH(std::string id, raw_crossroad.roads_in)
			{
				if(!boost::algorithm::equals(id, RN_PARAM_NONE))
				{
					std::cout << id << std::endl;
					road_ptr road = roads_factory->get_road(id);
					crossroad_p->put_road_input(road, pos);
				}
				pos ++;
			}
			pos = 0;
			BOOST_FOREACH(std::string id, raw_crossroad.roads_out)
			{
				std::cout << id << std::endl;
				if(!boost::algorithm::equals(id, RN_PARAM_NONE))
				{
					road_ptr road = roads_factory->get_road(id);
					crossroad_p->put_road_output(road, pos);
				}
				pos ++;
			}
		}

		BOOST_FOREACH(raw_feeders_list::value_type raw_feeder, feeders)
		{
			std::cout << raw_feeder.id << std::endl;
			if(boost::algorithm::equals(raw_feeder.feeder_mode, RN_FEEDER_MODE_SAVING))
			{
				vehicles_feeder->set_transfer_mode(SAVING);
			}
			if(boost::algorithm::equals(raw_feeder.feeder_mode, RN_FEEDER_MODE_DELETING))
			{
				vehicles_feeder->set_transfer_mode(DELETING);
			}

			BOOST_FOREACH(boost::container::list<vehicle_feeder_params>::value_type raw_params, raw_feeder.params)
			{
				feeder_params_ptr params (new feeder_params(raw_params.density, raw_params.init_speed,
						raw_params.max_speed, raw_params.car_prob, raw_params.bus_prob));
				if(boost::algorithm::equals(raw_params.mode, RN_FEEDER_PARAM_MODE_INITIAL))
				{
					params->mode = INITIAL;
				}
				if(boost::algorithm::equals(raw_params.mode, RN_FEEDER_PARAM_MODE_CONTINUOUS))
				{
					params->mode = CONTINUOUS;
				}
				if(boost::algorithm::equals(raw_params.mode, RN_FEEDER_PARAM_MODE_DISTRIBUTIVE))
				{
					params->mode = DISTRIBUTIVE;
					if(boost::algorithm::equals(raw_params.distribution, RN_FEEDER_PARAM_DISTRIBUTION_UNIFORM))
					{
						params->distribution_type = UNIFORM;
					}
					if(boost::algorithm::equals(raw_params.distribution, RN_FEEDER_PARAM_DISTRIBUTION_POISSON))
					{
						params->distribution_type = POISSON;
					}
					if(boost::algorithm::equals(raw_params.distribution, RN_FEEDER_PARAM_DISTRIBUTION_TRIANGLE))
					{
						params->distribution_type = TRIANGLE;
					}
				}
				road_ptr null_ptr;
				road_ptr road = roads_factory->get_road(raw_params.road_id);
				if(road != null_ptr)
				{
					vehicles_feeder->connect_feeding_road(road, params);
				}
			}

			BOOST_FOREACH(boost::container::list<roads_pair>::value_type raw_pair, raw_feeder.roads)
			{
				if(!boost::algorithm::equals(raw_pair.feeding_road, RN_PARAM_NONE) &&
					!boost::algorithm::equals(raw_pair.deadend_road, RN_PARAM_NONE))
				{
					road_ptr null_ptr;
					road_ptr road = roads_factory->get_road(raw_pair.deadend_road);
					if(road != null_ptr)
					{
						vehicles_feeder->connect_deadend_road(road, raw_pair.feeding_road);
					}
				}
			}
		}
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

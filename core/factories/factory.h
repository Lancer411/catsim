/*
 * factory.h
 *
 *  Created on: Nov 14, 2012
 *      Author: ngh
 */

#ifndef FACTORY_H_
#define FACTORY_H_
#include "define/cadef.h"
#include <map>

//typedef std::map<std::string, T> factory_container;

//template <class T>
class factory
{
public:
	factory();
	virtual ~factory();
};

#endif /* FACTORY_H_ */

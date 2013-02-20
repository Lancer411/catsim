/*
 * entity.h
 *
 *  Created on: Oct 31, 2012
 *      Author: ngh
 */

#ifndef ENTITY_H_
#define ENTITY_H_
#include "define/cadef.h"

class entity
{
	std::string id;
public:
	std::string get_id() const {return id;};
	void set_id(std::string id){this->id = id;};
};

#endif /* ENTITY_H_ */

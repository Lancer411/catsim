/*
 * command_line.h
 *
 *  Created on: 20.03.2013
 *      Author: ekaterina
 */

#ifndef COMMAND_LINE_H_
#define COMMAND_LINE_H_
#include <boost/program_options.hpp>
#include <iostream>

class command_line {
public:
	command_line();
	virtual ~command_line();
	int parser(int ac, char* av[]);
};

#endif /* COMMAND_LINE_H_ */

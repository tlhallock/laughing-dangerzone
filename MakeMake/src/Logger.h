/*
 * Logger.h
 *
 *  Created on: Aug 13, 2014
 *      Author: thallock
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <fstream>

namespace cccfg
{

enum log_level
{
	ERROR   = 0,
	INFO    = 1,
	VERBOSE = 2,
	DEBUG   = 2,
};

class Logger
{
public:
	Logger();
	~Logger();

	void log_line(const std::string &line, log_level level);
	void log_external_cmd(const std::string line);

	std::ofstream output;
};

Logger &get_logger();

}

#endif /* LOGGER_H_ */

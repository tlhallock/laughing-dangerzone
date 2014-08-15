/*
 * Logger.cpp
 *
 *  Created on: Aug 13, 2014
 *      Author: thallock
 */

#include "Logger.h"

#include "Config.h"

#include <iostream>

namespace cccfg
{

Logger::Logger() : output("./cccfg/log.txt") {}
Logger::~Logger() {}

void Logger::log_line(const std::string &line, log_level level)
{
	if (get_config().get_log_level() >= level)
	{
		std::cout << line << std::endl;
		output << line << std::endl;
	}
}

Logger &get_logger()
{
	static Logger *logger;
	if (logger == nullptr)
	{
		logger = new Logger;
	}
	return *logger;
}

void Logger::log_external_cmd(const std::string line)
{
	output << line << std::endl;
}

}

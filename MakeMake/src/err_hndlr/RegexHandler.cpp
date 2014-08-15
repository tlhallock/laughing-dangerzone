/*
 * RegexHandler.cpp
 *
 *  Created on: Aug 14, 2014
 *      Author: thallock
 */

#include "err_hndlr/RegexHandler.h"



namespace cccfg
{


RegexHandler::RegexHandler(const std::string &reg_) : reg(reg_) {}
RegexHandler::~RegexHandler() {}

bool RegexHandler::applies(std::string error_msg)
{
	std::string::const_iterator start = error_msg.begin();
	std::string::const_iterator stop = error_msg.end();

	boost::match_results<std::string::const_iterator> what;

	if (regex_search(start, stop, what, reg))
	{
		return true;
	}

	return false;
}

bool RegexHandler::fix(const std::string& error_msg, Cmd& cmd, FileSet &files)
{
	std::string::const_iterator start = error_msg.begin();
	std::string::const_iterator stop = error_msg.end();

	boost::match_results<std::string::const_iterator> what;

	bool fixed = false;

	while (regex_search(start, stop, what, reg))
	{
		std::string symbol = what[1];
		fixed |= apply_match(what[1], cmd, files);
		start = what[0].second;
	}

	return fixed;
}

}

/*
 * RegexHandler.h
 *
 *  Created on: Aug 14, 2014
 *      Author: thallock
 */

#ifndef REGEXHANDLER_H_
#define REGEXHANDLER_H_

#include "err_hndlr/ErrorHandler.h"

#include <boost/regex.hpp>


namespace cccfg
{

class RegexHandler : public ErrorHandler
{
public:
	RegexHandler(const std::string &reg);
	virtual ~RegexHandler();

	bool applies(std::string error_msg);
	bool fix(const std::string& error_msg, Cmd& cmd, FileSet &files);

	virtual bool apply_match(const std::string &match, Cmd &cmd, FileSet &files) = 0;
private:
	boost::regex reg;
};

}

#endif /* REGEXHANDLER_H_ */

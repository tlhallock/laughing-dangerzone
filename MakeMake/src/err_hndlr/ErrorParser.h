/*
 * ErrorParser.h
 *
 *  Created on: Aug 13, 2014
 *      Author: thallock
 */

#ifndef ERRORPARSER_H_
#define ERRORPARSER_H_

#include "Compiler.h"

#include "err_hndlr/ErrorHandler.h"

#include <vector>


namespace cccfg
{

class ErrorParser
{
public:
	ErrorParser();
	~ErrorParser();

	bool handle_error(compile_stage stage, const std::string &error_msg, Cmd &cmd, FileSet &files);
private:
	std::vector<ErrorHandler *> handlers;
};

ErrorParser &get_error_parser();

}

#endif /* ERRORPARSER_H_ */

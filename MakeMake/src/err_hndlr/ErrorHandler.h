/*
 * ErrorHandler.h
 *
 *  Created on: Aug 14, 2014
 *      Author: thallock
 */

#ifndef ERRORHANDLER_H_
#define ERRORHANDLER_H_

#include "states.h"

#include <string>

namespace cccfg
{

class Cmd;
class FileSet;

class ErrorHandler
{
public:
	ErrorHandler();
	virtual ~ErrorHandler();

	virtual bool applies(compile_stage stage);
	virtual bool applies(std::string error_msg);
	virtual bool fix(const std::string &error_msg, Cmd &cmd, FileSet &files);
};

}

#endif /* ERRORHANDLER_H_ */

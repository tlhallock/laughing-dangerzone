/*
 * ErrorHandler.cpp
 *
 *  Created on: Aug 14, 2014
 *      Author: thallock
 */

#include "err_hndlr/ErrorHandler.h"


namespace cccfg
{

ErrorHandler::ErrorHandler() {}
ErrorHandler::~ErrorHandler() {}

bool ErrorHandler::applies(compile_stage stage)
{
	// by default, run
	return true;
}

bool ErrorHandler::applies(std::string error_msg)
{
	// by default, run
	return true;
}

bool ErrorHandler::fix(const std::string& error_msg, Cmd& cmd, FileSet &files)
{
	// by default, do nothing
	return false;
}

}

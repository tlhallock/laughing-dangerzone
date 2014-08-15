/*
 * UnrosolvedReferenceHandler.cpp
 *
 *  Created on: Aug 15, 2014
 *      Author: thallock
 */

#include <err_hndlr/UnrosolvedReferenceHandler.h>

namespace cccfg
{

UnrosolvedReferenceHandler::UnrosolvedReferenceHandler() :
		RegexHandler("") {}

UnrosolvedReferenceHandler::~UnrosolvedReferenceHandler() {}

bool UnrosolvedReferenceHandler::applies(compile_stage stage)
{
	return false;
}

bool UnrosolvedReferenceHandler::apply_match(const std::string& match, Cmd& cmd, FileSet& files)
{
	return false;
}

}

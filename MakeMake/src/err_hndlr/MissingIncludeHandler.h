/*
 * MissingIncludeHandler.h
 *
 *  Created on: Aug 14, 2014
 *      Author: thallock
 */

#ifndef MISSINGINCLUDEHANDLER_H_
#define MISSINGINCLUDEHANDLER_H_

#include "err_hndlr/RegexHandler.h"

namespace cccfg
{

class MissingIncludeHandler : public RegexHandler
{
public:
	MissingIncludeHandler();
	virtual ~MissingIncludeHandler();

	bool applies(compile_stage stage);
	bool apply_match(const std::string &match, Cmd &cmd, FileSet &files);
private:
	std::string find_include_path(std::string include, FileSet &files);
};

}

#endif /* MISSINGINCLUDEHANDLER_H_ */

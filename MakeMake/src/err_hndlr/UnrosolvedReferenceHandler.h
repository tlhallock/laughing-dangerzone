/*
 * UnrosolvedReferenceHandler.h
 *
 *  Created on: Aug 15, 2014
 *      Author: thallock
 */

#ifndef UNROSOLVEDREFERENCEHANDLER_H_
#define UNROSOLVEDREFERENCEHANDLER_H_

#include "err_hndlr/RegexHandler.h"

namespace cccfg {

class UnresolvedReferenceHandler : public RegexHandler
{
public:
	UnresolvedReferenceHandler();
	virtual ~UnresolvedReferenceHandler();

	bool applies(compile_stage stage);
	bool apply_match(const std::string &match, Cmd &cmd, FileSet &files);
};

} /* namespace cccfg */

#endif /* UNROSOLVEDREFERENCEHANDLER_H_ */

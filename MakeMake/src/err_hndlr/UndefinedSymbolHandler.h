/*
 * UndefinedSymbolHandler.h
 *
 *  Created on: Aug 14, 2014
 *      Author: thallock
 */

#ifndef UNDEFINEDSYMBOLHANDLER_H_
#define UNDEFINEDSYMBOLHANDLER_H_

#include "err_hndlr/RegexHandler.h"

#include "Cmd.h"



namespace cccfg
{


class UndefinedSymbolHandler : public RegexHandler
{
public:
	UndefinedSymbolHandler();
	virtual ~UndefinedSymbolHandler();

	bool applies(compile_stage stage);
	bool apply_match(const std::string &match, Cmd &cmd, FileSet &files);
};


}
#endif /* UNDEFINEDSYMBOLHANDLER_H_ */

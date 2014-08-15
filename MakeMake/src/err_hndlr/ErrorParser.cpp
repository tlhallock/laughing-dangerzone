/*
 * ErrorParser.cpp
 *
 *  Created on: Aug 13, 2014
 *      Author: thallock
 */

#include "ErrorParser.h"

#include "Compiler.h"
#include "Logger.h"

#include "err_hndlr/MissingIncludeHandler.h"
#include "err_hndlr/UndefinedSymbolHandler.h"
#include "err_hndlr/UnrosolvedReferenceHandler.h"

namespace cccfg
{

ErrorParser& get_error_parser()
{
	static ErrorParser *parser;
	if (parser == nullptr)
	{
		parser = new ErrorParser;
	}
	return *parser;
}

ErrorParser::ErrorParser()
{
	handlers.push_back(new MissingIncludeHandler);
	handlers.push_back(new UndefinedSymbolHandler);
	handlers.push_back(new UnrosolvedReferenceHandler);
}

ErrorParser::~ErrorParser()
{
	auto end = handlers.end();
	for (auto it = handlers.begin(); it != end; ++it)
	{
		delete *it;
	}
}

bool ErrorParser::handle_error(compile_stage stage, const std::string &error_msg, Cmd& cmd, FileSet &files)
{
	bool fixed = false;

	auto end = handlers.end();
	for (auto it = handlers.begin(); it != end; ++it)
	{
		ErrorHandler *handler = *it;

		if (!handler->applies(stage))
		{
			continue;
		}
		if (!handler->applies(error_msg))
		{
			continue;
		}

		fixed |= handler->fix(error_msg, cmd, files);
	}

	return fixed;
}

}

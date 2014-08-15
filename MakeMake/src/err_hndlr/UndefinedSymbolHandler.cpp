/*
 * UndefinedSymbolHandler.cpp
 *
 *  Created on: Aug 14, 2014
 *      Author: thallock
 */

#include "err_hndlr/UndefinedSymbolHandler.h"

#include "Logger.h"
#include "History.h"

#include <iostream>
#include <memory>

namespace cccfg
{

namespace
{
	class UserDefine : public Option
	{
	public:
		UserDefine() : Option("Define the value yourself.", "") {}
		~UserDefine() {}

		void selected()
		{
			std::cout << "Please type the value exactly how you would like it defined: " << std::endl;

			std::string answer;
			std::cin >> answer;

			std::cout << "You chose: '" << answer << "'" << std::endl;
			serialization = answer;
		}
	};
}



UndefinedSymbolHandler::UndefinedSymbolHandler() :
	RegexHandler("error: ...([^ ]*)... was not declared in this scope") {}

UndefinedSymbolHandler::~UndefinedSymbolHandler() {}

bool UndefinedSymbolHandler::applies(compile_stage stage)
{
	return stage == COMPILE;
}

bool UndefinedSymbolHandler::apply_match(const std::string &symbol, Cmd& cmd, FileSet &files)
{
	get_logger().log_line("Found missing symbol: '" + symbol + "'", INFO);

	Decision *d = get_history().create_decision("Undefined symbol: '" + symbol + "'");
	std::unique_ptr<Decision> dptr(d);

	d->add_option(new UserDefine);
	d->add_option(new Option("Define as '\"" + symbol + "\"'", "\"" + symbol + "\""));
	d->add_option(new Option("Define as 0", "0"));
	d->add_option(new Option("Define as 1", "1"));

	Option *o = d->decide();
	if (o == nullptr)
	{
		return false;
	}

	cmd.define(symbol, o->get_serialization());
	return true;
}

}

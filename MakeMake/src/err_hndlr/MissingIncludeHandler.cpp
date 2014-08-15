/*
 * MissingIncludeHandler.cpp
 *
 *  Created on: Aug 14, 2014
 *      Author: thallock
 */

#include "err_hndlr/MissingIncludeHandler.h"

#include "Logger.h"
#include "System.h"
#include "files/FileSet.h"
#include "Cmd.h"

#include "err_hndlr/History.h"

#include <memory>

namespace cccfg
{

namespace
{
	void handle_no_include_possible(std::string include)
	{
		if (true)
		{
			get_logger().log_line("Skipping finding package for now...", DEBUG);
			return;
		}


		RunResult result = run_system_cmd("apt-file search " + include);

		get_logger().log_line("Unable to resolve include: " + include, ERROR);

		if (result.output.size() != 0)
		{
			get_logger().log_line("Perhaps these packages would help?", ERROR);
			get_logger().log_line(result.output, ERROR);
		}
	}
}

MissingIncludeHandler::MissingIncludeHandler() :
	RegexHandler("[^:]*:[0-9]*:[0-9]*: fatal error: ([^:]*): No such file or directory") {}

MissingIncludeHandler::~MissingIncludeHandler() {}

bool MissingIncludeHandler::applies(compile_stage stage)
{
	return stage == COMPILE;
}

bool MissingIncludeHandler::apply_match(const std::string &include, Cmd& cmd, FileSet &files)
{
	get_logger().log_line("Missing include: '" + include + "'", INFO);

	std::string include_path = find_include_path(include, files);
	if (include_path.length() == 0)
	{
		handle_no_include_possible(include);
		return false;
	}
	else
	{
		get_logger().log_line("Found include path: " + include_path, INFO);
		cmd.include(nullptr, include_path);
		return true;
	}
}

std::string MissingIncludeHandler::find_include_path(std::string include, FileSet &files)
{
	if (include.at(0) != '/')
	{
		include = "/" + include;
	}

	std::map<HeaderFile *, std::string> header_files;

	std::string last_include;

	auto end = files.headers().end();
	for (auto it = files.headers().begin(); it != end; ++it)
	{
		HeaderFile *header = *it;
		std::string satisfied = header->satisfy(include);
		if (satisfied.size() != 0)
		{
			header_files.insert(std::pair<HeaderFile *, std::string>(header, satisfied));
			last_include = satisfied;
		}
	}

	if (header_files.size() == 1)
	{
		return last_include;
	}

	Decision *d = get_history().create_decision("Missing include: " + include);
	std::unique_ptr<Decision> dptr(d);

	auto aend = header_files.end();
	for (auto it = header_files.begin(); it != aend; ++it)
	{
		d->add_option(new Option("Include header file at path '" + it->first->get_path() + "'.", it->second));
	}

	Option *o = d->decide();
	if (o == nullptr)
	{
		return "";
	}

	return o->get_serialization();
}

}

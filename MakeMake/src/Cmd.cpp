/*
 * Cmd.cpp
 *
 *  Created on: Aug 14, 2014
 *      Author: thallock
 */

#include "Cmd.h"

#include "files/LibraryFile.h"
#include "files/HeaderFile.h"
#include "files/SourceFile.h"
#include "files/ObjectFile.h"

#include "Logger.h"
#include "Config.h"

#include <sstream>


namespace cccfg
{

Cmd::Cmd(const std::string& c) : cmd(c) {}
Cmd::~Cmd() {}

std::string Cmd::to_string() const
{
	std::stringstream cmdstream;

	cmdstream << cmd << " ";

	auto end = options.end();
	for (auto it = options.begin(); it != end; ++it)
	{
		cmdstream << *it << " ";
	}

	return cmdstream.str();
}

void Cmd::static_link(const LibraryFile *lib)
{
	if (lib == nullptr)
	{
		return;
	}
	add_option(lib->get_path());
}

void Cmd::dynamic_link(const LibraryFile *lib)
{
	if (lib == nullptr)
	{
		return;
	}
	// not implemented...
	get_logger().log_line("Dynamic link not implemented...", ERROR);
}

void Cmd::include(const HeaderFile *header, const std::string &rel_path)
{
	add_option("-I " + rel_path);
}

void Cmd::add_source(const SourceFile *source)
{
	if (source == nullptr)
	{
		return;
	}
	add_option("-c " + source->get_path());
}

void Cmd::add_output(const std::string &path)
{
	add_option("-o " + path);
}

void Cmd::define(const std::string& key, const std::string& value)
{
	add_option( "-D" + key + "='" + value + "'");
}

void Cmd::add_object(const ObjectFile* object)
{
	if (object == nullptr)
	{
		return;
	}
	add_option(object->get_path());
}

void Cmd::add_option(const std::string& o)
{
	options.push_back(o);
}

bool Cmd::has_content() const
{
	return to_string().size() != 0;
}

Cmd create_compile_cmd()
{
	Cmd cmd{get_config().get_compile_cmd()};

	auto end = get_config().get_global_compiler_options().end();
	for (auto it = get_config().get_global_compiler_options().begin(); it != end; ++it)
	{
		cmd.add_option(*it);
	}

	return cmd;
}

Cmd create_solink_cmd()
{
	std::cout << "Not yet supported." << std::endl;
	exit(-1);
//	return Cmd{get_config().get_link_cmd()};
}

Cmd create_archive_cmd()
{
	return Cmd{get_config().get_link_cmd()};
}




}

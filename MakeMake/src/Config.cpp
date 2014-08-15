/*
 * Config.cpp
 *
 *  Created on: Aug 13, 2014
 *      Author: thallock
 */

#include "Config.h"

#include <sstream>


namespace cccfg
{

Config::Config() {}
Config::~Config() {}

const std::string Config::get_cplusplusfilt() const
{
	return compiler_prefix + "c++filt";
}

static int next_cmd;
const std::string Config::get_tmp_cmd_file() const
{
	char file[256];
	sprintf(file, "./cmds/scratch.%d.txt", next_cmd++);
	return std::string(file);
}

const std::string Config::get_compile_cmd() const
{
	return compiler_prefix + "g++";
}

log_level Config::get_log_level() const
{
	return cccfg::DEBUG;
}

const std::string Config::get_object_directory() const
{
	return "./objects";
}

const std::string Config::get_library_file() const
{
	return "static_library.a";
}

const std::string Config::get_link_cmd() const
{
	return compiler_prefix + "ar cvr " + get_library_file() + " ";
}


static long exe_num;
const std::string Config::get_exe_name(const std::string& source) const
{
	std::stringstream s;
	s << "./output/";
	s << source.substr(source.find_last_of("/") + 1, source.find_last_of("."));
	s << ".";
	s << exe_num++;
	s << ".out";
	return s.str();
}

void Config::set_compiler_prefix(const std::string prefix)
{
	compiler_prefix = prefix;
}


Config& get_config()
{
	static Config *config;
	if (config == nullptr)
	{
		config = new Config;
	}
	return *config;
}

void Config::add_global_option(const std::string& key, const std::string& value)
{
}

const std::set<std::string>& Config::get_source_extensions() const
{
	static std::set<std::string> exts;
	if (exts.size() == 0)
	{
		exts.insert(".c");
		exts.insert(".cc");
		exts.insert(".cpp");
	}
	return exts;
}

const std::set<std::string>& Config::get_library_extensions() const
{
	static std::set<std::string> exts;
	if (exts.size() == 0)
	{
		exts.insert(".a");
		exts.insert(".so");
	}
	return exts;
}

const std::set<std::string>& Config::get_header_extensions() const
{
	static std::set<std::string> exts;
	if (exts.size() == 0)
	{
		exts.insert(".h");
		exts.insert(".hpp");
		exts.insert(".inl");
	}
	return exts;
}

}

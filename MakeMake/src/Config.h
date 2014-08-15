/*
 * Config.h
 *
 *  Created on: Aug 13, 2014
 *      Author: thallock
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "states.h"
#include "Logger.h"

#include <set>

namespace cccfg
{

class Config
{
public:
	Config();
	~Config();

	// COMMANDS
	const std::string get_compile_cmd() const;
	const std::string get_cplusplusfilt() const;
	const std::string get_link_cmd() const;

	// OUTPUT
	const std::string get_library_file() const;
	const std::string get_tmp_cmd_file() const;
	const std::string get_object_directory() const;
	const std::string get_exe_name(const std::string &source) const;

	// OTHER
	log_level get_log_level() const;

	void set_compiler_prefix(const std::string prefix);
	void add_global_compiler_option(const std::string& option);
	const std::set<std::string>& get_global_compiler_options();

	const std::set<std::string> &get_source_extensions() const;
	const std::set<std::string> &get_library_extensions() const;
	const std::set<std::string> &get_header_extensions() const;

private:
	std::string compiler_prefix;
	std::set<std::string> global_compiler_options;
};


Config &get_config();

}

#endif /* CONFIG_H_ */

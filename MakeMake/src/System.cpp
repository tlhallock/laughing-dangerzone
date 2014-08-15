/*
 * System.cpp
 *
 *  Created on: Aug 13, 2014
 *      Author: thallock
 */

#include "System.h"

#include "Config.h"
#include "Logger.h"
#include "Cmd.h"
#include "files/FileSet.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <stdlib.h>
#include <alloca.h>


namespace cccfg
{

RunResult::RunResult(int code, std::string out) :
		status_code(code),
		output(out) {}

RunResult::~RunResult() {}

bool RunResult::successful()
{
	return status_code == 0;
}

RunResult run_system_cmd(const Cmd& cmd, bool need_output)
{
	return run_system_cmd(cmd.to_string(), need_output);
}

RunResult run_system_cmd(const std::stringstream &stream, bool need_output)
{
	return run_system_cmd(stream.str(), need_output);
}

RunResult run_system_cmd(const std::string &str, bool need_output)
{
	std::string output_file = get_config().get_tmp_cmd_file();
	get_logger().log_line("Saving cmd to '" + output_file + "': " + str, INFO);
	cccfg::ensure_directory_for_file(output_file);

	int status_code;
	{
		char *cmd = (char *) alloca (10 + str.size() + 2 * output_file.size());
		sprintf(cmd, "%s 2>%s 1>%s", str.c_str(), output_file.c_str(), output_file.c_str());
		status_code = system(cmd);
	}

	std::string output;
	if (need_output)
	{
		std::stringstream buffer;
		std::ifstream in_file(output_file);
		std::string line;
		while (std::getline(in_file, line))
		{
			buffer << line << "\n";
		}

		output = buffer.str();

		get_logger().log_external_cmd(output);
	}

	return RunResult(status_code, output);
}

}

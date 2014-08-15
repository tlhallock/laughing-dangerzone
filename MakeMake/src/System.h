/*
 * System.h
 *
 *  Created on: Aug 13, 2014
 *      Author: thallock
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <sstream>


namespace cccfg
{

class Cmd;

class RunResult
{
public:
	RunResult(int code, std::string out);
	~RunResult();

	int status_code;
	std::string output;

	bool successful();
};

RunResult run_system_cmd(const Cmd &cmd,                  bool need_output = true);
RunResult run_system_cmd(const std::stringstream &stream, bool need_output = true);
RunResult run_system_cmd(const std::string &str,          bool need_output = true);

}

#endif /* SYSTEM_H_ */

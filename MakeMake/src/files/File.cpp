/*
 * File.cpp
 *
 *  Created on: Aug 13, 2014
 *      Author: thallock
 */

#include "File.h"

#include "Logger.h"

#include <sstream>


namespace cccfg
{

File::File(const std::string &path_) :
	path(path_),
	failed(false) {}

File::~File() {}

const std::string& File::get_path() const
{
	return path;
}

void File::error()
{
	failed = true;
}

bool File::has_error()
{
	return failed;
}

void File::add_to_fileset(FileSet &fileset)
{
	get_logger().log_line("Unable to add file " + get_path(), ERROR);
}

void File::add_to_cmd(compile_stage stage, Cmd& cmd) {}

}

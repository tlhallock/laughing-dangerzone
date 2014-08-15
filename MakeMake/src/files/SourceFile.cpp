/*
 * SourceFile.cpp
 *
 *  Created on: Aug 13, 2014
 *      Author: thallock
 */

#include "SourceFile.h"

#include "Config.h"
#include "FileSet.h"
#include "Cmd.h"
#include "System.h"

#include <sstream>


namespace cccfg
{

SourceFile::SourceFile(const std::string &path) :
	File(path) {}

SourceFile::~SourceFile() {}

void SourceFile::add_to_cmd(compile_stage stage, Cmd& cmd)
{
	if (has_error())
	{
		return;
	}

	switch(stage)
	{
	case COMPILE:
		cmd.add_source(this);
		cmd.add_output(get_output_file());
		break;
	default:
		break;
	}
}

std::string SourceFile::get_output_file() const
{
	std::string no_ext = get_path().substr(0, get_path().find_last_of("."));
	std::string output_path = get_config().get_object_directory() + "/" + no_ext + ".o";
	ensure_directory_for_file(output_path);
	return output_path;
}

void SourceFile::add_to_fileset(FileSet& fileset)
{
	fileset.add_source(this);
}

}

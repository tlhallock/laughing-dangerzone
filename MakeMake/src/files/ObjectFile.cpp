/*
 * ObjectFile.cpp
 *
 *  Created on: Aug 14, 2014
 *      Author: thallock
 */

#include "files/ObjectFile.h"

#include "files/FileSet.h"
#include "Cmd.h"
#include "Config.h"


namespace cccfg
{

ObjectFile::ObjectFile(const std::string &path) : CompiledFile(path) {}
ObjectFile::~ObjectFile() {}
void ObjectFile::add_to_fileset(FileSet& fileset) { fileset.add_object(this); }

void ObjectFile::add_to_cmd(compile_stage stage, Cmd& cmd)
{
	std::string outpath;

	switch (stage)
	{
	case MAKE_EXES:
		outpath = get_config().get_exe_name(get_path());
		ensure_directory_for_file(outpath);
		cmd.add_output(outpath);
	case STATIC_LINK:
	case SO_LINK:
		cmd.add_object(this);
		break;
	default:
		break;
	}
}

}

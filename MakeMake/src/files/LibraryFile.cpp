/*
 * Library.cpp
 *
 *  Created on: Aug 13, 2014
 *      Author: thallock
 */

#include "LibraryFile.h"

#include "FileSet.h"
#include "Cmd.h"


namespace cccfg
{

LibraryFile::LibraryFile(const std::string &path) :
	CompiledFile(path) {}
LibraryFile::~LibraryFile() {}
void LibraryFile::add_to_fileset(FileSet& fileset) { fileset.add_library(this); }

void LibraryFile::add_to_cmd(compile_stage stage, Cmd& cmd)
{
	switch (stage)
	{
	case STATIC_LINK:
	case SO_LINK:
	case MAKE_EXES:
		link(cmd);
		break;
	default:
		break;
	}
}

SharedObjectFile::SharedObjectFile(const std::string& path) : LibraryFile(path) {}
SharedObjectFile::~SharedObjectFile() {}
void SharedObjectFile::link(Cmd& cmd) { cmd.dynamic_link(this); }

ArchiveFile::ArchiveFile(const std::string& path) : LibraryFile(path) {}
ArchiveFile::~ArchiveFile() {}
void ArchiveFile::link(Cmd& cmd) { cmd.static_link(this); }


}

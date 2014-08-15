/*
 * Library.h
 *
 *  Created on: Aug 13, 2014
 *      Author: thallock
 */

#ifndef LIBRARY_H_
#define LIBRARY_H_

#include "files/CompiledFile.h"

namespace cccfg
{

class LibraryFile : public CompiledFile
{
public:
	void add_to_cmd(compile_stage stage, Cmd &cmd);
	void add_to_fileset(FileSet &fileset);
protected:
	LibraryFile(const std::string &path);
	virtual ~LibraryFile();

	virtual void link(Cmd &cmd) = 0;
};

class ArchiveFile : public LibraryFile
{
public:
	ArchiveFile(const std::string &path);
	~ArchiveFile();
protected:
	void link(Cmd &cmd);
};


class SharedObjectFile : public LibraryFile
{
public:
	SharedObjectFile(const std::string &path);
	~SharedObjectFile();
protected:
	void link(Cmd &cmd);
};

}

#endif /* LIBRARY_H_ */

/*
 * ObjectFile.h
 *
 *  Created on: Aug 14, 2014
 *      Author: thallock
 */

#ifndef OBJECTFILE_H_
#define OBJECTFILE_H_

#include "files/CompiledFile.h"


namespace cccfg
{

class ObjectFile : public CompiledFile
{
public:
	ObjectFile(const std::string &path);
	~ObjectFile();

	void add_to_fileset(FileSet &fileset);
	void add_to_cmd(compile_stage stage, Cmd &cmd);
};

}

#endif /* OBJECTFILE_H_ */

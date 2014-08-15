/*
 * SourceFile.h
 *
 *  Created on: Aug 13, 2014
 *      Author: thallock
 */

#ifndef SOURCEFILE_H_
#define SOURCEFILE_H_

#include "files/File.h"
#include "files/HeaderFile.h"

#include <set>
#include <map>


namespace cccfg
{

class SourceFile : public File
{
public:
	SourceFile(const std::string &path);
	~SourceFile();

	void add_to_cmd(compile_stage stage, Cmd &cmd);
	void add_to_fileset(FileSet &fileset);

	/** This should return an object file object **/
	std::string get_output_file() const;
protected:
	/** should be shared with library files (there should actually be object file) **/
	void dump_methods();
};

}

#endif /* SOURCEFILE_H_ */

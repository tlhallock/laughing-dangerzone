/*
 * File.h
 *
 *  Created on: Aug 13, 2014
 *      Author: thallock
 */

#ifndef FILE_H_
#define FILE_H_

#include "states.h"

#include <string>


namespace cccfg
{

class FileSet;
class Cmd;

class File
{
public:
	File(const std::string &path);
	virtual ~File();

	const std::string &get_path() const;

	bool has_error();
	void error();

	bool has_main();
	bool has_method(const std::string& method_signature);

	virtual void add_to_fileset(FileSet &fileset);
	virtual void add_to_cmd(compile_stage stage, Cmd &cmd);
private:
	std::string path;
	bool failed;
};

}

#endif /* FILE_H_ */

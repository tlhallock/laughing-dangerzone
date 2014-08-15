/*
 * FileManager.h
 *
 *  Created on: Aug 13, 2014
 *      Author: thallock
 */

#ifndef FILEMANAGER_H_
#define FILEMANAGER_H_

#include <set>
#include <string>

#include "files/FileSet.h"

namespace cccfg
{

class Compiler
{
public:
	Compiler();
	~Compiler();

	void execute();

	void print_uncompiled();

	FileSet &get_files();
private:
	void compile();
	void link();
	void make_exes();

	FileSet files;
};

}


#endif /* FILEMANAGER_H_ */

/*
 * HeaderFile.h
 *
 *  Created on: Aug 13, 2014
 *      Author: thallock
 */

#ifndef HEADERFILE_H_
#define HEADERFILE_H_

#include "files/File.h"



namespace cccfg
{

class HeaderFile : public File
{
public:
	HeaderFile(const std::string &path);
	virtual ~HeaderFile();

	void add_to_fileset(FileSet &fileset);

	std::string satisfy(const std::string& include);
};


}

#endif /* HEADERFILE_H_ */

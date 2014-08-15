/*
 * HeaderFile.cpp
 *
 *  Created on: Aug 13, 2014
 *      Author: thallock
 */

#include "HeaderFile.h"

#include "files/FileFactory.h"

#include "FileSet.h"


namespace cccfg
{

HeaderFile::HeaderFile(const std::string &path) :
	File(path) {}

HeaderFile::~HeaderFile() {}

void HeaderFile::add_to_fileset(FileSet& fileset)
{
	fileset.add_header(this);
}

std::string HeaderFile::satisfy(const std::string& include)
{
	str_ends_with(get_path(), include);
	int start = (int) get_path().size() - (int) include.size();
	if (start <= 0)
	{
		return "";
	}

	std::string suffix = get_path().substr(start, get_path().length());
	if (suffix != include)
	{
		return "";
	}

	return get_path().substr(0, start);
}


}

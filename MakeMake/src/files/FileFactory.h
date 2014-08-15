/*
 * FileFactory.h
 *
 *  Created on: Aug 14, 2014
 *      Author: thallock
 */

#ifndef FILEFACTORY_H_
#define FILEFACTORY_H_

#include "files/File.h"

#include <set>

namespace cccfg
{

class FileFactory
{
public:
	bool handles_path(const std::string &path) const;
	virtual File *create_file(const std::string &path) const = 0;
	const std::set<std::string> &get_extensions() const;
protected:
	FileFactory(const std::string &ext);
	FileFactory(const std::set<std::string> &exts);
	virtual ~FileFactory();
private:
	void add_extension(std::string ext);
	std::set<std::string> extensions;
};

bool str_ends_with(const std::string &long_string, const std::string &suffix);
std::string str_cut(const std::string &larger, const std::string &suffix);

std::set<std::string> get_known_extensions();
cccfg::File *create_file(const std::string &path);

}

#endif /* FILEFACTORY_H_ */

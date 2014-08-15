/*
 * CompiledFile.h
 *
 *  Created on: Aug 14, 2014
 *      Author: thallock
 */

#ifndef COMPILEDFILE_H_
#define COMPILEDFILE_H_

#include "files/File.h"

#include <set>

namespace cccfg
{

class CompiledFile : public File
{
public:
	CompiledFile(const std::string &path);
	virtual ~CompiledFile();

	const std::set<std::string> &get_methods();

	bool has_main();
	bool has_method(const std::string& method_signature);

	bool duplicates(CompiledFile *other);
private:
	void dump_methods();
	std::set<std::string> methods;
};

}

#endif /* COMPILEDFILE_H_ */

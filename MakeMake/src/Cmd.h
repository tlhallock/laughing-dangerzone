/*
 * Cmd.h
 *
 *  Created on: Aug 14, 2014
 *      Author: thallock
 */

#ifndef CMD_H_
#define CMD_H_

#include <vector>
#include <string>

namespace cccfg
{

class LibraryFile;
class SourceFile;
class HeaderFile;
class ObjectFile;

class Cmd
{
public:
	Cmd(const std::string &c);
	virtual ~Cmd();

	virtual std::string to_string() const;

	void static_link(const LibraryFile *lib);
	void dynamic_link(const LibraryFile *lib);
	void include(const HeaderFile *header, const std::string &rel_path);
	void add_source(const SourceFile *source);
	void add_object(const ObjectFile *object);
	void define(const std::string& key, const std::string& value);

	void add_output(const std::string &path);
	void add_option(const std::string &o);

	bool has_content() const;
private:
	std::string cmd;
	std::vector<std::string> options;
};

}

#endif /* CMD_H_ */

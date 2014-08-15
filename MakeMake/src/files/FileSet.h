/*
 * FileSet.h
 *
 *  Created on: Aug 14, 2014
 *      Author: thallock
 */

#ifndef FILESET_H_
#define FILESET_H_

#include "files/SourceFile.h"
#include "files/HeaderFile.h"
#include "files/LibraryFile.h"
#include "files/ObjectFile.h"

#include <set>
#include <map>

namespace cccfg
{

void ensure_directory_for_file(const std::string path);

class FileSet
{
public:
	FileSet();
	~FileSet();

	void add_source(SourceFile *f);
	void add_header(HeaderFile *f);
	void add_library(LibraryFile *f);
	void add_object(ObjectFile *object);

	const std::set<SourceFile*>  &sources() const;
	const std::set<HeaderFile*>  &headers() const;
	const std::set<ObjectFile*>  &objects() const;
	const std::set<LibraryFile*> &libs() const;
	const std::map<std::string, File *> &all_files() const;

	void add_files(const std::string& path, const std::set<std::string>& exts);

	// convenience
	void add_path_to_includes(const std::string &path);
	void add_path_to_link(const std::string &path);
	void add_path_to_source(const std::string &path);

	File *get_file(const std::string &path);
private:
	void list_files(const std::string &path, const std::set<std::string> &extensions);

	std::set<SourceFile*>  m_sources;
	std::set<HeaderFile*>  m_headers;
	std::set<LibraryFile*> m_libraries;
	std::set<ObjectFile*>  m_objects;
//	std::set<ArchiveFile*> m_generated_archives;  <-- useful when there are duplicates...
	std::map<std::string, File *> m_all_files;
};

}

#endif /* FILESET_H_ */

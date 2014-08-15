/*
 * FileSet.cpp
 *
 *  Created on: Aug 14, 2014
 *      Author: thallock
 */

#include "files/FileSet.h"

#include "Logger.h"
#include "Config.h"
#include "files/FileFactory.h"
#include "System.h"

#include <sstream>

#include <alloca.h>


namespace cccfg
{

FileSet::FileSet() {}
FileSet::~FileSet() {}

const std::set<SourceFile*> &FileSet::sources() const
{
	return m_sources;
}

const std::set<HeaderFile*> &FileSet::headers() const
{
	return m_headers;
}

const std::set<LibraryFile*> &FileSet::libs() const
{
	return m_libraries;
}

const std::map<std::string, File *> &FileSet::all_files() const
{
	return m_all_files;
}

void FileSet::add_source(SourceFile* f)
{
	if (f == nullptr)
	{
		return;
	}
	get_logger().log_line("Found source: " + f->get_path(), DEBUG);
	m_sources.insert(f);
	m_all_files.insert(std::pair<std::string, File *>(f->get_path(), f));
}

void FileSet::add_header(HeaderFile* f)
{
	if (f == nullptr)
	{
		return;
	}
	get_logger().log_line("Found header: " + f->get_path(), DEBUG);
	m_headers.insert(f);
	m_all_files.insert(std::pair<std::string, File *>(f->get_path(), f));
}

void FileSet::add_library(LibraryFile* f)
{
	if (f == nullptr)
	{
		return;
	}
	get_logger().log_line("Found library: " + f->get_path(), DEBUG);
	m_libraries.insert(f);
	m_all_files.insert(std::pair<std::string, File *>(f->get_path(), f));
}

void FileSet::add_object(ObjectFile* object)
{
	if (object == nullptr)
	{
		return;
	}
	get_logger().log_line("Found object file: " + object->get_path(), DEBUG);
	m_objects.insert(object);
	m_all_files.insert(std::pair<std::string, ObjectFile *>(object->get_path(), object));
}

const std::set<ObjectFile*>& FileSet::objects() const
{
	return m_objects;
}

void FileSet::list_files(const std::string &path, const std::set<std::string> &extensions)
{
	std::stringstream cmdstream;
	cmdstream << "find $(realpath ";
	cmdstream << path;
	cmdstream << ") -type f ";

	if (extensions.size() != 0)
	{
		auto end = extensions.end();
		auto it = extensions.begin();

		cmdstream << " -name *" << *it << " ";

		for (; it != end; ++it)
		{
			cmdstream << " -o -name *" << *it << " ";
		}
	}

	RunResult result = run_system_cmd(cmdstream);

	std::stringstream files(result.output);

	std::string file;
	while (std::getline(files, file))
	{
		File *file_object = create_file(file);
		if (file_object == nullptr)
		{
			return;
		}
		file_object->add_to_fileset(*this);
	}
}

void FileSet::add_files(const std::string& path, const std::set<std::string>& exts)
{
	list_files(path, exts);
}

void FileSet::add_path_to_includes(const std::string& path)
{
	add_files(path, get_config().get_header_extensions());
}

void FileSet::add_path_to_link(const std::string& path)
{
	add_files(path, get_config().get_library_extensions());
}

void FileSet::add_path_to_source(const std::string& path)
{
	std::set<std::string> exts;
	exts.insert(get_config().get_header_extensions().begin(), get_config().get_header_extensions().end());
	exts.insert(get_config().get_source_extensions().begin(), get_config().get_source_extensions().end());
	add_files(path, exts);
}

File* FileSet::get_file(const std::string& path)
{
	auto it = m_all_files.find(path);
	if (it == m_all_files.end())
	{
		return nullptr;
	}
	return it->second;
}


void ensure_directory_for_file(const std::string path)
{
	char *cmd = (char *) alloca(path.size() + 20);
	sprintf(cmd, "mkdir -p $(dirname %s)", path.c_str());
	get_logger().log_line("Making directory for " + path, DEBUG);
	system(cmd);
}

}

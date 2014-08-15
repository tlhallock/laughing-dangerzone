/*
 * FileFactory.cpp
 *
 *  Created on: Aug 14, 2014
 *      Author: thallock
 */

#include "files/FileFactory.h"

#include "files/SourceFile.h"
#include "files/HeaderFile.h"
#include "files/LibraryFile.h"
#include "files/ObjectFile.h"

#include "Logger.h"
#include "Config.h"

#include <vector>

namespace cccfg
{

namespace
{
	const std::vector<const FileFactory *> &get_factories()
	{
		class SourceFileFactory : public FileFactory
		{
		public:
			SourceFileFactory() : FileFactory(get_config().get_source_extensions()) {}
			~SourceFileFactory() {}

			File *create_file(const std::string &path) const { return new SourceFile(path); }
		};

		class HeaderFileFactory : public FileFactory
		{
		public:
			HeaderFileFactory() : FileFactory(get_config().get_header_extensions()) {}
			~HeaderFileFactory() {}

			File *create_file(const std::string &path) const { return new HeaderFile(path); }
		};

		class ArchiveFileFactory : public FileFactory
		{
		public:
			ArchiveFileFactory() : FileFactory(".a") {}
			~ArchiveFileFactory() {}

			File *create_file(const std::string &path) const { return new ArchiveFile(path); }
		};

		class SharedFileFactory : public FileFactory
		{
		public:
			SharedFileFactory() : FileFactory(".so") {}
			~SharedFileFactory() {}

			File *create_file(const std::string &path) const { return new SharedObjectFile(path); }
		};

		class ObjectFileFactory : public FileFactory
		{
		public:
			ObjectFileFactory() : FileFactory(".o") {}
			~ObjectFileFactory() {}

			File *create_file(const std::string &path) const { return new ObjectFile(path); }
		};

		static std::vector<const FileFactory *> factories;
		if (factories.size() == 0)
		{
			factories.push_back(new SourceFileFactory);
			factories.push_back(new HeaderFileFactory);
			factories.push_back(new ArchiveFileFactory);
			factories.push_back(new SharedFileFactory);
			factories.push_back(new ObjectFileFactory);
		}
		return factories;
	}
}

std::set<std::string> get_known_extensions()
{
	std::set<std::string> ret_value;
	auto end = get_factories().end();
	for (auto it = get_factories().begin(); it != end; ++it)
	{
		const FileFactory *factory = *it;
		ret_value.insert(factory->get_extensions().begin(), factory->get_extensions().end());
	}
	return ret_value;
}

File* create_file(const std::string& path)
{
	auto end = get_factories().end();
	for (auto it = get_factories().begin(); it != end; ++it)
	{
		const FileFactory *factory = *it;
		if (!factory->handles_path(path))
		{
			continue;
		}
		return factory->create_file(path);
	}
	get_logger().log_line("Do not know how to create file for " + path, DEBUG);
	return nullptr;
}

FileFactory::FileFactory(const std::string &ext) { add_extension(ext); }
FileFactory::FileFactory(const std::set<std::string> &exts)
{
	extensions.insert(exts.begin(), exts.end());
}
FileFactory::~FileFactory() {}

void FileFactory::add_extension(std::string allocator)
{
	if (allocator.at(0) != '.')
	{
		get_logger().log_line("WARNING: adding extension that does not end in a '.'!", ERROR);
	}
	extensions.insert(allocator);
}

bool FileFactory::handles_path(const std::string& path) const
{
	auto end = extensions.end();
	for (auto it = extensions.begin(); it != end; ++it)
	{
		if (str_ends_with(path, *it))
		{
			return true;
		}
	}
	return false;
}

const std::set<std::string>& FileFactory::get_extensions() const
{
	return extensions;
}








bool str_ends_with(const std::string &long_string, const std::string &suffix)
{
	auto start = long_string.size() - suffix.size();
	if (start <= 0)
	{
		return false;
	}

	std::string longer_suffix = long_string.substr(start, long_string.size());
	if (longer_suffix != suffix)
	{
		return false;
	}

	return true;
}

std::string str_cut(const std::string &larger, const std::string &suffix)
{
	if (!str_ends_with(larger, suffix))
	{
		return "";
	}

	return larger.substr(0, larger.size() - suffix.size());
}

}

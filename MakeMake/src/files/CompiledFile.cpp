/*
 * CompiledFile.cpp
 *
 *  Created on: Aug 14, 2014
 *      Author: thallock
 */

#include "files/CompiledFile.h"

#include "Config.h"
#include "System.h"

namespace cccfg
{

CompiledFile::CompiledFile(const std::string &path) : File{path} {}
CompiledFile::~CompiledFile() {}


bool CompiledFile::has_main()
{
	return has_method("main");
}

bool CompiledFile::has_method(const std::string& method_signature)
{
	auto it = get_methods().find(method_signature);
	if (it == get_methods().end())
	{
		return false;
	}

	return true;
}
const std::set<std::string> &CompiledFile::get_methods()
{
	if (methods.size() <= 0)
	{
		dump_methods();
	}
	return methods;
}

bool CompiledFile::duplicates(CompiledFile* other)
{
	auto oend = other->get_methods().end();

	auto end = get_methods().end();
	for (auto it = get_methods().begin(); it != end; ++it)
	{
		std::string method = *it;
		if (other->get_methods().find(method) != oend)
		{
			return true;
		}
	}

	return false;
}

void CompiledFile::dump_methods()
{
	if (methods.size() > 0)
	{
		return;
	}

	RunResult result = run_system_cmd("readelf -Ws "
			+ get_path()
			+ " | grep -v UND "
			+ " | grep FUNC "
#if 0
			+ " | " + get_config().get_cplusplusfilt()
#endif
			+ " | awk ' { $1=$2=$3=$4=$5=$6=$7=\"\"; print $0} ' | sed 's/^[ \t]*//' | sed 's/[ \t]*$//' ");

	std::stringstream methods_file(result.output);

	std::string method;
	while (std::getline(methods_file, method))
	{
		methods.insert(method);
	}
}

}

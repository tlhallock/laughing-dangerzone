/*
 * FileManager.cpp
 *
 *  Created on: Aug 13, 2014
 *      Author: thallock
 */

#include "Compiler.h"

#include "Cmd.h"
#include "Config.h"
#include "System.h"
#include "err_hndlr/ErrorParser.h"
#include "files/FileSet.h"
#include "files/FileFactory.h"

#include <sstream>
#include <stdlib.h>

namespace cccfg
{

Compiler::Compiler() {}
Compiler::~Compiler() {}

void Compiler::compile()
{
	auto end = get_files().sources().end();
	for (auto it = get_files().sources().begin(); it != end; ++it)
	{
		Cmd cmd(get_config().get_compile_cmd());

		SourceFile *file = *it;
		file->add_to_cmd(COMPILE, cmd);

		get_logger().log_line("Compiling " + file->get_path(), INFO);

		for (;;)
		{
			RunResult result = run_system_cmd(cmd);
			if (result.successful())
			{
				get_logger().log_line("OK.", INFO);
				create_file(file->get_output_file())->add_to_fileset(files);
				break;
			}

			bool fixed = get_error_parser().handle_error(COMPILE, result.output, cmd, get_files());
			if (!fixed)
			{
				get_logger().log_line("Skipping " + file->get_path(), ERROR);
				file->error();
				break;
			}

			get_logger().log_line("New compile command: '" + cmd.to_string() + "'", INFO);
		}
	}
}

void Compiler::link()
{
	Cmd cmd(get_config().get_link_cmd());

	auto end = get_files().objects().end();
	for (auto it = get_files().objects().begin(); it != end; ++it)
	{
		CompiledFile *file = *it;

		if (file->has_main())
		{
			continue;
		}
		if (file->has_error())
		{
			continue;
		}

		file->add_to_cmd(STATIC_LINK, cmd);

		get_logger().log_line("Linking " + file->get_path(), DEBUG);
	}

	// TODO: no duplicate methods...

	for (;;)
	{
		RunResult result = run_system_cmd(cmd);
		if (result.successful())
		{
			get_logger().log_line("link OK.", cccfg::INFO);
			break;
		}

		bool fixed = get_error_parser().handle_error(STATIC_LINK, result.output, cmd, get_files());
		if (!fixed)
		{
			get_logger().log_line("Unable to link!", ERROR);
			break;
		}

		get_logger().log_line("New link command: '" + cmd.to_string() + "'", INFO);
	}
}

void Compiler::make_exes()
{
	auto end = get_files().objects().end();
	for (auto it = get_files().objects().begin(); it != end; ++it)
	{
		ObjectFile *object = *it;
		if (!object->has_main())
		{
			continue;
		}

		if (object->has_error())
		{
			continue;
		}

		get_logger().log_line("Making exe from " + object->get_path(), INFO);

		Cmd cmd(get_config().get_compile_cmd());

		object->add_to_cmd(MAKE_EXES, cmd);
		cmd.add_option(get_config().get_library_file());

		run_system_cmd(cmd, false);
	}
}

void Compiler::print_uncompiled()
{
	auto end = get_files().sources().end();
	for (auto it = get_files().sources().begin(); it != end; ++it)
	{
		SourceFile *source = *it;
		if (!source->has_error())
		{
			continue;
		}

		get_logger().log_line("E: !! Error compiling: " + source->get_path(), INFO);
	}
}

FileSet& Compiler::get_files()
{
	return files;
}

void Compiler::execute()
{
	compile();
	link();
	make_exes();
}

}

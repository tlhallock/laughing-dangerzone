/*
 * main.cpp
 *
 *  Created on: Aug 13, 2014
 *      Author: thallock
 */

#include "Config.h"
#include "Compiler.h"

int main(int argc, char **argv)
{
	// TODO: check for realpath, readelf, dirname, find, mkdir

	// add priorities to includes
	// add save to file option for decisions...

	// set configs to be local for a directory
	// serialize configs/cmds
	// don't put duplicate methods in an archive/so

//	cccfg::get_config().set_compiler_prefix("arm-cortex-linux-gnueabi-");

	cccfg::get_config().add_global_compiler_option(" -std=c++11 ");


	cccfg::Compiler compiler;

	compiler.get_files().add_path_to_link("/usr/lib/x86_64-linux-gnu/");
	compiler.get_files().add_path_to_includes("/usr/include");

	compiler.get_files().add_path_to_source("./");

	compiler.execute();

	compiler.print_uncompiled();

	return 0;
}

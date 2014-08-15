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

	// set configs to be local for a directory
	// serialize configs/cmds
	// don't put duplicate methods in an archive/so

	cccfg::get_config().set_compiler_prefix("arm-cortex-linux-gnueabi-");

	cccfg::Compiler compiler;

	compiler.get_files().add_path_to_source("/work/cgicc/cgicc-3.2.9/");
	compiler.get_files().add_path_to_source("/home/thallock/Documents/Source/C/cgi/another.cpp");

	compiler.execute();

	compiler.print_uncompiled();

	return 0;
}

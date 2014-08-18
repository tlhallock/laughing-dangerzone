/*
 * main.cpp
 *
 *  Created on: Aug 13, 2014
 *      Author: thallock
 */

#include "Config.h"
#include "Compiler.h"
#include "files/FileSet.h"

static void add_this_project(cccfg::FileSet &files)
{
		cccfg::get_config().add_global_compiler_option(" -std=c++11 ");

		files.add_path_to_link("/usr/lib/x86_64-linux-gnu/");
		files.add_path_to_includes("/usr/include");

		files.add_path_to_source("./");
}


static void add_hnav_stuff(cccfg::FileSet &files)
{
	cccfg::get_config().set_compiler_prefix("/media/thallock/0e53aea8-0c7a-4c02-9cba-f283a18835ba/work/rdk/twc-rdk-root/sdk/src/open_source_archive/linux/toolchains/gcc-4.7.3_glibc-x86_64/bin/arm-cortex-linux-gnueabi-");
//	cccfg::get_config().set_compiler_prefix("arm-cortex-linux-gnueabi-");

	files.add_path_to_source("/work/twc-rdk-root/tpc/iarm-bridge/src/");
//	files.add_path_to_source("/work/twc-rdk-root/tpc/iarm-bridge/src/SWUpgradeManagerClient.cpp");

	files.add_path_to_includes("/work/twc-rdk-root/");
//	files.add_path_to_includes("/work/twc-rdk-root/tpc/iarm-bridge/");
}

static void add_cgi_to(cccfg::FileSet &files)
{
	cccfg::get_config().set_compiler_prefix("/media/thallock/0e53aea8-0c7a-4c02-9cba-f283a18835ba/work/rdk/twc-rdk-root/sdk/src/open_source_archive/linux/toolchains/gcc-4.7.3_glibc-x86_64/bin/arm-cortex-linux-gnueabi-");

	files.add_path_to_source("/work/cgicc/cgicc-3.2.9/");
	files.add_path_to_source("/work/cgicc/mine/another.cpp");
}

int main(int argc, char **argv)
{
	// TODO: check for realpath, readelf, dirname, find, mkdir

	// add priorities to includes
	// add save to file option for decisions...

	// set configs to be local for a directory
	// serialize configs/cmds
	// don't put duplicate methods in an archive/so


	cccfg::Compiler compiler;
	add_cgi_to(compiler.get_files());
	compiler.execute();
	compiler.print_uncompiled();

	return 0;
}

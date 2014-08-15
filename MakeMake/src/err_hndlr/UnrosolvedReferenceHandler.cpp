/*
 * UnrosolvedReferenceHandler.cpp
 *
 *  Created on: Aug 15, 2014
 *      Author: thallock
 */

#include <err_hndlr/UnrosolvedReferenceHandler.h>

namespace cccfg
{

#if 0

RegexHandler.cpp:(.text._ZN5boost12regex_searchIN9__gnu_cxx17__normal_iteratorIPKcSsEESaINS_9sub_matchIS5_EEEcNS_12regex_traitsIcNS_16cpp_regex_traitsIcEEEEEEbT_SD_RNS_13match_resultsISD_T0_EERKNS_11basic_regexIT1_T2_EENS_15regex_constants12_match_flagsESD_[_ZN5boost12regex_searchIN9__gnu_cxx17__normal_iteratorIPKcSsEESaINS_9sub_matchIS5_EEEcNS_12regex_traitsIcNS_16cpp_regex_traitsIcEEEEEEbT_SD_RNS_13match_resultsISD_T0_EERKNS_11basic_regexIT1_T2_EENS_15regex_constants12_match_flagsESD_]+0xa2): undefined reference to `boost::re_detail::perl_matcher<__gnu_cxx::__normal_iterator<char const*, std::string>, std::allocator<boost::sub_match<__gnu_cxx::__normal_iterator<char const*, std::string> > >, boost::regex_traits<char, boost::cpp_regex_traits<char> > >::find()'



#endif

UnresolvedReferenceHandler::UnresolvedReferenceHandler() :
		RegexHandler("\\.text\\.([a-zA-Z0-9_])*[^\n]*\\): undefined reference to `") {}

UnresolvedReferenceHandler::~UnresolvedReferenceHandler() {}

bool UnresolvedReferenceHandler::applies(compile_stage stage)
{
	switch(stage)
	{
	case SO_LINK:
	case MAKE_EXES:
		return true;
	default:
		return false;
	}
}

bool UnresolvedReferenceHandler::apply_match(const std::string& match, Cmd& cmd, FileSet& files)
{
	std::cout << "Found undefined reference: " << match << std::endl;

	auto end = files.libs().end();
	for (auto it = files.libs().begin(); it != end; ++it)
	{
		// need to ask if it has the method BEFORE it goes through c++filt.
	}
	return false;
}

}

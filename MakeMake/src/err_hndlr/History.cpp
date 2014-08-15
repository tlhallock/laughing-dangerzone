/*
 * Decision.cpp
 *
 *  Created on: Aug 14, 2014
 *      Author: thallock
 */

#include "err_hndlr/History.h"

#include "Logger.h"

#include <string>

namespace cccfg
{

History& get_history()
{
	static History *history;
	if (history == nullptr)
	{
		history = new History;
	}
	return *history;
}

Option::Option(const std::string& display_text_, const std::string& serialization_) :
	display_text(display_text_),
	serialization(serialization_) {}

Option::Option(Option* o) :
		display_text(o->get_display()),
		serialization(o->get_serialization()) {}

Option::~Option() {}

void Option::selected() {}

const std::string& Option::get_display()
{
	return display_text;
}

const std::string& Option::get_serialization()
{
	return serialization;
}

Decision::Decision(History* h_, const std::string& problem_) :
		h(h_),
		problem(problem_) {}

Decision::~Decision()
{
	auto end = options.end();
	for (auto it = options.begin(); it != end; ++it)
	{
		delete *it;
	}
}

void Decision::add_option(Option* o)
{
	options.push_back(o);
}

History::History() {}
History::~History() {}

Decision* History::create_decision(const std::string& problem)
{
	return new Decision(this, problem);
}

void History::resolve(const std::string& problem, Option* o)
{
	resolutions.insert(std::pair<std::string, Option *> (problem, o));
}

static std::string to_string(int i)
{
	char integer[256];
	sprintf(integer, "%d", i);
	return std::string(integer);
}

Option* Decision::decide()
{
	auto it = get_history().get_resolutions().find(problem);
	if (it != get_history().get_resolutions().end())
	{
		return it->second;
	}

	if (options.size() == 0)
	{
		return nullptr;
	}

	std::cout << "There is a problem compiling, the problem has multiple solutions." << std::endl;
	std::cout << "The problem is: " << problem << std::endl;
	std::cout << "There are " << options.size() << " solutions." << std::endl;
	std::cout << "Enter the number of the solution you would like to choose: " << std::endl;

	Option *option = nullptr;
	bool solved = false;
	do
	{
		std::cout << "-1: quit." << std::endl;
		int i = 0;
		auto end = options.end();
		for (auto it = options.begin(); it != end; ++it)
		{
			std::cout << i++ << ": " << (*it)->get_display() << std::endl;
		}


		int answer;
		std::cin >> answer;
		if (answer < -1 || answer >= (int) options.size())
		{
			std::cout << "Found " << answer << " which is not valid." << std::endl;
			std::cout << "Again, your options were: " << std::endl;
			continue;
		}

		solved = true;
		if (answer < 0)
		{
			std::cout << "Quitting" << std::endl;
			exit(-1);
		}

		option = options.at(answer);
	} while (!solved);

	std::cout << "You chose: " << option->get_display() << std::endl;
	option->selected();

	int answer = -1;
	do
	{
		std::cout << "Would you like to save this option?" << std::endl;
		std::cout << "Enter 0 for no and 1 for yes:" << std::endl;

		std::cin >> answer;
	} while (answer != 0 && answer != 1);

	get_logger().log_line("Decision made. decision='" + problem
			+ "', number of options='" + to_string(options.size())
			+ "', option chose display text='" + option->get_display()
			+ "', option chose serialization='" + option->get_serialization()
			+ "', save='" + to_string(answer)
			+ "'", INFO);

	if (answer)
	{
		h->resolve(problem, new Option(option));
	}

	return option;
}

void History::load(std::ifstream& in) {}
void History::save(std::ofstream& out) {}

const std::map<std::string, Option*>& History::get_resolutions()
{
	return resolutions;
}

}

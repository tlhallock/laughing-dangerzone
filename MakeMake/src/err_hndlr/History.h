/*
 * Decision.h
 *
 *  Created on: Aug 14, 2014
 *      Author: thallock
 */

#ifndef DECISION_H_
#define DECISION_H_

#include <map>
#include <fstream>
#include <iostream>
#include <vector>

namespace cccfg
{

class Option;
class Decision;
class History;

class Option
{
public:
	Option(const std::string &display_text,
			const std::string &serialization);
	Option(Option *o);

	virtual ~Option();

	const std::string &get_display();
	const std::string &get_serialization();

	virtual void selected();
private:
	std::string display_text;
protected:
	std::string serialization;
};

class Decision
{
public:
	Decision(History *h, const std::string &problem);
	virtual ~Decision();

	void add_option(Option *o);

	Option *decide();
private:
	History *h;
	std::string problem;
	std::vector<Option *> options;
};

class History
{
public:
	History();
	virtual ~History();

	Decision *create_decision(const std::string &problem);

	void resolve(const std::string &problem, Option *o);

	void load(std::ifstream &in);
	void save(std::ofstream &out);

	const std::map<std::string, Option *> &get_resolutions();
private:
	std::map<std::string, Option*> resolutions;
};

History &get_history();

}

#endif /* DECISION_H_ */

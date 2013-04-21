/*
 * OutputObject.h
 *
 *  Created on: Apr 21, 2013
 *      Author: kristof
 */

#ifndef OUTPUTOBJECT_H_
#define OUTPUTOBJECT_H_

#include <iostream>
#include <string>

class OutputObject {
private:
	std::ostream& output;
	bool html;

public:
	OutputObject(std::ostream&, bool);
	virtual ~OutputObject();

	std::ostream& getOutput();
	void print(std::string);
	void closeHTML();
	bool getHTML();
};

#endif /* OUTPUTOBJECT_H_ */

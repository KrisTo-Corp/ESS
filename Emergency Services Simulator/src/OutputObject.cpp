/*
 * OutputObject.cpp
 *
 *  Created on: Apr 21, 2013
 *      Author: kristof
 */

#include "OutputObject.h"

OutputObject::OutputObject(std::ostream& stream, bool web) : output(stream){
	html = web;

	if (html) {
		output << "<!DOCTYPE html>" << std::endl;
		output << "<html>" << std::endl;
			output << "<head>" << std::endl;
				output << "<title>KrisTo corp Emergency Services Simulator</title>" << std::endl;
				output << "<body>" << std::endl;
				output << "<h1>Emergency Services Simulator</h1>" << std::endl;
					// New content will be added in the body.
//				o.print("</body>" << std::endl);
//			o.print("</head>" << std::endl);
//		o.print("</html>" << std::endl);

	}
}

OutputObject::~OutputObject() {
	// TODO Auto-generated destructor stub
}

void OutputObject::print(std::string s) {
	if (!html) {
		output << s;
	}
	else {
		output << "<p>" << s << "</p>";
	}
}

void OutputObject::closeHTML() {
	if (html) {
				output << "</body>" << std::endl;
				output << "</head>" << std::endl;
		output << "</html>" << std::endl;
	}
	else {
		std::cerr << "Output was not in HTML!" << std::endl;
	}
}

bool OutputObject::getHTML() {
	return html;
}

std::ostream& OutputObject::getOutput() {
	return output;
}

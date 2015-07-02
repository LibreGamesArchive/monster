/*
 * Copyright (c) 2007, Trent Gamblin
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY <copyright holder> ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <copyright holder> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "xml.h"
#include <cstring>

XMLData::XMLData(std::string* name, FILE* f) :
	file(f),
	debug(false),
	ungot(-1),
	ungotReady(false)
{
	this->name = new std::string(name->c_str());
}

XMLData::XMLData(char* filename) throw (ReadError) :
	debug(false),
	ungot(-1),
	ungotReady(false)

{
	name = new std::string("main");

	file = fopen(filename, "r");
	if (!file) {
		delete name;
		throw new ReadError();
	}

	read();

	fclose(file);
}

XMLData::XMLData(char* name, char* value) :
	debug(false)
{
	this->name = new std::string(name);
	this->value = std::string(value);
}

void XMLData::add(XMLData* node)
{
	nodes.push_back(node);
}

XMLData* XMLData::find(std::string name)
{
	std::list<XMLData*>::iterator it = nodes.begin();

	while (it != nodes.end()) {
		if (*(*it)->name == name) {
			return *it;
		}
		it++;
	}

	return 0;
}

std::string& XMLData::getValue()
{
	return value;
}

XMLData::~XMLData()
{
	std::list<XMLData*>::iterator it = nodes.begin();

	while (it != nodes.end()) {
		XMLData* node = *it;
		delete node;
		it++;
	}

	delete name;
}

std::string* XMLData::readToken()
{
	if (feof(file)) {
		return 0;
	}

	int c;

	/* Skip whitespace */

	for (;;) {
		c = get();
		if (c == EOF) {
			return 0;
		}
		if (!isspace(c)) {
			break;
		}
	}

	/* Found tag */

	if (c == '<') {
		if (debug)
			std::cout << "Found tag start/end\n";
		std::string token;
		token += c;
		for (;;) {
			c = get();
			if (c == EOF) {
				break;
			}
			token += c;
			if (c == '>')
				break;
		}
		if (debug)
			std::cout << "Read <token>: " << token << "\n";
		return new std::string(token);
	}
	/* Found data */
	else {
		std::string data;
		data += c;
		for (;;) {
			c = get();
			if (c == EOF) {
				break;
			}
			if (c == '<') {
				unget(c);
				break;
			}
			data += c;
		}
		if (debug)
			std::cout << "Read data: " << data << "\n";
		return new std::string(data);
	}

	return 0;
}

int XMLData::get()
{
	int c;

	if (ungotReady) {
		c = ungot;
		ungotReady = false;
	}
	else {
		c = fgetc(file);
	}

	return c;
}

void XMLData::unget(int c)
{
	ungot = c;
	ungotReady = true;
}

void XMLData::read()
{
	// read until EOF or end token
	
	for (;;) {
		std::string* token;
		token = readToken();
		if (!token || (token && !strncmp(token->c_str(), "</", 2))) {
			if (token) {
				delete token;
			}
			return;
		}
		if (token->c_str()[0] == '<') {
			if (debug) {
				std::cout << "Reading sub tag\n";
			}
			std::string* name = getName(token);
			if (debug)
				std::cout << "Token is " << name->c_str() << "\n";
			XMLData* newdata = new XMLData(name, file);
			delete name;
			newdata->read();
			nodes.push_back(newdata);
		}
		else {
			value += token->c_str();
		}
		delete token;
	}
}

std::string* XMLData::getName(std::string* token)
{
	std::string* s = new std::string;
	
	for (int i = 1; token->c_str()[i] != '>' && token->c_str()[i]; i++) {
		if (debug)
			std::cout << "Read character " << i << "\n";
		*s += token->c_str()[i];
	}

	return s;
}

void XMLData::write(std::ofstream& out, int tabs = 0)
{
	if (value == "") {
		for (int i = 0; i < tabs; i++) {
			out << "\t";
		}

		out << "<" << name->c_str() << ">" << std::endl;

		std::list<XMLData*>::iterator it = nodes.begin();

		while (it != nodes.end()) {
			XMLData* node = dynamic_cast<XMLData*>(*it);
			node->write(out, tabs+1);
			it++;
		}

		for (int i = 0; i < tabs; i++) {
			out << "\t";
		}

		out << "</" << name->c_str() << ">" << std::endl;
	}
	else {
		for (int i = 0; i < tabs; i++) {
			out << "\t";
		}

		out << "<" << name->c_str() << ">";

		out << value;
		
		std::list<XMLData*>::iterator it = nodes.begin();

		while (it != nodes.end()) {
			XMLData* node = dynamic_cast<XMLData*>(*it);
			node->write(out, tabs+1);
			it++;
		}

		out << "</" << name->c_str() << ">" << std::endl;
	}
}

/*
void XMLData::write(std::ofstream& out, int tabs = 0)
{
	if (value == "") {
		out << "<" << name->c_str() << ">";

		std::list<XMLData*>::iterator it = nodes.begin();

		while (it != nodes.end()) {
			XMLData* node = dynamic_cast<XMLData*>(*it);
			node->write(out, tabs+1);
			it++;
		}

		out << "</" << name->c_str() << ">";
	}
	else {
		out << "<" << name->c_str() << ">";

		out << value;
		
		std::list<XMLData*>::iterator it = nodes.begin();

		while (it != nodes.end()) {
			XMLData* node = dynamic_cast<XMLData*>(*it);
			node->write(out, tabs+1);
			it++;
		}

		out << "</" << name->c_str() << ">";
	}
}
*/

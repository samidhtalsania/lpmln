#include "Parser.h"
#include "FOLParser.h"
#include "ASPParser.h"
#include "Config.h"

#pragma once

class ParserFactory
{
public:
	~ParserFactory(){
		if(p)
			delete p;
	}
	static Parser* getParser(ParserType);

private:
	static Parser* p;
};
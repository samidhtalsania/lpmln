#include "Parser.h"
#include "FOLParser.h"
#include "ASPParser.h"
#include "MVSMParser.h"
#include "Config.h"

#pragma once

class ParserFactory
{
public:
	ParserFactory();
	~ParserFactory();
	static Parser* getParser(ParserType);
	static void free();

private:
	static Parser* p;
};
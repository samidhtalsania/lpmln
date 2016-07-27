#include "FOLLexer.h"
#include "ASPLexer.h"
#include "MVSMLexer.h"
#include "Config.h"
#include "Lexer.h"

#pragma once

class LexerFactory
{
public:
	LexerFactory();
	~LexerFactory(){
		if(l)
			delete l;
	}

	static Lexer* getLexer(ParserType);

private:
	static Lexer* l;
};
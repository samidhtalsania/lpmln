#include "FOLLexer.h"
#include "ASPLexer.h"
#include "MVSMLexer.h"
#include "F2LPLexer.h"
#include "Config.h"
#include "Lexer.h"

#pragma once

class LexerFactory
{
public:
	LexerFactory();
	~LexerFactory();

	static Lexer* getLexer(ParserType);
	static void free();

private:
	static Lexer* l;
};
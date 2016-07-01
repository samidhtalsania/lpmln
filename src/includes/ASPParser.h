#include "Parser.h"
#include "ASPParserGrammar.h"
#include <memory>
#include <stdlib.h> 
#pragma once

class ASPParser: public Parser
{
public:
	
	void Parse(int yymajor,Token* yyminor, Tree* tree){
		ASPParserGrammar(parser, yymajor, yyminor, tree);
	}

	void ParseTrace(FILE* TraceFILE, char* zTracePrompt){
		ASPParserGrammarTrace(TraceFILE, zTracePrompt);		
	}

	void ParseAlloc(){
		parser = ASPParserGrammarAlloc(malloc);
	}

	void ParseFree(){
		ASPParserGrammarFree(parser, free);
	}

private:
	void* parser;
};
#include "Parser.h"
#include "FOLParserGrammar.h"
#include <memory>
#include <stdlib.h> 
#pragma once

class FOLParser: public Parser
{
public:
	
	void Parse(int yymajor,Token* yyminor, Tree* tree){
		FOLParserGrammar(parser, yymajor, yyminor, tree);
	}

	void ParseTrace(FILE* TraceFILE, char* zTracePrompt){
		FOLParserGrammarTrace(TraceFILE, zTracePrompt);		
	}

	void ParseAlloc(){
		parser = FOLParserGrammarAlloc(malloc);
	}

	void ParseFree(){
		FOLParserGrammarFree(parser, free);
	}

private:
	void* parser;
};
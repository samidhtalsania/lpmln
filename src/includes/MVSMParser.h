#include "Parser.h"
#include "MVSMParserGrammar.h"
#include <memory>
#include <stdlib.h> 
#pragma once

class MVSMParser: public Parser
{
public:
	
	void Parse(int yymajor,Token* yyminor, Tree* tree){
		MVSMParserGrammar(parser, yymajor, yyminor, tree);
	}

	void ParseTrace(FILE* TraceFILE, char* zTracePrompt){
		MVSMParserGrammarTrace(TraceFILE, zTracePrompt);		
	}

	void ParseAlloc(){
		parser = MVSMParserGrammarAlloc(malloc);
	}

	void ParseFree(){
		MVSMParserGrammarFree(parser, free);
	}

private:
	void* parser;
};
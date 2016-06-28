#include "Parser.h"
#include <memory>
#include <stdlib.h> 

#pragma once


class ASPParser: public Parser
{
public:
	
	void Parse(int yymajor,Token* yyminor, Tree* tree){
		
	}

	void ParseTrace(FILE* TraceFILE, char* zTracePrompt){
	
	}

	void ParseAlloc(){
	
	}

	void ParseFree(){
	
	}

private:
	void* parser;
};
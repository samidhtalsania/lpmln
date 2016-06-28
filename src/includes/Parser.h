#pragma once
#include "Token.h"
#include "Tree.h"

class Parser
{
public:
	void showInfo(){
		std::cout<<"Nothing to show\n";
	}

	virtual ~Parser(){};

	virtual void Parse(int, Token* , Tree*) = 0;
	virtual void ParseAlloc() = 0;
	virtual void ParseFree() = 0;
	virtual void ParseTrace(FILE*, char*) = 0;
};
#include <string>
#include <memory>
#include "Config.h"
#include "Tree.h"
#include "Token.h"
#include "Parser.h"
#include "Lexer.h"

#pragma once

class ParserWrapper
{
public:
	ParserWrapper(Config);
	~ParserWrapper();

	int parse();

private:
	void parseComplete();
	void print(std::string);


	bool debug = true;
	Translation translation;
	ParserType parserType;
	OptimizationLevel level;
	std::string inputFile;
	FILE* pFile;
	Parser* parser;
	Lexer* lexer;
	Tree* tree;
	std::vector<Token*> v;
	/*TODO fix this*/
	bool isFOLlexer;
	
};
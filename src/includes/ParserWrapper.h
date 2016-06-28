#include <string>
#include <memory>
#include "Config.h"
#include "Tree.h"
#include "Token.h"
#include "Parser.h"

#pragma once

class ParserWrapper
{
public:
	ParserWrapper(Config);
	~ParserWrapper();

	int parse();

private:
	void parseComplete();
	bool debug = true;
	Translation translation;
	std::string inputFile;
	const std::string testFile = "lpmln_test.log";
	FILE* pFile;
	// void *parser;
	Parser* parser;
	Tree* tree;
	std::vector<Token*> v;
	
};
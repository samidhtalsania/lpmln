#include <string>
#include "Config.h"
#include "Tree.h"

class ParserWrapper
{
public:
	ParserWrapper(Config);
	~ParserWrapper();

	int parse();

private:

	void parseComplete();

	bool debug = false;
	Translation translation;
	std::string inputFile;
	const std::string testFile = "lpmln_test.log";
	FILE* pFile;
	void *parser;
	Tree* tree;
	
};
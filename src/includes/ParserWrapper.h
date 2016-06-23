#include <string>
#include "Config.h"
#include "Tree.h"
#include "Token.h"

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
	void *parser;
	Tree* tree;
	std::vector<Token*> v;
	
};
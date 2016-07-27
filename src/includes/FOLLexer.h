#include "Lexer.h"
#include "Constants.h"

class FOLLexer: public Lexer
{
public:
	int Tokenize(const char * yycursor, int len , lexeme_t* lexeme);
};
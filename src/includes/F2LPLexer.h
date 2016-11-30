#include "Lexer.h"
#include "Constants.h"

class F2LPLexer: public Lexer
{
public:
	int Tokenize(const char * yycursor, int len , lexeme_t* lexeme);
};
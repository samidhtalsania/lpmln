#include "Lexer.h"
#include "Constants.h"

class ASPLexer: public Lexer
{
public:
	int Tokenize(const char * yycursor, int len , lexeme_t* lexeme);
};
#include "FOLLexer.h"
#include "exceptions/syntax_exception.h"
#define YYCURSOR lexeme->current
int FOLLexer::Tokenize(const char * yycursor, int len , lexeme_t* lexeme){
	if (lexeme->current >= (YYCURSOR + len)) {
        return 0;
    }
    lexeme->start = lexeme->current;

    const char * YYMARKER;
    
	
	/*!re2c
		WS						= [ \t\v\f];
		NL						= [\n];
		
		"."						{ return FOL_PARSE_TOKEN_DOT; }
		'\000'              	{ return 0; }
		[0-9]+					{ return FOL_PARSE_TOKEN_NUMBER; }
		"not"|"NOT"				{ return FOL_PARSE_TOKEN_NEGATION;}
		[a-zA-Z]+[a-zA-Z0-9]*	{ return FOL_PARSE_TOKEN_STRING; }
		"=>"                	{ return FOL_PARSE_TOKEN_IMPLICATION; }
		"<="					{ return FOL_PARSE_TOKEN_REVERSE_IMPLICATION; }
		"}"						{ return FOL_PARSE_TOKEN_RPAREN; }
		"{"						{ return FOL_PARSE_TOKEN_LPAREN; }
		"="						{ return FOL_PARSE_TOKEN_EQUAL; }
		"("						{ return FOL_PARSE_TOKEN_LBRACKET; }
		")"						{ return FOL_PARSE_TOKEN_RBRACKET; }
		","						{ return FOL_PARSE_TOKEN_COMMA; }
		"^"|","					{ return FOL_PARSE_TOKEN_CONJUNCTION; }
		WS+ "v"{1} WS+ 			{
									while(*(lexeme->start) != 'v') lexeme->start++;
									while(*(lexeme->current) != 'v') lexeme->current--;
									lexeme->current++; 
									return FOL_PARSE_TOKEN_DISJUNCTION;
								}

		"-"						{ return FOL_PARSE_TOKEN_MINUS;}
		
		"!"						{ return FOL_PARSE_TOKEN_NEGATION;}
		
		WS						{ return -1; }
		NL						{ return FOL_PARSE_TOKEN_NEWLINE; }	
		*						{
									std::string str(--lexeme->current,0,1);
									throw syntax_exception("Syntax Error - Unexpected "+ str +"\n");
								}
								
	*/
}
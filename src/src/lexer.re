#include "lexer.h"
#include "Parser.h"
#include "exceptions/syntax_exception.h"
#include "Constants.h"

#include <iostream>


int lexer::tokenize(const char * YYCURSOR, int len , lexeme_t* lexeme)
{

 	if (lexeme->current >= (YYCURSOR + len)) {
        return 0;
    }
    lexeme->start = lexeme->current;

    const char * YYMARKER;
	
	#define YYCTYPE		char
	#define YYFILL(n)	{}
    #define YYLIMIT		YYCURSOR+len
    #define YYCURSOR 	lexeme->current

	/*!re2c
	

		WS						= [ \t\v\f];
		NL						= [\n];
		
		"."						{ return PARSE_TOKEN_DOT; }
		'\000'              	{ return 0; }
		[0-9]+					{ return PARSE_TOKEN_NUMBER; }
		[a-zA-Z]+[a-zA-Z0-9]*	{ return PARSE_TOKEN_STRING; }
		"=>"                	{ return PARSE_TOKEN_IMPLICATION; }
		"<="					{ return PARSE_TOKEN_REVERSE_IMPLICATION; }
		"}"						{ return PARSE_TOKEN_RPAREN; }
		"{"						{ return PARSE_TOKEN_LPAREN; }
		"="						{ return PARSE_TOKEN_EQUAL; }
		"("						{ return PARSE_TOKEN_LBRACKET; }
		")"						{ return PARSE_TOKEN_RBRACKET; }
		","						{ return PARSE_TOKEN_COMMA; }
		"^"						{ return PARSE_TOKEN_CONJUNCTION; }
		WS+ "v"{1} WS+ 			{
									while(*(lexeme->start) != 'v') lexeme->start++;
									while(*(lexeme->current) != 'v') lexeme->current--;
									lexeme->current++; 
									return PARSE_TOKEN_DISJUNCTION;
								}

		"-"						{ return PARSE_TOKEN_MINUS;}
		
		"!"						{ return PARSE_TOKEN_NEGATION;}
		
		WS						{ return PARSE_TOKEN_WS; }
		NL						{ return PARSE_TOKEN_NEWLINE; }	
		*						{
									std::string str(--lexeme->current,0,1);

									throw syntax_exception("Syntax Error - Unexpected "+ str +"\n");
								}
								
	*/


}
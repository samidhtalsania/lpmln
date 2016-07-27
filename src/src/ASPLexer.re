#include "ASPLexer.h"
#include "exceptions/syntax_exception.h"

int ASPLexer::Tokenize(const char * YYCURSOR, int len , lexeme_t* lexeme)
{

 	if (lexeme->current >= (YYCURSOR + len)) {
        return 0;
    }
    lexeme->start = lexeme->current;

    const char * YYMARKER;
	
	// #define YYCTYPE		char
	// #define YYFILL(n)	{}
 //    #define YYLIMIT		YYCURSOR+len
    #define YYCURSOR 	lexeme->current

	/*!re2c
		WS						= [ \t\v\f];
		NL						= [\n];
		
		"."						{ return ASP_PARSE_TOKEN_DOT; }
		'\000'              	{ return 0; }
		[0-9]+					{ return ASP_PARSE_TOKEN_NUMBER; }
		"not"|"NOT"				{ return ASP_PARSE_TOKEN_NEGATION;}
		[a-zA-Z]+[a-zA-Z0-9]*	{ return ASP_PARSE_TOKEN_STRING; }
		"=>"                	{ return ASP_PARSE_TOKEN_IMPLICATION; }
		"<="					{ return ASP_PARSE_TOKEN_REVERSE_IMPLICATION; }
		"}"						{ return ASP_PARSE_TOKEN_RPAREN; }
		"{"						{ return ASP_PARSE_TOKEN_LPAREN; }
		"="						{ return ASP_PARSE_TOKEN_EQUAL; }
		"("						{ return ASP_PARSE_TOKEN_LBRACKET; }
		")"						{ return ASP_PARSE_TOKEN_RBRACKET; }
		","						{ return ASP_PARSE_TOKEN_COMMA; }
		"^"|","					{ return ASP_PARSE_TOKEN_CONJUNCTION; }
		WS+ "v"{1} WS+ 			{
									while(*(lexeme->start) != 'v') lexeme->start++;
									while(*(lexeme->current) != 'v') lexeme->current--;
									lexeme->current++; 
									return ASP_PARSE_TOKEN_DISJUNCTION;
								}

		"-"						{ return ASP_PARSE_TOKEN_MINUS;}
		
		"!"						{ return ASP_PARSE_TOKEN_NEGATION;}
		
		WS						{ return -1; }
		NL						{ return ASP_PARSE_TOKEN_NEWLINE; }	
		*						{
									std::string str(--lexeme->current,0,1);
									throw syntax_exception("Syntax Error - Unexpected "+ str +"\n");
								}
								
	*/

}
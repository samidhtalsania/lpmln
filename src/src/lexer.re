#include "lexer.h"
#include "Parser.h"
#include "exceptions/syntax_exception.h"
#include "Constants.h"

#include <iostream>


int lexer::FOL_tokenize(const char * YYCURSOR, int len , lexeme_t* lexeme)
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

		":-" WS* "sorts"		{ return FOL_PARSE_TOKEN_SORTS;}
		":-" WS* "objects"		{ return FOL_PARSE_TOKEN_OBJECTS;}
		":-" WS* "constants"	{ return FOL_PARSE_TOKEN_CONSTANTS;}

		";"						{ return FOL_PARSE_TOKEN_SEMI_COLON;}
		
		WS						{ return FOL_PARSE_TOKEN_WS; }
		NL						{ return FOL_PARSE_TOKEN_NEWLINE; }	
		*						{
									std::string str(--lexeme->current,0,1);
									throw syntax_exception("Syntax Error - Unexpected "+ str +"\n");
								}
								
	*/

}


int lexer::ASP_tokenize(const char * YYCURSOR, int len , lexeme_t* lexeme)
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

		":-" WS* "sorts"		{ return ASP_PARSE_TOKEN_SORTS;}
		":-" WS* "objects"		{ return ASP_PARSE_TOKEN_OBJECTS;}
		":-" WS* "constants"	{ return ASP_PARSE_TOKEN_CONSTANTS;}

		";"						{ return ASP_PARSE_TOKEN_SEMI_COLON;}
		
		WS						{ return ASP_PARSE_TOKEN_WS; }
		NL						{ return ASP_PARSE_TOKEN_NEWLINE; }	
		*						{
									std::string str(--lexeme->current,0,1);
									throw syntax_exception("Syntax Error - Unexpected "+ str +"\n");
								}
								
	*/

}


int lexer::MVSM_tokenize(const char * YYCURSOR, int len , lexeme_t* lexeme)
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
		
		"."						{ return MVSM_PARSE_TOKEN_DOT; }
		'\000'              	{ return 0; }
		[0-9]+					{ return MVSM_PARSE_TOKEN_NUMBER; }
		"not"|"NOT"				{ return MVSM_PARSE_TOKEN_NEGATION;}
		[a-zA-Z]+[a-zA-Z0-9]*	{ return MVSM_PARSE_TOKEN_STRING; }
		"=>"                	{ return MVSM_PARSE_TOKEN_IMPLICATION; }
		"<="					{ return MVSM_PARSE_TOKEN_REVERSE_IMPLICATION; }
		"}"						{ return MVSM_PARSE_TOKEN_RPAREN; }
		"{"						{ return MVSM_PARSE_TOKEN_LPAREN; }
		"="						{ return MVSM_PARSE_TOKEN_EQUAL; }
		"("						{ return MVSM_PARSE_TOKEN_LBRACKET; }
		")"						{ return MVSM_PARSE_TOKEN_RBRACKET; }
		","						{ return MVSM_PARSE_TOKEN_COMMA; }
		"^"|","					{ return MVSM_PARSE_TOKEN_CONJUNCTION; }
		WS+ "v"{1} WS+ 			{
									while(*(lexeme->start) != 'v') lexeme->start++;
									while(*(lexeme->current) != 'v') lexeme->current--;
									lexeme->current++; 
									return MVSM_PARSE_TOKEN_DISJUNCTION;
								}

		"-"						{ return MVSM_PARSE_TOKEN_MINUS;}
		
		"!"						{ return MVSM_PARSE_TOKEN_NEGATION;}

		":-" WS* "sorts"		{ return MVSM_PARSE_TOKEN_SORTS;}
		":-" WS* "objects"		{ return MVSM_PARSE_TOKEN_OBJECTS;}
		":-" WS* "constants"	{ return MVSM_PARSE_TOKEN_CONSTANTS;}

		";"						{ return MVSM_PARSE_TOKEN_SEMI_COLON;}
		
		WS						{ return MVSM_PARSE_TOKEN_WS; }
		NL						{ return MVSM_PARSE_TOKEN_NEWLINE; }	
		*						{
									std::string str(--lexeme->current,0,1);
									throw syntax_exception("Syntax Error - Unexpected "+ str +"\n");
								}
								
	*/

}
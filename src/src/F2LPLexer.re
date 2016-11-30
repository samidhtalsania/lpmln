#include "F2LPLexer.h"
#include "exceptions/syntax_exception.h"

int F2LPLexer::Tokenize(const char * YYCURSOR, int len , lexeme_t* lexeme)
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
		
		"."						{ return MVSM_PARSE_TOKEN_DOT; }
		'\000'              	{ return 0; }
		[-]?([0-9]+[.]{1}[0-9]+|[0-9]+)
								{ return MVSM_PARSE_TOKEN_NUMBER; }
		"not"|"NOT"				{ return MVSM_PARSE_TOKEN_NEGATION;}
		[a-zA-Z]+[a-zA-Z0-9]*	{ return MVSM_PARSE_TOKEN_STRING; }
		"=>"                	{ return MVSM_PARSE_TOKEN_IMPLICATION; }
		"<-"					{ return MVSM_PARSE_TOKEN_REVERSE_IMPLICATION; }
		"}"						{ return MVSM_PARSE_TOKEN_RPAREN; }
		"{"						{ return MVSM_PARSE_TOKEN_LPAREN; }
		"="						{ return MVSM_PARSE_TOKEN_EQUAL; }
		"("						{ return MVSM_PARSE_TOKEN_LBRACKET; }
		")"						{ return MVSM_PARSE_TOKEN_RBRACKET; }
		","						{ return MVSM_PARSE_TOKEN_COMMA; }
		"&"						{ return MVSM_PARSE_TOKEN_CONJUNCTION; }
		"#count"				{ return MVSM_PARSE_TOKEN_COUNT;}
		"#sum"				{ return MVSM_PARSE_TOKEN_SUM;}
		WS+ "|"{1} WS+ 			{
									while(*(lexeme->start) != 'v') lexeme->start++;
									while(*(lexeme->current) != 'v') lexeme->current--;
									lexeme->current++; 
									return MVSM_PARSE_TOKEN_DISJUNCTION;
								}
	

		":-" WS* "sorts"		{ return MVSM_PARSE_TOKEN_SORTS;}
		":-" WS* "objects"		{ return MVSM_PARSE_TOKEN_OBJECTS;}
		":-" WS* "constants"	{ return MVSM_PARSE_TOKEN_CONSTANTS;}

		";"						{ return MVSM_PARSE_TOKEN_SEMI_COLON;}
		
		":"						{ return MVSM_PARSE_TOKEN_COLON; }

		WS						{ return -1; }
		NL						{ return MVSM_PARSE_TOKEN_NEWLINE; }	
		*						{
									std::string str(--lexeme->current,0,1);
									throw syntax_exception("Syntax Error - Unexpected "+ str +"\n");
								}
								
	*/

}
/* Generated by re2c 0.16 on Tue Jun  7 14:15:39 2016 */
#line 1 "lexer.re"
#include "lexer.h"
#include "parser.h"
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

	
#line 26 "<stdout>"
{
	YYCTYPE yych;
	if ((YYLIMIT - YYCURSOR) < 3) YYFILL(3);
	yych = *YYCURSOR;
	switch (yych) {
	case 0x00:	goto yy2;
	case '\t':
	case '\v':
	case '\f':
	case ' ':	goto yy6;
	case '\n':	goto yy8;
	case '!':	goto yy10;
	case '(':	goto yy12;
	case ')':	goto yy14;
	case '+':	goto yy16;
	case ',':	goto yy18;
	case '.':	goto yy20;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy22;
	case '=':	goto yy25;
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy27;
	case '^':	goto yy30;
	case '{':	goto yy32;
	case '}':	goto yy34;
	default:	goto yy4;
	}
yy2:
	++YYCURSOR;
#line 29 "lexer.re"
	{ return 0; }
#line 116 "<stdout>"
yy4:
	++YYCURSOR;
#line 51 "lexer.re"
	{
									std::cout<<"Error: Unexpected "<<lexeme->current<<"\n";
									return 0;
								}
#line 124 "<stdout>"
yy6:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case '\t':
	case '\v':
	case '\f':
	case ' ':	goto yy36;
	case 'v':	goto yy39;
	default:	goto yy7;
	}
yy7:
#line 49 "lexer.re"
	{ return PARSE_TOKEN_WS; }
#line 138 "<stdout>"
yy8:
	++YYCURSOR;
#line 50 "lexer.re"
	{ return PARSE_TOKEN_NEWLINE; }
#line 143 "<stdout>"
yy10:
	++YYCURSOR;
#line 47 "lexer.re"
	{ return PARSE_TOKEN_NEGATION;}
#line 148 "<stdout>"
yy12:
	++YYCURSOR;
#line 36 "lexer.re"
	{ return PARSE_TOKEN_LBRACKET; }
#line 153 "<stdout>"
yy14:
	++YYCURSOR;
#line 37 "lexer.re"
	{ return PARSE_TOKEN_RBRACKET; }
#line 158 "<stdout>"
yy16:
	++YYCURSOR;
#line 48 "lexer.re"
	{ return PARSE_TOKEN_PLUS ;}
#line 163 "<stdout>"
yy18:
	++YYCURSOR;
#line 38 "lexer.re"
	{ return PARSE_TOKEN_COMMA; }
#line 168 "<stdout>"
yy20:
	++YYCURSOR;
#line 28 "lexer.re"
	{ return PARSE_TOKEN_DOT; }
#line 173 "<stdout>"
yy22:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy22;
	default:	goto yy24;
	}
yy24:
#line 30 "lexer.re"
	{ return PARSE_TOKEN_NUMBER; }
#line 194 "<stdout>"
yy25:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case '>':	goto yy40;
	default:	goto yy26;
	}
yy26:
#line 35 "lexer.re"
	{ return PARSE_TOKEN_EQUAL; }
#line 204 "<stdout>"
yy27:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy27;
	default:	goto yy29;
	}
yy29:
#line 31 "lexer.re"
	{ return PARSE_TOKEN_STRING; }
#line 277 "<stdout>"
yy30:
	++YYCURSOR;
#line 39 "lexer.re"
	{ return PARSE_TOKEN_CONJUNCTION; }
#line 282 "<stdout>"
yy32:
	++YYCURSOR;
#line 34 "lexer.re"
	{ return PARSE_TOKEN_LPAREN; }
#line 287 "<stdout>"
yy34:
	++YYCURSOR;
#line 33 "lexer.re"
	{ return PARSE_TOKEN_RPAREN; }
#line 292 "<stdout>"
yy36:
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	switch (yych) {
	case '\t':
	case '\v':
	case '\f':
	case ' ':	goto yy36;
	case 'v':	goto yy39;
	default:	goto yy38;
	}
yy38:
	YYCURSOR = YYMARKER;
	goto yy7;
yy39:
	yych = *++YYCURSOR;
	switch (yych) {
	case '\t':
	case '\v':
	case '\f':
	case ' ':	goto yy42;
	default:	goto yy38;
	}
yy40:
	++YYCURSOR;
#line 32 "lexer.re"
	{ return PARSE_TOKEN_IMPLICATION; }
#line 321 "<stdout>"
yy42:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case '\t':
	case '\v':
	case '\f':
	case ' ':	goto yy42;
	default:	goto yy44;
	}
yy44:
#line 40 "lexer.re"
	{
									while(*(lexeme->start) != 'v') lexeme->start++;
									while(*(lexeme->current) != 'v') lexeme->current--;
									lexeme->current++; 
									return PARSE_TOKEN_DISJUNCTION;
								}
#line 341 "<stdout>"
}
#line 56 "lexer.re"



}
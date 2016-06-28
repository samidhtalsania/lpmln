/* This file was automatically generated.  Do not edit! */
#include <string.h>
#include <stdlib.h> 
#include <stdio.h>

#define FOLParserGrammarTOKENTYPE Token*
#define FOLParserGrammarARG_PDECL ,Tree* tree

void FOLParserGrammar(void *yyp,int yymajor,FOLParserGrammarTOKENTYPE yyminor FOLParserGrammarARG_PDECL);
void FOLParserGrammarFree(void *p,void(*freeProc)(void *));
void *FOLParserGrammarAlloc(void *(*mallocProc)(size_t));
void FOLParserGrammarTrace(FILE *TraceFILE,char *zTracePrompt);

#define FOLParserGrammarARG_STORE yypParser->tree = tree
#define FOLParserGrammarARG_FETCH Tree* tree = yypParser->tree
#define FOLParserGrammarARG_SDECL Tree* tree;
#define PARSE_TOKEN_MINUS                          17
#define PARSE_TOKEN_NUMBER                         16
#define PARSE_TOKEN_STRING                         15
#define PARSE_TOKEN_DOT                            14
#define PARSE_TOKEN_WS                             13
#define PARSE_TOKEN_NEGATION                       12
#define PARSE_TOKEN_REVERSE_IMPLICATION            11
#define PARSE_TOKEN_IMPLICATION                    10
#define PARSE_TOKEN_RBRACKET                        9
#define PARSE_TOKEN_LBRACKET                        8
#define PARSE_TOKEN_DISJUNCTION                     7
#define PARSE_TOKEN_CONJUNCTION                     6
#define PARSE_TOKEN_NEWLINE                         5
#define PARSE_TOKEN_RPAREN                          4
#define PARSE_TOKEN_LPAREN                          3
#define PARSE_TOKEN_COMMA                           2
#define PARSE_TOKEN_EQUAL                           1
#define INTERFACE 0
/* This file was automatically generated.  Do not edit! */
#include <string.h>
#include <stdlib.h> 
#include <stdio.h>
#include "Constants.h"

#define FOLParserGrammarTOKENTYPE Token*
#define FOLParserGrammarARG_PDECL ,Tree* tree

void FOLParserGrammar(void *yyp,int yymajor,FOLParserGrammarTOKENTYPE yyminor FOLParserGrammarARG_PDECL);
void FOLParserGrammarFree(void *p,void(*freeProc)(void *));
void *FOLParserGrammarAlloc(void *(*mallocProc)(size_t));
void FOLParserGrammarTrace(FILE *TraceFILE,char *zTracePrompt);

#define FOLParserGrammarARG_STORE yypParser->tree = tree
#define FOLParserGrammarARG_FETCH Tree* tree = yypParser->tree
#define FOLParserGrammarARG_SDECL Tree* tree;
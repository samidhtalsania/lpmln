/* This file was automatically generated.  Do not edit! */
#include <string.h>
#include <stdlib.h> 
#include <stdio.h>
#include "Constants.h"

#define MVSMParserGrammarTOKENTYPE Token*
#define MVSMParserGrammarARG_PDECL ,Tree* tree

void MVSMParserGrammar(void *yyp,int yymajor,MVSMParserGrammarTOKENTYPE yyminor MVSMParserGrammarARG_PDECL);
void MVSMParserGrammarFree(void *p,void(*freeProc)(void *));
void *MVSMParserGrammarAlloc(void *(*mallocProc)(size_t));
void MVSMParserGrammarTrace(FILE *TraceFILE,char *zTracePrompt);

#define MVSMParserGrammarARG_STORE yypParser->tree = tree
#define MVSMParserGrammarARG_FETCH Tree* tree = yypParser->tree
#define MVSMParserGrammarARG_SDECL Tree* tree;
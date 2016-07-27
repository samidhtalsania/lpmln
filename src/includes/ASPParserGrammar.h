/* This file was automatically generated.  Do not edit! */
#include <string.h>
#include <stdlib.h> 
#include <stdio.h>
#include "Constants.h"

#define ASPParserGrammarTOKENTYPE Token*
#define ASPParserGrammarARG_PDECL ,Tree* tree

void ASPParserGrammar(void *yyp,int yymajor,ASPParserGrammarTOKENTYPE yyminor ASPParserGrammarARG_PDECL);
void ASPParserGrammarFree(void *p,void(*freeProc)(void *));
void *ASPParserGrammarAlloc(void *(*mallocProc)(size_t));
void ASPParserGrammarTrace(FILE *TraceFILE,char *zTracePrompt);

#define ASPParserGrammarARG_STORE yypParser->tree = tree
#define ASPParserGrammarARG_FETCH Tree* tree = yypParser->tree
#define ASPParserGrammarARG_SDECL Tree* tree;
/*
** 2000-05-29
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** Driver template for the LEMON parser generator.
**
** The "lemon" program processes an LALR(1) input grammar file, then uses
** this template to construct a parser.  The "lemon" program inserts text
** at each "%%" line.  Also, any "P-a-r-s-e" identifer prefix (without the
** interstitial "-" characters) contained in this template is changed into
** the value of the %name directive from the grammar.  Otherwise, the content
** of this template is copied straight through into the generate parser
** source file.
**
** The following is the concatenation of all %include directives from the
** input grammar file:
*/
#include <stdio.h>
/************ Begin %include sections from the grammar ************************/

	#include <iostream>
	#include <assert.h> 
	#include <stdio.h>
	#include <string.h>
	#include <memory>
	#include <map>
	#include <set>
	#include <string>
	#include <algorithm>
	
	#include "Token.h"
	#include "Domain.h"
	#include "Tree.h"
	#include "Predicate.h"
	#include "FactCompletion.h"
	#include "RuleCompletion.h"
	#include "Head.h"
	#include "Body.h"
	#include "BodyDef.h"

	#include "exceptions/undefined_predicate.h"


	using namespace std;

	struct cmp{
		bool operator()(const std::pair<std::string, std::string>& left, const std::pair<std::string, std::string>& right) const{
			return left.first < right.first;
		}
	};
/**************** End of %include directives **********************************/
/* These constants specify the various numeric values for terminal symbols
** in a format understandable to "makeheaders".  This section is blank unless
** "lemon" is run with the "-m" command-line option.
***************** Begin makeheaders token definitions *************************/
/**************** End makeheaders token definitions ***************************/

/* The next sections is a series of control #defines.
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used to store the integer codes
**                       that represent terminal and non-terminal symbols.
**                       "unsigned char" is used if there are fewer than
**                       256 symbols.  Larger types otherwise.
**    YYNOCODE           is a number of type YYCODETYPE that is not used for
**                       any terminal or nonterminal symbol.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       (also known as: "terminal symbols") have fall-back
**                       values which should be used if the original symbol
**                       would not parse.  This permits keywords to sometimes
**                       be used as identifiers, for example.
**    YYACTIONTYPE       is the data type used for "action codes" - numbers
**                       that indicate what to do in response to the next
**                       token.
**    ParseTOKENTYPE     is the data type used for minor type for terminal
**                       symbols.  Background: A "minor type" is a semantic
**                       value associated with a terminal or non-terminal
**                       symbols.  For example, for an "ID" terminal symbol,
**                       the minor type might be the name of the identifier.
**                       Each non-terminal can have a different minor type.
**                       Terminal symbols all have the same minor type, though.
**                       This macros defines the minor type for terminal 
**                       symbols.
**    YYMINORTYPE        is the data type used for all minor types.
**                       This is typically a union of many types, one of
**                       which is ParseTOKENTYPE.  The entry in the union
**                       for terminal symbols is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    ParseARG_SDECL     A static variable declaration for the %extra_argument
**    ParseARG_PDECL     A parameter declaration for the %extra_argument
**    ParseARG_STORE     Code to store %extra_argument into yypParser
**    ParseARG_FETCH     Code to extract %extra_argument from yypParser
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YY_MAX_SHIFT       Maximum value for shift actions
**    YY_MIN_SHIFTREDUCE Minimum value for shift-reduce actions
**    YY_MAX_SHIFTREDUCE Maximum value for shift-reduce actions
**    YY_MIN_REDUCE      Maximum value for reduce actions
**    YY_ERROR_ACTION    The yy_action[] code for syntax error
**    YY_ACCEPT_ACTION   The yy_action[] code for accept
**    YY_NO_ACTION       The yy_action[] code for no-op
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/************* Begin control #defines *****************************************/
#define YYCODETYPE unsigned char
#define YYNOCODE 40
#define YYACTIONTYPE unsigned char
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  Tree* yy1;
  Variable* yy2;
  Predicate* yy6;
  Head* yy23;
  Body* yy25;
  BodyDef* yy30;
  std::vector<std::string*>* yy31;
  Domain* yy61;
  RuleCompletion* yy75;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  Tree* tree;
#define ParseARG_PDECL , Tree* tree
#define ParseARG_FETCH  Tree* tree = yypParser->tree
#define ParseARG_STORE yypParser->tree = tree
#define YYNSTATE             75
#define YYNRULE              51
#define YY_MAX_SHIFT         74
#define YY_MIN_SHIFTREDUCE   116
#define YY_MAX_SHIFTREDUCE   166
#define YY_MIN_REDUCE        167
#define YY_MAX_REDUCE        217
#define YY_ERROR_ACTION      218
#define YY_ACCEPT_ACTION     219
#define YY_NO_ACTION         220
/************* End control #defines *******************************************/

/* The yyzerominor constant is used to initialize instances of
** YYMINORTYPE objects to zero. */
static const YYMINORTYPE yyzerominor = { 0 };

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N <= YY_MAX_SHIFT             Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   N between YY_MIN_SHIFTREDUCE       Shift to an arbitrary state then
**     and YY_MAX_SHIFTREDUCE           reduce by rule N-YY_MIN_SHIFTREDUCE.
**
**   N between YY_MIN_REDUCE            Reduce by rule N-YY_MIN_REDUCE
**     and YY_MAX_REDUCE

**   N == YY_ERROR_ACTION               A syntax error has occurred.
**
**   N == YY_ACCEPT_ACTION              The parser accepts its input.
**
**   N == YY_NO_ACTION                  No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as
**
**      yy_action[ yy_shift_ofst[S] + X ]
**
** If the index value yy_shift_ofst[S]+X is out of range or if the value
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X or if yy_shift_ofst[S]
** is equal to YY_SHIFT_USE_DFLT, it means that the action is not in the table
** and that yy_default[S] should be used instead.  
**
** The formula above is for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
**
*********** Begin parsing tables **********************************************/
#define YY_ACTTAB_COUNT (205)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   219,   54,  118,   62,  120,  122,  161,  124,  126,   40,
 /*    10 */   139,   35,  161,   71,   33,   15,   37,  117,   70,  119,
 /*    20 */   121,  138,  123,  125,   40,  139,  166,   41,    2,   13,
 /*    30 */    15,   37,   24,   70,   43,   26,  161,   71,   33,  161,
 /*    40 */   161,   44,   12,  159,  158,  156,   70,   55,   46,  161,
 /*    50 */   159,  158,  156,   70,   11,   47,  155,  159,  158,  156,
 /*    60 */    70,   11,   48,   11,  159,  158,  156,   70,   36,   49,
 /*    70 */    45,  159,  158,  156,   70,  143,   50,  204,  159,  158,
 /*    80 */   156,   70,  204,   51,   11,  159,  158,  156,   70,  142,
 /*    90 */    52,  150,  159,  158,  156,   70,   39,  139,   65,  159,
 /*   100 */   158,  156,   70,   38,  159,  158,  157,   70,   53,  139,
 /*   110 */   136,  148,  164,   61,   56,   41,   53,  139,   57,  148,
 /*   120 */    66,   74,   56,   41,  138,  132,  137,  131,  202,   11,
 /*   130 */    42,   68,   42,  202,   25,   19,  149,   28,  161,   21,
 /*   140 */    20,  152,    3,   14,    4,   63,   28,   63,   23,   22,
 /*   150 */    31,   29,   16,    8,   69,  161,   63,   10,  137,   11,
 /*   160 */    67,  154,   11,  165,   41,   11,  141,   58,   11,  140,
 /*   170 */    59,  135,   64,   41,  142,   72,   41,   18,   17,  167,
 /*   180 */   134,  163,    5,  160,    1,    6,  133,   60,  130,    7,
 /*   190 */    27,  196,    9,   30,  198,  197,   32,  169,  169,  195,
 /*   200 */    34,  216,   73,  169,  129,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    19,   20,   21,   35,   23,   24,   15,   26,   27,   28,
 /*    10 */    29,   14,   15,   16,   17,   34,   35,   21,   37,   23,
 /*    20 */    24,   29,   26,   27,   28,   29,   16,   35,    3,    8,
 /*    30 */    34,   35,   11,   37,   25,   11,   15,   16,   17,   15,
 /*    40 */    15,   25,    8,   34,   35,   36,   37,   35,   25,   15,
 /*    50 */    34,   35,   36,   37,    2,   25,    4,   34,   35,   36,
 /*    60 */    37,    2,   25,    2,   34,   35,   36,   37,    9,   25,
 /*    70 */     9,   34,   35,   36,   37,   35,   25,    0,   34,   35,
 /*    80 */    36,   37,    5,   25,    2,   34,   35,   36,   37,   35,
 /*    90 */    25,    9,   34,   35,   36,   37,   28,   29,   35,   34,
 /*   100 */    35,   36,   37,   35,   34,   35,   36,   37,   28,   29,
 /*   110 */    31,   32,   38,   33,   35,   35,   28,   29,   31,   32,
 /*   120 */    35,   33,   35,   35,   29,   30,   29,   30,    0,    2,
 /*   130 */    35,   35,   35,    5,   11,    1,    9,    1,   15,    6,
 /*   140 */     7,   13,    8,   10,    8,   11,    1,   11,    6,    7,
 /*   150 */     1,   11,   10,    8,   37,   15,   11,    8,   29,    2,
 /*   160 */    11,   22,    2,   16,   35,    2,    9,   29,    2,    9,
 /*   170 */    29,   13,    9,   35,   35,    9,   35,    6,    7,    0,
 /*   180 */    13,   38,    8,   35,    5,    8,   13,    9,   13,    8,
 /*   190 */     1,    9,    8,    1,    9,    9,   13,   39,   39,    9,
 /*   200 */    13,   13,    9,   39,   13,
};
#define YY_SHIFT_USE_DFLT (-10)
#define YY_SHIFT_COUNT (74)
#define YY_SHIFT_MIN   (-9)
#define YY_SHIFT_MAX   (193)
static const short yy_shift_ofst[] = {
 /*     0 */    21,   21,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
 /*    10 */    -3,   -3,   24,   24,  123,   24,  123,  140,  140,   25,
 /*    20 */    24,   24,   24,   24,   34,   -9,   -9,   -9,   -9,   -9,
 /*    30 */    -9,   -9,   10,  147,   10,   -9,  128,  134,  136,  133,
 /*    40 */   142,  145,  149,   52,   59,   77,   61,   82,  127,  157,
 /*    50 */   160,  163,  166,  171,  179,  174,  177,  158,  167,  173,
 /*    60 */   175,  178,  181,  189,  182,  184,  185,  192,  186,  183,
 /*    70 */   187,  188,  190,  191,  193,
};
#define YY_REDUCE_USE_DFLT (-33)
#define YY_REDUCE_COUNT (35)
#define YY_REDUCE_MIN   (-32)
#define YY_REDUCE_MAX   (148)
static const short yy_reduce_ofst[] = {
 /*     0 */   -19,   -4,    9,   16,   23,   30,   37,   44,   51,   58,
 /*    10 */    65,   70,   80,   88,   79,   68,   87,   95,   97,  139,
 /*    20 */    -8,  129,  138,  141,  -32,   12,  -32,   40,   54,   63,
 /*    30 */    85,   96,   74,  117,  143,  148,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   179,  178,  218,  218,  218,  218,  218,  218,  218,  218,
 /*    10 */   218,  218,  218,  218,  218,  218,  218,  218,  218,  218,
 /*    20 */   218,  218,  218,  218,  218,  218,  218,  218,  218,  218,
 /*    30 */   218,  218,  218,  218,  218,  218,  191,  218,  218,  218,
 /*    40 */   218,  218,  218,  218,  218,  191,  218,  218,  218,  218,
 /*    50 */   218,  218,  218,  218,  218,  218,  218,  218,  189,  188,
 /*    60 */   218,  218,  218,  218,  192,  218,  194,  218,  193,  218,
 /*    70 */   218,  213,  191,  218,  218,
};
/********** End of lemon-generated parsing tables *****************************/

/* The next table maps tokens (terminal symbols) into fallback tokens.  
** If a construct like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
**
** This feature can be used, for example, to cause some keywords in a language
** to revert to identifiers if they keyword does not apply in the context where
** it appears.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
**
** After the "shift" half of a SHIFTREDUCE action, the stateno field
** actually contains the reduce action for the second half of the
** SHIFTREDUCE.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number, or reduce action in SHIFTREDUCE */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  int yyidx;                    /* Index of top element in stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyidxMax;                 /* Maximum value of yyidx */
#endif
  int yyerrcnt;                 /* Shifts left before out of the error */
  ParseARG_SDECL                /* A place to hold %extra_argument */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void ParseTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  "$",             "EQUAL",         "COMMA",         "LPAREN",      
  "RPAREN",        "NEWLINE",       "CONJUNCTION",   "DISJUNCTION", 
  "LBRACKET",      "RBRACKET",      "IMPLICATION",   "NEGATION",    
  "WS",            "DOT",           "PLUS",          "STRING",      
  "NUMBER",        "MINUS",         "error",         "start",       
  "prog",          "domain",        "domains",       "predicate",   
  "decl",          "variables",     "rule",          "ruleU",       
  "body",          "bodydef",       "bodydef2",      "head",        
  "headdef",       "ruleI",         "number",        "string",      
  "variable",      "lnumber",       "rnumber",     
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "start ::= prog",
 /*   1 */ "prog ::= prog NEWLINE domain",
 /*   2 */ "prog ::= domain",
 /*   3 */ "prog ::= prog NEWLINE predicate",
 /*   4 */ "prog ::= predicate",
 /*   5 */ "prog ::= prog NEWLINE decl",
 /*   6 */ "prog ::= decl",
 /*   7 */ "prog ::= prog NEWLINE rule",
 /*   8 */ "prog ::= rule",
 /*   9 */ "prog ::= prog NEWLINE ruleU",
 /*  10 */ "prog ::= ruleU",
 /*  11 */ "prog ::= prog NEWLINE",
 /*  12 */ "prog ::=",
 /*  13 */ "ruleU ::= LBRACKET ruleI RBRACKET DOT",
 /*  14 */ "ruleU ::= NEGATION LBRACKET ruleI RBRACKET DOT",
 /*  15 */ "ruleI ::= body CONJUNCTION bodydef2",
 /*  16 */ "ruleI ::= body DISJUNCTION bodydef2",
 /*  17 */ "rule ::= body CONJUNCTION bodydef DOT",
 /*  18 */ "rule ::= body DISJUNCTION bodydef DOT",
 /*  19 */ "rule ::= body IMPLICATION head DOT",
 /*  20 */ "rule ::= number body IMPLICATION head",
 /*  21 */ "body ::= body CONJUNCTION bodydef",
 /*  22 */ "body ::= body DISJUNCTION bodydef",
 /*  23 */ "body ::= bodydef",
 /*  24 */ "bodydef ::= string LBRACKET variables RBRACKET",
 /*  25 */ "bodydef ::= NEGATION string LBRACKET variables RBRACKET",
 /*  26 */ "bodydef ::= string EQUAL string",
 /*  27 */ "bodydef ::= string NEGATION EQUAL string",
 /*  28 */ "bodydef2 ::= string LBRACKET variables RBRACKET",
 /*  29 */ "bodydef2 ::= NEGATION string LBRACKET variables RBRACKET",
 /*  30 */ "bodydef2 ::= string EQUAL string",
 /*  31 */ "bodydef2 ::= string NEGATION EQUAL string",
 /*  32 */ "head ::= headdef",
 /*  33 */ "headdef ::= string LBRACKET variables RBRACKET",
 /*  34 */ "headdef ::= NEGATION string LBRACKET variables RBRACKET",
 /*  35 */ "decl ::= string LBRACKET variables RBRACKET",
 /*  36 */ "predicate ::= string LBRACKET variables RBRACKET DOT",
 /*  37 */ "predicate ::= number string LBRACKET variables RBRACKET",
 /*  38 */ "domain ::= string EQUAL domains",
 /*  39 */ "domains ::= LPAREN variables RPAREN",
 /*  40 */ "variables ::= variable",
 /*  41 */ "variables ::= variables COMMA variable",
 /*  42 */ "variable ::= string",
 /*  43 */ "variable ::= number",
 /*  44 */ "variable ::= PLUS string",
 /*  45 */ "string ::= STRING",
 /*  46 */ "number ::= NUMBER",
 /*  47 */ "number ::= lnumber DOT rnumber",
 /*  48 */ "number ::= MINUS lnumber DOT rnumber",
 /*  49 */ "lnumber ::= NUMBER",
 /*  50 */ "rnumber ::= NUMBER",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.
*/
static void yyGrowStack(yyParser *p){
  int newSize;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  if( pNew ){
    p->yystack = pNew;
    p->yystksz = newSize;
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows to %d entries!\n",
              yyTracePrompt, p->yystksz);
    }
#endif
  }
}
#endif

/* Datatype of the argument to the memory allocated passed as the
** second argument to ParseAlloc() below.  This can be changed by
** putting an appropriate #define in the %include section of the input
** grammar.
*/
#ifndef YYMALLOCARGTYPE
# define YYMALLOCARGTYPE size_t
#endif

/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to Parse and ParseFree.
*/
void *ParseAlloc(void *(*mallocProc)(YYMALLOCARGTYPE)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (YYMALLOCARGTYPE)sizeof(yyParser) );
  if( pParser ){
    pParser->yyidx = -1;
#ifdef YYTRACKMAXSTACKDEPTH
    pParser->yyidxMax = 0;
#endif
#if YYSTACKDEPTH<=0
    pParser->yystack = NULL;
    pParser->yystksz = 0;
    yyGrowStack(pParser);
#endif
  }
  return pParser;
}

/* The following function deletes the "minor type" or semantic value
** associated with a symbol.  The symbol can be either a terminal
** or nonterminal. "yymajor" is the symbol code, and "yypminor" is
** a pointer to the value to be deleted.  The code used to do the 
** deletions is derived from the %destructor and/or %token_destructor
** directives of the input grammar.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  ParseARG_FETCH;
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are *not* used
    ** inside the C code.
    */
/********* Begin destructor definitions ***************************************/
/********* End destructor definitions *****************************************/
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
*/
static void yy_pop_parser_stack(yyParser *pParser){
  yyStackEntry *yytos;
  assert( pParser->yyidx>=0 );
  yytos = &pParser->yystack[pParser->yyidx--];
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yy_destructor(pParser, yytos->major, &yytos->minor);
}

/* 
** Deallocate and destroy a parser.  Destructors are called for
** all stack elements before shutting the parser down.
**
** If the YYPARSEFREENEVERNULL macro exists (for example because it
** is defined in a %include section of the input grammar) then it is
** assumed that the input pointer is never NULL.
*/
void ParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
#ifndef YYPARSEFREENEVERNULL
  if( pParser==0 ) return;
#endif
  while( pParser->yyidx>=0 ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  free(pParser->yystack);
#endif
  (*freeProc)((void*)pParser);
}

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int ParseStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyidxMax;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
*/
static int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yystack[pParser->yyidx].stateno;
 
  if( stateno>=YY_MIN_REDUCE ) return stateno;
  assert( stateno <= YY_SHIFT_COUNT );
  do{
    i = yy_shift_ofst[stateno];
    if( i==YY_SHIFT_USE_DFLT ) return yy_default[stateno];
    assert( iLookAhead!=YYNOCODE );
    i += iLookAhead;
    if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
      if( iLookAhead>0 ){
#ifdef YYFALLBACK
        YYCODETYPE iFallback;            /* Fallback token */
        if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
               && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
          }
#endif
          assert( yyFallback[iFallback]==0 ); /* Fallback loop must terminate */
          iLookAhead = iFallback;
          continue;
        }
#endif
#ifdef YYWILDCARD
        {
          int j = i - iLookAhead + YYWILDCARD;
          if( 
#if YY_SHIFT_MIN+YYWILDCARD<0
            j>=0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
            j<YY_ACTTAB_COUNT &&
#endif
            yy_lookahead[j]==YYWILDCARD
          ){
#ifndef NDEBUG
            if( yyTraceFILE ){
              fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
                 yyTracePrompt, yyTokenName[iLookAhead],
                 yyTokenName[YYWILDCARD]);
            }
#endif /* NDEBUG */
            return yy_action[j];
          }
        }
#endif /* YYWILDCARD */
      }
      return yy_default[stateno];
    }else{
      return yy_action[i];
    }
  }while(1);
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( i!=YY_REDUCE_USE_DFLT );
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser, YYMINORTYPE *yypMinor){
   ParseARG_FETCH;
   yypParser->yyidx--;
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
/******** Begin %stack_overflow code ******************************************/
/******** End %stack_overflow code ********************************************/
   ParseARG_STORE; /* Suppress warning about unused %extra_argument var */
}

/*
** Print tracing information for a SHIFT action
*/
#ifndef NDEBUG
static void yyTraceShift(yyParser *yypParser, int yyNewState){
  if( yyTraceFILE ){
    if( yyNewState<YYNSTATE ){
      fprintf(yyTraceFILE,"%sShift '%s', go to state %d\n",
         yyTracePrompt,yyTokenName[yypParser->yystack[yypParser->yyidx].major],
         yyNewState);
    }else{
      fprintf(yyTraceFILE,"%sShift '%s'\n",
         yyTracePrompt,yyTokenName[yypParser->yystack[yypParser->yyidx].major]);
    }
  }
}
#else
# define yyTraceShift(X,Y)
#endif

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  YYMINORTYPE *yypMinor         /* Pointer to the minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yyidx++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( yypParser->yyidx>yypParser->yyidxMax ){
    yypParser->yyidxMax = yypParser->yyidx;
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yyidx>=YYSTACKDEPTH ){
    yyStackOverflow(yypParser, yypMinor);
    return;
  }
#else
  if( yypParser->yyidx>=yypParser->yystksz ){
    yyGrowStack(yypParser);
    if( yypParser->yyidx>=yypParser->yystksz ){
      yyStackOverflow(yypParser, yypMinor);
      return;
    }
  }
#endif
  yytos = &yypParser->yystack[yypParser->yyidx];
  yytos->stateno = (YYACTIONTYPE)yyNewState;
  yytos->major = (YYCODETYPE)yyMajor;
  yytos->minor = *yypMinor;
  yyTraceShift(yypParser, yyNewState);
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 19, 1 },
  { 20, 3 },
  { 20, 1 },
  { 20, 3 },
  { 20, 1 },
  { 20, 3 },
  { 20, 1 },
  { 20, 3 },
  { 20, 1 },
  { 20, 3 },
  { 20, 1 },
  { 20, 2 },
  { 20, 0 },
  { 27, 4 },
  { 27, 5 },
  { 33, 3 },
  { 33, 3 },
  { 26, 4 },
  { 26, 4 },
  { 26, 4 },
  { 26, 4 },
  { 28, 3 },
  { 28, 3 },
  { 28, 1 },
  { 29, 4 },
  { 29, 5 },
  { 29, 3 },
  { 29, 4 },
  { 30, 4 },
  { 30, 5 },
  { 30, 3 },
  { 30, 4 },
  { 31, 1 },
  { 32, 4 },
  { 32, 5 },
  { 24, 4 },
  { 23, 5 },
  { 23, 5 },
  { 21, 3 },
  { 22, 3 },
  { 25, 1 },
  { 25, 3 },
  { 36, 1 },
  { 36, 1 },
  { 36, 2 },
  { 35, 1 },
  { 34, 1 },
  { 34, 3 },
  { 34, 4 },
  { 37, 1 },
  { 38, 1 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  int yyruleno                 /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  YYMINORTYPE yygotominor;        /* The LHS of the rule reduced */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  ParseARG_FETCH;
  yymsp = &yypParser->yystack[yypParser->yyidx];
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno>=0 
        && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    yysize = yyRuleInfo[yyruleno].nrhs;
    fprintf(yyTraceFILE, "%sReduce [%s], go to state %d.\n", yyTracePrompt,
      yyRuleName[yyruleno], yymsp[-yysize].stateno);
  }
#endif /* NDEBUG */
  yygotominor = yyzerominor;

  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
/********** Begin reduce actions **********************************************/
      case 1: /* prog ::= prog NEWLINE domain */
      case 2: /* prog ::= domain */ yytestcase(yyruleno==2);
{ 
	tree->domains.insert(*yymsp[0].minor.yy61); 
	tree->domainNamesList.insert(yymsp[0].minor.yy61->getDomainVar());
	for(auto& v : yymsp[0].minor.yy61->getVars()){
		tree->domainList.insert(v);	
	}
	delete yymsp[0].minor.yy61;
}
        break;
      case 3: /* prog ::= prog NEWLINE predicate */
      case 4: /* prog ::= predicate */ yytestcase(yyruleno==4);
{ 
	FactCompletion f(*yymsp[0].minor.yy6);
	tree->facts.insert(std::pair<std::string,FactCompletion>(f.head.getVar(),f)); 
	delete yymsp[0].minor.yy6;
}
        break;
      case 5: /* prog ::= prog NEWLINE decl */
      case 6: /* prog ::= decl */ yytestcase(yyruleno==6);
{
	tree->variables.insert(*yymsp[0].minor.yy2);
	delete yymsp[0].minor.yy2;
}
        break;
      case 7: /* prog ::= prog NEWLINE rule */
      case 8: /* prog ::= rule */ yytestcase(yyruleno==8);
{
	if(yymsp[0].minor.yy75->isHeadTop == false)
		tree->rules.insert(std::pair<std::string,RuleCompletion>(yymsp[0].minor.yy75->head.getVar(),*yymsp[0].minor.yy75));
	delete yymsp[0].minor.yy75;
}
        break;
      case 9: /* prog ::= prog NEWLINE ruleU */
{
	
	//random
	delete yymsp[0].minor.yy75;
}
        break;
      case 10: /* prog ::= ruleU */
{
	//random
	delete yymsp[0].minor.yy75;
}
        break;
      case 15: /* ruleI ::= body CONJUNCTION bodydef2 */
      case 16: /* ruleI ::= body DISJUNCTION bodydef2 */ yytestcase(yyruleno==16);
{
	delete yymsp[0].minor.yy30;
}
        break;
      case 17: /* rule ::= body CONJUNCTION bodydef DOT */
      case 18: /* rule ::= body DISJUNCTION bodydef DOT */ yytestcase(yyruleno==18);
{
	yygotominor.yy75 = new RuleCompletion;
	yygotominor.yy75->isHeadTop = true;	
	delete yymsp[-3].minor.yy25;
	delete yymsp[-1].minor.yy30;
}
        break;
      case 19: /* rule ::= body IMPLICATION head DOT */
{
	std::set<std::pair<std::string,std::string>> orphanVarsMap;
	std::set<std::pair<std::string,std::string>> orphanVarsHeadMap;
	std::vector<Predicate> predList = yymsp[-3].minor.yy25->getPredicate();
	for(auto& p : predList){
		int tempCount = 0;
		for(auto& v : p.getTokens()){
			if(tree->variables.find(p.getVar()) == tree->variables.end()){
				undefined_predicate ex(p.getVar());
				throw ex;
			}
			else
				orphanVarsMap.insert(std::pair<std::string, std::string>(v,tree->variables.find(p.getVar())->getPosMap().at(tempCount++).getDomainVar()));
		}
	}

	int count = 0;
	std::map<int,std::pair<int, std::string>> varMap;
	int tempCount = 0;


	for(auto& str : yymsp[-1].minor.yy23->getPredicate().getTokens()){
		if(tree->isConstant(str)){
			varMap[count++] = std::pair<int, std::string>(count, str);
		}
		else
			count++;
		
		if(tree->variables.find(yymsp[-1].minor.yy23->getPredicate().getVar()) == tree->variables.end()){
			undefined_predicate ex(yymsp[-1].minor.yy23->getPredicate().getVar());
			throw ex;
		}
		else	
			orphanVarsHeadMap.insert(std::pair<std::string, std::string>(str,tree->variables.find(yymsp[-1].minor.yy23->getPredicate().getVar())->getPosMap().at(tempCount++).getDomainVar()));
	}

	std::set<std::string> result;
		
	tree->removeConstantsPair(orphanVarsMap);
	tree->removeConstantsPair(orphanVarsHeadMap);
	
	std::set<std::pair<std::string,std::string>> resultMap;
	std::set_difference(orphanVarsMap.begin(), orphanVarsMap.end(), orphanVarsHeadMap.begin(), orphanVarsHeadMap.end(),std::inserter(resultMap, resultMap.end()), cmp());

	yygotominor.yy75 = new RuleCompletion(yymsp[-1].minor.yy23->getPredicate(),predList, resultMap, varMap);
	delete yymsp[-3].minor.yy25;
	delete yymsp[-1].minor.yy23;
}
        break;
      case 20: /* rule ::= number body IMPLICATION head */
{
	std::set<std::pair<std::string,std::string>> orphanVarsMap;
	std::set<std::pair<std::string,std::string>> orphanVarsHeadMap;
	std::vector<Predicate> predList = yymsp[-2].minor.yy25->getPredicate();
	for(auto& p : predList){
		int tempCount = 0;
		for(auto& v : p.getTokens()){
			orphanVarsMap.insert(std::pair<std::string, std::string>(v,tree->variables.find(p.getVar())->getPosMap().at(tempCount++).getDomainVar()));
		}
	}

	int count = 0;
	std::map<int,std::pair<int, std::string>> varMap;
	int tempCount = 0;

	for(auto& str : yymsp[0].minor.yy23->getPredicate().getTokens()){
		if(tree->isConstant(str)){
			varMap[count] = std::pair<int, std::string>(count, str);
		}
		else
			count++;
			
		orphanVarsHeadMap.insert(std::pair<std::string, std::string>(str,tree->variables.find(yymsp[0].minor.yy23->getPredicate().getVar())->getPosMap().at(tempCount++).getDomainVar()));
	}

	
	
	std::set<std::string> result;
		
	tree->removeConstantsPair(orphanVarsMap);
	tree->removeConstantsPair(orphanVarsHeadMap);
	
	std::set<std::pair<std::string,std::string>> resultMap;
	std::set_difference(orphanVarsMap.begin(), orphanVarsMap.end(), orphanVarsHeadMap.begin(), orphanVarsHeadMap.end(),std::inserter(resultMap, resultMap.end()), cmp());

	yygotominor.yy75 = new RuleCompletion(yymsp[0].minor.yy23->getPredicate(),predList, resultMap, varMap);
	delete yymsp[-2].minor.yy25;
	delete yymsp[0].minor.yy23;
}
        break;
      case 21: /* body ::= body CONJUNCTION bodydef */
{
	yygotominor.yy25 = yymsp[-2].minor.yy25;
	yymsp[-2].minor.yy25->addPredicate(yymsp[0].minor.yy30->getPredicate());
	delete yymsp[0].minor.yy30;
}
        break;
      case 22: /* body ::= body DISJUNCTION bodydef */
{
	yygotominor.yy25 = yymsp[-2].minor.yy25;
	delete yymsp[0].minor.yy30;
}
        break;
      case 23: /* body ::= bodydef */
{
	yygotominor.yy25 = new Body;
	yygotominor.yy25->addPredicate(yymsp[0].minor.yy30->getPredicate());
	delete yymsp[0].minor.yy30;
}
        break;
      case 24: /* bodydef ::= string LBRACKET variables RBRACKET */
      case 25: /* bodydef ::= NEGATION string LBRACKET variables RBRACKET */ yytestcase(yyruleno==25);
{	
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-1].minor.yy31)
		vars.push_back(*v);
	
	Predicate p(yymsp[-3].minor.yy0->token, vars);
	yygotominor.yy30 = new BodyDef;
	yygotominor.yy30->addPredicate(p);
	delete yymsp[-1].minor.yy31;
}
        break;
      case 26: /* bodydef ::= string EQUAL string */
{
	Predicate p(yymsp[-2].minor.yy0->token,yymsp[0].minor.yy0->token);
	p.setEquality();
	yygotominor.yy30 = new BodyDef;
	yygotominor.yy30->addPredicate(p);
}
        break;
      case 27: /* bodydef ::= string NEGATION EQUAL string */
{
	Predicate p(yymsp[-3].minor.yy0->token,yymsp[0].minor.yy0->token);
	p.setInEquality();
	yygotominor.yy30 = new BodyDef;
	yygotominor.yy30->addPredicate(p);
}
        break;
      case 28: /* bodydef2 ::= string LBRACKET variables RBRACKET */
      case 29: /* bodydef2 ::= NEGATION string LBRACKET variables RBRACKET */ yytestcase(yyruleno==29);
{delete yymsp[-1].minor.yy31;}
        break;
      case 32: /* head ::= headdef */
{ 
	yygotominor.yy23 = yymsp[0].minor.yy23;
}
        break;
      case 33: /* headdef ::= string LBRACKET variables RBRACKET */
      case 34: /* headdef ::= NEGATION string LBRACKET variables RBRACKET */ yytestcase(yyruleno==34);
{
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-1].minor.yy31)
		vars.push_back(*v);
	
	Predicate p(yymsp[-3].minor.yy0->token, vars);
	yygotominor.yy23 = new Head;
	yygotominor.yy23->addPredicate(p);
	delete yymsp[-1].minor.yy31;
}
        break;
      case 35: /* decl ::= string LBRACKET variables RBRACKET */
{
	yygotominor.yy2 = new Variable;
	std::map<int, Domain> posMap;
	std::set<Domain>::iterator itr;
	int i=0;
	for(auto& v : *yymsp[-1].minor.yy31){
		itr = tree->domains.find(*v);
		if (itr == tree->domains.end()){
			std::cout<<"Error:Domain:"+ *v +" not found.\n";
			//Exit
		}
		else{
			// itr = tree->domains.find(*v);
			yygotominor.yy2->setVar(yymsp[-3].minor.yy0->token);
			posMap[i++] = *itr;
		}
	}
	yygotominor.yy2->setPosMap(posMap);
	delete yymsp[-1].minor.yy31;
}
        break;
      case 36: /* predicate ::= string LBRACKET variables RBRACKET DOT */
{
	yygotominor.yy6 = new Predicate;
	yygotominor.yy6->setVar(yymsp[-4].minor.yy0->token);
	yygotominor.yy6->setTokens(*yymsp[-2].minor.yy31);
	delete yymsp[-2].minor.yy31;
}
        break;
      case 37: /* predicate ::= number string LBRACKET variables RBRACKET */
{
	yygotominor.yy6 = new Predicate;
	yygotominor.yy6->setVar(yymsp[-3].minor.yy0->token);
	yygotominor.yy6->setTokens(*yymsp[-1].minor.yy31);
	delete yymsp[-1].minor.yy31;
}
        break;
      case 38: /* domain ::= string EQUAL domains */
{ 
	yygotominor.yy61 = yymsp[0].minor.yy61;
	yymsp[0].minor.yy61->setDomainVar(yymsp[-2].minor.yy0->token);
}
        break;
      case 39: /* domains ::= LPAREN variables RPAREN */
{
	yygotominor.yy61 = new Domain();
	yygotominor.yy61->setVars(*yymsp[-1].minor.yy31);
	delete yymsp[-1].minor.yy31;
}
        break;
      case 40: /* variables ::= variable */
{
	yygotominor.yy31 = new std::vector<std::string*>();
	yygotominor.yy31->push_back(yymsp[0].minor.yy0->token);
}
        break;
      case 41: /* variables ::= variables COMMA variable */
{
	yygotominor.yy31 = yymsp[-2].minor.yy31;
	yymsp[-2].minor.yy31->push_back(yymsp[0].minor.yy0->token);
}
        break;
      case 42: /* variable ::= string */
      case 43: /* variable ::= number */ yytestcase(yyruleno==43);
      case 44: /* variable ::= PLUS string */ yytestcase(yyruleno==44);
      case 45: /* string ::= STRING */ yytestcase(yyruleno==45);
      case 46: /* number ::= NUMBER */ yytestcase(yyruleno==46);
{ yygotominor.yy0=yymsp[0].minor.yy0;}
        break;
      case 47: /* number ::= lnumber DOT rnumber */
{ 
	yygotominor.yy0 = new Token(*(yymsp[-2].minor.yy0->token)+"."+*(yymsp[0].minor.yy0->token));
}
        break;
      case 48: /* number ::= MINUS lnumber DOT rnumber */
{ 
	yygotominor.yy0 = new Token("-"+*(yymsp[-2].minor.yy0->token)+"."+*(yymsp[0].minor.yy0->token));
}
        break;
      case 49: /* lnumber ::= NUMBER */
      case 50: /* rnumber ::= NUMBER */ yytestcase(yyruleno==50);
{ yygotominor.yy0=yymsp[0].minor.yy0; }
        break;
      default:
      /* (0) start ::= prog */ yytestcase(yyruleno==0);
      /* (11) prog ::= prog NEWLINE */ yytestcase(yyruleno==11);
      /* (12) prog ::= */ yytestcase(yyruleno==12);
      /* (13) ruleU ::= LBRACKET ruleI RBRACKET DOT */ yytestcase(yyruleno==13);
      /* (14) ruleU ::= NEGATION LBRACKET ruleI RBRACKET DOT */ yytestcase(yyruleno==14);
      /* (30) bodydef2 ::= string EQUAL string */ yytestcase(yyruleno==30);
      /* (31) bodydef2 ::= string NEGATION EQUAL string */ yytestcase(yyruleno==31);
        break;
/********** End reduce actions ************************************************/
  };
  assert( yyruleno>=0 && yyruleno<sizeof(yyRuleInfo)/sizeof(yyRuleInfo[0]) );
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yypParser->yyidx -= yysize;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,(YYCODETYPE)yygoto);
  if( yyact <= YY_MAX_SHIFTREDUCE ){
    if( yyact>YY_MAX_SHIFT ) yyact += YY_MIN_REDUCE - YY_MIN_SHIFTREDUCE;
    /* If the reduce action popped at least
    ** one element off the stack, then we can push the new element back
    ** onto the stack here, and skip the stack overflow test in yy_shift().
    ** That gives a significant speed improvement. */
    if( yysize ){
      yypParser->yyidx++;
      yymsp -= yysize-1;
      yymsp->stateno = (YYACTIONTYPE)yyact;
      yymsp->major = (YYCODETYPE)yygoto;
      yymsp->minor = yygotominor;
      yyTraceShift(yypParser, yyact);
    }else{
      yy_shift(yypParser,yyact,yygoto,&yygotominor);
    }
  }else{
    assert( yyact == YY_ACCEPT_ACTION );
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
/************ Begin %parse_failure code ***************************************/

    std::cout<<"Giving up.  Parser is lost...\n";
/************ End %parse_failure code *****************************************/
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  YYMINORTYPE yyminor            /* The minor type of the error token */
){
  ParseARG_FETCH;
#define TOKEN (yyminor.yy0)
/************ Begin %syntax_error code ****************************************/

	 std::cout << "syntax error - ";
    int n = sizeof(yyTokenName) / sizeof(yyTokenName[0]);
    for (int i = 0; i < n; ++i) {
            int a = yy_find_shift_action(yypParser, (YYCODETYPE)i);
            if (a < YYNSTATE + YYNRULE) {
                    std::cout << "expected " << yyTokenName[i] << std::endl;
            }
    }
/************ End %syntax_error code ******************************************/
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
/*********** Begin %parse_accept code *****************************************/

    std::cout<<("//parsing complete!\n");
/*********** End %parse_accept code *******************************************/
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "ParseAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void Parse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  ParseTOKENTYPE yyminor       /* The value for the token */
  ParseARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  int yyact;            /* The parser action. */
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  int yyendofinput;     /* True if we are at the end of input */
#endif
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser;  /* The parser */

  /* (re)initialize the parser, if necessary */
  yypParser = (yyParser*)yyp;
  if( yypParser->yyidx<0 ){
#if YYSTACKDEPTH<=0
    if( yypParser->yystksz <=0 ){
      /*memset(&yyminorunion, 0, sizeof(yyminorunion));*/
      yyminorunion = yyzerominor;
      yyStackOverflow(yypParser, &yyminorunion);
      return;
    }
#endif
    yypParser->yyidx = 0;
    yypParser->yyerrcnt = -1;
    yypParser->yystack[0].stateno = 0;
    yypParser->yystack[0].major = 0;
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sInitialize. Empty stack. State 0\n",
              yyTracePrompt);
    }
#endif
  }
  yyminorunion.yy0 = yyminor;
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  yyendofinput = (yymajor==0);
#endif
  ParseARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput '%s'\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,(YYCODETYPE)yymajor);
    if( yyact <= YY_MAX_SHIFTREDUCE ){
      if( yyact > YY_MAX_SHIFT ) yyact += YY_MIN_REDUCE - YY_MIN_SHIFTREDUCE;
      yy_shift(yypParser,yyact,yymajor,&yyminorunion);
      yypParser->yyerrcnt--;
      yymajor = YYNOCODE;
    }else if( yyact <= YY_MAX_REDUCE ){
      yy_reduce(yypParser,yyact-YY_MIN_REDUCE);
    }else{
      assert( yyact == YY_ERROR_ACTION );
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yymx = yypParser->yystack[yypParser->yyidx].major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor,&yyminorunion);
        yymajor = YYNOCODE;
      }else{
         while(
          yypParser->yyidx >= 0 &&
          yymx != YYERRORSYMBOL &&
          (yyact = yy_find_reduce_action(
                        yypParser->yystack[yypParser->yyidx].stateno,
                        YYERRORSYMBOL)) >= YY_MIN_REDUCE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yyidx < 0 || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          YYMINORTYPE u2;
          u2.YYERRSYMDT = 0;
          yy_shift(yypParser,yyact,YYERRORSYMBOL,&u2);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor,yyminorunion);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      yymajor = YYNOCODE;
      
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
      }
      yymajor = YYNOCODE;
#endif
    }
  }while( yymajor!=YYNOCODE && yypParser->yyidx>=0 );
#ifndef NDEBUG
  if( yyTraceFILE ){
    int i;
    fprintf(yyTraceFILE,"%sReturn. Stack=",yyTracePrompt);
    for(i=1; i<=yypParser->yyidx; i++)
      fprintf(yyTraceFILE,"%c%s", i==1 ? '[' : ' ', 
              yyTokenName[yypParser->yystack[i].major]);
    fprintf(yyTraceFILE,"]\n");
  }
#endif
  return;
}

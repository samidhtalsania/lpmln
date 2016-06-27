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
	#include "exceptions/syntax_exception.h"


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
#define YYNOCODE 38
#define YYACTIONTYPE unsigned char
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  Head* yy1;
  Tree* yy7;
  BodyDef* yy20;
  RuleCompletion* yy21;
  Predicate* yy26;
  std::vector<std::string*>* yy45;
  Domain* yy51;
  Body* yy53;
  Variable* yy57;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  Tree* tree;
#define ParseARG_PDECL , Tree* tree
#define ParseARG_FETCH  Tree* tree = yypParser->tree
#define ParseARG_STORE yypParser->tree = tree
#define YYNSTATE             100
#define YYNRULE              51
#define YY_MAX_SHIFT         99
#define YY_MIN_SHIFTREDUCE   140
#define YY_MAX_SHIFTREDUCE   190
#define YY_MIN_REDUCE        191
#define YY_MAX_REDUCE        241
#define YY_ERROR_ACTION      242
#define YY_ACCEPT_ACTION     243
#define YY_NO_ACTION         244
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
#define YY_ACTTAB_COUNT (267)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   243,   71,  142,   38,  144,  146,  185,  148,   48,  163,
 /*    10 */   184,  183,  182,   96,   20,   47,  141,   96,  143,  145,
 /*    20 */    93,  147,   48,  163,  185,   97,   44,   15,   20,   47,
 /*    30 */    31,   96,   53,  185,   97,   44,   17,   82,  180,   54,
 /*    40 */   184,  183,  181,   96,   55,   73,   83,  184,  183,  181,
 /*    50 */    96,   52,  184,  183,  181,   96,   57,   72,  170,   76,
 /*    60 */    59,   85,    2,  185,  184,  183,  181,   96,  184,  183,
 /*    70 */   181,   96,   61,  185,  159,  170,   79,   63,   85,  224,
 /*    80 */   184,  183,  181,   96,  224,  184,  183,  181,   96,   64,
 /*    90 */    86,  170,  174,   65,   85,   29,   28,  184,  183,  181,
 /*   100 */    96,  184,  183,  181,   96,   66,   36,   25,   24,  185,
 /*   110 */    67,   21,  190,  184,  183,  181,   96,   30,  184,  183,
 /*   120 */   181,   96,   68,   19,    3,   84,   69,   94,  189,  185,
 /*   130 */   184,  183,  181,   96,  184,  183,  181,   96,   27,   26,
 /*   140 */    70,  163,   22,   70,  163,   78,   91,   52,   81,   33,
 /*   150 */    52,   89,  185,   70,  163,   74,   91,  179,   99,   35,
 /*   160 */    52,   52,  185,   51,  163,   91,   92,  169,   32,  168,
 /*   170 */    52,  185,   50,  163,   16,   42,   42,   37,  168,   49,
 /*   180 */   185,   18,    6,   14,   34,   94,   94,  185,   27,   26,
 /*   190 */   162,  161,   23,   95,   17,   17,   52,   52,   87,   98,
 /*   200 */    40,   46,   75,  185,   52,   52,  229,   17,  226,   17,
 /*   210 */   228,  229,  188,  226,   56,  228,   58,   17,  227,   17,
 /*   220 */   187,   17,   17,  227,   60,   17,   62,   17,  172,  171,
 /*   230 */    17,   17,   88,  167,  166,  191,   77,  165,  164,  158,
 /*   240 */     1,    4,    5,  157,  156,  153,   80,    7,    8,  152,
 /*   250 */     9,   10,   39,  160,  206,   11,   12,   90,   13,   41,
 /*   260 */   193,  193,   43,  205,   45,  240,  151,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    18,   19,   20,   11,   22,   23,   14,   25,   26,   27,
 /*    10 */    32,   33,   34,   35,   32,   33,   20,   35,   22,   23,
 /*    20 */    33,   25,   26,   27,   14,   15,   16,    8,   32,   33,
 /*    30 */    11,   35,   24,   14,   15,   16,    2,   33,    4,   24,
 /*    40 */    32,   33,   34,   35,   24,   27,   33,   32,   33,   34,
 /*    50 */    35,   33,   32,   33,   34,   35,   24,   29,   30,   33,
 /*    60 */    24,   33,    3,   14,   32,   33,   34,   35,   32,   33,
 /*    70 */    34,   35,   24,   14,   29,   30,   33,   24,   33,    0,
 /*    80 */    32,   33,   34,   35,    5,   32,   33,   34,   35,   24,
 /*    90 */    29,   30,   13,   24,   33,    6,    7,   32,   33,   34,
 /*   100 */    35,   32,   33,   34,   35,   24,   11,    6,    7,   14,
 /*   110 */    24,   10,   15,   32,   33,   34,   35,    1,   32,   33,
 /*   120 */    34,   35,   24,    8,    8,   33,   24,   11,   15,   14,
 /*   130 */    32,   33,   34,   35,   32,   33,   34,   35,    6,    7,
 /*   140 */    26,   27,   10,   26,   27,   31,    8,   33,   31,   11,
 /*   150 */    33,   33,   14,   26,   27,   27,    8,   21,   31,   11,
 /*   160 */    33,   33,   14,   26,   27,    8,   33,   33,   11,   33,
 /*   170 */    33,   14,   26,   27,    8,    1,    1,   11,   33,   33,
 /*   180 */    14,    8,    8,    8,   11,   11,   11,   14,    6,    7,
 /*   190 */    27,   27,   10,   35,    2,    2,   33,   33,   27,   27,
 /*   200 */    11,    9,    9,   14,   33,   33,    0,    2,    0,    2,
 /*   210 */     0,    5,   36,    5,    9,    5,    9,    2,    0,    2,
 /*   220 */    36,    2,    2,    5,    9,    2,    9,    2,    9,    9,
 /*   230 */     2,    2,    9,    9,    9,    0,    9,    9,    9,   13,
 /*   240 */     5,    8,    8,   13,   13,   13,    9,    8,    8,   13,
 /*   250 */     8,    8,   11,    9,    9,    8,    8,   11,    8,    1,
 /*   260 */    37,   37,   13,    9,   13,   13,    9,
};
#define YY_SHIFT_USE_DFLT (-9)
#define YY_SHIFT_COUNT (99)
#define YY_SHIFT_MIN   (-8)
#define YY_SHIFT_MAX   (258)
static const short yy_shift_ofst[] = {
 /*     0 */    19,   19,   10,   10,   10,   10,   10,   10,   10,   10,
 /*    10 */    10,   10,   10,   10,   10,  138,  148,   10,  148,  148,
 /*    20 */   157,   -8,   -8,   -8,  148,  148,  148,  148,  148,  148,
 /*    30 */    59,  166,  173,   95,  115,  189,   49,   49,   49,   49,
 /*    40 */    49,   49,   49,   97,  113,   97,   79,  116,  101,  174,
 /*    50 */   132,  182,  175,   34,  192,  193,  206,  205,  208,  207,
 /*    60 */   210,  215,  218,  217,  219,  220,  223,  225,  228,  229,
 /*    70 */    89,  235,  226,  230,  231,  224,  233,  232,  227,  234,
 /*    80 */   236,  237,  239,  240,  242,  243,  244,  245,  224,  247,
 /*    90 */   241,  246,  248,  250,  258,  249,  251,  252,  254,  257,
};
#define YY_REDUCE_USE_DFLT (-23)
#define YY_REDUCE_COUNT (45)
#define YY_REDUCE_MIN   (-22)
#define YY_REDUCE_MAX   (184)
static const short yy_reduce_ofst[] = {
 /*     0 */   -18,   -4,    8,   15,   20,   32,   36,   48,   53,   65,
 /*    10 */    69,   81,   86,   98,  102,  114,  117,  -22,  127,  137,
 /*    20 */   146,   28,   45,   61,   18,  128,  163,  164,  171,  172,
 /*    30 */   136,  -13,    4,  -13,   13,  -13,   26,   43,   92,  118,
 /*    40 */   133,  134,  145,  176,  158,  184,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   201,  200,  242,  242,  242,  242,  242,  242,  242,  242,
 /*    10 */   242,  242,  242,  242,  242,  242,  242,  242,  242,  242,
 /*    20 */   242,  242,  242,  242,  242,  242,  242,  242,  242,  242,
 /*    30 */   242,  242,  242,  242,  242,  242,  242,  242,  242,  242,
 /*    40 */   242,  242,  242,  242,  242,  242,  215,  242,  242,  242,
 /*    50 */   242,  242,  242,  242,  242,  242,  217,  242,  215,  242,
 /*    60 */   216,  242,  217,  242,  242,  242,  242,  242,  242,  242,
 /*    70 */   242,  242,  242,  213,  212,  217,  242,  242,  242,  242,
 /*    80 */   242,  242,  242,  242,  242,  242,  242,  213,  242,  242,
 /*    90 */   242,  242,  242,  242,  242,  242,  242,  237,  212,  242,
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
  "WS",            "DOT",           "STRING",        "NUMBER",      
  "MINUS",         "error",         "start",         "prog",        
  "domain",        "domains",       "predicate",     "decl",        
  "variables",     "rule",          "body",          "bodydef",     
  "bodydef2",      "head",          "headdef",       "ruleU",       
  "number",        "string",        "variable",      "lnumber",     
  "rnumber",     
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
 /*   9 */ "prog ::= prog NEWLINE",
 /*  10 */ "prog ::=",
 /*  11 */ "rule ::= number NEGATION LBRACKET ruleU RBRACKET",
 /*  12 */ "rule ::= NEGATION LBRACKET ruleU RBRACKET DOT",
 /*  13 */ "rule ::= LBRACKET ruleU RBRACKET DOT",
 /*  14 */ "ruleU ::= body CONJUNCTION bodydef",
 /*  15 */ "ruleU ::= body DISJUNCTION bodydef",
 /*  16 */ "rule ::= body CONJUNCTION bodydef DOT",
 /*  17 */ "rule ::= body DISJUNCTION bodydef DOT",
 /*  18 */ "rule ::= body IMPLICATION head DOT",
 /*  19 */ "rule ::= number body IMPLICATION head",
 /*  20 */ "rule ::= number NEGATION NEGATION LBRACKET body IMPLICATION head RBRACKET",
 /*  21 */ "body ::= body CONJUNCTION bodydef",
 /*  22 */ "body ::= body DISJUNCTION bodydef",
 /*  23 */ "body ::= bodydef",
 /*  24 */ "bodydef ::= string LBRACKET variables RBRACKET",
 /*  25 */ "bodydef ::= NEGATION string LBRACKET variables RBRACKET",
 /*  26 */ "bodydef ::= NEGATION NEGATION string LBRACKET variables RBRACKET",
 /*  27 */ "bodydef ::= LBRACKET NEGATION NEGATION string LBRACKET variables RBRACKET RBRACKET",
 /*  28 */ "bodydef ::= string EQUAL string",
 /*  29 */ "bodydef ::= string NEGATION EQUAL string",
 /*  30 */ "head ::= headdef",
 /*  31 */ "headdef ::= string LBRACKET variables RBRACKET",
 /*  32 */ "headdef ::= NEGATION string LBRACKET variables RBRACKET",
 /*  33 */ "decl ::= string LBRACKET variables RBRACKET",
 /*  34 */ "predicate ::= string LBRACKET variables RBRACKET DOT",
 /*  35 */ "predicate ::= number string LBRACKET variables RBRACKET",
 /*  36 */ "predicate ::= number NEGATION NEGATION string LBRACKET variables RBRACKET",
 /*  37 */ "predicate ::= number NEGATION string LBRACKET variables RBRACKET",
 /*  38 */ "predicate ::= NEGATION NEGATION string LBRACKET variables RBRACKET",
 /*  39 */ "domain ::= string EQUAL domains",
 /*  40 */ "domains ::= LPAREN variables RPAREN",
 /*  41 */ "variables ::= variable",
 /*  42 */ "variables ::= variables COMMA variable",
 /*  43 */ "variable ::= string",
 /*  44 */ "variable ::= number",
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
  { 18, 1 },
  { 19, 3 },
  { 19, 1 },
  { 19, 3 },
  { 19, 1 },
  { 19, 3 },
  { 19, 1 },
  { 19, 3 },
  { 19, 1 },
  { 19, 2 },
  { 19, 0 },
  { 25, 5 },
  { 25, 5 },
  { 25, 4 },
  { 31, 3 },
  { 31, 3 },
  { 25, 4 },
  { 25, 4 },
  { 25, 4 },
  { 25, 4 },
  { 25, 8 },
  { 26, 3 },
  { 26, 3 },
  { 26, 1 },
  { 27, 4 },
  { 27, 5 },
  { 27, 6 },
  { 27, 8 },
  { 27, 3 },
  { 27, 4 },
  { 29, 1 },
  { 30, 4 },
  { 30, 5 },
  { 23, 4 },
  { 22, 5 },
  { 22, 5 },
  { 22, 7 },
  { 22, 6 },
  { 22, 6 },
  { 20, 3 },
  { 21, 3 },
  { 24, 1 },
  { 24, 3 },
  { 34, 1 },
  { 34, 1 },
  { 33, 1 },
  { 32, 1 },
  { 32, 3 },
  { 32, 4 },
  { 35, 1 },
  { 36, 1 },
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
	tree->domains.insert(*yymsp[0].minor.yy51); 
	tree->domainNamesList.insert(yymsp[0].minor.yy51->getDomainVar());
	for(auto& v : yymsp[0].minor.yy51->getVars()){
		tree->domainList.insert(v);	
	}
	delete yymsp[0].minor.yy51;
}
        break;
      case 3: /* prog ::= prog NEWLINE predicate */
{ 
	if(yymsp[0].minor.yy26->needsToBeCompleted()){	
		FactCompletion f(*yymsp[0].minor.yy26);
		tree->facts.insert(std::pair<std::string,FactCompletion>(f.head.getVar(),f)); 
	}	
	delete yymsp[0].minor.yy26;
}
        break;
      case 4: /* prog ::= predicate */
{ 
	if(yymsp[0].minor.yy26->needsToBeCompleted()){
		FactCompletion f(*yymsp[0].minor.yy26);
		tree->facts.insert(std::pair<std::string,FactCompletion>(f.head.getVar(),f)); 	
	}
	delete yymsp[0].minor.yy26;
}
        break;
      case 5: /* prog ::= prog NEWLINE decl */
      case 6: /* prog ::= decl */ yytestcase(yyruleno==6);
{
	tree->variables.insert(*yymsp[0].minor.yy57);
	delete yymsp[0].minor.yy57;
}
        break;
      case 7: /* prog ::= prog NEWLINE rule */
{
	if((yymsp[0].minor.yy21->isHeadTop == false) && (yymsp[0].minor.yy21->toBeCompleted == true))
		tree->rules.insert(std::pair<std::string,RuleCompletion>(yymsp[0].minor.yy21->head.getVar(),*yymsp[0].minor.yy21));
	delete yymsp[0].minor.yy21;
}
        break;
      case 8: /* prog ::= rule */
{
	if((yymsp[0].minor.yy21->isHeadTop == false) && (yymsp[0].minor.yy21->toBeCompleted == true))
		tree->rules.insert(std::pair<std::string,RuleCompletion>(yymsp[0].minor.yy21->head.getVar(),*yymsp[0].minor.yy21));

	delete yymsp[0].minor.yy21;
}
        break;
      case 11: /* rule ::= number NEGATION LBRACKET ruleU RBRACKET */
{
	yygotominor.yy21 = yymsp[-1].minor.yy21;
	yymsp[-1].minor.yy21->toBeCompleted = false;
}
        break;
      case 12: /* rule ::= NEGATION LBRACKET ruleU RBRACKET DOT */
{
	yygotominor.yy21 = yymsp[-2].minor.yy21;
	yymsp[-2].minor.yy21->toBeCompleted = false;
}
        break;
      case 13: /* rule ::= LBRACKET ruleU RBRACKET DOT */
{
	yygotominor.yy21 = yymsp[-2].minor.yy21;
	yymsp[-2].minor.yy21->toBeCompleted = false;
	//segfault here
}
        break;
      case 14: /* ruleU ::= body CONJUNCTION bodydef */
      case 15: /* ruleU ::= body DISJUNCTION bodydef */ yytestcase(yyruleno==15);
{
	yygotominor.yy21 = new RuleCompletion;
	// yygotominor.yy21->toBeCompleted = false;	
	delete yymsp[-2].minor.yy53;
	delete yymsp[0].minor.yy20;
}
        break;
      case 16: /* rule ::= body CONJUNCTION bodydef DOT */
      case 17: /* rule ::= body DISJUNCTION bodydef DOT */ yytestcase(yyruleno==17);
{
	yygotominor.yy21 = new RuleCompletion;
	yygotominor.yy21->isHeadTop = true;	
	delete yymsp[-3].minor.yy53;
	delete yymsp[-1].minor.yy20;
}
        break;
      case 18: /* rule ::= body IMPLICATION head DOT */
{
	std::set<std::pair<std::string,std::string>> orphanVarsMap;
	std::set<std::pair<std::string,std::string>> orphanVarsHeadMap;
	std::vector<Predicate> predList = yymsp[-3].minor.yy53->getPredicate();
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


	for(auto& str : yymsp[-1].minor.yy1->getPredicate().getTokens()){
		if(tree->isConstant(str)){
			varMap[count++] = std::pair<int, std::string>(count, str);
		}
		else
			count++;
		
		if(tree->variables.find(yymsp[-1].minor.yy1->getPredicate().getVar()) == tree->variables.end()){
			undefined_predicate ex(yymsp[-1].minor.yy1->getPredicate().getVar());
			throw ex;
		}
		else	
			orphanVarsHeadMap.insert(std::pair<std::string, std::string>(str,tree->variables.find(yymsp[-1].minor.yy1->getPredicate().getVar())->getPosMap().at(tempCount++).getDomainVar()));
	}

	std::set<std::string> result;
		
	tree->removeConstantsPair(orphanVarsMap);
	tree->removeConstantsPair(orphanVarsHeadMap);
	
	std::set<std::pair<std::string,std::string>> resultMap;
	std::set_difference(orphanVarsMap.begin(), orphanVarsMap.end(), orphanVarsHeadMap.begin(), orphanVarsHeadMap.end(),std::inserter(resultMap, resultMap.end()), cmp());

	yygotominor.yy21 = new RuleCompletion(yymsp[-1].minor.yy1->getPredicate(),predList, resultMap, varMap);
	delete yymsp[-3].minor.yy53;
	delete yymsp[-1].minor.yy1;
}
        break;
      case 19: /* rule ::= number body IMPLICATION head */
{
	std::set<std::pair<std::string,std::string>> orphanVarsMap;
	std::set<std::pair<std::string,std::string>> orphanVarsHeadMap;
	std::vector<Predicate> predList = yymsp[-2].minor.yy53->getPredicate();
	for(auto& p : predList){
		int tempCount = 0;
		for(auto& v : p.getTokens()){
			orphanVarsMap.insert(std::pair<std::string, std::string>(v,tree->variables.find(p.getVar())->getPosMap().at(tempCount++).getDomainVar()));
		}
	}

	int count = 0;
	std::map<int,std::pair<int, std::string>> varMap;
	int tempCount = 0;

	for(auto& str : yymsp[0].minor.yy1->getPredicate().getTokens()){
		if(tree->isConstant(str)){
			varMap[count] = std::pair<int, std::string>(count, str);
		}
		else
			count++;
			
		orphanVarsHeadMap.insert(std::pair<std::string, std::string>(str,tree->variables.find(yymsp[0].minor.yy1->getPredicate().getVar())->getPosMap().at(tempCount++).getDomainVar()));
	}

	
	
	std::set<std::string> result;
		
	tree->removeConstantsPair(orphanVarsMap);
	tree->removeConstantsPair(orphanVarsHeadMap);
	
	std::set<std::pair<std::string,std::string>> resultMap;
	std::set_difference(orphanVarsMap.begin(), orphanVarsMap.end(), orphanVarsHeadMap.begin(), orphanVarsHeadMap.end(),std::inserter(resultMap, resultMap.end()), cmp());

	yygotominor.yy21 = new RuleCompletion(yymsp[0].minor.yy1->getPredicate(),predList, resultMap, varMap);
	delete yymsp[-2].minor.yy53;
	delete yymsp[0].minor.yy1;
}
        break;
      case 20: /* rule ::= number NEGATION NEGATION LBRACKET body IMPLICATION head RBRACKET */
{
	yygotominor.yy21 = new RuleCompletion;
	yygotominor.yy21->isHeadTop = true;	
	tree->statHasDblNeg = true;
	delete yymsp[-3].minor.yy53;
	delete yymsp[-1].minor.yy1;
}
        break;
      case 21: /* body ::= body CONJUNCTION bodydef */
{
	yygotominor.yy53 = yymsp[-2].minor.yy53;
	yymsp[-2].minor.yy53->addPredicate(yymsp[0].minor.yy20->getPredicate());
	delete yymsp[0].minor.yy20;
}
        break;
      case 22: /* body ::= body DISJUNCTION bodydef */
{
	yygotominor.yy53 = yymsp[-2].minor.yy53;
	delete yymsp[0].minor.yy20;
}
        break;
      case 23: /* body ::= bodydef */
{
	yygotominor.yy53 = new Body;
	yygotominor.yy53->addPredicate(yymsp[0].minor.yy20->getPredicate());
	delete yymsp[0].minor.yy20;
}
        break;
      case 24: /* bodydef ::= string LBRACKET variables RBRACKET */
{	
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-1].minor.yy45)
		vars.push_back(*v);
	
	Predicate p(yymsp[-3].minor.yy0->token, vars);
	yygotominor.yy20 = new BodyDef;
	yygotominor.yy20->addPredicate(p);
	delete yymsp[-1].minor.yy45;
}
        break;
      case 25: /* bodydef ::= NEGATION string LBRACKET variables RBRACKET */
{	
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-1].minor.yy45)
		vars.push_back(*v);
	
	Predicate p(yymsp[-3].minor.yy0->token, vars);
	p.setSingleNegation();
	yygotominor.yy20 = new BodyDef;
	yygotominor.yy20->addPredicate(p);
	delete yymsp[-1].minor.yy45;
}
        break;
      case 26: /* bodydef ::= NEGATION NEGATION string LBRACKET variables RBRACKET */
{	
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-1].minor.yy45)
		vars.push_back(*v);
	
	Predicate p(yymsp[-3].minor.yy0->token, vars);
	p.setDoubleNegation();
	yygotominor.yy20 = new BodyDef;
	yygotominor.yy20->addPredicate(p);
	tree->statHasDblNeg = true;
	delete yymsp[-1].minor.yy45;
}
        break;
      case 27: /* bodydef ::= LBRACKET NEGATION NEGATION string LBRACKET variables RBRACKET RBRACKET */
{	
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-2].minor.yy45)
		vars.push_back(*v);
	
	Predicate p(yymsp[-4].minor.yy0->token, vars);
	p.setDoubleNegation();
	tree->statHasDblNeg = true;
	yygotominor.yy20 = new BodyDef;
	yygotominor.yy20->addPredicate(p);
	delete yymsp[-2].minor.yy45;
}
        break;
      case 28: /* bodydef ::= string EQUAL string */
{
	Predicate p(yymsp[-2].minor.yy0->token,yymsp[0].minor.yy0->token);
	p.setEquality();
	yygotominor.yy20 = new BodyDef;
	yygotominor.yy20->addPredicate(p);
}
        break;
      case 29: /* bodydef ::= string NEGATION EQUAL string */
{
	Predicate p(yymsp[-3].minor.yy0->token,yymsp[0].minor.yy0->token);
	p.setInEquality();
	yygotominor.yy20 = new BodyDef;
	yygotominor.yy20->addPredicate(p);
}
        break;
      case 30: /* head ::= headdef */
{ 
	yygotominor.yy1 = yymsp[0].minor.yy1;
}
        break;
      case 31: /* headdef ::= string LBRACKET variables RBRACKET */
{
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-1].minor.yy45)
		vars.push_back(*v);
	
	Predicate p(yymsp[-3].minor.yy0->token, vars);
	yygotominor.yy1 = new Head;
	yygotominor.yy1->addPredicate(p);
	delete yymsp[-1].minor.yy45;
}
        break;
      case 32: /* headdef ::= NEGATION string LBRACKET variables RBRACKET */
{
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-1].minor.yy45)
		vars.push_back(*v);
	
	Predicate p(yymsp[-3].minor.yy0->token, vars);
	p.setSingleNegation();
	yygotominor.yy1 = new Head;
	yygotominor.yy1->addPredicate(p);
	delete yymsp[-1].minor.yy45;
}
        break;
      case 33: /* decl ::= string LBRACKET variables RBRACKET */
{
	yygotominor.yy57 = new Variable;
	std::map<int, Domain> posMap;
	std::set<Domain>::iterator itr;
	int i=0;
	for(auto& v : *yymsp[-1].minor.yy45){
		itr = tree->domains.find(*v);
		if (itr == tree->domains.end()){
			std::cout<<"Error:Domain:"+ *v +" not found.\n";
			//Exit
		}
		else{
			// itr = tree->domains.find(*v);
			yygotominor.yy57->setVar(yymsp[-3].minor.yy0->token);
			posMap[i++] = *itr;
		}
	}
	yygotominor.yy57->setPosMap(posMap);
	delete yymsp[-1].minor.yy45;
}
        break;
      case 34: /* predicate ::= string LBRACKET variables RBRACKET DOT */
{
	yygotominor.yy26 = new Predicate;
	yygotominor.yy26->setVar(yymsp[-4].minor.yy0->token);
	yygotominor.yy26->setTokens(*yymsp[-2].minor.yy45);
	delete yymsp[-2].minor.yy45;
}
        break;
      case 35: /* predicate ::= number string LBRACKET variables RBRACKET */
{
	yygotominor.yy26 = new Predicate;
	yygotominor.yy26->setVar(yymsp[-3].minor.yy0->token);
	yygotominor.yy26->setTokens(*yymsp[-1].minor.yy45);
	delete yymsp[-1].minor.yy45;
}
        break;
      case 36: /* predicate ::= number NEGATION NEGATION string LBRACKET variables RBRACKET */
      case 38: /* predicate ::= NEGATION NEGATION string LBRACKET variables RBRACKET */ yytestcase(yyruleno==38);
{
	yygotominor.yy26 = new Predicate;
	yygotominor.yy26->notToBeCompleted();
	tree->statHasDblNeg = true;
	delete yymsp[-1].minor.yy45;
}
        break;
      case 37: /* predicate ::= number NEGATION string LBRACKET variables RBRACKET */
{
	yygotominor.yy26 = new Predicate;
	yygotominor.yy26->notToBeCompleted();
	// tree->statHasDblNeg = true;
	delete yymsp[-1].minor.yy45;
}
        break;
      case 39: /* domain ::= string EQUAL domains */
{ 
	yygotominor.yy51 = yymsp[0].minor.yy51;
	yymsp[0].minor.yy51->setDomainVar(yymsp[-2].minor.yy0->token);
}
        break;
      case 40: /* domains ::= LPAREN variables RPAREN */
{
	yygotominor.yy51 = new Domain();
	yygotominor.yy51->setVars(*yymsp[-1].minor.yy45);
	delete yymsp[-1].minor.yy45;
}
        break;
      case 41: /* variables ::= variable */
{
	yygotominor.yy45 = new std::vector<std::string*>();
	yygotominor.yy45->push_back(yymsp[0].minor.yy0->token);
}
        break;
      case 42: /* variables ::= variables COMMA variable */
{
	yygotominor.yy45 = yymsp[-2].minor.yy45;
	yymsp[-2].minor.yy45->push_back(yymsp[0].minor.yy0->token);
}
        break;
      case 43: /* variable ::= string */
      case 44: /* variable ::= number */ yytestcase(yyruleno==44);
      case 45: /* string ::= STRING */ yytestcase(yyruleno==45);
      case 46: /* number ::= NUMBER */ yytestcase(yyruleno==46);
{ yygotominor.yy0=yymsp[0].minor.yy0;}
        break;
      case 47: /* number ::= lnumber DOT rnumber */
{ 
	// yygotominor.yy0 = new Token(*(yymsp[-2].minor.yy0->token)+"."+*(yymsp[0].minor.yy0->token));
	yygotominor.yy0 = yymsp[-2].minor.yy0;
	yygotominor.yy0->modifyToken(*(yymsp[-2].minor.yy0->token)+"."+*(yymsp[0].minor.yy0->token));
}
        break;
      case 48: /* number ::= MINUS lnumber DOT rnumber */
{
	yygotominor.yy0 = yymsp[-2].minor.yy0;
	yygotominor.yy0->modifyToken("-"+*(yymsp[-2].minor.yy0->token)+"."+*(yymsp[0].minor.yy0->token));
	// yygotominor.yy0 = new Token("-"+*(yymsp[-2].minor.yy0->token)+"."+*(yymsp[0].minor.yy0->token));
}
        break;
      case 49: /* lnumber ::= NUMBER */
      case 50: /* rnumber ::= NUMBER */ yytestcase(yyruleno==50);
{ yygotominor.yy0=yymsp[0].minor.yy0; }
        break;
      default:
      /* (0) start ::= prog */ yytestcase(yyruleno==0);
      /* (9) prog ::= prog NEWLINE */ yytestcase(yyruleno==9);
      /* (10) prog ::= */ yytestcase(yyruleno==10);
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

    // std::cout<<"Giving up.  Parser is lost...\n";

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

	 // std::cout << ;
    int n = sizeof(yyTokenName) / sizeof(yyTokenName[0]);
    for (int i = 0; i < n; ++i) {
            int a = yy_find_shift_action(yypParser, (YYCODETYPE)i);
            if (a < YYNSTATE + YYNRULE) {
                    // std::cout << "expected " << yyTokenName[i] << std::endl;
            		yy_parse_failed(yypParser);
                    throw syntax_exception("Syntax Error - Expected " + std::string(yyTokenName[i]) + " Found " + std::string(yyTokenName[yymajor])
+ "\n");
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

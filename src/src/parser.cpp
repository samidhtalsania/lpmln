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
#define YYNSTATE             95
#define YYNRULE              55
#define YY_MAX_SHIFT         94
#define YY_MIN_SHIFTREDUCE   139
#define YY_MAX_SHIFTREDUCE   193
#define YY_MIN_REDUCE        194
#define YY_MAX_REDUCE        248
#define YY_ERROR_ACTION      249
#define YY_ACCEPT_ACTION     250
#define YY_NO_ACTION         251
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
#define YY_ACTTAB_COUNT (270)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   250,   69,  141,   78,  143,  145,  188,  147,  149,   52,
 /*    10 */   164,   44,  188,   91,   42,   18,   46,  140,   90,  142,
 /*    20 */   144,  163,  146,  148,   52,  164,  193,   53,    2,   15,
 /*    30 */    18,   46,   31,   90,   55,   33,  188,   91,   42,  188,
 /*    40 */   188,   56,   14,  186,  185,  183,   90,   71,   58,  188,
 /*    50 */   186,  185,  183,   90,   13,   60,  182,  186,  185,  183,
 /*    60 */    90,   13,   61,  169,  186,  185,  183,   90,   45,   62,
 /*    70 */   234,  186,  185,  183,   90,  234,   63,   13,  186,  185,
 /*    80 */   183,   90,   13,   64,   57,  186,  185,  183,   90,   59,
 /*    90 */    65,  235,  186,  185,  183,   90,  235,   66,   13,  186,
 /*   100 */   185,  183,   90,  168,   67,  176,  186,  185,  183,   90,
 /*   110 */    49,  164,   81,  186,  185,  183,   90,   53,  186,  185,
 /*   120 */   184,   90,   68,  164,   85,   83,  191,   77,   34,   53,
 /*   130 */    68,  164,  188,   50,  164,   94,   83,   53,   16,   32,
 /*   140 */    48,   34,   86,  188,   83,  188,   88,   30,   51,  164,
 /*   150 */    83,  188,   17,   38,  190,   47,  188,  188,  163,  155,
 /*   160 */   162,  154,   20,   19,   54,  192,   54,  162,   70,  174,
 /*   170 */   160,  174,   72,   53,   72,  159,  174,   73,  174,   72,
 /*   180 */   232,   72,   29,   37,   36,  232,  161,  188,   89,    3,
 /*   190 */   187,    4,   79,  178,   79,   36,   26,   25,  158,    6,
 /*   200 */    21,  194,    5,   26,   25,   79,    1,   22,    7,   26,
 /*   210 */    25,   28,   27,   23,   36,   24,   40,  181,   76,  157,
 /*   220 */    13,    9,   74,   12,   79,   75,   87,  175,   53,   13,
 /*   230 */   168,   53,   13,   13,   13,   13,  166,  156,  153,  165,
 /*   240 */    80,   84,   92,    8,   35,  167,   10,   39,   37,  226,
 /*   250 */    82,  228,   11,  196,  227,  196,  196,  196,  196,  225,
 /*   260 */    41,   43,  247,  196,  152,  196,  196,  196,  196,   93,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    19,   20,   21,   35,   23,   24,   15,   26,   27,   28,
 /*    10 */    29,   14,   15,   16,   17,   34,   35,   21,   37,   23,
 /*    20 */    24,   29,   26,   27,   28,   29,   16,   35,    3,    8,
 /*    30 */    34,   35,   11,   37,   25,   11,   15,   16,   17,   15,
 /*    40 */    15,   25,    8,   34,   35,   36,   37,   35,   25,   15,
 /*    50 */    34,   35,   36,   37,    2,   25,    4,   34,   35,   36,
 /*    60 */    37,    2,   25,   35,   34,   35,   36,   37,    9,   25,
 /*    70 */     0,   34,   35,   36,   37,    5,   25,    2,   34,   35,
 /*    80 */    36,   37,    2,   25,    9,   34,   35,   36,   37,    9,
 /*    90 */    25,    0,   34,   35,   36,   37,    5,   25,    2,   34,
 /*   100 */    35,   36,   37,   35,   25,    9,   34,   35,   36,   37,
 /*   110 */    28,   29,   35,   34,   35,   36,   37,   35,   34,   35,
 /*   120 */    36,   37,   28,   29,   35,    8,   38,   33,   11,   35,
 /*   130 */    28,   29,   15,   28,   29,   33,    8,   35,    8,   11,
 /*   140 */    35,   11,   35,   15,    8,   15,   35,   11,   28,   29,
 /*   150 */     8,   15,   11,   11,   38,   35,   15,   15,   29,   30,
 /*   160 */    29,   30,    6,    7,   35,   16,   35,   29,   31,   32,
 /*   170 */    31,   32,   35,   35,   35,   31,   32,   31,   32,   35,
 /*   180 */     0,   35,    1,   11,    1,    5,    9,   15,   37,    8,
 /*   190 */    35,    8,   11,   13,   11,    1,    6,    7,   13,    8,
 /*   200 */    10,    0,    8,    6,    7,   11,    5,   10,    8,    6,
 /*   210 */     7,    6,    7,   10,    1,   10,    1,   22,    9,   13,
 /*   220 */     2,    8,   29,    8,   11,   29,   11,    9,   35,    2,
 /*   230 */    35,   35,    2,    2,    2,    2,    9,   13,   13,    9,
 /*   240 */     9,    9,    9,    8,    1,    9,    8,    1,   11,    9,
 /*   250 */    11,    9,    8,   39,    9,   39,   39,   39,   39,    9,
 /*   260 */    13,   13,   13,   39,   13,   39,   39,   39,   39,    9,
};
#define YY_SHIFT_USE_DFLT (-10)
#define YY_SHIFT_COUNT (94)
#define YY_SHIFT_MIN   (-9)
#define YY_SHIFT_MAX   (260)
static const short yy_shift_ofst[] = {
 /*     0 */    21,   21,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
 /*    10 */    -3,   -3,   -3,   -3,  117,  128,  128,  130,  136,  142,
 /*    20 */   142,   24,   24,   24,   24,  117,  117,  117,  117,   25,
 /*    30 */   141,   34,  172,   -9,   -9,   -9,   -9,   -9,   -9,   -9,
 /*    40 */    -9,   10,  149,   10,   -9,  180,  181,  183,  194,  190,
 /*    50 */   197,  203,  205,  213,  215,   52,   59,   70,   75,   91,
 /*    60 */    80,   96,  218,  227,  230,  231,  232,  233,  156,  201,
 /*    70 */   177,  191,  200,  185,  206,  224,  225,  209,  235,  243,
 /*    80 */   236,  238,  237,  239,  240,  244,  242,  246,  245,  247,
 /*    90 */   248,  249,  250,  251,  260,
};
#define YY_REDUCE_USE_DFLT (-33)
#define YY_REDUCE_COUNT (44)
#define YY_REDUCE_MIN   (-32)
#define YY_REDUCE_MAX   (196)
static const short yy_reduce_ofst[] = {
 /*     0 */   -19,   -4,    9,   16,   23,   30,   37,   44,   51,   58,
 /*    10 */    65,   72,   79,   84,   94,  102,   82,  105,  120,  129,
 /*    20 */   131,  137,  139,  144,  146,   -8,  138,  193,  196,  195,
 /*    30 */   -32,  -32,  -32,   12,  -32,   28,   68,   77,   89,  107,
 /*    40 */   111,   88,  151,  116,  155,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   206,  205,  249,  249,  249,  249,  249,  249,  249,  249,
 /*    10 */   249,  249,  249,  249,  249,  249,  249,  249,  249,  249,
 /*    20 */   249,  249,  249,  249,  249,  249,  249,  249,  249,  249,
 /*    30 */   249,  249,  249,  249,  249,  249,  249,  249,  249,  249,
 /*    40 */   249,  249,  249,  249,  249,  220,  249,  249,  249,  249,
 /*    50 */   249,  249,  249,  249,  249,  249,  249,  220,  249,  220,
 /*    60 */   249,  249,  249,  249,  249,  249,  249,  249,  249,  249,
 /*    70 */   249,  249,  249,  249,  218,  217,  249,  249,  249,  249,
 /*    80 */   249,  249,  249,  249,  221,  249,  224,  249,  223,  249,
 /*    90 */   249,  244,  220,  249,  249,
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
 /*  21 */ "rule ::= number NEGATION NEGATION body IMPLICATION head",
 /*  22 */ "rule ::= number NEGATION NEGATION LBRACKET body IMPLICATION head RBRACKET",
 /*  23 */ "body ::= body CONJUNCTION bodydef",
 /*  24 */ "body ::= body DISJUNCTION bodydef",
 /*  25 */ "body ::= bodydef",
 /*  26 */ "bodydef ::= string LBRACKET variables RBRACKET",
 /*  27 */ "bodydef ::= NEGATION string LBRACKET variables RBRACKET",
 /*  28 */ "bodydef ::= LBRACKET NEGATION NEGATION string LBRACKET variables RBRACKET RBRACKET",
 /*  29 */ "bodydef ::= string EQUAL string",
 /*  30 */ "bodydef ::= string NEGATION EQUAL string",
 /*  31 */ "bodydef2 ::= string LBRACKET variables RBRACKET",
 /*  32 */ "bodydef2 ::= NEGATION string LBRACKET variables RBRACKET",
 /*  33 */ "bodydef2 ::= string EQUAL string",
 /*  34 */ "bodydef2 ::= string NEGATION EQUAL string",
 /*  35 */ "head ::= headdef",
 /*  36 */ "headdef ::= string LBRACKET variables RBRACKET",
 /*  37 */ "headdef ::= NEGATION string LBRACKET variables RBRACKET",
 /*  38 */ "decl ::= string LBRACKET variables RBRACKET",
 /*  39 */ "predicate ::= string LBRACKET variables RBRACKET DOT",
 /*  40 */ "predicate ::= number string LBRACKET variables RBRACKET",
 /*  41 */ "predicate ::= number NEGATION NEGATION string LBRACKET variables RBRACKET",
 /*  42 */ "domain ::= string EQUAL domains",
 /*  43 */ "domains ::= LPAREN variables RPAREN",
 /*  44 */ "variables ::= variable",
 /*  45 */ "variables ::= variables COMMA variable",
 /*  46 */ "variable ::= string",
 /*  47 */ "variable ::= number",
 /*  48 */ "variable ::= PLUS string",
 /*  49 */ "string ::= STRING",
 /*  50 */ "number ::= NUMBER",
 /*  51 */ "number ::= lnumber DOT rnumber",
 /*  52 */ "number ::= MINUS lnumber DOT rnumber",
 /*  53 */ "lnumber ::= NUMBER",
 /*  54 */ "rnumber ::= NUMBER",
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
  { 26, 6 },
  { 26, 8 },
  { 28, 3 },
  { 28, 3 },
  { 28, 1 },
  { 29, 4 },
  { 29, 5 },
  { 29, 8 },
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
  { 23, 7 },
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
{ 
	if(yymsp[0].minor.yy6->needsToBeCompleted()){	
		FactCompletion f(*yymsp[0].minor.yy6);
		tree->facts.insert(std::pair<std::string,FactCompletion>(f.head.getVar(),f)); 
	}	
	delete yymsp[0].minor.yy6;
}
        break;
      case 4: /* prog ::= predicate */
{ 
	if(yymsp[0].minor.yy6->needsToBeCompleted()){
		FactCompletion f(*yymsp[0].minor.yy6);
		tree->facts.insert(std::pair<std::string,FactCompletion>(f.head.getVar(),f)); 	
	}
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
      case 21: /* rule ::= number NEGATION NEGATION body IMPLICATION head */
{
	tree->statHasDblNeg = true;
	yygotominor.yy75 = new RuleCompletion;
	yygotominor.yy75->isHeadTop = true;	
	delete yymsp[-2].minor.yy25;
	delete yymsp[0].minor.yy23;
}
        break;
      case 22: /* rule ::= number NEGATION NEGATION LBRACKET body IMPLICATION head RBRACKET */
{
	yygotominor.yy75 = new RuleCompletion;
	yygotominor.yy75->isHeadTop = true;	
	tree->statHasDblNeg = true;
	delete yymsp[-3].minor.yy25;
	delete yymsp[-1].minor.yy23;
}
        break;
      case 23: /* body ::= body CONJUNCTION bodydef */
{
	yygotominor.yy25 = yymsp[-2].minor.yy25;
	yymsp[-2].minor.yy25->addPredicate(yymsp[0].minor.yy30->getPredicate());
	delete yymsp[0].minor.yy30;
}
        break;
      case 24: /* body ::= body DISJUNCTION bodydef */
{
	yygotominor.yy25 = yymsp[-2].minor.yy25;
	delete yymsp[0].minor.yy30;
}
        break;
      case 25: /* body ::= bodydef */
{
	yygotominor.yy25 = new Body;
	yygotominor.yy25->addPredicate(yymsp[0].minor.yy30->getPredicate());
	delete yymsp[0].minor.yy30;
}
        break;
      case 26: /* bodydef ::= string LBRACKET variables RBRACKET */
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
      case 27: /* bodydef ::= NEGATION string LBRACKET variables RBRACKET */
{	
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-1].minor.yy31)
		vars.push_back(*v);
	
	Predicate p(yymsp[-3].minor.yy0->token, vars);
	p.setSingleNegation();
	yygotominor.yy30 = new BodyDef;
	yygotominor.yy30->addPredicate(p);
	delete yymsp[-1].minor.yy31;
}
        break;
      case 28: /* bodydef ::= LBRACKET NEGATION NEGATION string LBRACKET variables RBRACKET RBRACKET */
{	
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-2].minor.yy31)
		vars.push_back(*v);
	
	Predicate p(yymsp[-4].minor.yy0->token, vars);
	p.setDoubleNegation();
	tree->statHasDblNeg = true;
	yygotominor.yy30 = new BodyDef;
	yygotominor.yy30->addPredicate(p);
	delete yymsp[-2].minor.yy31;
}
        break;
      case 29: /* bodydef ::= string EQUAL string */
{
	Predicate p(yymsp[-2].minor.yy0->token,yymsp[0].minor.yy0->token);
	p.setEquality();
	yygotominor.yy30 = new BodyDef;
	yygotominor.yy30->addPredicate(p);
}
        break;
      case 30: /* bodydef ::= string NEGATION EQUAL string */
{
	Predicate p(yymsp[-3].minor.yy0->token,yymsp[0].minor.yy0->token);
	p.setInEquality();
	yygotominor.yy30 = new BodyDef;
	yygotominor.yy30->addPredicate(p);
}
        break;
      case 31: /* bodydef2 ::= string LBRACKET variables RBRACKET */
      case 32: /* bodydef2 ::= NEGATION string LBRACKET variables RBRACKET */ yytestcase(yyruleno==32);
{delete yymsp[-1].minor.yy31;}
        break;
      case 35: /* head ::= headdef */
{ 
	yygotominor.yy23 = yymsp[0].minor.yy23;
}
        break;
      case 36: /* headdef ::= string LBRACKET variables RBRACKET */
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
      case 37: /* headdef ::= NEGATION string LBRACKET variables RBRACKET */
{
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-1].minor.yy31)
		vars.push_back(*v);
	
	Predicate p(yymsp[-3].minor.yy0->token, vars);
	p.setSingleNegation();
	yygotominor.yy23 = new Head;
	yygotominor.yy23->addPredicate(p);
	delete yymsp[-1].minor.yy31;
}
        break;
      case 38: /* decl ::= string LBRACKET variables RBRACKET */
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
      case 39: /* predicate ::= string LBRACKET variables RBRACKET DOT */
{
	yygotominor.yy6 = new Predicate;
	yygotominor.yy6->setVar(yymsp[-4].minor.yy0->token);
	yygotominor.yy6->setTokens(*yymsp[-2].minor.yy31);
	delete yymsp[-2].minor.yy31;
}
        break;
      case 40: /* predicate ::= number string LBRACKET variables RBRACKET */
{
	yygotominor.yy6 = new Predicate;
	yygotominor.yy6->setVar(yymsp[-3].minor.yy0->token);
	yygotominor.yy6->setTokens(*yymsp[-1].minor.yy31);
	delete yymsp[-1].minor.yy31;
}
        break;
      case 41: /* predicate ::= number NEGATION NEGATION string LBRACKET variables RBRACKET */
{
	yygotominor.yy6 = new Predicate;
	yygotominor.yy6->notToBeCompleted();
	tree->statHasDblNeg = true;
	delete yymsp[-1].minor.yy31;
}
        break;
      case 42: /* domain ::= string EQUAL domains */
{ 
	yygotominor.yy61 = yymsp[0].minor.yy61;
	yymsp[0].minor.yy61->setDomainVar(yymsp[-2].minor.yy0->token);
}
        break;
      case 43: /* domains ::= LPAREN variables RPAREN */
{
	yygotominor.yy61 = new Domain();
	yygotominor.yy61->setVars(*yymsp[-1].minor.yy31);
	delete yymsp[-1].minor.yy31;
}
        break;
      case 44: /* variables ::= variable */
{
	yygotominor.yy31 = new std::vector<std::string*>();
	yygotominor.yy31->push_back(yymsp[0].minor.yy0->token);
}
        break;
      case 45: /* variables ::= variables COMMA variable */
{
	yygotominor.yy31 = yymsp[-2].minor.yy31;
	yymsp[-2].minor.yy31->push_back(yymsp[0].minor.yy0->token);
}
        break;
      case 46: /* variable ::= string */
      case 47: /* variable ::= number */ yytestcase(yyruleno==47);
      case 48: /* variable ::= PLUS string */ yytestcase(yyruleno==48);
      case 49: /* string ::= STRING */ yytestcase(yyruleno==49);
      case 50: /* number ::= NUMBER */ yytestcase(yyruleno==50);
{ yygotominor.yy0=yymsp[0].minor.yy0;}
        break;
      case 51: /* number ::= lnumber DOT rnumber */
{ 
	// yygotominor.yy0 = new Token(*(yymsp[-2].minor.yy0->token)+"."+*(yymsp[0].minor.yy0->token));
	yygotominor.yy0 = yymsp[-2].minor.yy0;
	yygotominor.yy0->modifyToken(*(yymsp[-2].minor.yy0->token)+"."+*(yymsp[0].minor.yy0->token));
}
        break;
      case 52: /* number ::= MINUS lnumber DOT rnumber */
{
	yygotominor.yy0 = yymsp[-2].minor.yy0;
	yygotominor.yy0->modifyToken("-"+*(yymsp[-2].minor.yy0->token)+"."+*(yymsp[0].minor.yy0->token));
	// yygotominor.yy0 = new Token("-"+*(yymsp[-2].minor.yy0->token)+"."+*(yymsp[0].minor.yy0->token));
}
        break;
      case 53: /* lnumber ::= NUMBER */
      case 54: /* rnumber ::= NUMBER */ yytestcase(yyruleno==54);
{ yygotominor.yy0=yymsp[0].minor.yy0; }
        break;
      default:
      /* (0) start ::= prog */ yytestcase(yyruleno==0);
      /* (11) prog ::= prog NEWLINE */ yytestcase(yyruleno==11);
      /* (12) prog ::= */ yytestcase(yyruleno==12);
      /* (13) ruleU ::= LBRACKET ruleI RBRACKET DOT */ yytestcase(yyruleno==13);
      /* (14) ruleU ::= NEGATION LBRACKET ruleI RBRACKET DOT */ yytestcase(yyruleno==14);
      /* (33) bodydef2 ::= string EQUAL string */ yytestcase(yyruleno==33);
      /* (34) bodydef2 ::= string NEGATION EQUAL string */ yytestcase(yyruleno==34);
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

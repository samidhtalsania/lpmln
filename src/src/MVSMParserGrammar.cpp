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

	#define SPACE " "
	#define COMMENT "//"

	struct cmp{
		bool operator()(const std::pair<std::string, std::string>& left, const std::pair<std::string, std::string>& right) const{
			return left.first < right.first;
		}
	};

	RuleCompletion* RuleCompletion_BH(Body*, Head*, Tree*);
	void RuleCompletion_HD_BT(Head*, Tree*);
	void RuleCompletion_HD_BC(Head*, Body*, bool, Tree*);

#include "MVSMParserGrammar.h"
/**************** End of %include directives **********************************/
/* These constants specify the various numeric values for terminal symbols
** in a format understandable to "makeheaders".  This section is blank unless
** "lemon" is run with the "-m" command-line option.
***************** Begin makeheaders token definitions *************************/
#if INTERFACE
#define MVSM_PARSE_TOKEN_EQUAL                           1
#define MVSM_PARSE_TOKEN_COMMA                           2
#define MVSM_PARSE_TOKEN_LPAREN                          3
#define MVSM_PARSE_TOKEN_RPAREN                          4
#define MVSM_PARSE_TOKEN_NEWLINE                         5
#define MVSM_PARSE_TOKEN_CONJUNCTION                     6
#define MVSM_PARSE_TOKEN_DISJUNCTION                     7
#define MVSM_PARSE_TOKEN_LBRACKET                        8
#define MVSM_PARSE_TOKEN_RBRACKET                        9
#define MVSM_PARSE_TOKEN_IMPLICATION                    10
#define MVSM_PARSE_TOKEN_REVERSE_IMPLICATION            11
#define MVSM_PARSE_TOKEN_SORTS                          12
#define MVSM_PARSE_TOKEN_NEGATION                       13
#define MVSM_PARSE_TOKEN_WS                             14
#define MVSM_PARSE_TOKEN_DOT                            15
#define MVSM_PARSE_TOKEN_SEMI_COLON                     16
#define MVSM_PARSE_TOKEN_OBJECTS                        17
#define MVSM_PARSE_TOKEN_COLON                          18
#define MVSM_PARSE_TOKEN_CONSTANTS                      19
#define MVSM_PARSE_TOKEN_STRING                         20
#define MVSM_PARSE_TOKEN_NUMBER                         21
#define MVSM_PARSE_TOKEN_MINUS                          22
#endif
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
**    MVSMParserGrammarTOKENTYPE     is the data type used for minor type for terminal
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
**                       which is MVSMParserGrammarTOKENTYPE.  The entry in the union
**                       for terminal symbols is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    MVSMParserGrammarARG_SDECL     A static variable declaration for the %extra_argument
**    MVSMParserGrammarARG_PDECL     A parameter declaration for the %extra_argument
**    MVSMParserGrammarARG_STORE     Code to store %extra_argument into yypParser
**    MVSMParserGrammarARG_FETCH     Code to extract %extra_argument from yypParser
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
#define YYNOCODE 44
#define YYACTIONTYPE unsigned short int
#if INTERFACE
#define MVSMParserGrammarTOKENTYPE Token*
#endif
typedef union {
  int yyinit;
  MVSMParserGrammarTOKENTYPE yy0;
  Variable* yy1;
  BodyDef* yy28;
  Predicate* yy32;
  Head* yy37;
  RuleCompletion* yy59;
  Tree* yy61;
  std::vector<std::string*>* yy77;
  Body* yy83;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#if INTERFACE
#define MVSMParserGrammarARG_SDECL Tree* tree;
#define MVSMParserGrammarARG_PDECL ,Tree* tree
#define MVSMParserGrammarARG_FETCH Tree* tree = yypParser->tree
#define MVSMParserGrammarARG_STORE yypParser->tree = tree
#endif
#define YYNSTATE             110
#define YYNRULE              63
#define YY_MAX_SHIFT         109
#define YY_MIN_SHIFTREDUCE   161
#define YY_MAX_SHIFTREDUCE   223
#define YY_MIN_REDUCE        224
#define YY_MAX_REDUCE        286
#define YY_ERROR_ACTION      287
#define YY_ACCEPT_ACTION     288
#define YY_NO_ACTION         289
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
#define YY_ACTTAB_COUNT (298)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   288,   76,  178,  180,   73,  163,   47,  168,  173,  182,
 /*    10 */    25,  200,   99,   55,   20,   17,  214,  107,  177,  179,
 /*    20 */    73,  162,   47,  167,  172,  181,   51,  200,  216,   55,
 /*    30 */    23,   17,  214,  107,   86,   19,   97,  217,  214,  107,
 /*    40 */     3,   34,  218,   21,  164,   31,  265,  216,  218,  169,
 /*    50 */   265,  174,  218,  108,   44,   50,  217,  215,  107,  101,
 /*    60 */    91,  266,   93,   82,   50,  266,  265,   27,  101,   91,
 /*    70 */   265,   93,   84,   58,  209,  216,  197,  109,   60,   85,
 /*    80 */   216,   62,   50,  216,  217,  214,  107,   80,  218,  217,
 /*    90 */   214,  107,  217,  214,  107,    9,   78,   67,  103,  216,
 /*   100 */    33,   68,   89,  216,  218,  108,   44,  218,  217,  214,
 /*   110 */   107,   50,  217,  214,  107,  101,   91,   42,   93,   90,
 /*   120 */    69,   95,  216,   70,    5,  216,   71,   79,  216,  105,
 /*   130 */    26,  217,  214,  107,  217,  214,  107,  217,  214,  107,
 /*   140 */    50,   75,   98,  216,  101,   91,   97,   93,  102,   42,
 /*   150 */    49,   35,  217,  214,  107,  200,   15,   66,  218,   27,
 /*   160 */    72,  105,   50,  165,  166,   50,   52,  201,  194,   50,
 /*   170 */   200,    4,   53,   54,  201,   50,   35,   50,   42,   56,
 /*   180 */   201,   63,  201,  218,   50,   13,  171,  170,   50,  200,
 /*   190 */   105,   64,   87,  201,   50,   50,   50,   50,   50,  199,
 /*   200 */   198,   65,   92,  100,   36,   32,   37,   39,   16,   27,
 /*   210 */    16,  218,  218,  218,  218,   77,   16,   57,  191,   16,
 /*   220 */   267,  223,   27,   59,  267,  196,   61,   26,  262,   16,
 /*   230 */    28,   22,  262,   16,   24,   16,   88,   16,   16,   16,
 /*   240 */    94,  207,  204,   16,  203,  202,  224,  176,  175,  206,
 /*   250 */    48,    1,  221,  106,   74,  104,    2,  220,  213,  222,
 /*   260 */    18,   81,  192,   83,    6,  188,  187,    7,   27,  205,
 /*   270 */   186,    8,  263,  253,   29,   40,   10,   30,   11,   38,
 /*   280 */    12,   14,   96,  252,  185,   41,  226,  226,  226,  226,
 /*   290 */   226,   43,   45,  285,  226,  226,  226,   46,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    24,   25,   26,   27,   28,   29,   30,   31,   32,   33,
 /*    10 */     7,   35,   30,   37,   11,   39,   40,   41,   26,   27,
 /*    20 */    28,   29,   30,   31,   32,   33,   28,   35,   30,   37,
 /*    30 */     8,   39,   40,   41,   30,    3,    8,   39,   40,   41,
 /*    40 */     8,   13,   20,   11,   12,   13,    7,   30,   20,   17,
 /*    50 */    11,   19,   20,   21,   22,   30,   39,   40,   41,   34,
 /*    60 */    35,    7,   37,   38,   30,   11,    7,    6,   34,   35,
 /*    70 */    11,   37,   38,   28,   15,   30,   15,   18,   28,   30,
 /*    80 */    30,   28,   30,   30,   39,   40,   41,   35,   20,   39,
 /*    90 */    40,   41,   39,   40,   41,    8,   30,   28,   11,   30,
 /*   100 */    13,   28,   30,   30,   20,   21,   22,   20,   39,   40,
 /*   110 */    41,   30,   39,   40,   41,   34,   35,    1,   37,   38,
 /*   120 */    28,   30,   30,   28,    8,   30,   28,    4,   30,   13,
 /*   130 */     7,   39,   40,   41,   39,   40,   41,   39,   40,   41,
 /*   140 */    30,   28,   30,   30,   34,   35,    8,   37,   38,    1,
 /*   150 */    30,   13,   39,   40,   41,   35,    8,   37,   20,    6,
 /*   160 */    30,   13,   30,   15,   16,   30,   34,   35,   15,   30,
 /*   170 */    35,    8,   37,   34,   35,   30,   13,   30,    1,   34,
 /*   180 */    35,   34,   35,   20,   30,    8,   15,   16,   30,   35,
 /*   190 */    13,   37,   34,   35,   30,   30,   30,   30,   30,   35,
 /*   200 */    35,   35,   35,   35,   13,   13,   13,   13,    2,    6,
 /*   210 */     2,   20,   20,   20,   20,    9,    2,    9,   15,    2,
 /*   220 */     7,   21,    6,    9,   11,    9,    9,    7,    7,    2,
 /*   230 */     7,   11,   11,    2,   11,    2,    9,    2,    2,    2,
 /*   240 */     9,   30,    9,    2,    9,    9,    0,   15,   16,   30,
 /*   250 */     9,    5,   42,   41,   30,   18,    8,   42,   15,   21,
 /*   260 */    11,    9,   15,    9,    8,   15,   15,    8,    6,    9,
 /*   270 */     9,    8,    7,    9,    7,   18,    8,    6,    8,   13,
 /*   280 */     8,    8,   13,    9,    9,    1,   43,   43,   43,   43,
 /*   290 */    43,   15,   15,   15,   43,   43,   43,   18,
};
#define YY_SHIFT_USE_DFLT (-1)
#define YY_SHIFT_COUNT (109)
#define YY_SHIFT_MIN   (0)
#define YY_SHIFT_MAX   (284)
static const short yy_shift_ofst[] = {
 /*     0 */    32,   32,   84,   28,   28,   84,   84,   84,   84,   28,
 /*    10 */    84,   84,   84,   84,  138,   84,   84,   87,  138,  138,
 /*    20 */   138,  163,  138,  138,  138,  138,  138,  138,  138,  138,
 /*    30 */   138,  191,   22,  192,  193,  194,   68,   68,   68,   68,
 /*    40 */    68,   68,   68,  200,  238,  200,   68,  148,   59,  116,
 /*    50 */   177,  206,   61,  123,  153,    3,  203,   39,  208,   54,
 /*    60 */   214,  213,  217,  216,  220,  221,  223,  227,  231,  233,
 /*    70 */   235,  236,  171,  237,  232,  241,  246,  243,  248,  249,
 /*    80 */   247,  250,  252,  251,  254,  256,  259,  262,  260,  263,
 /*    90 */   261,  265,  264,  267,  260,  268,  266,  269,  270,  272,
 /*   100 */   274,  271,  275,  273,  257,  284,  276,  277,  278,  279,
};
#define YY_REDUCE_USE_DFLT (-25)
#define YY_REDUCE_COUNT (46)
#define YY_REDUCE_MIN   (-24)
#define YY_REDUCE_MAX   (224)
static const short yy_reduce_ofst[] = {
 /*     0 */   -24,   -8,   -2,   25,   34,   45,   50,   53,   69,   81,
 /*    10 */    73,   92,   95,   98,  110,  113,   17,  120,  132,  135,
 /*    20 */   139,  145,  147,  154,  158,   52,  164,  165,  166,  167,
 /*    30 */   168,  -18,    4,   49,  -18,  -18,   66,   72,   91,  112,
 /*    40 */   130,  211,  219,  210,  212,  215,  224,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   247,  246,  287,  287,  287,  287,  287,  287,  287,  287,
 /*    10 */   287,  287,  287,  287,  287,  287,  287,  280,  287,  287,
 /*    20 */   287,  287,  287,  287,  287,  287,  287,  287,  287,  287,
 /*    30 */   287,  287,  287,  287,  287,  287,  287,  287,  287,  287,
 /*    40 */   287,  287,  287,  287,  287,  287,  287,  279,  271,  287,
 /*    50 */   287,  287,  287,  287,  287,  287,  287,  273,  287,  275,
 /*    60 */   287,  274,  287,  287,  287,  256,  287,  287,  287,  287,
 /*    70 */   287,  287,  287,  287,  287,  287,  287,  267,  287,  287,
 /*    80 */   262,  287,  287,  287,  287,  287,  287,  258,  267,  287,
 /*    90 */   287,  264,  262,  287,  287,  287,  287,  287,  287,  287,
 /*   100 */   261,  287,  287,  287,  287,  287,  287,  287,  282,  287,
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
  MVSMParserGrammarARG_SDECL                /* A place to hold %extra_argument */
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
void MVSMParserGrammarTrace(FILE *TraceFILE, char *zTracePrompt){
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
  "LBRACKET",      "RBRACKET",      "IMPLICATION",   "REVERSE_IMPLICATION",
  "SORTS",         "NEGATION",      "WS",            "DOT",         
  "SEMI_COLON",    "OBJECTS",       "COLON",         "CONSTANTS",   
  "STRING",        "NUMBER",        "MINUS",         "error",       
  "start",         "prog",          "predicate",     "decl",        
  "variables",     "sort",          "string",        "object",      
  "constant",      "rule",          "body",          "bodydef",     
  "bodydef2",      "head",          "ruleU",         "number",      
  "variable",      "lnumber",       "rnumber",     
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "start ::= prog",
 /*   1 */ "prog ::= prog NEWLINE sort",
 /*   2 */ "prog ::= sort",
 /*   3 */ "sort ::= SORTS",
 /*   4 */ "sort ::= string DOT",
 /*   5 */ "sort ::= string SEMI_COLON",
 /*   6 */ "prog ::= prog NEWLINE object",
 /*   7 */ "prog ::= object",
 /*   8 */ "object ::= OBJECTS",
 /*   9 */ "object ::= variables COLON COLON string SEMI_COLON",
 /*  10 */ "object ::= variables COLON COLON string DOT",
 /*  11 */ "prog ::= prog NEWLINE constant",
 /*  12 */ "prog ::= constant",
 /*  13 */ "constant ::= CONSTANTS",
 /*  14 */ "constant ::= string LBRACKET variables RBRACKET COLON COLON string SEMI_COLON",
 /*  15 */ "constant ::= string LBRACKET variables RBRACKET COLON COLON string DOT",
 /*  16 */ "prog ::= prog NEWLINE predicate",
 /*  17 */ "prog ::= predicate",
 /*  18 */ "prog ::= prog NEWLINE decl",
 /*  19 */ "prog ::= decl",
 /*  20 */ "prog ::= prog NEWLINE rule",
 /*  21 */ "prog ::= rule",
 /*  22 */ "prog ::= prog NEWLINE",
 /*  23 */ "prog ::=",
 /*  24 */ "rule ::= number REVERSE_IMPLICATION LBRACKET ruleU RBRACKET",
 /*  25 */ "rule ::= number LBRACKET ruleU RBRACKET",
 /*  26 */ "rule ::= REVERSE_IMPLICATION LBRACKET ruleU RBRACKET DOT",
 /*  27 */ "rule ::= LBRACKET ruleU RBRACKET DOT",
 /*  28 */ "ruleU ::= body CONJUNCTION bodydef",
 /*  29 */ "ruleU ::= head DISJUNCTION bodydef",
 /*  30 */ "rule ::= REVERSE_IMPLICATION body DOT",
 /*  31 */ "rule ::= head DISJUNCTION bodydef DOT",
 /*  32 */ "rule ::= number head DISJUNCTION bodydef",
 /*  33 */ "rule ::= head REVERSE_IMPLICATION body DOT",
 /*  34 */ "rule ::= number head REVERSE_IMPLICATION body",
 /*  35 */ "rule ::= number NEGATION NEGATION LBRACKET head REVERSE_IMPLICATION body RBRACKET",
 /*  36 */ "rule ::= LPAREN head RPAREN REVERSE_IMPLICATION body DOT",
 /*  37 */ "body ::= body CONJUNCTION bodydef",
 /*  38 */ "head ::= head DISJUNCTION bodydef",
 /*  39 */ "head ::= bodydef",
 /*  40 */ "body ::= bodydef",
 /*  41 */ "bodydef ::= string LBRACKET variables RBRACKET",
 /*  42 */ "bodydef ::= NEGATION string LBRACKET variables RBRACKET",
 /*  43 */ "bodydef ::= NEGATION NEGATION string LBRACKET variables RBRACKET",
 /*  44 */ "bodydef ::= LBRACKET NEGATION NEGATION string LBRACKET variables RBRACKET RBRACKET",
 /*  45 */ "bodydef ::= string EQUAL string",
 /*  46 */ "bodydef ::= string NEGATION EQUAL string",
 /*  47 */ "decl ::= string LBRACKET variables RBRACKET",
 /*  48 */ "predicate ::= string LBRACKET variables RBRACKET DOT",
 /*  49 */ "predicate ::= number string LBRACKET variables RBRACKET",
 /*  50 */ "predicate ::= number NEGATION NEGATION string LBRACKET variables RBRACKET",
 /*  51 */ "predicate ::= number NEGATION string LBRACKET variables RBRACKET",
 /*  52 */ "predicate ::= NEGATION NEGATION string LBRACKET variables RBRACKET DOT",
 /*  53 */ "variables ::= variable",
 /*  54 */ "variables ::= variables COMMA variable",
 /*  55 */ "variable ::= string",
 /*  56 */ "variable ::= number",
 /*  57 */ "string ::= STRING",
 /*  58 */ "number ::= NUMBER",
 /*  59 */ "number ::= lnumber DOT rnumber",
 /*  60 */ "number ::= MINUS lnumber DOT rnumber",
 /*  61 */ "lnumber ::= NUMBER",
 /*  62 */ "rnumber ::= NUMBER",
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
** second argument to MVSMParserGrammarAlloc() below.  This can be changed by
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
** to MVSMParserGrammar and MVSMParserGrammarFree.
*/
void *MVSMParserGrammarAlloc(void *(*mallocProc)(YYMALLOCARGTYPE)){
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
  MVSMParserGrammarARG_FETCH;
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
void MVSMParserGrammarFree(
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
int MVSMParserGrammarStackPeak(void *p){
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
   MVSMParserGrammarARG_FETCH;
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
   MVSMParserGrammarARG_STORE; /* Suppress warning about unused %extra_argument var */
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
  { 24, 1 },
  { 25, 3 },
  { 25, 1 },
  { 29, 1 },
  { 29, 2 },
  { 29, 2 },
  { 25, 3 },
  { 25, 1 },
  { 31, 1 },
  { 31, 5 },
  { 31, 5 },
  { 25, 3 },
  { 25, 1 },
  { 32, 1 },
  { 32, 8 },
  { 32, 8 },
  { 25, 3 },
  { 25, 1 },
  { 25, 3 },
  { 25, 1 },
  { 25, 3 },
  { 25, 1 },
  { 25, 2 },
  { 25, 0 },
  { 33, 5 },
  { 33, 4 },
  { 33, 5 },
  { 33, 4 },
  { 38, 3 },
  { 38, 3 },
  { 33, 3 },
  { 33, 4 },
  { 33, 4 },
  { 33, 4 },
  { 33, 4 },
  { 33, 8 },
  { 33, 6 },
  { 34, 3 },
  { 37, 3 },
  { 37, 1 },
  { 34, 1 },
  { 35, 4 },
  { 35, 5 },
  { 35, 6 },
  { 35, 8 },
  { 35, 3 },
  { 35, 4 },
  { 27, 4 },
  { 26, 5 },
  { 26, 5 },
  { 26, 7 },
  { 26, 6 },
  { 26, 7 },
  { 28, 1 },
  { 28, 3 },
  { 40, 1 },
  { 40, 1 },
  { 30, 1 },
  { 39, 1 },
  { 39, 3 },
  { 39, 4 },
  { 41, 1 },
  { 42, 1 },
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
  MVSMParserGrammarARG_FETCH;
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
      case 3: /* sort ::= SORTS */
{
	if (tree->cdp == Tree::Current_Decl_Part::DECL_NONE){
		tree->cdp = Tree::Current_Decl_Part::DECL_SORTS;
	}
	else{
		throw syntax_exception("Expected Sorts.");
	}
}
        break;
      case 4: /* sort ::= string DOT */
{
	std::string str = yymsp[-1].minor.yy0->toString();
	auto it = tree->domainNamesList.find(str);
	if(it != tree->domainNamesList.end())
		throw syntax_exception("Redeclaration of sort "+yymsp[-1].minor.yy0->toString()+"\n");
	else
		tree->domainNamesList.insert(str);	
	tree->cdp = Tree::Current_Decl_Part::DECL_NONE;
}
        break;
      case 5: /* sort ::= string SEMI_COLON */
{
	std::string str = yymsp[-1].minor.yy0->toString();
	auto it = tree->domainNamesList.find(str);
	if(it != tree->domainNamesList.end())
		throw syntax_exception("Redeclaration of sort "+yymsp[-1].minor.yy0->toString()+"\n");
	else
		tree->domainNamesList.insert(yymsp[-1].minor.yy0->toString());
}
        break;
      case 8: /* object ::= OBJECTS */
{
	if (tree->cdp == Tree::Current_Decl_Part::DECL_NONE){
		tree->cdp = Tree::Current_Decl_Part::DECL_OBJECTS;
	}
	else{
		throw syntax_exception("Expected Objects.");
	}
}
        break;
      case 9: /* object ::= variables COLON COLON string SEMI_COLON */
{
	if(tree->cdp == Tree::Current_Decl_Part::DECL_OBJECTS){
		auto itr = tree->domainNamesList.find(yymsp[-1].minor.yy0->toString());
		if(itr != tree->domainNamesList.end()){
			Domain* d  = new Domain(yymsp[-1].minor.yy0->toString());
			d->setVars(*yymsp[-4].minor.yy77);
			tree->domains.insert(*d);
			for(auto& v : d->getVars()){
				tree->domainList.insert(v);	
			}
			cout<<d->toString(false);
			delete d;
		}
		else{
			throw syntax_exception("Domain " + yymsp[-1].minor.yy0->toString() +" not declared.\n");
		}
	}
	else if(tree->cdp == Tree::Current_Decl_Part::DECL_CONSTANTS){
		Variable* v = new Variable;
		std::string str = *(yymsp[-4].minor.yy77->at(0));
		std::map<int, Domain> posMap;
		std::set<Domain>::iterator itr;
		int i=0;
		itr = tree->domains.find(yymsp[-1].minor.yy0->toString());
		if (itr == tree->domains.end()){
			throw syntax_exception("Syntax Error - Domain " + yymsp[-1].minor.yy0->toString() + " not found.\n");
		}
		else{
			v->setVar(str);
			posMap[0] = *itr;
		}
		v->setPosMap(posMap);
		tree->variables.insert(*v);
		cout<<v->toString();
		delete v;		
	}
	delete yymsp[-4].minor.yy77;
}
        break;
      case 10: /* object ::= variables COLON COLON string DOT */
{

	if(tree->cdp == Tree::Current_Decl_Part::DECL_OBJECTS){
		auto itr = tree->domainNamesList.find(yymsp[-1].minor.yy0->toString());
		if(itr != tree->domainNamesList.end()){
			Domain* d  = new Domain(yymsp[-1].minor.yy0->toString());
			d->setVars(*yymsp[-4].minor.yy77);
			tree->domains.insert(*d);
			for(auto& v : d->getVars()){
				tree->domainList.insert(v);	
			}
			cout<<d->toString(false);
			delete d;
		}
		else{
			throw syntax_exception("Domain " + yymsp[-1].minor.yy0->toString() +" not declared.\n");
		}
		tree->cdp = Tree::Current_Decl_Part::DECL_NONE;
	}

	else if(tree->cdp == Tree::Current_Decl_Part::DECL_CONSTANTS){
		Variable* v = new Variable;
		std::string str = *(yymsp[-4].minor.yy77->at(0));
		std::map<int, Domain> posMap;
		std::set<Domain>::iterator itr;
		int i=0;
		itr = tree->domains.find(yymsp[-1].minor.yy0->toString());
		if (itr == tree->domains.end()){
			throw syntax_exception("Syntax Error - Domain " + yymsp[-1].minor.yy0->toString() + " not found.\n");
		}
		else{
			v->setVar(str);
			posMap[0] = *itr;
		}
		v->setPosMap(posMap);
		
		tree->variables.insert(*v);
		cout<<v->toString();
		tree->cdp = Tree::Current_Decl_Part::DECL_NONE;		
		delete v;
	}
	delete yymsp[-4].minor.yy77;
}
        break;
      case 13: /* constant ::= CONSTANTS */
{
	if (tree->cdp == Tree::Current_Decl_Part::DECL_NONE){
		tree->cdp = Tree::Current_Decl_Part::DECL_CONSTANTS;
	}
	else{
		throw syntax_exception("Expected Constants.");
	}
}
        break;
      case 14: /* constant ::= string LBRACKET variables RBRACKET COLON COLON string SEMI_COLON */
{
	Variable* va = new Variable;
	std::map<int, Domain> posMap;
	std::set<Domain>::iterator itr;
	int i=0;
	for(auto& v : *yymsp[-5].minor.yy77){
		itr = tree->domains.find(*v);
		if (itr == tree->domains.end()){
			// std::cout<<"Error:Domain:"+ *v +" not found.\n";
			throw syntax_exception("Syntax Error - Domain " + *v + " not found.\n");
		}
		else{
			// itr = tree->domains.find(*v);
			// va->setVar(yymsp[-7].minor.yy0->token);
			posMap[i++] = *itr;
		}
	}

	itr = tree->domains.find(yymsp[-1].minor.yy0->toString());
	if (itr == tree->domains.end()){
		throw syntax_exception("Syntax Error - Domain " + yymsp[-1].minor.yy0->toString() + " not found.\n");
	}
	else{
		posMap[i] = *itr;
	}

	va->setVar(yymsp[-7].minor.yy0->toString());
	va->setPosMap(posMap);
	tree->variables.insert(*va);
	cout<<va->toString();
	delete yymsp[-5].minor.yy77;
	delete va;
}
        break;
      case 15: /* constant ::= string LBRACKET variables RBRACKET COLON COLON string DOT */
{
	Variable* va = new Variable;
	std::map<int, Domain> posMap;
	std::set<Domain>::iterator itr;
	int i=0;
	for(auto& v : *yymsp[-5].minor.yy77){
		itr = tree->domains.find(*v);
		if (itr == tree->domains.end()){
			// std::cout<<"Error:Domain:"+ *v +" not found.\n";
			throw syntax_exception("Syntax Error - Domain " + *v + " not found.\n");
		}
		else{
			// itr = tree->domains.find(*v);
			// D->setVar(yymsp[-7].minor.yy0->token);
			posMap[i++] = *itr;
		}
	}

	itr = tree->domains.find(yymsp[-1].minor.yy0->toString());
	if (itr == tree->domains.end()){
		throw syntax_exception("Syntax Error - Domain " + yymsp[-1].minor.yy0->toString() + " not found.\n");
	}
	else{
		posMap[i] = *itr;
	}

	va->setVar(yymsp[-7].minor.yy0->toString());
	va->setPosMap(posMap);
	tree->variables.insert(*va);
	tree->cdp = Tree::Current_Decl_Part::DECL_NONE;
	cout<<va->toString();
	delete yymsp[-5].minor.yy77;
	delete va;
}
        break;
      case 16: /* prog ::= prog NEWLINE predicate */
{ 
	if(yymsp[0].minor.yy32->needsToBeCompleted()){	
		FactCompletion f(*yymsp[0].minor.yy32);
		tree->facts.insert(std::pair<std::string,FactCompletion>(f.getHead().getVar(),f)); 
	}	
	delete yymsp[0].minor.yy32;
}
        break;
      case 17: /* prog ::= predicate */
{ 
	if(yymsp[0].minor.yy32->needsToBeCompleted()){
		FactCompletion f(*yymsp[0].minor.yy32);
		tree->facts.insert(std::pair<std::string,FactCompletion>(f.getHead().getVar(),f)); 	
	}
	delete yymsp[0].minor.yy32;
}
        break;
      case 18: /* prog ::= prog NEWLINE decl */
      case 19: /* prog ::= decl */ yytestcase(yyruleno==19);
{
	tree->variables.insert(*yymsp[0].minor.yy1);
	cout<<yymsp[0].minor.yy1->toString();
	delete yymsp[0].minor.yy1;
}
        break;
      case 20: /* prog ::= prog NEWLINE rule */
      case 21: /* prog ::= rule */ yytestcase(yyruleno==21);
{
	if((yymsp[0].minor.yy59->isHeadTop == false) && (yymsp[0].minor.yy59->toBeCompleted == true))
		tree->rules.insert(std::pair<std::string,RuleCompletion>(yymsp[0].minor.yy59->getHead().getVar(),*yymsp[0].minor.yy59));
	delete yymsp[0].minor.yy59;
}
        break;
      case 24: /* rule ::= number REVERSE_IMPLICATION LBRACKET ruleU RBRACKET */
{
	yygotominor.yy59 = yymsp[-1].minor.yy59;
	yygotominor.yy59->toBeCompleted = false;
	if(yymsp[-1].minor.yy59->getBodyType() == BodyType::DISJUNCTION){
		throw syntax_exception("Unexpected DISJUNCTION in BODY of RULE.\n");
	}
	cout<<yymsp[-4].minor.yy0->toString()<<SPACE<<"!("<<yymsp[-1].minor.yy59->toString()<<")"<<"\n";
}
        break;
      case 25: /* rule ::= number LBRACKET ruleU RBRACKET */
{
	yygotominor.yy59 = yymsp[-1].minor.yy59;
	yygotominor.yy59->toBeCompleted = false;
	if(yymsp[-1].minor.yy59->getBodyType() == BodyType::CONJUNCTION){
		throw syntax_exception("Unexpected CONJUNCTION in HEAD of RULE.\n");
	}
	cout<<yymsp[-3].minor.yy0->toString()<<SPACE<<"("<<yymsp[-1].minor.yy59->toString()<<")"<<"\n";
}
        break;
      case 26: /* rule ::= REVERSE_IMPLICATION LBRACKET ruleU RBRACKET DOT */
{
	yygotominor.yy59 = yymsp[-2].minor.yy59;
	yymsp[-2].minor.yy59->toBeCompleted = false;
	if(yymsp[-2].minor.yy59->getBodyType() == BodyType::DISJUNCTION){
		throw syntax_exception("Unexpected DISJUNCTION in BODY of RULE.\n");
	}
	cout<<"!("<<yymsp[-2].minor.yy59->toString()<<")."<<"\n";
}
        break;
      case 27: /* rule ::= LBRACKET ruleU RBRACKET DOT */
{
	yygotominor.yy59 = yymsp[-2].minor.yy59;
	yygotominor.yy59->toBeCompleted = false;
	if(yymsp[-2].minor.yy59->getBodyType() == BodyType::CONJUNCTION){
		throw syntax_exception("Unexpected CONJUNCTION in HEAD of RULE.\n");
	}
	cout<<"("<<yymsp[-2].minor.yy59->toString()<<")."<<"\n";
}
        break;
      case 28: /* ruleU ::= body CONJUNCTION bodydef */
{
	yygotominor.yy59 = new RuleCompletion;
	yymsp[-2].minor.yy83->appendStr(yymsp[0].minor.yy28->getPredicate().toString(),false,false,true);
	yygotominor.yy59->appendStr(yymsp[-2].minor.yy83->toString());
	yygotominor.yy59->setBodyType(BodyType::CONJUNCTION);
	delete yymsp[-2].minor.yy83;
	delete yymsp[0].minor.yy28;
}
        break;
      case 29: /* ruleU ::= head DISJUNCTION bodydef */
{
	yygotominor.yy59 = new RuleCompletion;	
	yygotominor.yy59->isHeadTop = true;
	yymsp[-2].minor.yy37->addPredicate(yymsp[0].minor.yy28->getPredicate());
	// RULE_COMPLETION_HEAD_DIS_BODY_TOP(yymsp[-2].minor.yy37,yymsp[0].minor.yy28)
	try{
		RuleCompletion_HD_BT(yymsp[-2].minor.yy37,tree);
	}
	catch(const std::out_of_range& e){
		throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}

	yymsp[-2].minor.yy37->appendStr(yymsp[0].minor.yy28->getPredicate().toString(),false,true,false);
	yygotominor.yy59->appendStr(yymsp[-2].minor.yy37->toString());
	yygotominor.yy59->setBodyType(BodyType::DISJUNCTION);
	delete yymsp[-2].minor.yy37;
	delete yymsp[0].minor.yy28;
}
        break;
      case 30: /* rule ::= REVERSE_IMPLICATION body DOT */
{
	yygotominor.yy59 = new RuleCompletion;
	yygotominor.yy59->isHeadTop = true;
	// yymsp[-1].minor.yy83->appendStr(yymsp[-1].minor.yy83->getPredicate().toString(),false,false,true);
	std::cout<<"!("<<yymsp[-1].minor.yy83->toString()<<")."<<"\n";	
	delete yymsp[-1].minor.yy83;
	// delete B1;
}
        break;
      case 31: /* rule ::= head DISJUNCTION bodydef DOT */
{
	//Doing this 
	yygotominor.yy59 = new RuleCompletion;
	yygotominor.yy59->isHeadTop = true;
	yymsp[-3].minor.yy37->addPredicate(yymsp[-1].minor.yy28->getPredicate());
	// RULE_COMPLETION_HEAD_DIS_BODY_TOP(yymsp[-3].minor.yy37,yymsp[-1].minor.yy28)
	try{
		RuleCompletion_HD_BT(yymsp[-3].minor.yy37,tree);
	}
	catch(const std::out_of_range& e){
		throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}
	yymsp[-3].minor.yy37->appendStr(yymsp[-1].minor.yy28->getPredicate().toString(),false,true,false);
	std::cout<<yymsp[-3].minor.yy37->toString()<<"."<<"\n";
	delete yymsp[-3].minor.yy37;
	delete yymsp[-1].minor.yy28;
}
        break;
      case 32: /* rule ::= number head DISJUNCTION bodydef */
{
	//Doing this 
	yygotominor.yy59 = new RuleCompletion;
	yygotominor.yy59->isHeadTop = true;
	yymsp[-2].minor.yy37->addPredicate(yymsp[0].minor.yy28->getPredicate());
	// RULE_COMPLETION_HEAD_DIS_BODY_TOP(yymsp[-2].minor.yy37,yymsp[0].minor.yy28)
	try{
		RuleCompletion_HD_BT(yymsp[-2].minor.yy37,tree);
	}
	catch(const std::out_of_range& e){
		throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}
	yymsp[-2].minor.yy37->appendStr(yymsp[0].minor.yy28->getPredicate().toString(),false,true,false);
	std::cout<<yymsp[-3].minor.yy0->toString()<<SPACE<<yymsp[-2].minor.yy37->toString()<<"\n";
	delete yymsp[-2].minor.yy37;
	delete yymsp[0].minor.yy28;
}
        break;
      case 33: /* rule ::= head REVERSE_IMPLICATION body DOT */
{
	yygotominor.yy59 = new RuleCompletion;

	if (yymsp[-3].minor.yy37->getDisjunction()){
		// RULE_COMPLETION_HEAD_DIS_BODY_TOP(yymsp[-3].minor.yy37,yymsp[-1].minor.yy83)
		yygotominor.yy59->isHeadTop = true;
		RuleCompletion_HD_BC(yymsp[-3].minor.yy37,yymsp[-1].minor.yy83,true,tree);
		std::cout<<yymsp[-1].minor.yy83->toString()<<" => "<<yymsp[-3].minor.yy37->toString()<<"."<<"\n";
		// std::cout << op;
	}
	else{
		// RULE_COMPLETION_BH(yymsp[-1].minor.yy83,yymsp[-3].minor.yy37);
		// yygotominor.yy59 = new RuleCompletion(yymsp[-3].minor.yy37->getPredicate(),predList, resultMap, varMap);
		try{
			yygotominor.yy59 = RuleCompletion_BH(yymsp[-1].minor.yy83,yymsp[-3].minor.yy37,tree);
		}
		catch(const std::out_of_range& e){
			throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
		}
		std::cout<<yymsp[-1].minor.yy83->toString()<<" => "<<yymsp[-3].minor.yy37->toString()<<"."<<"\n";
	}
	delete yymsp[-1].minor.yy83;
	delete yymsp[-3].minor.yy37;
}
        break;
      case 34: /* rule ::= number head REVERSE_IMPLICATION body */
{
	// RULE_COMPLETION_BH(yymsp[0].minor.yy83,yymsp[-2].minor.yy37);
	// yygotominor.yy59 = new RuleCompletion(yymsp[-2].minor.yy37->getPredicate(),predList, resultMap, varMap);
	try{
		yygotominor.yy59 = RuleCompletion_BH(yymsp[0].minor.yy83,yymsp[-2].minor.yy37,tree);
	}
	catch(const std::out_of_range& e){
			throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}
	std::cout<< yymsp[-3].minor.yy0->toString()<<SPACE<<yymsp[0].minor.yy83->toString()<<" => "<<yymsp[-2].minor.yy37->toString()<<"\n";
	delete yymsp[0].minor.yy83;
	delete yymsp[-2].minor.yy37;
}
        break;
      case 35: /* rule ::= number NEGATION NEGATION LBRACKET head REVERSE_IMPLICATION body RBRACKET */
{
	yygotominor.yy59 = new RuleCompletion;
	yygotominor.yy59->isHeadTop = true;	
	tree->statHasDblNeg = true;
	std::cout<< yymsp[-7].minor.yy0->toString() << SPACE <<"!!("<<yymsp[-1].minor.yy83->toString()<<" => "<<yymsp[-3].minor.yy37->toString()<<"\n"; 
	delete yymsp[-1].minor.yy83;
	delete yymsp[-3].minor.yy37;
}
        break;
      case 36: /* rule ::= LPAREN head RPAREN REVERSE_IMPLICATION body DOT */
{
	
	if (yymsp[-4].minor.yy37->getPredicate().checkEquality() != 0){
		throw syntax_exception("Cannot have equality/Inequlity as a part of choice rule\n");
	}

	// RULE_COMPLETION_BH(yymsp[-1].minor.yy83,yymsp[-4].minor.yy37);
	// yygotominor.yy59 = new RuleCompletion(yymsp[-4].minor.yy37->getPredicate(),predList, resultMap, varMap);
	try{
		yygotominor.yy59 = RuleCompletion_BH(yymsp[-1].minor.yy83,yymsp[-4].minor.yy37,tree);
	}
	catch(const std::out_of_range& e){
			throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}
	std::cout<<COMMENT<<yymsp[-1].minor.yy83->toString()<<" => "<<yymsp[-4].minor.yy37->toString()<<"\n";
	delete yymsp[-1].minor.yy83;
	delete yymsp[-4].minor.yy37;
}
        break;
      case 37: /* body ::= body CONJUNCTION bodydef */
{
	yygotominor.yy83 = yymsp[-2].minor.yy83;
	yymsp[-2].minor.yy83->addPredicate(yymsp[0].minor.yy28->getPredicate());
	yygotominor.yy83->appendStr(yymsp[0].minor.yy28->getPredicate().toString(),false,false,true);
	delete yymsp[0].minor.yy28;
}
        break;
      case 38: /* head ::= head DISJUNCTION bodydef */
{
	yygotominor.yy37 = yymsp[-2].minor.yy37;
	yymsp[-2].minor.yy37->addPredicate(yymsp[0].minor.yy28->getPredicate());
	yygotominor.yy37->appendStr(yymsp[0].minor.yy28->getPredicate().toString(),false,true,false);
	yygotominor.yy37->setDisjunction(true);
	delete yymsp[0].minor.yy28;
}
        break;
      case 39: /* head ::= bodydef */
{
	yygotominor.yy37 = new Head(yymsp[0].minor.yy28->getPredicate());
	// yygotominor.yy37->addPredicate(yymsp[0].minor.yy28->getPredicate());
	yygotominor.yy37->appendStr(yymsp[0].minor.yy28->getPredicate().toString(),false,false,false);
	delete yymsp[0].minor.yy28;
}
        break;
      case 40: /* body ::= bodydef */
{
	yygotominor.yy83 = new Body;
	yygotominor.yy83->addPredicate(yymsp[0].minor.yy28->getPredicate());
	yygotominor.yy83->appendStr(yymsp[0].minor.yy28->getPredicate().toString(),false,false,false);
	delete yymsp[0].minor.yy28;
}
        break;
      case 41: /* bodydef ::= string LBRACKET variables RBRACKET */
{	
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-1].minor.yy77)
		vars.push_back(*v);
	
	Predicate p(yymsp[-3].minor.yy0->token, vars);
	yygotominor.yy28 = new BodyDef;
	yygotominor.yy28->addPredicate(p);
	delete yymsp[-1].minor.yy77;
	int expectedArgs = (tree->variables.find(*(yymsp[-3].minor.yy0->token)))->getSize();
	if (expectedArgs != vars.size()){
		delete yygotominor.yy28;
		throw invalid_arguments(expectedArgs, vars.size(), *(yymsp[-3].minor.yy0->token));
	}

}
        break;
      case 42: /* bodydef ::= NEGATION string LBRACKET variables RBRACKET */
{	
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-1].minor.yy77)
		vars.push_back(*v);
	
	Predicate p(yymsp[-3].minor.yy0->token, vars);
	p.setSingleNegation(true);
	yygotominor.yy28 = new BodyDef;
	yygotominor.yy28->addPredicate(p);
	delete yymsp[-1].minor.yy77;
	int expectedArgs = (tree->variables.find(*(yymsp[-3].minor.yy0->token)))->getSize();
	if (expectedArgs != vars.size()){
		delete yygotominor.yy28;
		throw invalid_arguments(expectedArgs, vars.size(), *(yymsp[-3].minor.yy0->token));
	}

}
        break;
      case 43: /* bodydef ::= NEGATION NEGATION string LBRACKET variables RBRACKET */
{	
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-1].minor.yy77)
		vars.push_back(*v);
	
	Predicate p(yymsp[-3].minor.yy0->token, vars);
	p.setDoubleNegation(true);
	yygotominor.yy28 = new BodyDef;
	yygotominor.yy28->addPredicate(p);
	tree->statHasDblNeg = true;
	delete yymsp[-1].minor.yy77;
	int expectedArgs = (tree->variables.find(*(yymsp[-3].minor.yy0->token)))->getSize();
	if (expectedArgs != vars.size()){
		delete yygotominor.yy28;
		throw invalid_arguments(expectedArgs, vars.size(), *(yymsp[-3].minor.yy0->token));
	}

}
        break;
      case 44: /* bodydef ::= LBRACKET NEGATION NEGATION string LBRACKET variables RBRACKET RBRACKET */
{	
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-2].minor.yy77)
		vars.push_back(*v);
	
	Predicate p(yymsp[-4].minor.yy0->token, vars);
	p.setDoubleNegation(true);
	tree->statHasDblNeg = true;
	yygotominor.yy28 = new BodyDef;
	yygotominor.yy28->addPredicate(p);
	delete yymsp[-2].minor.yy77;
	int expectedArgs = (tree->variables.find(*(yymsp[-4].minor.yy0->token)))->getSize();
	if (expectedArgs != vars.size()){
		delete yygotominor.yy28;
		throw invalid_arguments(expectedArgs, vars.size(), *(yymsp[-4].minor.yy0->token));
	}

}
        break;
      case 45: /* bodydef ::= string EQUAL string */
{
	Predicate p(yymsp[-2].minor.yy0->token,yymsp[0].minor.yy0->token);
	p.setEquality();
	yygotominor.yy28 = new BodyDef;
	yygotominor.yy28->addPredicate(p);
}
        break;
      case 46: /* bodydef ::= string NEGATION EQUAL string */
{
	
	Predicate p(yymsp[-3].minor.yy0->token,yymsp[0].minor.yy0->token);
	p.setInEquality();
	yygotominor.yy28 = new BodyDef;
	yygotominor.yy28->addPredicate(p);
}
        break;
      case 47: /* decl ::= string LBRACKET variables RBRACKET */
{
	yygotominor.yy1 = new Variable;
	std::map<int, Domain> posMap;
	std::set<Domain>::iterator itr;
	int i=0;
	for(auto& v : *yymsp[-1].minor.yy77){
		itr = tree->domains.find(*v);
		if (itr == tree->domains.end()){
			// std::cout<<"Error:Domain:"+ *v +" not found.\n";
			throw syntax_exception("Syntax Error - Domain " + *v + " not found.\n");
		}
		else{
			// itr = tree->domains.find(*v);
			yygotominor.yy1->setVar(yymsp[-3].minor.yy0->token);
			posMap[i++] = *itr;
		}
	}
	yygotominor.yy1->setPosMap(posMap);
	delete yymsp[-1].minor.yy77;
}
        break;
      case 48: /* predicate ::= string LBRACKET variables RBRACKET DOT */
{
	yygotominor.yy32 = new Predicate;
	yygotominor.yy32->setVar(yymsp[-4].minor.yy0->token);
	yygotominor.yy32->setTokens(*yymsp[-2].minor.yy77);
	std::string s1;
	cout<<yygotominor.yy32->toString(s1,true);
	delete yymsp[-2].minor.yy77;
}
        break;
      case 49: /* predicate ::= number string LBRACKET variables RBRACKET */
{
	yygotominor.yy32 = new Predicate;
	yygotominor.yy32->setVar(yymsp[-3].minor.yy0->token);
	yygotominor.yy32->setTokens(*yymsp[-1].minor.yy77);
	cout<<yygotominor.yy32->toString(yymsp[-4].minor.yy0->toString()+SPACE, false);
	delete yymsp[-1].minor.yy77;
}
        break;
      case 50: /* predicate ::= number NEGATION NEGATION string LBRACKET variables RBRACKET */
{
	yygotominor.yy32 = new Predicate;
	yygotominor.yy32->notToBeCompleted();
	tree->statHasDblNeg = true;
	yygotominor.yy32->setVar(yymsp[-3].minor.yy0->token);
	yygotominor.yy32->setTokens(*yymsp[-1].minor.yy77);
	cout<<yygotominor.yy32->toString(yymsp[-6].minor.yy0->toString()+SPACE, false);
	delete yymsp[-1].minor.yy77;
}
        break;
      case 51: /* predicate ::= number NEGATION string LBRACKET variables RBRACKET */
{
	yygotominor.yy32 = new Predicate;
	yygotominor.yy32->notToBeCompleted();
	yygotominor.yy32->setVar(yymsp[-3].minor.yy0->token);
	yygotominor.yy32->setTokens(*yymsp[-1].minor.yy77);
	cout<<yygotominor.yy32->toString(yymsp[-5].minor.yy0->toString()+SPACE+"!", false);
	delete yymsp[-1].minor.yy77;
}
        break;
      case 52: /* predicate ::= NEGATION NEGATION string LBRACKET variables RBRACKET DOT */
{
	yygotominor.yy32 = new Predicate;
	yygotominor.yy32->notToBeCompleted();
	tree->statHasDblNeg = true;
	yygotominor.yy32->setVar(yymsp[-4].minor.yy0->token);
	yygotominor.yy32->setTokens(*yymsp[-2].minor.yy77);
	std::string s1; 
	cout<<yygotominor.yy32->toString(s1, false);
	delete yymsp[-2].minor.yy77;
}
        break;
      case 53: /* variables ::= variable */
{
	yygotominor.yy77 = new std::vector<std::string*>();
	yygotominor.yy77->push_back(yymsp[0].minor.yy0->token);
}
        break;
      case 54: /* variables ::= variables COMMA variable */
{
	yygotominor.yy77 = yymsp[-2].minor.yy77;
	yymsp[-2].minor.yy77->push_back(yymsp[0].minor.yy0->token);
}
        break;
      case 55: /* variable ::= string */
      case 56: /* variable ::= number */ yytestcase(yyruleno==56);
      case 57: /* string ::= STRING */ yytestcase(yyruleno==57);
      case 58: /* number ::= NUMBER */ yytestcase(yyruleno==58);
{ yygotominor.yy0=yymsp[0].minor.yy0;}
        break;
      case 59: /* number ::= lnumber DOT rnumber */
{ 
	// yygotominor.yy0 = new Token(*(yymsp[-2].minor.yy0->token)+"."+*(yymsp[0].minor.yy0->token));
	yygotominor.yy0 = yymsp[-2].minor.yy0;
	yygotominor.yy0->modifyToken(*(yymsp[-2].minor.yy0->token)+"."+*(yymsp[0].minor.yy0->token));
}
        break;
      case 60: /* number ::= MINUS lnumber DOT rnumber */
{
	yygotominor.yy0 = yymsp[-2].minor.yy0;
	yygotominor.yy0->modifyToken("-"+*(yymsp[-2].minor.yy0->token)+"."+*(yymsp[0].minor.yy0->token));
}
        break;
      case 61: /* lnumber ::= NUMBER */
      case 62: /* rnumber ::= NUMBER */ yytestcase(yyruleno==62);
{ yygotominor.yy0=yymsp[0].minor.yy0; }
        break;
      default:
      /* (0) start ::= prog */ yytestcase(yyruleno==0);
      /* (1) prog ::= prog NEWLINE sort */ yytestcase(yyruleno==1);
      /* (2) prog ::= sort */ yytestcase(yyruleno==2);
      /* (6) prog ::= prog NEWLINE object */ yytestcase(yyruleno==6);
      /* (7) prog ::= object */ yytestcase(yyruleno==7);
      /* (11) prog ::= prog NEWLINE constant */ yytestcase(yyruleno==11);
      /* (12) prog ::= constant */ yytestcase(yyruleno==12);
      /* (22) prog ::= prog NEWLINE */ yytestcase(yyruleno==22);
      /* (23) prog ::= */ yytestcase(yyruleno==23);
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
  MVSMParserGrammarARG_FETCH;
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
  MVSMParserGrammarARG_STORE; /* Suppress warning about unused %extra_argument variable */
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
  MVSMParserGrammarARG_FETCH;
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
  MVSMParserGrammarARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  MVSMParserGrammarARG_FETCH;
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
  MVSMParserGrammarARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "MVSMParserGrammarAlloc" which describes the current state of the parser.
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
void MVSMParserGrammar(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  MVSMParserGrammarTOKENTYPE yyminor       /* The value for the token */
  MVSMParserGrammarARG_PDECL               /* Optional %extra_argument parameter */
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
  MVSMParserGrammarARG_STORE;

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

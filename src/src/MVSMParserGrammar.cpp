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
	#include "LanguageConstants.h"
	#include "Util.h"
	

	#include "exceptions/undefined_predicate.h"
	#include "exceptions/syntax_exception.h"


	using namespace std;

	#define SPACE " "
	#define COMMENT "//"

	#define YYNOERRORRECOVERY 
	#undef YYERRORSYMBOL

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
#define MVSM_PARSE_TOKEN_REVERSE_IMPLICATION             1
#define MVSM_PARSE_TOKEN_EQUAL                           2
#define MVSM_PARSE_TOKEN_COMMA                           3
#define MVSM_PARSE_TOKEN_LPAREN                          4
#define MVSM_PARSE_TOKEN_RPAREN                          5
#define MVSM_PARSE_TOKEN_NEWLINE                         6
#define MVSM_PARSE_TOKEN_CONJUNCTION                     7
#define MVSM_PARSE_TOKEN_DISJUNCTION                     8
#define MVSM_PARSE_TOKEN_LBRACKET                        9
#define MVSM_PARSE_TOKEN_RBRACKET                       10
#define MVSM_PARSE_TOKEN_IMPLICATION                    11
#define MVSM_PARSE_TOKEN_SORTS                          12
#define MVSM_PARSE_TOKEN_NEGATION                       13
#define MVSM_PARSE_TOKEN_WS                             14
#define MVSM_PARSE_TOKEN_SEMI_COLON                     15
#define MVSM_PARSE_TOKEN_DOT                            16
#define MVSM_PARSE_TOKEN_OBJECTS                        17
#define MVSM_PARSE_TOKEN_COLON                          18
#define MVSM_PARSE_TOKEN_CONSTANTS                      19
#define MVSM_PARSE_TOKEN_COUNT                          20
#define MVSM_PARSE_TOKEN_STRING                         21
#define MVSM_PARSE_TOKEN_NUMBER                         22
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
#define YYNOCODE 46
#define YYACTIONTYPE unsigned short int
#if INTERFACE
#define MVSMParserGrammarTOKENTYPE Token*
#endif
typedef union {
  int yyinit;
  MVSMParserGrammarTOKENTYPE yy0;
  RuleCompletion* yy3;
  Predicate* yy42;
  BodyDef* yy43;
  Body* yy49;
  Head* yy65;
  Tree* yy67;
  Variable* yy73;
  std::vector<std::string*>* yy85;
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
#define YYNSTATE             94
#define YYNRULE              64
#define YY_MAX_SHIFT         93
#define YY_MIN_SHIFTREDUCE   146
#define YY_MAX_SHIFTREDUCE   209
#define YY_MIN_REDUCE        210
#define YY_MAX_REDUCE        273
#define YY_ERROR_ACTION      274
#define YY_ACCEPT_ACTION     275
#define YY_NO_ACTION         276
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
#define YY_ACTTAB_COUNT (318)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   275,   49,  165,   17,   70,   36,   50,  159,   71,  186,
 /*    10 */   164,  167,  177,  180,   50,   54,    2,   76,  191,  166,
 /*    20 */   208,  180,   50,   54,    2,   76,  191,   10,   64,  180,
 /*    30 */     4,   61,  207,   55,  191,   84,  187,    9,   63,   18,
 /*    40 */    77,   65,  197,   15,   50,   84,   44,  208,  209,   20,
 /*    50 */    51,  181,   50,   31,  207,  182,  191,  208,  209,  180,
 /*    60 */    50,   52,  207,  182,  191,   84,   53,  181,  208,   21,
 /*    70 */   207,  182,  191,   11,  203,   50,   70,  208,  209,  157,
 /*    80 */    71,   58,  181,   50,  188,  207,  182,  191,  208,  209,
 /*    90 */   180,   50,   59,  207,  182,  191,   22,   79,  181,   19,
 /*   100 */    40,  207,  182,  191,  208,  209,   50,  208,  209,   64,
 /*   110 */   208,  209,   80,  181,   50,  208,  207,  182,  191,   63,
 /*   120 */    68,  181,   25,  198,  207,  182,  191,   72,  206,  206,
 /*   130 */   154,   73,   72,   17,  206,  152,   73,   26,  207,  207,
 /*   140 */   189,  204,  174,   50,  207,   72,  204,  206,  151,   73,
 /*   150 */    78,   50,  163,  207,  182,  191,  199,  207,  179,  204,
 /*   160 */    50,  207,  182,  191,  149,   74,   50,   60,  210,  160,
 /*   170 */   207,  182,  191,  178,    1,   32,  207,  182,  191,   62,
 /*   180 */    42,  155,   67,  208,  209,   13,   62,   38,    7,  207,
 /*   190 */   183,  191,  207,   57,  191,   17,  207,   56,  191,   67,
 /*   200 */   208,  209,   67,   70,  170,   67,  156,   71,   67,  207,
 /*   210 */    75,  191,  207,   82,  191,  207,  196,  191,  207,   85,
 /*   220 */   191,   67,  148,   74,   67,   37,  158,   67,  147,   74,
 /*   230 */    67,  207,  194,  191,  207,  195,  191,  207,   86,  191,
 /*   240 */   207,  193,  191,   66,  206,  206,    3,   17,   67,   69,
 /*   250 */   176,  206,   87,  208,  207,  207,  205,  204,  207,  184,
 /*   260 */   191,  207,   43,  204,    5,  246,  172,  247,   17,   31,
 /*   270 */   192,   14,  246,   81,  247,  248,    6,  243,    8,   33,
 /*   280 */    34,   28,  248,   15,  243,   16,   39,   88,   90,   39,
 /*   290 */    39,   45,  185,   89,   31,   35,   29,   92,   24,   12,
 /*   300 */   153,   23,   30,  212,   93,   41,  150,   83,  212,   27,
 /*   310 */   212,  212,   87,   46,   47,   91,  212,   48,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    24,   25,   26,    7,   30,    6,   30,   33,   34,   30,
 /*    10 */    26,   35,   16,   37,   30,   39,   40,   41,   42,   35,
 /*    20 */    21,   37,   30,   39,   40,   41,   42,    1,   30,   37,
 /*    30 */     4,   39,   40,   41,   42,    9,   30,    1,   40,   13,
 /*    40 */     5,   43,   44,    8,   30,    9,    2,   21,   22,   13,
 /*    50 */    36,   37,   30,    9,   40,   41,   42,   21,   22,   37,
 /*    60 */    30,   39,   40,   41,   42,    9,   36,   37,   21,   13,
 /*    70 */    40,   41,   42,    6,   16,   30,   30,   21,   22,   33,
 /*    80 */    34,   36,   37,   30,   30,   40,   41,   42,   21,   22,
 /*    90 */    37,   30,   39,   40,   41,   42,   13,   36,   37,   13,
 /*   100 */     6,   40,   41,   42,   21,   22,   30,   21,   22,   30,
 /*   110 */    21,   22,   36,   37,   30,   21,   40,   41,   42,   40,
 /*   120 */    36,   37,    3,   44,   40,   41,   42,   28,   30,   30,
 /*   130 */    31,   32,   28,    7,   30,   31,   32,   18,   40,   40,
 /*   140 */    42,   42,   16,   30,   40,   28,   42,   30,   31,   32,
 /*   150 */    37,   30,   30,   40,   41,   42,   16,   40,   37,   42,
 /*   160 */    30,   40,   41,   42,   29,   30,   30,   37,    0,   30,
 /*   170 */    40,   41,   42,   37,    6,   13,   40,   41,   42,   30,
 /*   180 */    12,   30,   30,   21,   22,   17,   30,   19,    9,   40,
 /*   190 */    41,   42,   40,   41,   42,    7,   40,   41,   42,   30,
 /*   200 */    21,   22,   30,   30,   16,   30,   33,   34,   30,   40,
 /*   210 */    41,   42,   40,   41,   42,   40,   41,   42,   40,   41,
 /*   220 */    42,   30,   29,   30,   30,   15,   16,   30,   29,   30,
 /*   230 */    30,   40,   41,   42,   40,   41,   42,   40,   41,   42,
 /*   240 */    40,   41,   42,   28,   30,   30,    1,    7,   30,   28,
 /*   250 */    10,   30,   20,   21,   40,   40,   42,   42,   40,   41,
 /*   260 */    42,   40,    2,   42,    1,    1,   16,    1,    7,    9,
 /*   270 */     5,    8,    8,   13,    8,    1,    1,    1,    1,    9,
 /*   280 */    15,    3,    8,    8,    8,    8,    3,    2,   18,    3,
 /*   290 */     3,    2,   10,   10,    9,    2,   18,   10,   18,   15,
 /*   300 */    16,   13,    4,   45,   18,   15,   16,   13,   45,   18,
 /*   310 */    45,   45,   20,   18,   18,   18,   45,   18,
};
#define YY_SHIFT_USE_DFLT (-5)
#define YY_SHIFT_COUNT (93)
#define YY_SHIFT_MIN   (-4)
#define YY_SHIFT_MAX   (299)
static const short yy_shift_ofst[] = {
 /*     0 */    26,   26,   36,   56,   56,   56,   56,   56,   56,   56,
 /*    10 */    56,   67,   67,   67,   56,   56,   56,   56,   83,  179,
 /*    20 */    86,  162,   89,   89,   89,   89,   89,   89,   89,   89,
 /*    30 */    89,   89,   89,   89,   89,   89,   -1,   -1,   -1,   89,
 /*    40 */    94,   94,   94,  232,  232,   47,   47,   47,   47,  168,
 /*    50 */   260,   -4,   35,  126,  263,  264,  266,  274,  240,  275,
 /*    60 */   276,  277,   44,  119,  278,  265,  283,  285,  188,  287,
 /*    70 */   270,  210,  286,  284,  290,   58,  140,  245,  250,  261,
 /*    80 */   261,  289,  282,  288,  294,  280,  291,  298,  292,  293,
 /*    90 */   295,  296,  297,  299,
};
#define YY_REDUCE_USE_DFLT (-27)
#define YY_REDUCE_COUNT (48)
#define YY_REDUCE_MIN   (-26)
#define YY_REDUCE_MAX   (221)
static const short yy_reduce_ofst[] = {
 /*     0 */   -24,  -16,   -8,   14,   22,   30,   45,   53,   61,   76,
 /*    10 */    84,   99,  104,  117,  113,  121,  130,  136,  149,  152,
 /*    20 */   156,  149,  169,  172,  175,  178,  191,  194,  197,  200,
 /*    30 */    -2,  215,  218,  221,   79,   98,  -26,   46,  173,  214,
 /*    40 */   135,  193,  199,  -21,    6,   54,  122,  139,  151,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   233,  232,  271,  274,  274,  274,  274,  274,  274,  274,
 /*    10 */   274,  274,  274,  274,  274,  274,  274,  274,  274,  274,
 /*    20 */   274,  274,  274,  274,  274,  274,  274,  274,  274,  274,
 /*    30 */   274,  274,  274,  274,  274,  274,  274,  274,  274,  274,
 /*    40 */   274,  274,  274,  274,  274,  274,  274,  274,  274,  274,
 /*    50 */   270,  274,  274,  274,  274,  264,  266,  265,  274,  274,
 /*    60 */   237,  274,  270,  274,  274,  274,  274,  270,  274,  274,
 /*    70 */   226,  274,  274,  274,  274,  248,  246,  274,  243,  239,
 /*    80 */   235,  274,  274,  274,  274,  274,  274,  274,  274,  254,
 /*    90 */   274,  274,  225,  274,
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
  "$",             "REVERSE_IMPLICATION",  "EQUAL",         "COMMA",       
  "LPAREN",        "RPAREN",        "NEWLINE",       "CONJUNCTION", 
  "DISJUNCTION",   "LBRACKET",      "RBRACKET",      "IMPLICATION", 
  "SORTS",         "NEGATION",      "WS",            "SEMI_COLON",  
  "DOT",           "OBJECTS",       "COLON",         "CONSTANTS",   
  "COUNT",         "STRING",        "NUMBER",        "error",       
  "start",         "prog",          "predicate",     "decl",        
  "variables",     "sortdecl",      "string",        "objectdecl",  
  "object",        "constantdecl",  "constant",      "rule",        
  "body",          "bodydef",       "bodydef2",      "head",        
  "number",        "literal",       "variable",      "aggregateCum",
  "aggregate",   
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "start ::= prog",
 /*   1 */ "prog ::= prog SORTS sortdecl",
 /*   2 */ "sortdecl ::= string SEMI_COLON sortdecl",
 /*   3 */ "sortdecl ::= NEWLINE sortdecl",
 /*   4 */ "sortdecl ::= string DOT",
 /*   5 */ "prog ::= prog OBJECTS objectdecl",
 /*   6 */ "objectdecl ::= object SEMI_COLON objectdecl",
 /*   7 */ "objectdecl ::= object DOT",
 /*   8 */ "objectdecl ::= NEWLINE objectdecl",
 /*   9 */ "object ::= variables COLON COLON string",
 /*  10 */ "prog ::= prog CONSTANTS constantdecl",
 /*  11 */ "constantdecl ::= constant SEMI_COLON constantdecl",
 /*  12 */ "constantdecl ::= constant DOT",
 /*  13 */ "constantdecl ::= NEWLINE constantdecl",
 /*  14 */ "constant ::= string LBRACKET variables RBRACKET COLON COLON string",
 /*  15 */ "constant ::= string LBRACKET variables RBRACKET",
 /*  16 */ "constant ::= string",
 /*  17 */ "constant ::= string COLON COLON string",
 /*  18 */ "prog ::= prog NEWLINE predicate",
 /*  19 */ "prog ::= predicate",
 /*  20 */ "prog ::= prog NEWLINE rule",
 /*  21 */ "prog ::= rule",
 /*  22 */ "prog ::= prog NEWLINE",
 /*  23 */ "prog ::=",
 /*  24 */ "rule ::= REVERSE_IMPLICATION body DOT",
 /*  25 */ "rule ::= number REVERSE_IMPLICATION body",
 /*  26 */ "rule ::= head DISJUNCTION bodydef DOT",
 /*  27 */ "rule ::= number head DISJUNCTION bodydef",
 /*  28 */ "rule ::= head REVERSE_IMPLICATION body DOT",
 /*  29 */ "rule ::= number head REVERSE_IMPLICATION body",
 /*  30 */ "rule ::= number NEGATION NEGATION LBRACKET head REVERSE_IMPLICATION body RBRACKET",
 /*  31 */ "rule ::= LPAREN head RPAREN REVERSE_IMPLICATION body DOT",
 /*  32 */ "body ::= body CONJUNCTION bodydef",
 /*  33 */ "head ::= head DISJUNCTION bodydef",
 /*  34 */ "head ::= bodydef",
 /*  35 */ "body ::= bodydef",
 /*  36 */ "bodydef ::= literal",
 /*  37 */ "bodydef ::= NEGATION literal",
 /*  38 */ "bodydef ::= NEGATION NEGATION literal",
 /*  39 */ "bodydef ::= LBRACKET NEGATION NEGATION literal RBRACKET",
 /*  40 */ "bodydef ::= string EQUAL string",
 /*  41 */ "bodydef ::= NEGATION string EQUAL string",
 /*  42 */ "bodydef ::= string NEGATION EQUAL string",
 /*  43 */ "literal ::= string LBRACKET variables RBRACKET EQUAL variable",
 /*  44 */ "literal ::= string LBRACKET variables RBRACKET",
 /*  45 */ "literal ::= variable",
 /*  46 */ "literal ::= string EQUAL COUNT LPAREN aggregateCum RPAREN",
 /*  47 */ "aggregate ::= string COLON literal",
 /*  48 */ "aggregate ::= number COLON literal",
 /*  49 */ "aggregate ::= string COMMA literal COLON literal",
 /*  50 */ "aggregate ::= number COMMA literal COLON literal",
 /*  51 */ "aggregateCum ::= aggregate",
 /*  52 */ "aggregateCum ::= aggregateCum SEMI_COLON aggregate",
 /*  53 */ "predicate ::= literal DOT",
 /*  54 */ "predicate ::= number literal",
 /*  55 */ "predicate ::= number NEGATION NEGATION literal",
 /*  56 */ "predicate ::= number NEGATION literal",
 /*  57 */ "predicate ::= NEGATION NEGATION literal DOT",
 /*  58 */ "variables ::= variable",
 /*  59 */ "variables ::= variables COMMA variable",
 /*  60 */ "variable ::= string",
 /*  61 */ "variable ::= number",
 /*  62 */ "string ::= STRING",
 /*  63 */ "number ::= NUMBER",
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
  { 29, 3 },
  { 29, 2 },
  { 29, 2 },
  { 25, 3 },
  { 31, 3 },
  { 31, 2 },
  { 31, 2 },
  { 32, 4 },
  { 25, 3 },
  { 33, 3 },
  { 33, 2 },
  { 33, 2 },
  { 34, 7 },
  { 34, 4 },
  { 34, 1 },
  { 34, 4 },
  { 25, 3 },
  { 25, 1 },
  { 25, 3 },
  { 25, 1 },
  { 25, 2 },
  { 25, 0 },
  { 35, 3 },
  { 35, 3 },
  { 35, 4 },
  { 35, 4 },
  { 35, 4 },
  { 35, 4 },
  { 35, 8 },
  { 35, 6 },
  { 36, 3 },
  { 39, 3 },
  { 39, 1 },
  { 36, 1 },
  { 37, 1 },
  { 37, 2 },
  { 37, 3 },
  { 37, 5 },
  { 37, 3 },
  { 37, 4 },
  { 37, 4 },
  { 41, 6 },
  { 41, 4 },
  { 41, 1 },
  { 41, 6 },
  { 44, 3 },
  { 44, 3 },
  { 44, 5 },
  { 44, 5 },
  { 43, 1 },
  { 43, 3 },
  { 26, 2 },
  { 26, 2 },
  { 26, 4 },
  { 26, 3 },
  { 26, 4 },
  { 28, 1 },
  { 28, 3 },
  { 42, 1 },
  { 42, 1 },
  { 30, 1 },
  { 40, 1 },
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
      case 2: /* sortdecl ::= string SEMI_COLON sortdecl */
{
	std::string str = yymsp[-2].minor.yy0->toString();
	auto it = tree->domainNamesList.find(str);
	if(it != tree->domainNamesList.end())
		throw syntax_exception("Redeclaration of sort "+yymsp[-2].minor.yy0->toString()+"\n");
	else
		tree->domainNamesList.insert(yymsp[-2].minor.yy0->toString());
}
        break;
      case 4: /* sortdecl ::= string DOT */
{
	std::string str = yymsp[-1].minor.yy0->toString();
	auto it = tree->domainNamesList.find(str);
	if(it != tree->domainNamesList.end())
		throw syntax_exception("Redeclaration of sort "+yymsp[-1].minor.yy0->toString()+"\n");
	else
		tree->domainNamesList.insert(str);	
}
        break;
      case 9: /* object ::= variables COLON COLON string */
{
	// if(tree->cdp == Tree::Current_Decl_Part::DECL_OBJECTS){
		auto itr = tree->domainNamesList.find(yymsp[0].minor.yy0->toString());
		if(itr != tree->domainNamesList.end()){
			Domain* d  = new Domain(yymsp[0].minor.yy0->toString());
			d->setVars(*yymsp[-3].minor.yy85);
			tree->domains.insert(*d);
			for(auto& v : d->getVars()){
				tree->domainList.insert(v);	
			}
			cout<<d->toString(false);
			delete d;
		}
		else{
			throw syntax_exception("Domain " + yymsp[0].minor.yy0->toString() +" not declared.\n");
		}
	
	delete yymsp[-3].minor.yy85;
}
        break;
      case 14: /* constant ::= string LBRACKET variables RBRACKET COLON COLON string */
{
	Variable* va = new Variable;
	std::map<int, Domain> posMap;
	std::set<Domain>::iterator itr;
	int i=0;
	for(auto& v : *yymsp[-4].minor.yy85){
		itr = tree->domains.find(*v);
		if (itr == tree->domains.end()){
			// std::cout<<"Error:Domain:"+ *v +" not found.\n";
			throw syntax_exception("Syntax Error - Domain " + *v + " not found.\n");
		}
		else{
			// itr = tree->domains.find(*v);
			// va->setVar(yymsp[-6].minor.yy0->token);
			posMap[i++] = *itr;
		}
	}

	itr = tree->domains.find(yymsp[0].minor.yy0->toString());
	if (itr == tree->domains.end()){
		throw syntax_exception("Syntax Error - Domain " + yymsp[0].minor.yy0->toString() + " not found.\n");
	}
	else{
		posMap[i] = *itr;
		va->setRhsDomain(*itr);
	}

	va->setVar(yymsp[-6].minor.yy0->toString());
	va->setPosMap(posMap);
	tree->variables.insert(*va);
	

	/*for ASP output we do not print constants */
	if(tree->outputType != OutputType::OUTPUT_ASP)
		cout<<va->toString();

	delete va;
	delete yymsp[-4].minor.yy85;
}
        break;
      case 15: /* constant ::= string LBRACKET variables RBRACKET */
{
	Variable* va = new Variable;
	std::map<int, Domain> posMap;
	std::set<Domain>::iterator itr;
	int i=0;
	for(auto& v : *yymsp[-1].minor.yy85){
		itr = tree->domains.find(*v);
		if (itr == tree->domains.end()){
			throw syntax_exception("Syntax Error - Domain " + *v + " not found.\n");
		}
		else{
			posMap[i++] = *itr;
		}
	}

	va->setVar(yymsp[-3].minor.yy0->toString());
	va->setPosMap(posMap);
	tree->variables.insert(*va);

	/*for ASP output we do not print constants */
	if(tree->outputType != OutputType::OUTPUT_ASP)
		cout<<va->toString();
	delete yymsp[-1].minor.yy85;
	delete va;
}
        break;
      case 16: /* constant ::= string */
{
	Variable* va = new Variable;
	va->setVar(yymsp[0].minor.yy0->toString());
	tree->variables.insert(*va);
	/*for ASP output we do not print constants */
	if(tree->outputType != OutputType::OUTPUT_ASP)
		cout<<va->toString()<<"\n";
	
	delete va;	
}
        break;
      case 17: /* constant ::= string COLON COLON string */
{
	Variable* va = new Variable;
	std::map<int, Domain> posMap;
	std::set<Domain>::iterator itr;
	int i=0;
	

	itr = tree->domains.find(yymsp[0].minor.yy0->toString());
	if (itr == tree->domains.end()){
		throw syntax_exception("Syntax Error - Domain " + yymsp[0].minor.yy0->toString() + " not found.\n");
	}
	else{
		posMap[i] = *itr;
		va->setRhsDomain(*itr);
	}

	va->setVar(yymsp[-3].minor.yy0->toString());
	va->setPosMap(posMap);
	tree->variables.insert(*va);
	/*for ASP output we do not print constants */
	if(tree->outputType != OutputType::OUTPUT_ASP)
		cout<<va->toString();
	
	delete va;	
}
        break;
      case 18: /* prog ::= prog NEWLINE predicate */
{ 
	if(yymsp[0].minor.yy42->needsToBeCompleted()){	
		FactCompletion f(*yymsp[0].minor.yy42);
		tree->facts.insert(std::pair<std::string,FactCompletion>(f.getHead().getVar(),f)); 
	}

			
	delete yymsp[0].minor.yy42;
}
        break;
      case 19: /* prog ::= predicate */
{ 
	if(yymsp[0].minor.yy42->needsToBeCompleted()){
		FactCompletion f(*yymsp[0].minor.yy42);
		tree->facts.insert(std::pair<std::string,FactCompletion>(f.getHead().getVar(),f)); 	
	}
	delete yymsp[0].minor.yy42;
}
        break;
      case 20: /* prog ::= prog NEWLINE rule */
      case 21: /* prog ::= rule */ yytestcase(yyruleno==21);
{
	if((yymsp[0].minor.yy3->isHeadTop == false) && (yymsp[0].minor.yy3->toBeCompleted == true))
		tree->rules.insert(std::pair<std::string,RuleCompletion>(yymsp[0].minor.yy3->getHead().getVar(),*yymsp[0].minor.yy3));
	delete yymsp[0].minor.yy3;
}
        break;
      case 24: /* rule ::= REVERSE_IMPLICATION body DOT */
{
	yygotominor.yy3 = new RuleCompletion;
	yygotominor.yy3->isHeadTop = true;
	
	if(tree->outputType != OutputType::OUTPUT_ASP){
		std::cout<<"("
					<<yymsp[-1].minor.yy49->toNNFString()
					<<")"
					<<LanguageConstants::LINE_END
					<<"\n";
	}
	else{
		std::cout<<LanguageConstants::IMPL
				<<yymsp[-1].minor.yy49->toString()
				<<LanguageConstants::LINE_END
				<<"\n";
	}
	delete yymsp[-1].minor.yy49;
}
        break;
      case 25: /* rule ::= number REVERSE_IMPLICATION body */
{
	yygotominor.yy3 = new RuleCompletion;
	yygotominor.yy3->isHeadTop = true;
	
	if(tree->outputType != OutputType::OUTPUT_ASP){
		std::cout<<yymsp[-2].minor.yy0->toString()<<SPACE
					<<"("
					<<yymsp[0].minor.yy49->toNNFString()
					<<")"
					<<"\n";
	}
	else{
		std::string str = ":~"
				+ yymsp[0].minor.yy49->toString()
				+ " , "
				+ yymsp[0].minor.yy49->getExtra(tree->variables) 
				+ LanguageConstants::LINE_END
				+ " "
				+ "["
				+  std::to_string((int)(std::stof(yymsp[-2].minor.yy0->toString())* 10000))
				+  ","
				+  std::to_string(tree->weak_constraint_counter);

		std::string temp = yymsp[0].minor.yy49->getExtraConstants();
		if(temp.length() > 0){
			str += ","
				+ temp;
		}
				
		str += std::string("]") + std::string("\n");

		cout << str;
		tree->weak_constraint_counter++;
	
	}
	// std::cout<<yymsp[-2].minor.yy0->toString()<<SPACE<<"("<<yymsp[0].minor.yy49->toNNFString()<<")"<<"\n";
	delete yymsp[0].minor.yy49;
}
        break;
      case 26: /* rule ::= head DISJUNCTION bodydef DOT */
{
	//Doing this 
	yygotominor.yy3 = new RuleCompletion;
	yygotominor.yy3->isHeadTop = true;
	yymsp[-3].minor.yy65->addPredicate(yymsp[-1].minor.yy43->getPredicate());
	// RULE_COMPLETION_HEAD_DIS_BODY_TOP(yymsp[-3].minor.yy65,yymsp[-1].minor.yy43)
	try{
		RuleCompletion_HD_BT(yymsp[-3].minor.yy65,tree);
	}
	catch(const std::out_of_range& e){
		throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}
	
	yymsp[-3].minor.yy65->appendStr(yymsp[-1].minor.yy43->getPredicate().toString(),false,true,false);
	
	std::string temp;
	if(tree->outputType == OutputType::OUTPUT_ASP){
		temp = yymsp[-3].minor.yy65->getExtra(tree->variables);
		if(temp.length() > 0){
			temp = yymsp[-3].minor.yy65->toString() + ":-" + temp;
		}
		else{
			temp = yymsp[-3].minor.yy65->toString();
		}
	}
	
	std::cout<<temp<<"."<<"\n";
	
	delete yymsp[-3].minor.yy65;
	delete yymsp[-1].minor.yy43;
}
        break;
      case 27: /* rule ::= number head DISJUNCTION bodydef */
{
	//Doing this 
	yygotominor.yy3 = new RuleCompletion;
	yygotominor.yy3->isHeadTop = true;
	yymsp[-2].minor.yy65->addPredicate(yymsp[0].minor.yy43->getPredicate());
	// RULE_COMPLETION_HEAD_DIS_BODY_TOP(yymsp[-2].minor.yy65,yymsp[0].minor.yy43)
	try{
		RuleCompletion_HD_BT(yymsp[-2].minor.yy65,tree);
	}
	catch(const std::out_of_range& e){
		throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}
	yymsp[-2].minor.yy65->appendStr(yymsp[0].minor.yy43->getPredicate().toString(),false,true,false);
	std::cout<<yymsp[-3].minor.yy0->toString()<<SPACE<<yymsp[-2].minor.yy65->toString()<<"\n";
	delete yymsp[-2].minor.yy65;
	delete yymsp[0].minor.yy43;
}
        break;
      case 28: /* rule ::= head REVERSE_IMPLICATION body DOT */
{
	yygotominor.yy3 = new RuleCompletion;

	if (yymsp[-3].minor.yy65->getDisjunction()){
		// RULE_COMPLETION_HEAD_DIS_BODY_TOP(yymsp[-3].minor.yy65,yymsp[-1].minor.yy49)
		yygotominor.yy3->isHeadTop = true;
		RuleCompletion_HD_BC(yymsp[-3].minor.yy65,yymsp[-1].minor.yy49,true,tree);
		if(tree->outputType == OutputType::OUTPUT_ALCHEMY)
			std::cout<<yymsp[-1].minor.yy49->toString()
					<<" => "
					<<yymsp[-3].minor.yy65->toString()
					<<LanguageConstants::LINE_END
					<<"\n";
		if(tree->outputType == OutputType::OUTPUT_ASP)
			tree->printASPRuleHB(yymsp[-3].minor.yy65,yymsp[-1].minor.yy49);
	}
	else{
		// RULE_COMPLETION_BH(yymsp[-1].minor.yy49,yymsp[-3].minor.yy65);
		// yygotominor.yy3 = new RuleCompletion(yymsp[-3].minor.yy65->getPredicate(),predList, resultMap, varMap);
		try{
			yygotominor.yy3 = RuleCompletion_BH(yymsp[-1].minor.yy49,yymsp[-3].minor.yy65,tree);
		}
		catch(const std::out_of_range& e){
			throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
		}
		if(tree->outputType == OutputType::OUTPUT_ALCHEMY)
			std::cout<<yymsp[-1].minor.yy49->toString()
					<<" => "
					<<yymsp[-3].minor.yy65->toString()
					<<LanguageConstants::LINE_END
					<<"\n";
		if(tree->outputType == OutputType::OUTPUT_ASP)
			tree->printASPRuleHB(yymsp[-3].minor.yy65,yymsp[-1].minor.yy49);
	}
	delete yymsp[-1].minor.yy49;
	delete yymsp[-3].minor.yy65;
}
        break;
      case 29: /* rule ::= number head REVERSE_IMPLICATION body */
{
	// RULE_COMPLETION_BH(yymsp[0].minor.yy49,yymsp[-2].minor.yy65);
	// yygotominor.yy3 = new RuleCompletion(yymsp[-2].minor.yy65->getPredicate(),predList, resultMap, varMap);
	try{
		yygotominor.yy3 = RuleCompletion_BH(yymsp[0].minor.yy49,yymsp[-2].minor.yy65,tree);
	}
	catch(const std::out_of_range& e){
			throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY)
		std::cout<< yymsp[-3].minor.yy0->toString()
				<<SPACE
				<<yymsp[0].minor.yy49->toString()
				<<" => "
				<<yymsp[-2].minor.yy65->toString()
				<<"\n";
	
	if(tree->outputType == OutputType::OUTPUT_ASP){

		std::cout << "unsat(" << tree->weak_constraint_counter << ")"
					<< " :- "
					<< yymsp[0].minor.yy49->toString()
					<< " , "
					/*Change this to NNF String*/
					<< yymsp[-2].minor.yy65->toNNFString()
					<<LanguageConstants::LINE_END
					<<"\n"; 

		std::cout << yymsp[-2].minor.yy65->toString()
					<< " :- "
					<< yymsp[0].minor.yy49->toString()
					<< " , "
					<< "not "
					<< "unsat(" << tree->weak_constraint_counter << ")"
					<<LanguageConstants::LINE_END
					<<"\n"; 

	
		std::cout   << " :~ "
					<< "unsat(" << tree->weak_constraint_counter << ")"
					<< ". "
					<< "["
					<< std::to_string((int)(std::stof(yymsp[-3].minor.yy0->toString())* 10000))
					<<","
					<< tree->weak_constraint_counter
					<< "]"
					<<"\n";

		tree->weak_constraint_counter++; 


	}


	delete yymsp[0].minor.yy49;
	delete yymsp[-2].minor.yy65;
}
        break;
      case 30: /* rule ::= number NEGATION NEGATION LBRACKET head REVERSE_IMPLICATION body RBRACKET */
{
	yygotominor.yy3 = new RuleCompletion;
	yygotominor.yy3->isHeadTop = true;	
	tree->statHasDblNeg = true;

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY)
		std::cout<< yymsp[-7].minor.yy0->toString() 
				<< SPACE 
				<<"!!("
				<<yymsp[-1].minor.yy49->toString()
				<<" => "
				<<yymsp[-3].minor.yy65->toString()
				<<"\n"; 
	if(tree->outputType == OutputType::OUTPUT_ASP)
		std::cout<< yymsp[-7].minor.yy0->toString() 
				<< SPACE 
				<<yymsp[-3].minor.yy65->toString()
				<<" :- "
				<<yymsp[-1].minor.yy49->toString()
				<<LanguageConstants::LINE_END
				<<"\n"; 
	
	delete yymsp[-1].minor.yy49;
	delete yymsp[-3].minor.yy65;
}
        break;
      case 31: /* rule ::= LPAREN head RPAREN REVERSE_IMPLICATION body DOT */
{
	
	if (yymsp[-4].minor.yy65->getPredicate().checkEquality() != 0){
		throw syntax_exception("Cannot have equality/Inequlity as a part of choice rule\n");
	}

	// RULE_COMPLETION_BH(yymsp[-1].minor.yy49,yymsp[-4].minor.yy65);
	// yygotominor.yy3 = new RuleCompletion(yymsp[-4].minor.yy65->getPredicate(),predList, resultMap, varMap);
	try{
		yygotominor.yy3 = RuleCompletion_BH(yymsp[-1].minor.yy49,yymsp[-4].minor.yy65,tree);
	}
	catch(const std::out_of_range& e){
			throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY)
		std::cout<<COMMENT<<yymsp[-1].minor.yy49->toString()<<" => "<<yymsp[-4].minor.yy65->toString()<<"\n";
	if(tree->outputType == OutputType::OUTPUT_ASP)
		std::cout<<yymsp[-4].minor.yy65->toString()<<" :- "<<yymsp[-1].minor.yy49->toString()<<LanguageConstants::LINE_END<<"\n";
	delete yymsp[-1].minor.yy49;
	delete yymsp[-4].minor.yy65;
}
        break;
      case 32: /* body ::= body CONJUNCTION bodydef */
{
	yygotominor.yy49 = yymsp[-2].minor.yy49;
	yymsp[-2].minor.yy49->addPredicate(yymsp[0].minor.yy43->getPredicate());
	yygotominor.yy49->appendStr(yymsp[0].minor.yy43->getPredicate(),false,false,true);
	delete yymsp[0].minor.yy43;
}
        break;
      case 33: /* head ::= head DISJUNCTION bodydef */
{
	yygotominor.yy65 = yymsp[-2].minor.yy65;
	yymsp[-2].minor.yy65->addPredicate(yymsp[0].minor.yy43->getPredicate());
	yygotominor.yy65->appendStr(yymsp[0].minor.yy43->getPredicate().toString(),false,true,false);
	yygotominor.yy65->setDisjunction(true);
	delete yymsp[0].minor.yy43;
}
        break;
      case 34: /* head ::= bodydef */
{
	yygotominor.yy65 = new Head(yymsp[0].minor.yy43->getPredicate());
	// yygotominor.yy65->addPredicate(yymsp[0].minor.yy43->getPredicate());
	yygotominor.yy65->appendStr(yymsp[0].minor.yy43->getPredicate().toString(),false,false,false);
	delete yymsp[0].minor.yy43;
}
        break;
      case 35: /* body ::= bodydef */
{
	yygotominor.yy49 = new Body;
	Predicate p = yymsp[0].minor.yy43->getPredicate();
	yygotominor.yy49->addPredicate(p);
	yygotominor.yy49->appendStr(p,false,false,false);
	delete yymsp[0].minor.yy43;
}
        break;
      case 36: /* bodydef ::= literal */
{	
	yygotominor.yy43 = yymsp[0].minor.yy43;
}
        break;
      case 37: /* bodydef ::= NEGATION literal */
{	
	yygotominor.yy43 = yymsp[0].minor.yy43;
	Predicate p = yygotominor.yy43->getPredicate();
	p.setSingleNegation(true);
	yygotominor.yy43->addPredicate(p);
	// yygotominor.yy43->getPredicate().setSingleNegation(true);
}
        break;
      case 38: /* bodydef ::= NEGATION NEGATION literal */
{	
	yygotominor.yy43 = yymsp[0].minor.yy43;
	tree->statHasDblNeg = true;
	yygotominor.yy43->getPredicate().setDoubleNegation(true);
}
        break;
      case 39: /* bodydef ::= LBRACKET NEGATION NEGATION literal RBRACKET */
{	
	yygotominor.yy43 = yymsp[-1].minor.yy43;
	tree->statHasDblNeg = true;
	yygotominor.yy43->getPredicate().setDoubleNegation(true);
}
        break;
      case 40: /* bodydef ::= string EQUAL string */
{
	yygotominor.yy43 = new BodyDef;
	auto itr = tree->variables.find(*(yymsp[-2].minor.yy0->token));
	if (itr != tree->variables.end()){
		/*Treat it as a bodydef with 1 variable*/

		/* 
		Check if yymsp[0].minor.yy0 is a valid value of it's domain.
		If it is not throw syntax_exception.
		Why? It could be a variable also which is not a part of the domain. 
		Not required in this case.
		*/
		
		std::vector<std::string> vars;
		vars.push_back(*(yymsp[0].minor.yy0->token));
		Predicate p(yymsp[-2].minor.yy0->token);
		p.setTokens(vars, tree->domainList);
		yygotominor.yy43->addPredicate(p);
		int expectedArgs = (tree->variables.find(*(yymsp[-2].minor.yy0->token)))->getSize();
		if (expectedArgs != vars.size()){
			delete yygotominor.yy43;
			throw invalid_arguments(expectedArgs, vars.size(), *(yymsp[-2].minor.yy0->token));
		}
	}
	
	else{
		Predicate p(yymsp[-2].minor.yy0->token,yymsp[0].minor.yy0->token);
		p.setEquality();
		yygotominor.yy43->addPredicate(p);
	}
}
        break;
      case 41: /* bodydef ::= NEGATION string EQUAL string */
{
	std::vector<std::string> vars;
	vars.push_back(yymsp[0].minor.yy0->toString());
	Predicate p(yymsp[-2].minor.yy0->token);
	p.setTokens(vars, tree->domainList);
	p.setSingleNegation(true);
	yygotominor.yy43 = new BodyDef;
	yygotominor.yy43->addPredicate(p);
	// delete Ve;
	int expectedArgs = (tree->variables.find(*(yymsp[-2].minor.yy0->token)))->getSize();
	if (expectedArgs != vars.size()){
		delete yygotominor.yy43;
		throw invalid_arguments(expectedArgs, vars.size(), *(yymsp[-2].minor.yy0->token));
	}
}
        break;
      case 42: /* bodydef ::= string NEGATION EQUAL string */
{
	
	/*check if yymsp[-3].minor.yy0 is declared in constant section
	 if it is then it's a syntax error 
	 Cannot have HiddeIn != P1 */
	auto itr = tree->variables.find(*(yymsp[-3].minor.yy0->token));
	if (itr != tree->variables.end()){
		throw syntax_exception("!= cannot be used with a constant on LHS.\n");
	}

	Predicate p(yymsp[-3].minor.yy0->token,yymsp[0].minor.yy0->token);
	p.setInEquality();
	yygotominor.yy43 = new BodyDef;
	yygotominor.yy43->addPredicate(p);
}
        break;
      case 43: /* literal ::= string LBRACKET variables RBRACKET EQUAL variable */
{
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-3].minor.yy85)
		vars.push_back(*v);
	vars.push_back(*(yymsp[0].minor.yy0->token));
	Predicate p(yymsp[-5].minor.yy0->token);
	p.setTokens(vars, tree->domainList);
	yygotominor.yy43 = new BodyDef;
	yygotominor.yy43->addPredicate(p);
	auto itr = tree->variables.find(yymsp[-5].minor.yy0->toString());
	if(itr == tree->variables.end()){
		delete yygotominor.yy43;
		throw syntax_exception("Literal "+ yymsp[-5].minor.yy0->toString() + " not found.\n");
	}
	delete yymsp[-3].minor.yy85;
	int expectedArgs = (tree->variables.find(yymsp[-5].minor.yy0->toString()))->getSize();
	if (expectedArgs != vars.size()){
		delete yygotominor.yy43;
		throw invalid_arguments(expectedArgs, vars.size(), *(yymsp[-5].minor.yy0->token));
	}
}
        break;
      case 44: /* literal ::= string LBRACKET variables RBRACKET */
{
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-1].minor.yy85)
		vars.push_back(*v);
	Predicate p(yymsp[-3].minor.yy0->token);
	p.setTokens(vars, tree->domainList);
	yygotominor.yy43 = new BodyDef;
	yygotominor.yy43->addPredicate(p);
	delete yymsp[-1].minor.yy85;
	auto itr = tree->variables.find(yymsp[-3].minor.yy0->toString());
	if(itr == tree->variables.end()){
		delete yygotominor.yy43;
		throw syntax_exception("Literal "+ yymsp[-3].minor.yy0->toString() + " not found.\n");
	}
	int expectedArgs = itr->getSize();
	if (expectedArgs != vars.size()){
		delete yygotominor.yy43;
		throw invalid_arguments(expectedArgs, vars.size(), *(yymsp[-3].minor.yy0->token));
	}	
}
        break;
      case 45: /* literal ::= variable */
{
	Predicate p(yymsp[0].minor.yy0->token);
	auto itr = tree->variables.find(yymsp[0].minor.yy0->toString());
	yygotominor.yy43 = new BodyDef;
	/*Special Case: BodyDef does not have variables*/
	yygotominor.yy43->setHasVariables();
	yygotominor.yy43->addPredicate(p);
}
        break;
      case 46: /* literal ::= string EQUAL COUNT LPAREN aggregateCum RPAREN */
{
	std::string s = (*yymsp[-5].minor.yy0).toString();
	Util::toUpper(s);
	s = s + "= #count{" + yymsp[-1].minor.yy0->toString() + "}";
	Predicate p(yymsp[-5].minor.yy0->token);
	p.setString(s);
	yygotominor.yy43 = new BodyDef;
	yygotominor.yy43->addPredicate(p);
	delete yymsp[-1].minor.yy0;
}
        break;
      case 47: /* aggregate ::= string COLON literal */
{
	yygotominor.yy0 = new Token(*(yymsp[-2].minor.yy0->token));
	std::string s1 = yygotominor.yy0->toString();
	Util::toUpper(s1);
	s1 = s1 + ":" + yymsp[0].minor.yy43->toString();
	yygotominor.yy0->modifyToken(s1);
	delete yymsp[0].minor.yy43;
}
        break;
      case 48: /* aggregate ::= number COLON literal */
{
	yygotominor.yy0 = new Token(*(yymsp[-2].minor.yy0->token));
	std::string s1 = yygotominor.yy0->toString();
	s1 = s1 + ":" + yymsp[0].minor.yy43->toString();
	yygotominor.yy0->modifyToken(s1);
	delete yymsp[0].minor.yy43;
}
        break;
      case 49: /* aggregate ::= string COMMA literal COLON literal */
{
	yygotominor.yy0 = new Token(*(yymsp[-4].minor.yy0->token));
	std::string s1 = yygotominor.yy0->toString();
	Util::toUpper(s1);
	s1 = s1 + "," + yymsp[-2].minor.yy43->toString() + ":" + yymsp[0].minor.yy43->toString();
	yygotominor.yy0->modifyToken(s1);
}
        break;
      case 50: /* aggregate ::= number COMMA literal COLON literal */
{
	yygotominor.yy0 = new Token(*(yymsp[-4].minor.yy0->token));
	std::string s1 = (*yymsp[-4].minor.yy0).toString();
	// Util::toUpper(s1);
	s1 = s1 + "," + yymsp[-2].minor.yy43->toString()+ ":" + yymsp[0].minor.yy43->toString();
	yygotominor.yy0->modifyToken(s1);
}
        break;
      case 51: /* aggregateCum ::= aggregate */
{
	yygotominor.yy0 = new Token(*(yymsp[0].minor.yy0->token));
	delete yymsp[0].minor.yy0;
}
        break;
      case 52: /* aggregateCum ::= aggregateCum SEMI_COLON aggregate */
{
	yygotominor.yy0 = yymsp[-2].minor.yy0;
	yygotominor.yy0->modifyToken(yymsp[-2].minor.yy0->toString() + ";" + yymsp[0].minor.yy0->toString());
	delete yymsp[0].minor.yy0;
}
        break;
      case 53: /* predicate ::= literal DOT */
{
	yygotominor.yy42 = new Predicate;
	*yygotominor.yy42 = yymsp[-1].minor.yy43->getPredicate();
	if(yymsp[-1].minor.yy43->getHasVariables() == false){
		/*Its a special case*/
		yygotominor.yy42->notToBeCompleted();	
	}
	
	auto itr = tree->variables.find(yygotominor.yy42->getVar());
	if(itr != tree->variables.end()){
		itr->setCompleted();
	}

	std::string s1,s2;
	

	if(tree->outputType == OutputType::OUTPUT_ASP){
		s2 = yygotominor.yy42->getExtra(tree->variables);

		if(s2.length() > 0){
			s1 = yygotominor.yy42->toString(s1,false);
			s1 += ":-";
			s1 += s2;
			s1 += ".\n";
		}
		else{
			s1 = yygotominor.yy42->toString(s1,true);
		}
			

		
	}

	cout<<s1;

	delete yymsp[-1].minor.yy43;
}
        break;
      case 54: /* predicate ::= number literal */
{
	yygotominor.yy42 = new Predicate;
	*yygotominor.yy42 = yymsp[0].minor.yy43->getPredicate();

	if(yymsp[0].minor.yy43->getHasVariables() == false){
		/*Its a special case*/
		yygotominor.yy42->notToBeCompleted();	
	}
	
	auto itr = tree->variables.find(yygotominor.yy42->getVar());
	if(itr != tree->variables.end()){
		itr->setCompleted();
	}

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY){
		cout<<yygotominor.yy42->toString(yymsp[-1].minor.yy0->toString()+SPACE, false);
	}
	if(tree->outputType == OutputType::OUTPUT_ASP){

		std::cout << "unsat(" << tree->weak_constraint_counter << ")"
					<< " :- "
					<< "not "
					<< yygotominor.yy42->toString()
					<<LanguageConstants::LINE_END
					<<"\n"; 

		std::cout << yygotominor.yy42->toString()
					<< " :- "
					<< "not "
					<< "unsat(" << tree->weak_constraint_counter << ")"
					<<LanguageConstants::LINE_END
					<<"\n"; 

	
		std::cout   << " :~ "
					<< "unsat(" << tree->weak_constraint_counter << ")"
					<< ". "
					<< "["
					<< std::to_string((int)(std::stof(yymsp[-1].minor.yy0->toString())* 10000))
					<<","
					<< tree->weak_constraint_counter
					<< "]"
					<<"\n";

		tree->weak_constraint_counter++; 

	}	
	delete yymsp[0].minor.yy43;
}
        break;
      case 55: /* predicate ::= number NEGATION NEGATION literal */
{
	yygotominor.yy42 = new Predicate;
	*yygotominor.yy42 = yymsp[0].minor.yy43->getPredicate();
	yygotominor.yy42->notToBeCompleted();

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY){
		tree->statHasDblNeg = true;
		cout<<yygotominor.yy42->toString(yymsp[-3].minor.yy0->toString()+SPACE, false);	
	}
	else if(tree->outputType == OutputType::OUTPUT_ASP){
		std::string str = yygotominor.yy42->toString(":~ not ", false);
		std::string temp  = yygotominor.yy42->getExtra(tree->variables);	
		if(temp.length() > 0)
			str += ",";
		str += temp;
		str += LanguageConstants::LINE_END;
		str += " [" + 
				std::to_string((int)(std::stof(yymsp[-3].minor.yy0->toString())* 10000)) + 
				"," + 
				std::to_string(tree->weak_constraint_counter++) + 
				"," +
				yygotominor.yy42->getExtraConstants()+
				"]\n";
		cout<<str;
	}
	
	delete yymsp[0].minor.yy43;
}
        break;
      case 56: /* predicate ::= number NEGATION literal */
{
	yygotominor.yy42 = new Predicate;
	*yygotominor.yy42 = yymsp[0].minor.yy43->getPredicate();
	yygotominor.yy42->notToBeCompleted();

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY){
		cout<<yygotominor.yy42->toString(yymsp[-2].minor.yy0->toString()+SPACE, false);
	}
	else if(tree->outputType == OutputType::OUTPUT_ASP){
		std::string str = yygotominor.yy42->toString(":~ ", false);		
		std::string temp  = yygotominor.yy42->getExtra(tree->variables);	
		if(temp.length() > 0)
			str += ",";
		str += " [" + 
		std::to_string((int)(std::stof(yymsp[-2].minor.yy0->toString())* 10000)) + 
		"," + 
		std::to_string(tree->weak_constraint_counter++) + 
		"," +
		yygotominor.yy42->getExtraConstants() + 
		"]\n";
		cout<<str;
	}

	
	delete yymsp[0].minor.yy43;
}
        break;
      case 57: /* predicate ::= NEGATION NEGATION literal DOT */
{
	yygotominor.yy42 = new Predicate;
	*yygotominor.yy42 = yymsp[-1].minor.yy43->getPredicate();
	yygotominor.yy42->notToBeCompleted();
	tree->statHasDblNeg = true;
	std::string s1; 

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY){
		cout<<yygotominor.yy42->toString(s1, false);
	}
	else if(tree->outputType == OutputType::OUTPUT_ASP){
		cout<<yygotominor.yy42->toString(":- not ", true);		
	}


	
	delete yymsp[-1].minor.yy43;	
}
        break;
      case 58: /* variables ::= variable */
{
	yygotominor.yy85 = new std::vector<std::string*>();	
	yygotominor.yy85->push_back(yymsp[0].minor.yy0->token);
}
        break;
      case 59: /* variables ::= variables COMMA variable */
{
	yygotominor.yy85 = yymsp[-2].minor.yy85;
	yymsp[-2].minor.yy85->push_back(yymsp[0].minor.yy0->token);
}
        break;
      case 60: /* variable ::= string */
      case 61: /* variable ::= number */ yytestcase(yyruleno==61);
      case 62: /* string ::= STRING */ yytestcase(yyruleno==62);
{ yygotominor.yy0=yymsp[0].minor.yy0;}
        break;
      case 63: /* number ::= NUMBER */
{ yygotominor.yy0=yymsp[0].minor.yy0; }
        break;
      default:
      /* (0) start ::= prog */ yytestcase(yyruleno==0);
      /* (1) prog ::= prog SORTS sortdecl */ yytestcase(yyruleno==1);
      /* (3) sortdecl ::= NEWLINE sortdecl */ yytestcase(yyruleno==3);
      /* (5) prog ::= prog OBJECTS objectdecl */ yytestcase(yyruleno==5);
      /* (6) objectdecl ::= object SEMI_COLON objectdecl */ yytestcase(yyruleno==6);
      /* (7) objectdecl ::= object DOT */ yytestcase(yyruleno==7);
      /* (8) objectdecl ::= NEWLINE objectdecl */ yytestcase(yyruleno==8);
      /* (10) prog ::= prog CONSTANTS constantdecl */ yytestcase(yyruleno==10);
      /* (11) constantdecl ::= constant SEMI_COLON constantdecl */ yytestcase(yyruleno==11);
      /* (12) constantdecl ::= constant DOT */ yytestcase(yyruleno==12);
      /* (13) constantdecl ::= NEWLINE constantdecl */ yytestcase(yyruleno==13);
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

    std::cout<<"Giving up.Parser is lost...\n";

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
            		// yy_parse_failed(yypParser);
                    throw syntax_exception("Syntax Error - Expected " + std::string(yyTokenName[i]) + " Found " + std::string(yyTokenName[yymajor])
+ "\n");
            }
    }
    throw syntax_exception("Parsing Failed. Unexpected sequence of tokens\n");
    
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

	if (tree->outputType == OutputType::OUTPUT_ASP)
		std::cout<<("%parsing complete!\n");
	else
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

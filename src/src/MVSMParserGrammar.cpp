/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is included that follows the "include" declaration
** in the input grammar file. */
#include <stdio.h>
#line 4 "MVSMParserGrammar.y"

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

#line 55 "MVSMParserGrammar.c"
#include "MVSMParserGrammar.h"
/* Next is all token values, in a form suitable for use by makeheaders.
** This section will be null unless lemon is run with the -m switch.
*/
/* 
** These constants (all generated automatically by the parser generator)
** specify the various kinds of tokens (terminals) that the parser
** understands. 
**
** Each symbol here is a terminal symbol in the grammar.
*/
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
#define MVSM_PARSE_TOKEN_SUM                            21
#define MVSM_PARSE_TOKEN_STRING                         22
#define MVSM_PARSE_TOKEN_NUMBER                         23
#endif
/* Make sure the INTERFACE macro is defined.
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/* The next thing included is series of defines which control
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 terminals
**                       and nonterminals.  "int" is used otherwise.
**    YYNOCODE           is a number of type YYCODETYPE which corresponds
**                       to no legal terminal or nonterminal number.  This
**                       number is used to fill in empty slots of the hash 
**                       table.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       have fall-back values which should be used if the
**                       original value of the token will not parse.
**    YYACTIONTYPE       is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 rules and
**                       states combined.  "int" is used otherwise.
**    MVSMParserGrammarTOKENTYPE     is the data type used for minor tokens given 
**                       directly to the parser from the tokenizer.
**    YYMINORTYPE        is the data type used for all minor tokens.
**                       This is typically a union of many types, one of
**                       which is MVSMParserGrammarTOKENTYPE.  The entry in the union
**                       for base tokens is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    MVSMParserGrammarARG_SDECL     A static variable declaration for the %extra_argument
**    MVSMParserGrammarARG_PDECL     A parameter declaration for the %extra_argument
**    MVSMParserGrammarARG_STORE     Code to store %extra_argument into yypParser
**    MVSMParserGrammarARG_FETCH     Code to extract %extra_argument from yypParser
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
*/
#define YYCODETYPE unsigned char
#define YYNOCODE 47
#define YYACTIONTYPE unsigned char
#if INTERFACE
#define MVSMParserGrammarTOKENTYPE Token*
#endif
typedef union {
  int yyinit;
  MVSMParserGrammarTOKENTYPE yy0;
  std::vector<std::string*>* yy7;
  Predicate* yy16;
  Body* yy21;
  RuleCompletion* yy57;
  Tree* yy63;
  Head* yy77;
  Variable* yy89;
  BodyDef* yy92;
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
#define YYNSTATE 157
#define YYNRULE 66
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)

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
**   0 <= N < YYNSTATE                  Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   YYNSTATE <= N < YYNSTATE+YYNRULE   Reduce by rule N-YYNSTATE.
**
**   N == YYNSTATE+YYNRULE              A syntax error has occurred.
**
**   N == YYNSTATE+YYNRULE+1            The parser accepts its input.
**
**   N == YYNSTATE+YYNRULE+2            No such action.  Denotes unused
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
*/
#define YY_ACTTAB_COUNT (344)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   224,   52,  104,   93,   90,  153,   53,   11,   74,  125,
 /*    10 */   146,   41,  103,  137,  110,  134,   57,    2,   81,   53,
 /*    20 */    51,  145,  125,  153,  144,  133,  102,  110,  100,   57,
 /*    30 */     2,   81,   77,   41,  146,  151,   78,  101,   17,   77,
 /*    40 */    97,  146,  150,   78,  101,  145,   77,  132,  146,  149,
 /*    50 */    78,  101,  145,  126,   53,   40,   89,  125,   29,  145,
 /*    60 */    21,   73,  113,   35,   53,  145,  130,  125,   98,  153,
 /*    70 */   144,   85,  113,   30,   53,  145,  130,  125,   43,  152,
 /*    80 */    53,   84,  113,  125,   68,  145,  130,   50,  110,   96,
 /*    90 */    62,  145,  130,   53,   34,   67,  125,   69,  119,   53,
 /*   100 */    61,  113,  125,   95,  145,  130,   56,  113,   49,   53,
 /*   110 */   145,  130,  125,  146,   42,   53,  147,  110,  125,   55,
 /*   120 */   145,  130,   54,  113,  145,   53,  145,  130,  125,  146,
 /*   130 */   153,   72,   99,  110,  125,   64,  145,   58,   10,  157,
 /*   140 */   145,    4,  145,  128,   75,    1,   89,   48,  141,   76,
 /*   150 */    18,   44,   72,   31,   53,  125,   13,  125,   39,  153,
 /*   160 */   144,   70,  131,  145,  124,  145,  130,   53,   32,   53,
 /*   170 */   125,   71,  125,  146,   28,   63,  137,  111,  145,  130,
 /*   180 */   145,  130,   53,    9,  145,  125,   72,   93,   90,  125,
 /*   190 */    83,   89,   33,  145,  130,   20,   72,  145,   92,  125,
 /*   200 */   118,  153,  144,   72,  153,  144,  125,  145,  123,   72,
 /*   210 */    35,   68,  125,   36,  145,  122,   72,   12,  142,  125,
 /*   220 */   145,   91,   67,   72,   66,  119,  125,  145,  121,   72,
 /*   230 */    41,   45,  125,   25,  145,   87,   65,   94,   32,  125,
 /*   240 */   145,   80,   86,   65,   24,   26,  125,  145,  129,  156,
 /*   250 */    79,   38,  135,   72,  145,   59,  125,   75,   37,   68,
 /*   260 */    27,  140,   76,   75,  145,   60,  146,  139,   76,  127,
 /*   270 */    67,   19,    7,  120,  153,   46,   17,  145,   22,  112,
 /*   280 */   153,  144,   32,    8,  191,  153,  144,  153,  144,    6,
 /*   290 */    16,  191,  196,  195,  194,    5,   15,   17,   88,  196,
 /*   300 */   195,  194,   14,   17,   47,   82,  108,  116,   15,  155,
 /*   310 */    79,   23,  107,   17,  154,   79,    3,  153,  144,  109,
 /*   320 */   106,  105,  225,  153,  225,  225,  225,  225,  225,  225,
 /*   330 */   148,  225,  225,  225,  225,  225,  225,  225,  143,  138,
 /*   340 */   136,  114,  117,  115,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    25,   26,   27,   20,   21,   22,   31,    6,   29,   34,
 /*    10 */    31,    3,   37,   34,   39,   27,   41,   42,   43,   31,
 /*    20 */    18,   42,   34,   22,   23,   37,   18,   39,   16,   41,
 /*    30 */    42,   43,   29,    3,   31,   32,   33,   34,    7,   29,
 /*    40 */    10,   31,   32,   33,   34,   42,   29,   16,   31,   32,
 /*    50 */    33,   34,   42,    5,   31,   16,    9,   34,    3,   42,
 /*    60 */    13,   38,   39,   15,   31,   42,   43,   34,   18,   22,
 /*    70 */    23,   38,   39,   18,   31,   42,   43,   34,   15,   16,
 /*    80 */    31,   38,   39,   34,   31,   42,   43,   18,   39,   18,
 /*    90 */    41,   42,   43,   31,    9,   42,   34,   44,   45,   31,
 /*   100 */    38,   39,   34,   18,   42,   43,   38,   39,   18,   31,
 /*   110 */    42,   43,   34,   31,    6,   31,   34,   39,   34,   41,
 /*   120 */    42,   43,   38,   39,   42,   31,   42,   43,   34,   31,
 /*   130 */    22,   31,   34,   39,   34,   41,   42,   43,    1,    0,
 /*   140 */    42,    4,   42,   43,   31,    6,    9,   18,   35,   36,
 /*   150 */    13,   12,   31,    4,   31,   34,   17,   34,   19,   22,
 /*   160 */    23,    2,   39,   42,   43,   42,   43,   31,    9,   31,
 /*   170 */    34,   29,   34,   31,   18,   39,   34,   39,   42,   43,
 /*   180 */    42,   43,   31,    1,   42,   34,   31,   20,   21,   34,
 /*   190 */    39,    9,   13,   42,   43,   13,   31,   42,   43,   34,
 /*   200 */     5,   22,   23,   31,   22,   23,   34,   42,   43,   31,
 /*   210 */    15,   31,   34,    2,   42,   43,   31,   15,   16,   34,
 /*   220 */    42,   43,   42,   31,   44,   45,   34,   42,   43,   31,
 /*   230 */     3,    2,   34,   18,   42,   43,   31,   10,    9,   34,
 /*   240 */    42,   43,   13,   31,    4,    3,   34,   42,   43,   30,
 /*   250 */    31,   15,   16,   31,   42,   43,   34,   31,    6,   31,
 /*   260 */    18,   35,   36,   31,   42,   43,   31,   35,   36,   34,
 /*   270 */    42,   13,    9,   45,   22,    2,    7,   42,   13,   10,
 /*   280 */    22,   23,    9,    1,    1,   22,   23,   22,   23,    1,
 /*   290 */     8,    8,    1,    1,    1,    1,    8,    7,   13,    8,
 /*   300 */     8,    8,    8,    7,    2,    5,   16,   10,    8,   30,
 /*   310 */    31,   13,   16,    7,   30,   31,    1,   22,   23,   16,
 /*   320 */    16,   16,   46,   22,   46,   46,   46,   46,   46,   46,
 /*   330 */    31,   46,   46,   46,   46,   46,   46,   46,   31,   31,
 /*   340 */    31,   31,   31,   31,
};
#define YY_SHIFT_USE_DFLT (-18)
#define YY_SHIFT_COUNT (102)
#define YY_SHIFT_MIN   (-17)
#define YY_SHIFT_MAX   (315)
static const short yy_shift_ofst[] = {
 /*     0 */   137,  137,  182,   47,   47,   47,   47,   47,   47,   47,
 /*    10 */    47,    1,    1,    1,   47,   47,   47,   47,  265,  263,
 /*    20 */   258,  179,  295,  295,  295,  295,  295,  295,  295,  295,
 /*    30 */   295,  295,  295,  295,  295,  295,  295,  252,  252,  252,
 /*    40 */   295,  295,  108,  108,  108,  -17,  -17,  301,  301,  301,
 /*    50 */   301,  301,  139,  229,  296,  300,  290,  294,  293,  292,
 /*    60 */   291,  269,  288,  283,  282,  273,  195,  242,   55,   48,
 /*    70 */   167,  227,  159,   31,   30,   85,  236,    8,  202,   63,
 /*    80 */   305,  304,  315,  303,  306,  306,  302,  297,  298,  285,
 /*    90 */   240,  215,  156,  149,  211,  129,   90,   71,   69,   50,
 /*   100 */    39,   12,    2,
};
#define YY_REDUCE_USE_DFLT (-26)
#define YY_REDUCE_COUNT (51)
#define YY_REDUCE_MIN   (-25)
#define YY_REDUCE_MAX   (312)
static const short yy_reduce_ofst[] = {
 /*     0 */   -25,  -12,   94,   84,   78,   68,   62,   49,   43,   33,
 /*    10 */    23,   17,   10,    3,  151,  138,  136,  123,  205,  222,
 /*    20 */   212,  205,  198,  192,  180,  185,  178,  172,  165,  155,
 /*    30 */   121,   53,  142,  100,  -21,  228,  235,  232,  226,  113,
 /*    40 */    98,   82,  284,  279,  219,  312,  311,  310,  309,  308,
 /*    50 */   307,  299,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   181,  180,  220,  223,  223,  223,  223,  223,  223,  223,
 /*    10 */   223,  223,  223,  223,  223,  223,  223,  223,  223,  223,
 /*    20 */   223,  223,  223,  223,  223,  223,  223,  223,  223,  223,
 /*    30 */   223,  223,  223,  223,  223,  223,  223,  223,  223,  223,
 /*    40 */   223,  223,  223,  223,  223,  223,  223,  223,  223,  223,
 /*    50 */   223,  223,  223,  219,  223,  223,  223,  223,  213,  215,
 /*    60 */   214,  223,  223,  185,  223,  219,  223,  223,  223,  223,
 /*    70 */   223,  223,  219,  223,  223,  174,  223,  223,  223,  223,
 /*    80 */   196,  194,  223,  191,  187,  183,  223,  223,  223,  223,
 /*    90 */   223,  223,  223,  223,  202,  223,  223,  173,  223,  223,
 /*   100 */   223,  217,  223,  179,  177,  216,  212,  189,  186,  184,
 /*   110 */   192,  191,  188,  193,  200,  198,  197,  199,  205,  210,
 /*   120 */   211,  209,  207,  208,  206,  203,  204,  201,  196,  195,
 /*   130 */   194,  190,  182,  178,  176,  170,  175,  217,  172,  171,
 /*   140 */   169,  168,  164,  167,  222,  220,  219,  218,  166,  165,
 /*   150 */   163,  162,  161,  221,  160,  159,  158,
};

/* The next table maps tokens into fallback tokens.  If a construct
** like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
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
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number */
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
  "COUNT",         "SUM",           "STRING",        "NUMBER",      
  "error",         "start",         "prog",          "predicate",   
  "decl",          "variables",     "sortdecl",      "string",      
  "objectdecl",    "object",        "variable",      "constantdecl",
  "constant",      "rule",          "body",          "bodydef",     
  "bodydef2",      "head",          "number",        "literal",     
  "aggregateCum",  "aggregate",   
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
 /*  10 */ "object ::= variable DOT DOT variable COLON COLON string",
 /*  11 */ "prog ::= prog CONSTANTS constantdecl",
 /*  12 */ "constantdecl ::= constant SEMI_COLON constantdecl",
 /*  13 */ "constantdecl ::= constant DOT",
 /*  14 */ "constantdecl ::= NEWLINE constantdecl",
 /*  15 */ "constant ::= string LBRACKET variables RBRACKET COLON COLON string",
 /*  16 */ "constant ::= string LBRACKET variables RBRACKET",
 /*  17 */ "constant ::= string",
 /*  18 */ "constant ::= string COLON COLON string",
 /*  19 */ "prog ::= prog NEWLINE predicate",
 /*  20 */ "prog ::= predicate",
 /*  21 */ "prog ::= prog NEWLINE rule",
 /*  22 */ "prog ::= rule",
 /*  23 */ "prog ::= prog NEWLINE",
 /*  24 */ "prog ::=",
 /*  25 */ "rule ::= REVERSE_IMPLICATION body DOT",
 /*  26 */ "rule ::= number REVERSE_IMPLICATION body",
 /*  27 */ "rule ::= head DISJUNCTION bodydef DOT",
 /*  28 */ "rule ::= number head DISJUNCTION bodydef",
 /*  29 */ "rule ::= head REVERSE_IMPLICATION body DOT",
 /*  30 */ "rule ::= number head REVERSE_IMPLICATION body",
 /*  31 */ "rule ::= number NEGATION NEGATION LBRACKET head REVERSE_IMPLICATION body RBRACKET",
 /*  32 */ "rule ::= LPAREN head RPAREN REVERSE_IMPLICATION body DOT",
 /*  33 */ "body ::= body CONJUNCTION bodydef",
 /*  34 */ "head ::= head DISJUNCTION bodydef",
 /*  35 */ "head ::= bodydef",
 /*  36 */ "body ::= bodydef",
 /*  37 */ "bodydef ::= literal",
 /*  38 */ "bodydef ::= NEGATION literal",
 /*  39 */ "bodydef ::= NEGATION NEGATION literal",
 /*  40 */ "bodydef ::= LBRACKET NEGATION NEGATION literal RBRACKET",
 /*  41 */ "bodydef ::= string EQUAL string",
 /*  42 */ "bodydef ::= NEGATION string EQUAL string",
 /*  43 */ "bodydef ::= string NEGATION EQUAL string",
 /*  44 */ "literal ::= string LBRACKET variables RBRACKET EQUAL variable",
 /*  45 */ "literal ::= string LBRACKET variables RBRACKET",
 /*  46 */ "literal ::= variable",
 /*  47 */ "literal ::= string EQUAL COUNT LPAREN aggregateCum RPAREN",
 /*  48 */ "literal ::= string EQUAL SUM LPAREN aggregateCum RPAREN",
 /*  49 */ "aggregate ::= string COLON literal",
 /*  50 */ "aggregate ::= number COLON literal",
 /*  51 */ "aggregate ::= string COMMA literal COLON literal",
 /*  52 */ "aggregate ::= number COMMA literal COLON literal",
 /*  53 */ "aggregateCum ::= aggregate",
 /*  54 */ "aggregateCum ::= aggregateCum SEMI_COLON aggregate",
 /*  55 */ "predicate ::= literal DOT",
 /*  56 */ "predicate ::= number literal",
 /*  57 */ "predicate ::= number NEGATION NEGATION literal",
 /*  58 */ "predicate ::= number NEGATION literal",
 /*  59 */ "predicate ::= NEGATION NEGATION literal DOT",
 /*  60 */ "variables ::= variable",
 /*  61 */ "variables ::= variables COMMA variable",
 /*  62 */ "variable ::= string",
 /*  63 */ "variable ::= number",
 /*  64 */ "string ::= STRING",
 /*  65 */ "number ::= NUMBER",
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
void *MVSMParserGrammarAlloc(void *(*mallocProc)(size_t)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (size_t)sizeof(yyParser) );
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

/* The following function deletes the value associated with a
** symbol.  The symbol can be either a terminal or nonterminal.
** "yymajor" is the symbol code, and "yypminor" is a pointer to
** the value.
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
    ** which appear on the RHS of the rule, but which are not used
    ** inside the C code.
    */
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
**
** Return the major token number for the symbol popped.
*/
static int yy_pop_parser_stack(yyParser *pParser){
  YYCODETYPE yymajor;
  yyStackEntry *yytos = &pParser->yystack[pParser->yyidx];

  if( pParser->yyidx<0 ) return 0;
#ifndef NDEBUG
  if( yyTraceFILE && pParser->yyidx>=0 ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yymajor = yytos->major;
  yy_destructor(pParser, yymajor, &yytos->minor);
  pParser->yyidx--;
  return yymajor;
}

/* 
** Deallocate and destroy a parser.  Destructors are all called for
** all stack elements before shutting the parser down.
**
** Inputs:
** <ul>
** <li>  A pointer to the parser.  This should be a pointer
**       obtained from MVSMParserGrammarAlloc.
** <li>  A pointer to a function used to reclaim memory obtained
**       from malloc.
** </ul>
*/
void MVSMParserGrammarFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
  if( pParser==0 ) return;
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
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yystack[pParser->yyidx].stateno;
 
  if( stateno>YY_SHIFT_COUNT
   || (i = yy_shift_ofst[stateno])==YY_SHIFT_USE_DFLT ){
    return yy_default[stateno];
  }
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
        return yy_find_shift_action(pParser, iFallback);
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
               yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[YYWILDCARD]);
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
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
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
   MVSMParserGrammarARG_STORE; /* Suppress warning about unused %extra_argument var */
}

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
#ifndef NDEBUG
  if( yyTraceFILE && yypParser->yyidx>0 ){
    int i;
    fprintf(yyTraceFILE,"%sShift %d\n",yyTracePrompt,yyNewState);
    fprintf(yyTraceFILE,"%sStack:",yyTracePrompt);
    for(i=1; i<=yypParser->yyidx; i++)
      fprintf(yyTraceFILE," %s",yyTokenName[yypParser->yystack[i].major]);
    fprintf(yyTraceFILE,"\n");
  }
#endif
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 25, 1 },
  { 26, 3 },
  { 30, 3 },
  { 30, 2 },
  { 30, 2 },
  { 26, 3 },
  { 32, 3 },
  { 32, 2 },
  { 32, 2 },
  { 33, 4 },
  { 33, 7 },
  { 26, 3 },
  { 35, 3 },
  { 35, 2 },
  { 35, 2 },
  { 36, 7 },
  { 36, 4 },
  { 36, 1 },
  { 36, 4 },
  { 26, 3 },
  { 26, 1 },
  { 26, 3 },
  { 26, 1 },
  { 26, 2 },
  { 26, 0 },
  { 37, 3 },
  { 37, 3 },
  { 37, 4 },
  { 37, 4 },
  { 37, 4 },
  { 37, 4 },
  { 37, 8 },
  { 37, 6 },
  { 38, 3 },
  { 41, 3 },
  { 41, 1 },
  { 38, 1 },
  { 39, 1 },
  { 39, 2 },
  { 39, 3 },
  { 39, 5 },
  { 39, 3 },
  { 39, 4 },
  { 39, 4 },
  { 43, 6 },
  { 43, 4 },
  { 43, 1 },
  { 43, 6 },
  { 43, 6 },
  { 45, 3 },
  { 45, 3 },
  { 45, 5 },
  { 45, 5 },
  { 44, 1 },
  { 44, 3 },
  { 27, 2 },
  { 27, 2 },
  { 27, 4 },
  { 27, 3 },
  { 27, 4 },
  { 29, 1 },
  { 29, 3 },
  { 34, 1 },
  { 34, 1 },
  { 31, 1 },
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
    fprintf(yyTraceFILE, "%sReduce [%s].\n", yyTracePrompt,
      yyRuleName[yyruleno]);
  }
#endif /* NDEBUG */

  /* Silence complaints from purify about yygotominor being uninitialized
  ** in some cases when it is copied into the stack after the following
  ** switch.  yygotominor is uninitialized when a rule reduces that does
  ** not set the value of its left-hand side nonterminal.  Leaving the
  ** value of the nonterminal uninitialized is utterly harmless as long
  ** as the value is never used.  So really the only thing this code
  ** accomplishes is to quieten purify.  
  **
  ** 2007-01-16:  The wireshark project (www.wireshark.org) reports that
  ** without this code, their parser segfaults.  I'm not sure what there
  ** parser is doing to make this happen.  This is the second bug report
  ** from wireshark this week.  Clearly they are stressing Lemon in ways
  ** that it has not been previously stressed...  (SQLite ticket #2172)
  */
  /*memset(&yygotominor, 0, sizeof(yygotominor));*/
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
      case 2: /* sortdecl ::= string SEMI_COLON sortdecl */
#line 121 "MVSMParserGrammar.y"
{
	std::string str = yymsp[-2].minor.yy0->toString();
	auto it = tree->domainNamesList.find(str);
	if(it != tree->domainNamesList.end())
		throw syntax_exception("Redeclaration of sort "+yymsp[-2].minor.yy0->toString()+"\n");
	else
		tree->domainNamesList.insert(yymsp[-2].minor.yy0->toString());
}
#line 969 "MVSMParserGrammar.c"
        break;
      case 4: /* sortdecl ::= string DOT */
#line 132 "MVSMParserGrammar.y"
{
	std::string str = yymsp[-1].minor.yy0->toString();
	auto it = tree->domainNamesList.find(str);
	if(it != tree->domainNamesList.end())
		throw syntax_exception("Redeclaration of sort "+yymsp[-1].minor.yy0->toString()+"\n");
	else
		tree->domainNamesList.insert(str);	
}
#line 981 "MVSMParserGrammar.c"
        break;
      case 9: /* object ::= variables COLON COLON string */
#line 149 "MVSMParserGrammar.y"
{
	// if(tree->cdp == Tree::Current_Decl_Part::DECL_OBJECTS){
		auto itr = tree->domainNamesList.find(yymsp[0].minor.yy0->toString());
		if(itr != tree->domainNamesList.end()){
			Domain* d  = new Domain(yymsp[0].minor.yy0->toString());
			d->setVars(*yymsp[-3].minor.yy7);
			tree->domains.insert(*d);
			for(auto& v : d->getVars()){
				tree->domainList.insert(v);	
			}

			if(tree->outputType != OutputType::OUTPUT_ASP){
				cout<<d->toString(false);
			}
			else{
				cout<<d->toString(false);	
			}
			delete d;
		}
		else{
			throw syntax_exception("Domain " + yymsp[0].minor.yy0->toString() +" not declared.\n");
		}
	
	delete yymsp[-3].minor.yy7;
}
#line 1010 "MVSMParserGrammar.c"
        break;
      case 10: /* object ::= variable DOT DOT variable COLON COLON string */
#line 175 "MVSMParserGrammar.y"
{
	auto itr = tree->domainNamesList.find(yymsp[0].minor.yy0->toString());
	if(itr != tree->domainNamesList.end()){
		Domain* d  = new Domain(yymsp[0].minor.yy0->toString());

		int start = stoi(*(yymsp[-6].minor.yy0->token));
		int end = stoi(*(yymsp[-3].minor.yy0->token));

		for(int i=start; i<=end ;i++){
			d->addVars(to_string(i));
			tree->domainList.insert(to_string(i));
		}

		cout<<d->toString(false);
		delete d;
	}
	else{
		throw syntax_exception("Domain " + yymsp[0].minor.yy0->toString() +" not declared.\n");
	}
	
	// delete Ve;
}
#line 1036 "MVSMParserGrammar.c"
        break;
      case 15: /* constant ::= string LBRACKET variables RBRACKET COLON COLON string */
#line 206 "MVSMParserGrammar.y"
{
	Variable* va = new Variable;
	std::map<int, Domain> posMap;
	std::set<Domain>::iterator itr;
	int i=0;
	for(auto& v : *yymsp[-4].minor.yy7){
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
	delete yymsp[-4].minor.yy7;
}
#line 1079 "MVSMParserGrammar.c"
        break;
      case 16: /* constant ::= string LBRACKET variables RBRACKET */
#line 246 "MVSMParserGrammar.y"
{
	Variable* va = new Variable;
	std::map<int, Domain> posMap;
	std::set<Domain>::iterator itr;
	int i=0;
	for(auto& v : *yymsp[-1].minor.yy7){
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
	delete yymsp[-1].minor.yy7;
	delete va;
}
#line 1108 "MVSMParserGrammar.c"
        break;
      case 17: /* constant ::= string */
#line 272 "MVSMParserGrammar.y"
{
	Variable* va = new Variable;
	va->setVar(yymsp[0].minor.yy0->toString());
	tree->variables.insert(*va);
	/*for ASP output we do not print constants */
	if(tree->outputType != OutputType::OUTPUT_ASP)
		cout<<va->toString()<<"\n";
	
	delete va;	
}
#line 1122 "MVSMParserGrammar.c"
        break;
      case 18: /* constant ::= string COLON COLON string */
#line 283 "MVSMParserGrammar.y"
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
#line 1151 "MVSMParserGrammar.c"
        break;
      case 19: /* prog ::= prog NEWLINE predicate */
#line 310 "MVSMParserGrammar.y"
{ 
	if(yymsp[0].minor.yy16->needsToBeCompleted()){	
		FactCompletion f(*yymsp[0].minor.yy16);
		tree->facts.insert(std::pair<std::string,FactCompletion>(f.getHead().getVar(),f)); 
	}

			
	delete yymsp[0].minor.yy16;
}
#line 1164 "MVSMParserGrammar.c"
        break;
      case 20: /* prog ::= predicate */
#line 320 "MVSMParserGrammar.y"
{ 
	if(yymsp[0].minor.yy16->needsToBeCompleted()){
		FactCompletion f(*yymsp[0].minor.yy16);
		tree->facts.insert(std::pair<std::string,FactCompletion>(f.getHead().getVar(),f)); 	
	}
	delete yymsp[0].minor.yy16;
}
#line 1175 "MVSMParserGrammar.c"
        break;
      case 21: /* prog ::= prog NEWLINE rule */
      case 22: /* prog ::= rule */ yytestcase(yyruleno==22);
#line 328 "MVSMParserGrammar.y"
{
	if((yymsp[0].minor.yy57->isHeadTop == false) && (yymsp[0].minor.yy57->toBeCompleted == true))
		tree->rules.insert(std::pair<std::string,RuleCompletion>(yymsp[0].minor.yy57->getHead().getVar(),*yymsp[0].minor.yy57));
	delete yymsp[0].minor.yy57;
}
#line 1185 "MVSMParserGrammar.c"
        break;
      case 25: /* rule ::= REVERSE_IMPLICATION body DOT */
#line 361 "MVSMParserGrammar.y"
{
	yygotominor.yy57 = new RuleCompletion;
	yygotominor.yy57->isHeadTop = true;
	
	if(tree->outputType != OutputType::OUTPUT_ASP){
		std::cout<<"("
					<<yymsp[-1].minor.yy21->toNNFString()
					<<")"
					<<LanguageConstants::LINE_END
					<<"\n";
	}
	else{
		std::cout<<LanguageConstants::IMPL
				<<yymsp[-1].minor.yy21->toString()
				<<LanguageConstants::LINE_END
				<<"\n";
	}
	delete yymsp[-1].minor.yy21;
}
#line 1208 "MVSMParserGrammar.c"
        break;
      case 26: /* rule ::= number REVERSE_IMPLICATION body */
#line 382 "MVSMParserGrammar.y"
{
	yygotominor.yy57 = new RuleCompletion;
	yygotominor.yy57->isHeadTop = true;
	
	if(tree->outputType != OutputType::OUTPUT_ASP){
		std::cout<<yymsp[-2].minor.yy0->toString()<<SPACE
					<<"("
					<<yymsp[0].minor.yy21->toNNFString()
					<<")"
					<<"\n";
	}
	else{
		std::string extra = yymsp[0].minor.yy21->getExtra(tree->variables);
		if(extra.length() != 0){
			extra = "," + extra; 
		}
		std::string str = ":~"
				+ yymsp[0].minor.yy21->toString()
				+ extra 
				+ LanguageConstants::LINE_END
				+ " "
				+ "["
				+  std::to_string((int)(std::stof(yymsp[-2].minor.yy0->toString())* 1))
				+  ","
				+  std::to_string(tree->weak_constraint_counter);

		std::string temp = yymsp[0].minor.yy21->getExtraConstants();
		if(temp.length() > 0){
			str += ","
				+ temp;
		}
				
		str += std::string("]") + std::string("\n");

		cout << str;
		tree->weak_constraint_counter++;
	
	}
	// std::cout<<yymsp[-2].minor.yy0->toString()<<SPACE<<"("<<yymsp[0].minor.yy21->toNNFString()<<")"<<"\n";
	delete yymsp[0].minor.yy21;
}
#line 1253 "MVSMParserGrammar.c"
        break;
      case 27: /* rule ::= head DISJUNCTION bodydef DOT */
#line 427 "MVSMParserGrammar.y"
{
	yygotominor.yy57 = new RuleCompletion;
	yygotominor.yy57->isHeadTop = true;
	yymsp[-3].minor.yy77->addPredicate(yymsp[-1].minor.yy92->getPredicate());
	// RULE_COMPLETION_HEAD_DIS_BODY_TOP(yymsp[-3].minor.yy77,yymsp[-1].minor.yy92)
	try{
		RuleCompletion_HD_BT(yymsp[-3].minor.yy77,tree);
	}
	catch(const std::out_of_range& e){
		throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}
	
	yymsp[-3].minor.yy77->appendStr(yymsp[-1].minor.yy92->getPredicate().toString(tree->domainList),false,true,false);
	
	std::string temp;
	if(tree->outputType == OutputType::OUTPUT_ASP){
		temp = yymsp[-3].minor.yy77->getExtra(tree->variables);
		if(temp.length() > 0){
			temp = yymsp[-3].minor.yy77->toString() + ":-" + temp;
		}
		else{
			temp = yymsp[-3].minor.yy77->toString();
		}
		std::cout<<temp<<"."<<"\n";
	}
	else{
		std::cout<<yymsp[-3].minor.yy77->toString()<<".\n";	
	}
	
	
	
	delete yymsp[-3].minor.yy77;
	delete yymsp[-1].minor.yy92;
}
#line 1291 "MVSMParserGrammar.c"
        break;
      case 28: /* rule ::= number head DISJUNCTION bodydef */
#line 465 "MVSMParserGrammar.y"
{
	//Doing this 
	yygotominor.yy57 = new RuleCompletion;
	yygotominor.yy57->isHeadTop = true;
	yymsp[-2].minor.yy77->addPredicate(yymsp[0].minor.yy92->getPredicate());
	// RULE_COMPLETION_HEAD_DIS_BODY_TOP(yymsp[-2].minor.yy77,yymsp[0].minor.yy92)
	try{
		RuleCompletion_HD_BT(yymsp[-2].minor.yy77,tree);
	}
	catch(const std::out_of_range& e){
		throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}

	if(tree->outputType == OutputType::OUTPUT_ASP){
		std::set<std::string> uniqueSet = tree->findVariables(yymsp[-2].minor.yy77->toNNFString(tree->domainList));
		std::string uniqueSetStr;
		for(auto itr = uniqueSet.begin(); itr != uniqueSet.end(); ++itr){
			uniqueSetStr += *itr + ",";
		}
		if (uniqueSetStr.length() > 0)
		{
			uniqueSetStr.pop_back();
			uniqueSetStr = "," + uniqueSetStr; 
		}
		string unsatString = "unsat(" + std::to_string(tree->weak_constraint_counter) + ",0," + std::to_string((int)(std::stof(yymsp[-3].minor.yy0->toString())* 1)) + uniqueSetStr + ")";
		std::cout << unsatString 
				<< " :- "
				<<yymsp[-2].minor.yy77->toNNFString(tree->domainList)
				<<".\n";
		std::cout << yymsp[-2].minor.yy77->toString(tree->domainList)
					<< " :- "
					<< "not "
					<< unsatString
					<< ".\n";

		std::cout   << " :~ "
					<< unsatString
					<< ". "
					<< "["
					<< std::to_string((int)(std::stof(yymsp[-3].minor.yy0->toString())* 1))
					<<","
					<< tree->weak_constraint_counter
					<< uniqueSetStr
					<< "]"
					<<"\n";
	}
	else{
		yymsp[-2].minor.yy77->appendStr(yymsp[0].minor.yy92->getPredicate().toString(tree->domainList),false,true,false);	
		std::cout<<yymsp[-3].minor.yy0->toString()<<SPACE<<yymsp[-2].minor.yy77->toString()<<"\n";
	}
	
	delete yymsp[-2].minor.yy77;
	delete yymsp[0].minor.yy92;
}
#line 1349 "MVSMParserGrammar.c"
        break;
      case 29: /* rule ::= head REVERSE_IMPLICATION body DOT */
#line 525 "MVSMParserGrammar.y"
{
	yygotominor.yy57 = new RuleCompletion;

	if (yymsp[-3].minor.yy77->getDisjunction()){
		// RULE_COMPLETION_HEAD_DIS_BODY_TOP(yymsp[-3].minor.yy77,yymsp[-1].minor.yy21)
		yygotominor.yy57->isHeadTop = true;
		RuleCompletion_HD_BC(yymsp[-3].minor.yy77,yymsp[-1].minor.yy21,true,tree);
		if(tree->outputType == OutputType::OUTPUT_ALCHEMY)
			std::cout<<yymsp[-1].minor.yy21->toString()
					<<" => "
					<<yymsp[-3].minor.yy77->toString()
					<<LanguageConstants::LINE_END
					<<"\n";
		if(tree->outputType == OutputType::OUTPUT_ASP)
			tree->printASPRuleHB(yymsp[-3].minor.yy77,yymsp[-1].minor.yy21);
	}
	else{
		// RULE_COMPLETION_BH(yymsp[-1].minor.yy21,yymsp[-3].minor.yy77);
		// yygotominor.yy57 = new RuleCompletion(yymsp[-3].minor.yy77->getPredicate(),predList, resultMap, varMap);
		try{
			yygotominor.yy57 = RuleCompletion_BH(yymsp[-1].minor.yy21,yymsp[-3].minor.yy77,tree);
		}
		catch(const std::out_of_range& e){
			throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
		}
		if(tree->outputType == OutputType::OUTPUT_ALCHEMY)
			std::cout<<yymsp[-1].minor.yy21->toString()
					<<" => "
					<<yymsp[-3].minor.yy77->toString()
					<<LanguageConstants::LINE_END
					<<"\n";
		if(tree->outputType == OutputType::OUTPUT_ASP)
			tree->printASPRuleHB(yymsp[-3].minor.yy77,yymsp[-1].minor.yy21);
	}
	delete yymsp[-1].minor.yy21;
	delete yymsp[-3].minor.yy77;
}
#line 1390 "MVSMParserGrammar.c"
        break;
      case 30: /* rule ::= number head REVERSE_IMPLICATION body */
#line 566 "MVSMParserGrammar.y"
{
	// RULE_COMPLETION_BH(yymsp[0].minor.yy21,yymsp[-2].minor.yy77);
	// yygotominor.yy57 = new RuleCompletion(yymsp[-2].minor.yy77->getPredicate(),predList, resultMap, varMap);
	try{
		yygotominor.yy57 = RuleCompletion_BH(yymsp[0].minor.yy21,yymsp[-2].minor.yy77,tree);
	}
	catch(const std::out_of_range& e){
			throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY)
		std::cout<< yymsp[-3].minor.yy0->toString()
				<<SPACE
				<<yymsp[0].minor.yy21->toString()
				<<" => "
				<<yymsp[-2].minor.yy77->toString()
				<<"\n";
	
	if(tree->outputType == OutputType::OUTPUT_ASP){
		std::set<std::string> uniqueSet = tree->findFreeVariables(yymsp[-2].minor.yy77->toNNFString(tree->domainList),yymsp[0].minor.yy21->toString());
		std::string uniqueSetStr;
		for(auto itr = uniqueSet.begin(); itr != uniqueSet.end(); ++itr){
			uniqueSetStr += *itr + ",";
		}
		if (uniqueSetStr.length() > 0)
		{
			uniqueSetStr.pop_back();
			uniqueSetStr = "," + uniqueSetStr; 
		}
		string unsatString = "unsat(" + std::to_string(tree->weak_constraint_counter) + ",0," + std::to_string((int)(std::stof(yymsp[-3].minor.yy0->toString())* 1)) + uniqueSetStr + ")";
		std::cout << unsatString
					<< " :- "
					<< yymsp[0].minor.yy21->toString()
					<< " , "
					/*Change this to NNF String*/
					<< yymsp[-2].minor.yy77->toNNFString(tree->domainList)
					<<LanguageConstants::LINE_END
					<<"\n"; 

		std::cout << yymsp[-2].minor.yy77->toString()
					<< " :- "
					<< yymsp[0].minor.yy21->toString()
					<< " , "
					<< "not "
					<< unsatString
					<<LanguageConstants::LINE_END
					<<"\n"; 

	
		std::cout   << " :~ "
					<< unsatString
					<< ". "
					<< "["
					<< std::to_string((int)(std::stof(yymsp[-3].minor.yy0->toString())* 1))
					<< "@0"
					<<","
					<< tree->weak_constraint_counter
					<< uniqueSetStr
					<< "]"
					<<"\n";

		tree->weak_constraint_counter++; 


	}


	delete yymsp[0].minor.yy21;
	delete yymsp[-2].minor.yy77;
}
#line 1464 "MVSMParserGrammar.c"
        break;
      case 31: /* rule ::= number NEGATION NEGATION LBRACKET head REVERSE_IMPLICATION body RBRACKET */
#line 640 "MVSMParserGrammar.y"
{
	yygotominor.yy57 = new RuleCompletion;
	yygotominor.yy57->isHeadTop = true;	
	tree->statHasDblNeg = true;

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY)
		std::cout<< yymsp[-7].minor.yy0->toString() 
				<< SPACE 
				<<"!!("
				<<yymsp[-1].minor.yy21->toString()
				<<" => "
				<<yymsp[-3].minor.yy77->toString()
				<<"\n"; 
	if(tree->outputType == OutputType::OUTPUT_ASP)
		std::cout<< yymsp[-7].minor.yy0->toString() 
				<< SPACE 
				<<yymsp[-3].minor.yy77->toString()
				<<" :- "
				<<yymsp[-1].minor.yy21->toString()
				<<LanguageConstants::LINE_END
				<<"\n"; 
	
	delete yymsp[-1].minor.yy21;
	delete yymsp[-3].minor.yy77;
}
#line 1493 "MVSMParserGrammar.c"
        break;
      case 32: /* rule ::= LPAREN head RPAREN REVERSE_IMPLICATION body DOT */
#line 666 "MVSMParserGrammar.y"
{
	
	if (yymsp[-4].minor.yy77->getPredicate().checkEquality() != 0){
		throw syntax_exception("Cannot have equality/Inequlity as a part of choice rule\n");
	}

	// RULE_COMPLETION_BH(yymsp[-1].minor.yy21,yymsp[-4].minor.yy77);
	// yygotominor.yy57 = new RuleCompletion(yymsp[-4].minor.yy77->getPredicate(),predList, resultMap, varMap);
	try{
		yygotominor.yy57 = RuleCompletion_BH(yymsp[-1].minor.yy21,yymsp[-4].minor.yy77,tree);
	}
	catch(const std::out_of_range& e){
			throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY)
		std::cout<<COMMENT<<yymsp[-1].minor.yy21->toString()<<" => "<<yymsp[-4].minor.yy77->toString()<<"\n";
	if(tree->outputType == OutputType::OUTPUT_ASP)
		std::cout<<yymsp[-4].minor.yy77->toString()<<" :- "<<yymsp[-1].minor.yy21->toString()<<LanguageConstants::LINE_END<<"\n";
	delete yymsp[-1].minor.yy21;
	delete yymsp[-4].minor.yy77;
}
#line 1519 "MVSMParserGrammar.c"
        break;
      case 33: /* body ::= body CONJUNCTION bodydef */
#line 690 "MVSMParserGrammar.y"
{
	yygotominor.yy21 = yymsp[-2].minor.yy21;
	yymsp[-2].minor.yy21->addPredicate(yymsp[0].minor.yy92->getPredicate());
	yygotominor.yy21->appendStr(yymsp[0].minor.yy92->getPredicate(),false,false,true,tree->domainList);
	delete yymsp[0].minor.yy92;
}
#line 1529 "MVSMParserGrammar.c"
        break;
      case 34: /* head ::= head DISJUNCTION bodydef */
#line 697 "MVSMParserGrammar.y"
{
	yygotominor.yy77 = yymsp[-2].minor.yy77;
	yymsp[-2].minor.yy77->addPredicate(yymsp[0].minor.yy92->getPredicate());
	yygotominor.yy77->appendStr(yymsp[0].minor.yy92->getPredicate().toString(tree->domainList),false,true,false);
	yygotominor.yy77->setDisjunction(true);
	delete yymsp[0].minor.yy92;
}
#line 1540 "MVSMParserGrammar.c"
        break;
      case 35: /* head ::= bodydef */
#line 705 "MVSMParserGrammar.y"
{
	yygotominor.yy77 = new Head(yymsp[0].minor.yy92->getPredicate());
	// yygotominor.yy77->addPredicate(yymsp[0].minor.yy92->getPredicate());
	yygotominor.yy77->appendStr(yymsp[0].minor.yy92->getPredicate().toString(tree->domainList),false,false,false);
	delete yymsp[0].minor.yy92;
}
#line 1550 "MVSMParserGrammar.c"
        break;
      case 36: /* body ::= bodydef */
#line 712 "MVSMParserGrammar.y"
{
	yygotominor.yy21 = new Body;
	Predicate p = yymsp[0].minor.yy92->getPredicate();
	yygotominor.yy21->addPredicate(p);
	yygotominor.yy21->appendStr(p,false,false,false,tree->domainList);
	delete yymsp[0].minor.yy92;
}
#line 1561 "MVSMParserGrammar.c"
        break;
      case 37: /* bodydef ::= literal */
#line 723 "MVSMParserGrammar.y"
{	
	yygotominor.yy92 = yymsp[0].minor.yy92;
}
#line 1568 "MVSMParserGrammar.c"
        break;
      case 38: /* bodydef ::= NEGATION literal */
#line 728 "MVSMParserGrammar.y"
{	
	yygotominor.yy92 = yymsp[0].minor.yy92;
	Predicate p = yygotominor.yy92->getPredicate();
	p.setSingleNegation(true);
	yygotominor.yy92->addPredicate(p);
	// yygotominor.yy92->getPredicate().setSingleNegation(true);
}
#line 1579 "MVSMParserGrammar.c"
        break;
      case 39: /* bodydef ::= NEGATION NEGATION literal */
#line 737 "MVSMParserGrammar.y"
{	
	yygotominor.yy92 = yymsp[0].minor.yy92;
	tree->statHasDblNeg = true;
	yygotominor.yy92->getPredicate().setDoubleNegation(true);
}
#line 1588 "MVSMParserGrammar.c"
        break;
      case 40: /* bodydef ::= LBRACKET NEGATION NEGATION literal RBRACKET */
#line 746 "MVSMParserGrammar.y"
{	
	yygotominor.yy92 = yymsp[-1].minor.yy92;
	tree->statHasDblNeg = true;
	yygotominor.yy92->getPredicate().setDoubleNegation(true);
}
#line 1597 "MVSMParserGrammar.c"
        break;
      case 41: /* bodydef ::= string EQUAL string */
#line 753 "MVSMParserGrammar.y"
{
	yygotominor.yy92 = new BodyDef;
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
		yygotominor.yy92->addPredicate(p);
		unsigned int expectedArgs = (tree->variables.find(*(yymsp[-2].minor.yy0->token)))->getSize();
		if (expectedArgs != vars.size()){
			delete yygotominor.yy92;
			throw invalid_arguments(expectedArgs, vars.size(), *(yymsp[-2].minor.yy0->token));
		}
	}
	
	else{
		Predicate p(yymsp[-2].minor.yy0->token,yymsp[0].minor.yy0->token);
		p.setEquality();
		yygotominor.yy92->addPredicate(p);
	}
}
#line 1632 "MVSMParserGrammar.c"
        break;
      case 42: /* bodydef ::= NEGATION string EQUAL string */
#line 786 "MVSMParserGrammar.y"
{
	std::vector<std::string> vars;
	vars.push_back(yymsp[0].minor.yy0->toString());
	Predicate p(yymsp[-2].minor.yy0->token);
	p.setTokens(vars, tree->domainList);
	p.setSingleNegation(true);
	yygotominor.yy92 = new BodyDef;
	yygotominor.yy92->addPredicate(p);
	// delete Ve;
	unsigned int expectedArgs = (tree->variables.find(*(yymsp[-2].minor.yy0->token)))->getSize();
	if (expectedArgs != vars.size()){
		delete yygotominor.yy92;
		throw invalid_arguments(expectedArgs, vars.size(), *(yymsp[-2].minor.yy0->token));
	}
}
#line 1651 "MVSMParserGrammar.c"
        break;
      case 43: /* bodydef ::= string NEGATION EQUAL string */
#line 802 "MVSMParserGrammar.y"
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
	yygotominor.yy92 = new BodyDef;
	yygotominor.yy92->addPredicate(p);
}
#line 1670 "MVSMParserGrammar.c"
        break;
      case 44: /* literal ::= string LBRACKET variables RBRACKET EQUAL variable */
#line 821 "MVSMParserGrammar.y"
{
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-3].minor.yy7)
		vars.push_back(*v);
	vars.push_back(*(yymsp[0].minor.yy0->token));
	Predicate p(yymsp[-5].minor.yy0->token);
	p.setTokens(vars, tree->domainList);
	yygotominor.yy92 = new BodyDef;
	yygotominor.yy92->addPredicate(p);
	auto itr = tree->variables.find(yymsp[-5].minor.yy0->toString());
	if(itr == tree->variables.end()){
		delete yygotominor.yy92;
		throw syntax_exception("Literal "+ yymsp[-5].minor.yy0->toString() + " not found.\n");
	}
	delete yymsp[-3].minor.yy7;
	unsigned int expectedArgs = (tree->variables.find(yymsp[-5].minor.yy0->toString()))->getSize();
	if (expectedArgs != vars.size()){
		delete yygotominor.yy92;
		throw invalid_arguments(expectedArgs, vars.size(), *(yymsp[-5].minor.yy0->token));
	}
}
#line 1695 "MVSMParserGrammar.c"
        break;
      case 45: /* literal ::= string LBRACKET variables RBRACKET */
#line 843 "MVSMParserGrammar.y"
{
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-1].minor.yy7)
		vars.push_back(*v);
	Predicate p(yymsp[-3].minor.yy0->token);
	p.setTokens(vars, tree->domainList);
	yygotominor.yy92 = new BodyDef;
	yygotominor.yy92->addPredicate(p);
	delete yymsp[-1].minor.yy7;
	auto itr = tree->variables.find(yymsp[-3].minor.yy0->toString());
	if(itr == tree->variables.end()){
		delete yygotominor.yy92;
		throw syntax_exception("Literal "+ yymsp[-3].minor.yy0->toString() + " not found.\n");
	}
	unsigned int expectedArgs = itr->getSize();
	if (expectedArgs != vars.size()){
		delete yygotominor.yy92;
		throw invalid_arguments(expectedArgs, vars.size(), *(yymsp[-3].minor.yy0->token));
	}	
}
#line 1719 "MVSMParserGrammar.c"
        break;
      case 46: /* literal ::= variable */
#line 864 "MVSMParserGrammar.y"
{
	Predicate p(yymsp[0].minor.yy0->token);
	auto itr = tree->variables.find(yymsp[0].minor.yy0->toString());
	yygotominor.yy92 = new BodyDef;
	/*Special Case: BodyDef does not have variables*/
	yygotominor.yy92->setHasVariables();
	yygotominor.yy92->addPredicate(p);
}
#line 1731 "MVSMParserGrammar.c"
        break;
      case 47: /* literal ::= string EQUAL COUNT LPAREN aggregateCum RPAREN */
#line 873 "MVSMParserGrammar.y"
{
	std::string s = (*yymsp[-5].minor.yy0).toString();
	Util::toUpper(s);
	s = s + "= #count{" + yymsp[-1].minor.yy0->toString() + "}";
	Predicate p(yymsp[-5].minor.yy0->token);
	p.setString(s);
	yygotominor.yy92 = new BodyDef;
	yygotominor.yy92->addPredicate(p);
	delete yymsp[-1].minor.yy0;
}
#line 1745 "MVSMParserGrammar.c"
        break;
      case 48: /* literal ::= string EQUAL SUM LPAREN aggregateCum RPAREN */
#line 884 "MVSMParserGrammar.y"
{
	std::string s = (*yymsp[-5].minor.yy0).toString();
	Util::toUpper(s);
	s = s + "= #sum{" + yymsp[-1].minor.yy0->toString() + "}";
	Predicate p(yymsp[-5].minor.yy0->token);
	p.setString(s);
	yygotominor.yy92 = new BodyDef;
	yygotominor.yy92->addPredicate(p);
	delete yymsp[-1].minor.yy0;
}
#line 1759 "MVSMParserGrammar.c"
        break;
      case 49: /* aggregate ::= string COLON literal */
#line 896 "MVSMParserGrammar.y"
{
	yygotominor.yy0 = new Token(*(yymsp[-2].minor.yy0->token));
	std::string s1 = yygotominor.yy0->toString();
	Util::toUpper(s1);
	s1 = s1 + ":" + yymsp[0].minor.yy92->toString(tree->domainList);
	yygotominor.yy0->modifyToken(s1);
	delete yymsp[0].minor.yy92;
}
#line 1771 "MVSMParserGrammar.c"
        break;
      case 50: /* aggregate ::= number COLON literal */
#line 905 "MVSMParserGrammar.y"
{
	yygotominor.yy0 = new Token(*(yymsp[-2].minor.yy0->token));
	std::string s1 = yygotominor.yy0->toString();
	s1 = s1 + ":" + yymsp[0].minor.yy92->toString(tree->domainList);
	yygotominor.yy0->modifyToken(s1);
	delete yymsp[0].minor.yy92;
}
#line 1782 "MVSMParserGrammar.c"
        break;
      case 51: /* aggregate ::= string COMMA literal COLON literal */
#line 913 "MVSMParserGrammar.y"
{
	yygotominor.yy0 = new Token(*(yymsp[-4].minor.yy0->token));
	std::string s1 = yygotominor.yy0->toString();
	Util::toUpper(s1);
	s1 = s1 + "," + yymsp[-2].minor.yy92->toString(tree->domainList) + ":" + yymsp[0].minor.yy92->toString(tree->domainList);
	yygotominor.yy0->modifyToken(s1);
}
#line 1793 "MVSMParserGrammar.c"
        break;
      case 52: /* aggregate ::= number COMMA literal COLON literal */
#line 922 "MVSMParserGrammar.y"
{
	yygotominor.yy0 = new Token(*(yymsp[-4].minor.yy0->token));
	std::string s1 = (*yymsp[-4].minor.yy0).toString();
	// Util::toUpper(s1);
	s1 = s1 + "," + yymsp[-2].minor.yy92->toString(tree->domainList)+ ":" + yymsp[0].minor.yy92->toString(tree->domainList);
	yygotominor.yy0->modifyToken(s1);
}
#line 1804 "MVSMParserGrammar.c"
        break;
      case 53: /* aggregateCum ::= aggregate */
#line 930 "MVSMParserGrammar.y"
{
	yygotominor.yy0 = new Token(*(yymsp[0].minor.yy0->token));
	delete yymsp[0].minor.yy0;
}
#line 1812 "MVSMParserGrammar.c"
        break;
      case 54: /* aggregateCum ::= aggregateCum SEMI_COLON aggregate */
#line 935 "MVSMParserGrammar.y"
{
	yygotominor.yy0 = yymsp[-2].minor.yy0;
	yygotominor.yy0->modifyToken(yymsp[-2].minor.yy0->toString() + ";" + yymsp[0].minor.yy0->toString());
	delete yymsp[0].minor.yy0;
}
#line 1821 "MVSMParserGrammar.c"
        break;
      case 55: /* predicate ::= literal DOT */
#line 942 "MVSMParserGrammar.y"
{
	yygotominor.yy16 = new Predicate;
	*yygotominor.yy16 = yymsp[-1].minor.yy92->getPredicate();
	if(yymsp[-1].minor.yy92->getHasVariables() == false){
		/*Its a special case*/
		yygotominor.yy16->notToBeCompleted();	
	}
	
	auto itr = tree->variables.find(yygotominor.yy16->getVar());
	if(itr != tree->variables.end()){
		itr->setCompleted();
	}

	std::string s1,s2;
	if(tree->outputType == OutputType::OUTPUT_ALCHEMY){
		cout<<yygotominor.yy16->toString(tree->domainList) + ".\n";
	}

	if(tree->outputType == OutputType::OUTPUT_ASP){
		s2 = yygotominor.yy16->getExtra(tree->variables);

		if(s2.length() > 0){
			s1 = yygotominor.yy16->toString(s1,false);
			s1 += ":-";
			s1 += s2;
			s1 += ".\n";
		}
		else{
			s1 = yygotominor.yy16->toString(s1,true);
		}
			

		
	}

	cout<<s1;

	delete yymsp[-1].minor.yy92;
}
#line 1864 "MVSMParserGrammar.c"
        break;
      case 56: /* predicate ::= number literal */
#line 982 "MVSMParserGrammar.y"
{
	yygotominor.yy16 = new Predicate;
	*yygotominor.yy16 = yymsp[0].minor.yy92->getPredicate();

	if(yymsp[0].minor.yy92->getHasVariables() == false){
		/*Its a special case*/
		yygotominor.yy16->notToBeCompleted();	
	}
	
	auto itr = tree->variables.find(yygotominor.yy16->getVar());
	if(itr != tree->variables.end()){
		itr->setCompleted();
	}

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY){
		cout<<yygotominor.yy16->toString(yymsp[-1].minor.yy0->toString()+SPACE, false);
	}
	if(tree->outputType == OutputType::OUTPUT_ASP){
		std::set<std::string> uniqueSet = tree->findVariables(yygotominor.yy16->toString(tree->domainList));
		std::string uniqueSetStr;
		for(auto itr = uniqueSet.begin(); itr != uniqueSet.end(); ++itr){
			uniqueSetStr += *itr + ",";
		}
		if (uniqueSetStr.length() > 0)
		{
			uniqueSetStr.pop_back();
			uniqueSetStr = "," + uniqueSetStr; 
		}
		string unsatString = "unsat(" + std::to_string(tree->weak_constraint_counter) + ",0," + std::to_string((int)(std::stof(yymsp[-1].minor.yy0->toString())* 1)) + uniqueSetStr + ")";
		std::cout << unsatString
					<< " :- "
					<< "not "
					<< yygotominor.yy16->toString(tree->domainList)
					<<LanguageConstants::LINE_END
					<<"\n"; 

		std::cout << yygotominor.yy16->toString(tree->domainList)
					<< " :- "
					<< "not "
					<< unsatString
					<<LanguageConstants::LINE_END
					<<"\n"; 

	
		std::cout   << " :~ "
					<< unsatString
					<< ". "
					<< "["
					<< std::to_string((int)(std::stof(yymsp[-1].minor.yy0->toString())* 1))
					<<","
					<< tree->weak_constraint_counter
					<< uniqueSetStr
					<< "]"
					<<"\n";

		tree->weak_constraint_counter++; 

	}	
	delete yymsp[0].minor.yy92;
}
#line 1928 "MVSMParserGrammar.c"
        break;
      case 57: /* predicate ::= number NEGATION NEGATION literal */
#line 1043 "MVSMParserGrammar.y"
{
	yygotominor.yy16 = new Predicate;
	*yygotominor.yy16 = yymsp[0].minor.yy92->getPredicate();
	yygotominor.yy16->notToBeCompleted();

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY){
		tree->statHasDblNeg = true;
		cout<<yygotominor.yy16->toString(yymsp[-3].minor.yy0->toString()+SPACE, false);	
	}
	else if(tree->outputType == OutputType::OUTPUT_ASP){
		std::string str = yygotominor.yy16->toString(":~ not ", false);
		std::string temp  = yygotominor.yy16->getExtra(tree->variables);	
		if(temp.length() > 0)
			str += ",";
		str += temp;
		std::string constants = yygotominor.yy16->getExtraConstants();
		if (constants.length() > 0)
		{
			constants = "," + constants; 
		}

		std::set<std::string> uniqueSet = tree->findVariables(str);
		std::string uniqueSetStr;
		for(auto itr = uniqueSet.begin(); itr != uniqueSet.end(); ++itr){
			uniqueSetStr += *itr + ",";
		}
		if (uniqueSetStr.length() > 0)
		{
			uniqueSetStr.pop_back();
			uniqueSetStr = "," + uniqueSetStr; 
		}

		str += LanguageConstants::LINE_END;
		str += " [" + 
				std::to_string((int)(std::stof(yymsp[-3].minor.yy0->toString())* 1)) + 
				"," + 
				std::to_string(tree->weak_constraint_counter++) + 
				constants + 
				"]\n";
		cout<<str;
	}
	
	delete yymsp[0].minor.yy92;
}
#line 1976 "MVSMParserGrammar.c"
        break;
      case 58: /* predicate ::= number NEGATION literal */
#line 1088 "MVSMParserGrammar.y"
{
	yygotominor.yy16 = new Predicate;
	*yygotominor.yy16 = yymsp[0].minor.yy92->getPredicate();
	yygotominor.yy16->notToBeCompleted();

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY){
		cout<<yygotominor.yy16->toString(yymsp[-2].minor.yy0->toString()+SPACE, false);
	}
	else if(tree->outputType == OutputType::OUTPUT_ASP){
		std::string str = yygotominor.yy16->toString(":~ ", false);		
		std::string temp  = yygotominor.yy16->getExtra(tree->variables);	
		if(temp.length() > 0)
			str += ",";

		std::string constants = yygotominor.yy16->getExtraConstants();
		if (constants.length() > 0)
		{
			constants = "," + constants; 
		}

		std::set<std::string> uniqueSet = tree->findVariables(str);
		std::string uniqueSetStr;
		for(auto itr = uniqueSet.begin(); itr != uniqueSet.end(); ++itr){
			uniqueSetStr += *itr + ",";
		}
		if (uniqueSetStr.length() > 0)
		{
			uniqueSetStr.pop_back();
			uniqueSetStr = "," + uniqueSetStr; 
		}
		



		str += " [" + 
		std::to_string((int)(std::stof(yymsp[-2].minor.yy0->toString())* 1)) + 
		"," + 
		std::to_string(tree->weak_constraint_counter++) + 
		constants + 
		"]\n";
		cout<<str;
	}

	
	delete yymsp[0].minor.yy92;
}
#line 2026 "MVSMParserGrammar.c"
        break;
      case 59: /* predicate ::= NEGATION NEGATION literal DOT */
#line 1135 "MVSMParserGrammar.y"
{
	yygotominor.yy16 = new Predicate;
	*yygotominor.yy16 = yymsp[-1].minor.yy92->getPredicate();
	yygotominor.yy16->notToBeCompleted();
	tree->statHasDblNeg = true;
	std::string s1; 

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY){
		cout<<yygotominor.yy16->toString(s1, false);
	}
	else if(tree->outputType == OutputType::OUTPUT_ASP){
		cout<<yygotominor.yy16->toString(":- not ", true);		
	}


	
	delete yymsp[-1].minor.yy92;	
}
#line 2048 "MVSMParserGrammar.c"
        break;
      case 60: /* variables ::= variable */
#line 1155 "MVSMParserGrammar.y"
{
	yygotominor.yy7 = new std::vector<std::string*>();	
	yygotominor.yy7->push_back(yymsp[0].minor.yy0->token);
}
#line 2056 "MVSMParserGrammar.c"
        break;
      case 61: /* variables ::= variables COMMA variable */
#line 1160 "MVSMParserGrammar.y"
{
	yygotominor.yy7 = yymsp[-2].minor.yy7;
	yymsp[-2].minor.yy7->push_back(yymsp[0].minor.yy0->token);
}
#line 2064 "MVSMParserGrammar.c"
        break;
      case 62: /* variable ::= string */
      case 63: /* variable ::= number */ yytestcase(yyruleno==63);
      case 64: /* string ::= STRING */ yytestcase(yyruleno==64);
#line 1165 "MVSMParserGrammar.y"
{ yygotominor.yy0=yymsp[0].minor.yy0;}
#line 2071 "MVSMParserGrammar.c"
        break;
      case 65: /* number ::= NUMBER */
#line 1173 "MVSMParserGrammar.y"
{ yygotominor.yy0=yymsp[0].minor.yy0; }
#line 2076 "MVSMParserGrammar.c"
        break;
      default:
      /* (0) start ::= prog */ yytestcase(yyruleno==0);
      /* (1) prog ::= prog SORTS sortdecl */ yytestcase(yyruleno==1);
      /* (3) sortdecl ::= NEWLINE sortdecl */ yytestcase(yyruleno==3);
      /* (5) prog ::= prog OBJECTS objectdecl */ yytestcase(yyruleno==5);
      /* (6) objectdecl ::= object SEMI_COLON objectdecl */ yytestcase(yyruleno==6);
      /* (7) objectdecl ::= object DOT */ yytestcase(yyruleno==7);
      /* (8) objectdecl ::= NEWLINE objectdecl */ yytestcase(yyruleno==8);
      /* (11) prog ::= prog CONSTANTS constantdecl */ yytestcase(yyruleno==11);
      /* (12) constantdecl ::= constant SEMI_COLON constantdecl */ yytestcase(yyruleno==12);
      /* (13) constantdecl ::= constant DOT */ yytestcase(yyruleno==13);
      /* (14) constantdecl ::= NEWLINE constantdecl */ yytestcase(yyruleno==14);
      /* (23) prog ::= prog NEWLINE */ yytestcase(yyruleno==23);
      /* (24) prog ::= */ yytestcase(yyruleno==24);
        break;
  };
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yypParser->yyidx -= yysize;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,(YYCODETYPE)yygoto);
  if( yyact < YYNSTATE ){
#ifdef NDEBUG
    /* If we are not debugging and the reduce action popped at least
    ** one element off the stack, then we can push the new element back
    ** onto the stack here, and skip the stack overflow test in yy_shift().
    ** That gives a significant speed improvement. */
    if( yysize ){
      yypParser->yyidx++;
      yymsp -= yysize-1;
      yymsp->stateno = (YYACTIONTYPE)yyact;
      yymsp->major = (YYCODETYPE)yygoto;
      yymsp->minor = yygotominor;
    }else
#endif
    {
      yy_shift(yypParser,yyact,yygoto,&yygotominor);
    }
  }else{
    assert( yyact == YYNSTATE + YYNRULE + 1 );
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
#line 66 "MVSMParserGrammar.y"

    std::cout<<"Giving up.Parser is lost...\n";

#line 2141 "MVSMParserGrammar.c"
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
#line 71 "MVSMParserGrammar.y"

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
    
#line 2171 "MVSMParserGrammar.c"
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
#line 58 "MVSMParserGrammar.y"

	if (tree->outputType == OutputType::OUTPUT_ASP)
		std::cout<<("%parsing complete!\n");
	else
    	std::cout<<("//parsing complete!\n");
#line 2196 "MVSMParserGrammar.c"
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
  int yyendofinput;     /* True if we are at the end of input */
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
  }
  yyminorunion.yy0 = yyminor;
  yyendofinput = (yymajor==0);
  MVSMParserGrammarARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput %s\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,(YYCODETYPE)yymajor);
    if( yyact<YYNSTATE ){
      assert( !yyendofinput );  /* Impossible to shift the $ token */
      yy_shift(yypParser,yyact,yymajor,&yyminorunion);
      yypParser->yyerrcnt--;
      yymajor = YYNOCODE;
    }else if( yyact < YYNSTATE + YYNRULE ){
      yy_reduce(yypParser,yyact-YYNSTATE);
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
                        YYERRORSYMBOL)) >= YYNSTATE
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
  return;
}

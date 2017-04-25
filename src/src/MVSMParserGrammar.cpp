/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is included that follows the "include" declaration
** in the input grammar file. */
#include <stdio.h>

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
#define YYNOCODE 49
#define YYACTIONTYPE unsigned char
#if INTERFACE
#define MVSMParserGrammarTOKENTYPE Token*
#endif
typedef union {
  int yyinit;
  MVSMParserGrammarTOKENTYPE yy0;
  Body* yy1;
  Predicate* yy12;
  Variable* yy13;
  BodyDef* yy24;
  Domain* yy43;
  Head* yy65;
  Tree* yy79;
  RuleCompletion* yy81;
  std::vector<std::string*>* yy91;
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
#define YYNSTATE 170
#define YYNRULE 74
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
#define YY_ACTTAB_COUNT (367)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   245,   56,  113,  110,  111,   82,   48,   54,   55,  154,
 /*    10 */    83,  136,  107,   34,  112,   11,  121,   93,   64,    2,
 /*    20 */    88,  147,  144,  145,  137,  159,   23,   55,  160,   42,
 /*    30 */   136,  166,  157,  146,   37,  121,  158,   64,    2,   88,
 /*    40 */   236,   44,  100,   97,  166,   43,   89,  236,   22,   15,
 /*    50 */    79,  105,   93,  136,   84,  236,  159,  164,   85,  108,
 /*    60 */   109,  158,  139,   53,   75,  115,   96,  158,  126,   84,
 /*    70 */    21,  159,  163,   85,  108,   74,   36,   76,  130,  166,
 /*    80 */   157,   75,  158,   43,   84,  102,  159,  162,   85,  108,
 /*    90 */   104,   58,   74,   58,  136,  131,  136,  158,   80,  124,
 /*   100 */    92,  124,  158,  141,  158,  141,   58,   46,  165,  136,
 /*   110 */    60,   35,  159,   91,  124,  150,   58,  158,  141,  136,
 /*   120 */   166,  157,   58,  158,  121,  136,   69,  158,  141,   68,
 /*   130 */   124,   45,   58,  158,  141,  136,   12,  155,   58,   63,
 /*   140 */   124,  136,    7,  158,  141,    9,  121,  166,   62,  158,
 /*   150 */   141,   58,   39,   96,  136,  166,  157,   20,   61,  124,
 /*   160 */   103,   58,  158,  141,  136,   52,  166,  157,  166,  121,
 /*   170 */    31,   71,  158,   65,   10,  170,   38,    4,  100,   97,
 /*   180 */   166,    1,   96,  219,   38,   32,   18,   47,   17,   51,
 /*   190 */   219,  123,   13,   17,   41,  166,  157,   58,  219,   81,
 /*   200 */   136,  159,  119,   58,  150,  142,  136,   33,  158,  141,
 /*   210 */    30,   70,  158,   27,  158,  141,   58,   82,   78,  136,
 /*   220 */   159,  153,   83,  150,  122,   26,   58,  158,  141,  136,
 /*   230 */    79,  158,   79,  136,   90,  136,   95,  158,  141,   25,
 /*   240 */    75,  158,  135,  158,   99,   79,   17,  127,  136,   79,
 /*   250 */    50,   74,  136,   73,  130,  143,  158,  134,   40,  148,
 /*   260 */   158,  133,   79,   77,   79,  136,   79,  136,   79,  136,
 /*   270 */    34,  136,   17,  158,   98,  158,  132,  158,   94,  158,
 /*   280 */    87,   59,   43,  159,  120,   72,  150,   72,  136,  101,
 /*   290 */   136,  100,   97,   28,  158,   17,  158,  140,  158,   66,
 /*   300 */    79,    3,  159,  136,  118,  106,  169,   86,   29,  129,
 /*   310 */    82,  158,   67,  158,  152,   83,   19,  159,  117,   37,
 /*   320 */   138,   43,   49,  114,   24,  166,  157,  161,  158,   34,
 /*   330 */     8,  208,    6,  166,  157,  213,  212,   16,  208,   15,
 /*   340 */   211,    5,  213,  212,   43,  168,   86,  211,   14,  167,
 /*   350 */    86,   57,  116,  246,  166,  157,  156,  151,  149,  166,
 /*   360 */   125,  128,  246,  246,  246,  246,  126,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    25,   26,   27,   28,   29,   33,    2,   18,   33,   37,
 /*    10 */    38,   36,   16,    9,   39,    6,   41,   13,   43,   44,
 /*    20 */    45,   27,   28,   29,    5,   33,    4,   33,   36,   16,
 /*    30 */    36,   22,   23,   39,   15,   41,   44,   43,   44,   45,
 /*    40 */     1,    2,   20,   21,   22,    3,    5,    8,    9,    8,
 /*    50 */    33,   18,   13,   36,   31,   16,   33,   34,   35,   36,
 /*    60 */    18,   44,   45,   18,   33,   30,    9,   44,   33,   31,
 /*    70 */    13,   33,   34,   35,   36,   44,    9,   46,   47,   22,
 /*    80 */    23,   33,   44,    3,   31,   18,   33,   34,   35,   36,
 /*    90 */    10,   33,   44,   33,   36,   47,   36,   44,   40,   41,
 /*   100 */    40,   41,   44,   45,   44,   45,   33,   15,   16,   36,
 /*   110 */    31,   13,   33,   40,   41,   36,   33,   44,   45,   36,
 /*   120 */    22,   23,   33,   44,   41,   36,   43,   44,   45,   40,
 /*   130 */    41,    6,   33,   44,   45,   36,   15,   16,   33,   40,
 /*   140 */    41,   36,    9,   44,   45,    1,   41,   22,   43,   44,
 /*   150 */    45,   33,    6,    9,   36,   22,   23,   13,   40,   41,
 /*   160 */    18,   33,   44,   45,   36,   18,   22,   23,   22,   41,
 /*   170 */     3,   43,   44,   45,    1,    0,    2,    4,   20,   21,
 /*   180 */    22,    6,    9,    1,    2,   18,   13,   12,    7,   18,
 /*   190 */     8,   10,   17,    7,   19,   22,   23,   33,   16,   31,
 /*   200 */    36,   33,   16,   33,   36,   41,   36,    4,   44,   45,
 /*   210 */    18,   41,   44,   18,   44,   45,   33,   33,   31,   36,
 /*   220 */    33,   37,   38,   36,   41,    4,   33,   44,   45,   36,
 /*   230 */    33,   44,   33,   36,   41,   36,   13,   44,   45,   13,
 /*   240 */    33,   44,   45,   44,   45,   33,    7,   10,   36,   33,
 /*   250 */     2,   44,   36,   46,   47,   16,   44,   45,   15,   16,
 /*   260 */    44,   45,   33,    2,   33,   36,   33,   36,   33,   36,
 /*   270 */     9,   36,    7,   44,   45,   44,   45,   44,   45,   44,
 /*   280 */    45,   31,    3,   33,   16,   33,   36,   33,   36,   10,
 /*   290 */    36,   20,   21,    3,   44,    7,   44,   45,   44,   45,
 /*   300 */    33,    1,   33,   36,   16,   36,   32,   33,   18,    5,
 /*   310 */    33,   44,   45,   44,   37,   38,   13,   33,   16,   15,
 /*   320 */    36,    3,    2,    5,   13,   22,   23,   33,   44,    9,
 /*   330 */     1,    1,    1,   22,   23,    1,    1,    8,    8,    8,
 /*   340 */     1,    1,    8,    8,    3,   32,   33,    8,    8,   32,
 /*   350 */    33,   10,   16,   48,   22,   23,   33,   33,   33,   22,
 /*   360 */    33,   33,   48,   48,   48,   48,   33,
};
#define YY_SHIFT_USE_DFLT (-12)
#define YY_SHIFT_COUNT (109)
#define YY_SHIFT_MIN   (-11)
#define YY_SHIFT_MAX   (341)
static const short yy_shift_ofst[] = {
 /*     0 */   173,  173,  144,   57,   57,   57,   57,   57,   57,   57,
 /*    10 */    57,    9,    9,    9,   57,   57,   57,   57,  311,  133,
 /*    20 */   303,   98,  332,  332,  332,  332,  332,  332,  332,  332,
 /*    30 */   332,  332,  332,  332,  332,  332,  332,  332,  332,  146,
 /*    40 */   146,  146,  332,  332,   22,  125,  125,  125,  158,  158,
 /*    50 */   337,  337,  337,  337,  337,   39,  175,  182,    4,  341,
 /*    60 */   318,  288,   41,  186,  340,  339,  335,  334,  181,  331,
 /*    70 */   330,  329,  320,  304,  290,  167,   19,  271,  279,  261,
 /*    80 */   239,   80,   67,  243,   42,  121,   92,  336,  302,  300,
 /*    90 */   268,  265,  265,  248,  237,  226,  223,  221,  195,  192,
 /*   100 */   203,  174,  171,  147,  142,   45,   33,   13,   -4,  -11,
};
#define YY_REDUCE_USE_DFLT (-29)
#define YY_REDUCE_COUNT (54)
#define YY_REDUCE_MIN   (-28)
#define YY_REDUCE_MAX   (333)
static const short yy_reduce_ofst[] = {
 /*     0 */   -25,   -6,  128,  118,  105,   99,   89,   83,   73,   60,
 /*    10 */    58,   53,   38,   23,  193,  183,  170,  164,  252,  267,
 /*    20 */   254,  252,  250,   79,  235,  233,  207,  231,  229,  216,
 /*    30 */   212,  199,  197,   31,  187,   17,  168,   48,  284,  277,
 /*    40 */   184,  -28,  269,   -8,   35,  317,  313,  274,  333,  328,
 /*    50 */   327,  325,  324,  323,  294,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   198,  197,  237,  244,  244,  244,  244,  244,  244,  244,
 /*    10 */   244,  244,  244,  244,  244,  244,  244,  244,  244,  244,
 /*    20 */   244,  244,  244,  244,  244,  244,  244,  244,  244,  244,
 /*    30 */   244,  244,  244,  244,  244,  244,  244,  244,  244,  244,
 /*    40 */   244,  244,  244,  244,  244,  244,  244,  244,  244,  244,
 /*    50 */   244,  244,  244,  244,  244,  243,  244,  242,  236,  244,
 /*    60 */   244,  244,  244,  244,  244,  230,  232,  231,  244,  244,
 /*    70 */   202,  244,  236,  244,  244,  244,  244,  244,  244,  236,
 /*    80 */   244,  244,  187,  244,  244,  244,  244,  213,  211,  244,
 /*    90 */   208,  204,  200,  244,  244,  244,  244,  244,  244,  244,
 /*   100 */   244,  219,  244,  244,  186,  244,  244,  244,  234,  244,
 /*   110 */   196,  194,  192,  190,  241,  240,  233,  229,  206,  203,
 /*   120 */   201,  209,  208,  205,  210,  217,  215,  214,  216,  222,
 /*   130 */   227,  228,  226,  224,  225,  223,  220,  221,  218,  213,
 /*   140 */   212,  211,  207,  199,  195,  193,  191,  189,  183,  188,
 /*   150 */   234,  185,  184,  182,  181,  177,  180,  239,  237,  236,
 /*   160 */   235,  179,  178,  176,  175,  174,  238,  173,  172,  171,
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
  "decl",          "domain",        "domains",       "variables",   
  "sortdecl",      "string",        "objectdecl",    "object",      
  "variable",      "constantdecl",  "constant",      "rule",        
  "body",          "bodydef",       "bodydef2",      "head",        
  "number",        "literal",       "aggregateCum",  "aggregate",   
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
 /*  23 */ "prog ::= prog NEWLINE domain",
 /*  24 */ "prog ::= domain",
 /*  25 */ "prog ::= prog NEWLINE decl",
 /*  26 */ "prog ::= decl",
 /*  27 */ "prog ::= prog NEWLINE",
 /*  28 */ "prog ::=",
 /*  29 */ "rule ::= REVERSE_IMPLICATION body DOT",
 /*  30 */ "rule ::= number REVERSE_IMPLICATION body",
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
 /*  41 */ "bodydef ::= literal",
 /*  42 */ "bodydef ::= NEGATION literal",
 /*  43 */ "bodydef ::= NEGATION NEGATION literal",
 /*  44 */ "bodydef ::= LBRACKET NEGATION NEGATION literal RBRACKET",
 /*  45 */ "bodydef ::= string EQUAL string",
 /*  46 */ "bodydef ::= NEGATION string EQUAL string",
 /*  47 */ "bodydef ::= string NEGATION EQUAL string",
 /*  48 */ "literal ::= string LBRACKET variables RBRACKET EQUAL variable",
 /*  49 */ "literal ::= string LBRACKET variables RBRACKET",
 /*  50 */ "literal ::= variable",
 /*  51 */ "literal ::= string EQUAL COUNT LPAREN aggregateCum RPAREN",
 /*  52 */ "literal ::= string EQUAL SUM LPAREN aggregateCum RPAREN",
 /*  53 */ "aggregate ::= string COLON literal",
 /*  54 */ "aggregate ::= number COLON literal",
 /*  55 */ "aggregate ::= string COMMA literal COLON literal",
 /*  56 */ "aggregate ::= number COMMA literal COLON literal",
 /*  57 */ "aggregateCum ::= aggregate",
 /*  58 */ "aggregateCum ::= aggregateCum SEMI_COLON aggregate",
 /*  59 */ "predicate ::= literal DOT",
 /*  60 */ "predicate ::= number literal",
 /*  61 */ "predicate ::= number NEGATION NEGATION literal",
 /*  62 */ "predicate ::= number NEGATION literal",
 /*  63 */ "predicate ::= NEGATION NEGATION literal DOT",
 /*  64 */ "variables ::= variable",
 /*  65 */ "variables ::= variables COMMA variable",
 /*  66 */ "variable ::= string",
 /*  67 */ "variable ::= number",
 /*  68 */ "string ::= STRING",
 /*  69 */ "number ::= NUMBER",
 /*  70 */ "domain ::= string EQUAL domains",
 /*  71 */ "domains ::= LPAREN variables RPAREN",
 /*  72 */ "decl ::= string LBRACKET variables RBRACKET",
 /*  73 */ "decl ::= string",
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
  { 32, 3 },
  { 32, 2 },
  { 32, 2 },
  { 26, 3 },
  { 34, 3 },
  { 34, 2 },
  { 34, 2 },
  { 35, 4 },
  { 35, 7 },
  { 26, 3 },
  { 37, 3 },
  { 37, 2 },
  { 37, 2 },
  { 38, 7 },
  { 38, 4 },
  { 38, 1 },
  { 38, 4 },
  { 26, 3 },
  { 26, 1 },
  { 26, 3 },
  { 26, 1 },
  { 26, 3 },
  { 26, 1 },
  { 26, 3 },
  { 26, 1 },
  { 26, 2 },
  { 26, 0 },
  { 39, 3 },
  { 39, 3 },
  { 39, 4 },
  { 39, 4 },
  { 39, 4 },
  { 39, 4 },
  { 39, 8 },
  { 39, 6 },
  { 40, 3 },
  { 43, 3 },
  { 43, 1 },
  { 40, 1 },
  { 41, 1 },
  { 41, 2 },
  { 41, 3 },
  { 41, 5 },
  { 41, 3 },
  { 41, 4 },
  { 41, 4 },
  { 45, 6 },
  { 45, 4 },
  { 45, 1 },
  { 45, 6 },
  { 45, 6 },
  { 47, 3 },
  { 47, 3 },
  { 47, 5 },
  { 47, 5 },
  { 46, 1 },
  { 46, 3 },
  { 27, 2 },
  { 27, 2 },
  { 27, 4 },
  { 27, 3 },
  { 27, 4 },
  { 31, 1 },
  { 31, 3 },
  { 36, 1 },
  { 36, 1 },
  { 33, 1 },
  { 44, 1 },
  { 29, 3 },
  { 30, 3 },
  { 28, 4 },
  { 28, 1 },
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
			d->setVars(*yymsp[-3].minor.yy91);
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
	
	delete yymsp[-3].minor.yy91;
}
        break;
      case 10: /* object ::= variable DOT DOT variable COLON COLON string */
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
        break;
      case 15: /* constant ::= string LBRACKET variables RBRACKET COLON COLON string */
{
	Variable* va = new Variable;
	std::map<int, Domain> posMap;
	std::set<Domain>::iterator itr;
	int i=0;
	for(auto& v : *yymsp[-4].minor.yy91){
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
	delete yymsp[-4].minor.yy91;
}
        break;
      case 16: /* constant ::= string LBRACKET variables RBRACKET */
{
	Variable* va = new Variable;
	std::map<int, Domain> posMap;
	std::set<Domain>::iterator itr;
	int i=0;
	for(auto& v : *yymsp[-1].minor.yy91){
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
	delete yymsp[-1].minor.yy91;
	delete va;
}
        break;
      case 17: /* constant ::= string */
      case 73: /* decl ::= string */ yytestcase(yyruleno==73);
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
      case 18: /* constant ::= string COLON COLON string */
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
      case 19: /* prog ::= prog NEWLINE predicate */
{ 
	if(yymsp[0].minor.yy12->needsToBeCompleted()){	
		FactCompletion f(*yymsp[0].minor.yy12);
		tree->facts.insert(std::pair<std::string,FactCompletion>(f.getHead().getVar(),f)); 
	}

			
	delete yymsp[0].minor.yy12;
}
        break;
      case 20: /* prog ::= predicate */
{ 
	if(yymsp[0].minor.yy12->needsToBeCompleted()){
		FactCompletion f(*yymsp[0].minor.yy12);
		tree->facts.insert(std::pair<std::string,FactCompletion>(f.getHead().getVar(),f)); 	
	}
	delete yymsp[0].minor.yy12;
}
        break;
      case 21: /* prog ::= prog NEWLINE rule */
      case 22: /* prog ::= rule */ yytestcase(yyruleno==22);
{
	if((yymsp[0].minor.yy81->isHeadTop == false) && (yymsp[0].minor.yy81->toBeCompleted == true))
		tree->rules.insert(std::pair<std::string,RuleCompletion>(yymsp[0].minor.yy81->getHead().getVar(),*yymsp[0].minor.yy81));
	delete yymsp[0].minor.yy81;
}
        break;
      case 23: /* prog ::= prog NEWLINE domain */
{ 
	tree->domains.insert(*yymsp[0].minor.yy43); 
	tree->domainNamesList.insert(yymsp[0].minor.yy43->getDomainVar());
	for(auto& v : yymsp[0].minor.yy43->getVars()){
		tree->domainList.insert(v);	
	}
	// domains not printed in tuffy, rockit
	if(tree->outputType != OutputType::OUTPUT_TUFFY && tree->outputType != OutputType::OUTPUT_ROCKIT)
		cout<<yymsp[0].minor.yy43->toString(false);
	delete yymsp[0].minor.yy43;
}
        break;
      case 24: /* prog ::= domain */
{ 
	tree->domains.insert(*yymsp[0].minor.yy43); 
	tree->domainNamesList.insert(yymsp[0].minor.yy43->getDomainVar());
	for(auto& v : yymsp[0].minor.yy43->getVars()){
		tree->domainList.insert(v);	
	}
	// domains not printed in tuffy
	if(tree->outputType != OutputType::OUTPUT_TUFFY && tree->outputType != OutputType::OUTPUT_ROCKIT)
		cout<<yymsp[0].minor.yy43->toString(false);
	delete yymsp[0].minor.yy43;
}
        break;
      case 29: /* rule ::= REVERSE_IMPLICATION body DOT */
{
	yygotominor.yy81 = new RuleCompletion;
	yygotominor.yy81->isHeadTop = true;
	
	
	if(tree->outputType == OutputType::OUTPUT_ALCHEMY){
		std::cout<<"("
					<<yymsp[-1].minor.yy1->toNNFString()
					<<")"
					<<LanguageConstants::LINE_END
					<<"\n";
	}
	else if(tree->outputType == OutputType::OUTPUT_TUFFY || tree->outputType == OutputType::OUTPUT_ROCKIT){
		std::cout<<yymsp[-1].minor.yy1->toNNFString()
					<<LanguageConstants::LINE_END
					<<"\n";
	}
	else{
		std::cout<<LanguageConstants::IMPL
				<<yymsp[-1].minor.yy1->toString()
				<<LanguageConstants::LINE_END
				<<"\n";
	}
	delete yymsp[-1].minor.yy1;
}
        break;
      case 30: /* rule ::= number REVERSE_IMPLICATION body */
{
	yygotominor.yy81 = new RuleCompletion;
	yygotominor.yy81->isHeadTop = true;
	
	if(tree->outputType == OutputType::OUTPUT_ALCHEMY){
		std::cout<<yymsp[-2].minor.yy0->toString()<<SPACE
					<<"("
					<<yymsp[0].minor.yy1->toNNFString()
					<<")"
					<<"\n";
	}
	else if(tree->outputType == OutputType::OUTPUT_TUFFY || tree->outputType == OutputType::OUTPUT_ROCKIT){

		std::cout<<yymsp[-2].minor.yy0->toString()<<SPACE
					
					<<yymsp[0].minor.yy1->toNNFString()
					
					<<"\n";
	}
	else{
		std::string extra = yymsp[0].minor.yy1->getExtra(tree->variables);
		if(extra.length() != 0){
			extra = "," + extra; 
		}
		std::string str = ":~"
				+ yymsp[0].minor.yy1->toString()
				+ extra 
				+ LanguageConstants::LINE_END
				+ " "
				+ "["
				+  std::to_string((int)(std::stof(yymsp[-2].minor.yy0->toString())* 10000))
				+  ","
				+  std::to_string(tree->weak_constraint_counter);

		std::string temp = yymsp[0].minor.yy1->getExtraConstants();
		if(temp.length() > 0){
			str += ","
				+ temp;
		}
				
		str += std::string("]") + std::string("\n");

		cout << str;
		tree->weak_constraint_counter++;
	
	}
	// std::cout<<yymsp[-2].minor.yy0->toString()<<SPACE<<"("<<yymsp[0].minor.yy1->toNNFString()<<")"<<"\n";
	delete yymsp[0].minor.yy1;
}
        break;
      case 31: /* rule ::= head DISJUNCTION bodydef DOT */
{
	yygotominor.yy81 = new RuleCompletion;
	yygotominor.yy81->isHeadTop = true;
	yymsp[-3].minor.yy65->addPredicate(yymsp[-1].minor.yy24->getPredicate());
	// RULE_COMPLETION_HEAD_DIS_BODY_TOP(yymsp[-3].minor.yy65,yymsp[-1].minor.yy24)
	try{
		RuleCompletion_HD_BT(yymsp[-3].minor.yy65,tree);
	}
	catch(const std::out_of_range& e){
		throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}
	
	yymsp[-3].minor.yy65->appendStr(yymsp[-1].minor.yy24->getPredicate().toString(tree->domainList),false,true,false);
	
	std::string temp;
	if(tree->outputType == OutputType::OUTPUT_ASP){
		temp = yymsp[-3].minor.yy65->getExtra(tree->variables);
		if(temp.length() > 0){
			temp = yymsp[-3].minor.yy65->toString() + ":-" + temp;
		}
		else{
			temp = yymsp[-3].minor.yy65->toString();
		}
		std::cout<<temp<<"."<<"\n";
	}
	else{
		std::cout<<yymsp[-3].minor.yy65->toString()<<".\n";	
	}
	
	
	
	delete yymsp[-3].minor.yy65;
	delete yymsp[-1].minor.yy24;
}
        break;
      case 32: /* rule ::= number head DISJUNCTION bodydef */
{
	//Doing this 
	yygotominor.yy81 = new RuleCompletion;
	yygotominor.yy81->isHeadTop = true;
	yymsp[-2].minor.yy65->addPredicate(yymsp[0].minor.yy24->getPredicate());
	// RULE_COMPLETION_HEAD_DIS_BODY_TOP(yymsp[-2].minor.yy65,yymsp[0].minor.yy24)
	try{
		RuleCompletion_HD_BT(yymsp[-2].minor.yy65,tree);
	}
	catch(const std::out_of_range& e){
		throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}

	if(tree->outputType == OutputType::OUTPUT_ASP){
		std::set<std::string> uniqueSet = tree->findVariables(yymsp[-2].minor.yy65->toNNFString(tree->domainList));
		std::string uniqueSetStr;
		for(auto itr = uniqueSet.begin(); itr != uniqueSet.end(); ++itr){
			uniqueSetStr += *itr + ",";
		}
		if (uniqueSetStr.length() > 0)
		{
			uniqueSetStr.pop_back();
			uniqueSetStr = "," + uniqueSetStr; 
		}
		string unsatString = "unsat(" + std::to_string(tree->weak_constraint_counter) + ",0," + std::to_string((int)(std::stof(yymsp[-3].minor.yy0->toString())* 10000)) + uniqueSetStr + ")";
		std::cout << unsatString 
				<< " :- "
				<<yymsp[-2].minor.yy65->toNNFString(tree->domainList)
				<<".\n";
		std::cout << yymsp[-2].minor.yy65->toString(tree->domainList)
					<< " :- "
					<< "not "
					<< unsatString
					<< ".\n";

		std::cout   << " :~ "
					<< unsatString
					<< ". "
					<< "["
					<< std::to_string((int)(std::stof(yymsp[-3].minor.yy0->toString())* 10000))
					<<","
					<< tree->weak_constraint_counter
					<< uniqueSetStr
					<< "]"
					<<"\n";
	}
	else{
		yymsp[-2].minor.yy65->appendStr(yymsp[0].minor.yy24->getPredicate().toString(tree->domainList),false,true,false);	
		std::cout<<yymsp[-3].minor.yy0->toString()<<SPACE<<yymsp[-2].minor.yy65->toString()<<"\n";
	}
	
	delete yymsp[-2].minor.yy65;
	delete yymsp[0].minor.yy24;
}
        break;
      case 33: /* rule ::= head REVERSE_IMPLICATION body DOT */
{
	yygotominor.yy81 = new RuleCompletion;

	if (yymsp[-3].minor.yy65->getDisjunction()){
		// RULE_COMPLETION_HEAD_DIS_BODY_TOP(yymsp[-3].minor.yy65,yymsp[-1].minor.yy1)
		yygotominor.yy81->isHeadTop = true;
		RuleCompletion_HD_BC(yymsp[-3].minor.yy65,yymsp[-1].minor.yy1,true,tree);
		if(tree->outputType == OutputType::OUTPUT_ALCHEMY || tree->outputType == OutputType::OUTPUT_TUFFY)
			std::cout<<yymsp[-1].minor.yy1->toString()
					<<" => "
					<<yymsp[-3].minor.yy65->toString()
					<<LanguageConstants::LINE_END
					<<"\n";
		if(tree->outputType == OutputType::OUTPUT_ASP)
			tree->printASPRuleHB(yymsp[-3].minor.yy65,yymsp[-1].minor.yy1);
		if(tree->outputType == OutputType::OUTPUT_ROCKIT){
			std::cout<<yymsp[-1].minor.yy1->toNNFString()
					<<" v "
					<<yymsp[-3].minor.yy65->toString()
					<<LanguageConstants::LINE_END
					<<"\n";
		}
	}
	else{
		// RULE_COMPLETION_BH(yymsp[-1].minor.yy1,yymsp[-3].minor.yy65);
		// yygotominor.yy81 = new RuleCompletion(yymsp[-3].minor.yy65->getPredicate(),predList, resultMap, varMap);
		try{
			yygotominor.yy81 = RuleCompletion_BH(yymsp[-1].minor.yy1,yymsp[-3].minor.yy65,tree);
		}
		catch(const std::out_of_range& e){
			throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
		}
		if(tree->outputType == OutputType::OUTPUT_ALCHEMY || tree->outputType == OutputType::OUTPUT_TUFFY)
			std::cout<<yymsp[-1].minor.yy1->toString()
					<<" => "
					<<yymsp[-3].minor.yy65->toString()
					<<LanguageConstants::LINE_END
					<<"\n";
		if(tree->outputType == OutputType::OUTPUT_ASP)
			tree->printASPRuleHB(yymsp[-3].minor.yy65,yymsp[-1].minor.yy1);
		if(tree->outputType == OutputType::OUTPUT_ROCKIT){
			std::cout<<yymsp[-1].minor.yy1->toNNFString()
					<<" v "
					<<yymsp[-3].minor.yy65->toString()
					<<LanguageConstants::LINE_END
					<<"\n";
		}
	}
	delete yymsp[-1].minor.yy1;
	delete yymsp[-3].minor.yy65;
}
        break;
      case 34: /* rule ::= number head REVERSE_IMPLICATION body */
{
	// RULE_COMPLETION_BH(yymsp[0].minor.yy1,yymsp[-2].minor.yy65);
	// yygotominor.yy81 = new RuleCompletion(yymsp[-2].minor.yy65->getPredicate(),predList, resultMap, varMap);
	try{
		yygotominor.yy81 = RuleCompletion_BH(yymsp[0].minor.yy1,yymsp[-2].minor.yy65,tree);
	}
	catch(const std::out_of_range& e){
			throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY || tree->outputType == OutputType::OUTPUT_TUFFY)
		std::cout<< yymsp[-3].minor.yy0->toString()
				<<SPACE
				<<yymsp[0].minor.yy1->toString()
				<<" => "
				<<yymsp[-2].minor.yy65->toString()
				<<"\n";
	
	if(tree->outputType == OutputType::OUTPUT_ASP){
		std::set<std::string> uniqueSet = tree->findFreeVariables(yymsp[-2].minor.yy65->toNNFString(tree->domainList),yymsp[0].minor.yy1->toString());
		std::string uniqueSetStr;
		for(auto itr = uniqueSet.begin(); itr != uniqueSet.end(); ++itr){
			uniqueSetStr += *itr + ",";
		}
		if (uniqueSetStr.length() > 0)
		{
			uniqueSetStr.pop_back();
			uniqueSetStr = "," + uniqueSetStr; 
		}
		string unsatString = "unsat(" + std::to_string(tree->weak_constraint_counter) + ",0," + std::to_string((int)(std::stof(yymsp[-3].minor.yy0->toString())* 10000)) + uniqueSetStr + ")";
		std::cout << unsatString
					<< " :- "
					<< yymsp[0].minor.yy1->toString()
					<< " , "
					/*Change this to NNF String*/
					<< yymsp[-2].minor.yy65->toNNFString(tree->domainList)
					<<LanguageConstants::LINE_END
					<<"\n"; 

		std::cout << yymsp[-2].minor.yy65->toString()
					<< " :- "
					<< yymsp[0].minor.yy1->toString()
					<< " , "
					<< "not "
					<< unsatString
					<<LanguageConstants::LINE_END
					<<"\n"; 

	
		std::cout   << " :~ "
					<< unsatString
					<< ". "
					<< "["
					<< std::to_string((int)(std::stof(yymsp[-3].minor.yy0->toString())* 10000))
					<< "@0"
					<<","
					<< tree->weak_constraint_counter
					<< uniqueSetStr
					<< "]"
					<<"\n";

		tree->weak_constraint_counter++; 
	}

	if(tree->outputType == OutputType::OUTPUT_ROCKIT){
		std::cout<< yymsp[-3].minor.yy0->toString()
				<<SPACE
				<<yymsp[0].minor.yy1->toNNFString()
				<<" v "
				<<yymsp[-2].minor.yy65->toString()
				<<"\n";
		
	}

	delete yymsp[0].minor.yy1;
	delete yymsp[-2].minor.yy65;
}
        break;
      case 35: /* rule ::= number NEGATION NEGATION LBRACKET head REVERSE_IMPLICATION body RBRACKET */
{
	yygotominor.yy81 = new RuleCompletion;
	yygotominor.yy81->isHeadTop = true;	
	tree->statHasDblNeg = true;

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY || tree->outputType == OutputType::OUTPUT_TUFFY)
		std::cout<< yymsp[-7].minor.yy0->toString() 
				<< SPACE 
				<<"!!("
				<<yymsp[-1].minor.yy1->toString()
				<<" => "
				<<yymsp[-3].minor.yy65->toString()
				<<"\n"; 
	if(tree->outputType == OutputType::OUTPUT_ASP)
		std::cout<< yymsp[-7].minor.yy0->toString() 
				<< SPACE 
				<<yymsp[-3].minor.yy65->toString()
				<<" :- "
				<<yymsp[-1].minor.yy1->toString()
				<<LanguageConstants::LINE_END
				<<"\n"; 

	if(tree->outputType == OutputType::OUTPUT_ROCKIT){
		std::cout<< yymsp[-7].minor.yy0->toString() 
				<< SPACE 
				<<yymsp[-1].minor.yy1->toNNFString()
				<<" v "
				<<yymsp[-3].minor.yy65->toString()
				<<"\n"; 
	}
	
	delete yymsp[-1].minor.yy1;
	delete yymsp[-3].minor.yy65;
}
        break;
      case 36: /* rule ::= LPAREN head RPAREN REVERSE_IMPLICATION body DOT */
{
	
	if (yymsp[-4].minor.yy65->getPredicate().checkEquality() != 0){
		throw syntax_exception("Cannot have equality/Inequlity as a part of choice rule\n");
	}

	// RULE_COMPLETION_BH(yymsp[-1].minor.yy1,yymsp[-4].minor.yy65);
	// yygotominor.yy81 = new RuleCompletion(yymsp[-4].minor.yy65->getPredicate(),predList, resultMap, varMap);
	try{
		yygotominor.yy81 = RuleCompletion_BH(yymsp[-1].minor.yy1,yymsp[-4].minor.yy65,tree);
	}
	catch(const std::out_of_range& e){
			throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY || tree->outputType == OutputType::OUTPUT_TUFFY || tree->outputType == OutputType::OUTPUT_ROCKIT)
		std::cout<<COMMENT<<yymsp[-1].minor.yy1->toString()<<" => "<<yymsp[-4].minor.yy65->toString()<<"\n";
	
	if(tree->outputType == OutputType::OUTPUT_ASP)
		std::cout<<yymsp[-4].minor.yy65->toString()<<" :- "<<yymsp[-1].minor.yy1->toString()<<LanguageConstants::LINE_END<<"\n";
	delete yymsp[-1].minor.yy1;
	delete yymsp[-4].minor.yy65;
}
        break;
      case 37: /* body ::= body CONJUNCTION bodydef */
{
	yygotominor.yy1 = yymsp[-2].minor.yy1;
	yymsp[-2].minor.yy1->addPredicate(yymsp[0].minor.yy24->getPredicate());
	yygotominor.yy1->appendStr(yymsp[0].minor.yy24->getPredicate(),false,false,true,tree->domainList);
	delete yymsp[0].minor.yy24;
}
        break;
      case 38: /* head ::= head DISJUNCTION bodydef */
{
	yygotominor.yy65 = yymsp[-2].minor.yy65;
	yymsp[-2].minor.yy65->addPredicate(yymsp[0].minor.yy24->getPredicate());
	yygotominor.yy65->appendStr(yymsp[0].minor.yy24->getPredicate().toString(tree->domainList),false,true,false);
	yygotominor.yy65->setDisjunction(true);
	delete yymsp[0].minor.yy24;
}
        break;
      case 39: /* head ::= bodydef */
{
	yygotominor.yy65 = new Head(yymsp[0].minor.yy24->getPredicate());
	// yygotominor.yy65->addPredicate(yymsp[0].minor.yy24->getPredicate());
	yygotominor.yy65->appendStr(yymsp[0].minor.yy24->getPredicate().toString(tree->domainList),false,false,false);
	delete yymsp[0].minor.yy24;
}
        break;
      case 40: /* body ::= bodydef */
{
	yygotominor.yy1 = new Body;
	Predicate p = yymsp[0].minor.yy24->getPredicate();
	yygotominor.yy1->addPredicate(p);
	yygotominor.yy1->appendStr(p,false,false,false,tree->domainList);
	delete yymsp[0].minor.yy24;
}
        break;
      case 41: /* bodydef ::= literal */
{	
	yygotominor.yy24 = yymsp[0].minor.yy24;
}
        break;
      case 42: /* bodydef ::= NEGATION literal */
{	
	yygotominor.yy24 = yymsp[0].minor.yy24;
	Predicate p = yygotominor.yy24->getPredicate();
	p.setSingleNegation(true);
	yygotominor.yy24->addPredicate(p);
	// yygotominor.yy24->getPredicate().setSingleNegation(true);
}
        break;
      case 43: /* bodydef ::= NEGATION NEGATION literal */
{	
	yygotominor.yy24 = yymsp[0].minor.yy24;
	tree->statHasDblNeg = true;
	yygotominor.yy24->getPredicate().setDoubleNegation(true);
}
        break;
      case 44: /* bodydef ::= LBRACKET NEGATION NEGATION literal RBRACKET */
{	
	yygotominor.yy24 = yymsp[-1].minor.yy24;
	tree->statHasDblNeg = true;
	yygotominor.yy24->getPredicate().setDoubleNegation(true);
}
        break;
      case 45: /* bodydef ::= string EQUAL string */
{
	yygotominor.yy24 = new BodyDef;
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
		yygotominor.yy24->addPredicate(p);
		unsigned int expectedArgs = (tree->variables.find(*(yymsp[-2].minor.yy0->token)))->getSize();
		if (expectedArgs != vars.size()){
			delete yygotominor.yy24;
			throw invalid_arguments(expectedArgs, vars.size(), *(yymsp[-2].minor.yy0->token));
		}
	}
	
	else{
		Predicate p(yymsp[-2].minor.yy0->token,yymsp[0].minor.yy0->token);
		p.setEquality();
		yygotominor.yy24->addPredicate(p);
	}
}
        break;
      case 46: /* bodydef ::= NEGATION string EQUAL string */
{
	std::vector<std::string> vars;
	vars.push_back(yymsp[0].minor.yy0->toString());
	Predicate p(yymsp[-2].minor.yy0->token);
	p.setTokens(vars, tree->domainList);
	p.setSingleNegation(true);
	yygotominor.yy24 = new BodyDef;
	yygotominor.yy24->addPredicate(p);
	// delete Ve;
	unsigned int expectedArgs = (tree->variables.find(*(yymsp[-2].minor.yy0->token)))->getSize();
	if (expectedArgs != vars.size()){
		delete yygotominor.yy24;
		throw invalid_arguments(expectedArgs, vars.size(), *(yymsp[-2].minor.yy0->token));
	}
}
        break;
      case 47: /* bodydef ::= string NEGATION EQUAL string */
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
	yygotominor.yy24 = new BodyDef;
	yygotominor.yy24->addPredicate(p);
}
        break;
      case 48: /* literal ::= string LBRACKET variables RBRACKET EQUAL variable */
{
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-3].minor.yy91)
		vars.push_back(*v);
	vars.push_back(*(yymsp[0].minor.yy0->token));
	Predicate p(yymsp[-5].minor.yy0->token);
	p.setTokens(vars, tree->domainList);
	yygotominor.yy24 = new BodyDef;
	yygotominor.yy24->addPredicate(p);
	auto itr = tree->variables.find(yymsp[-5].minor.yy0->toString());
	if(itr == tree->variables.end()){
		delete yygotominor.yy24;
		throw syntax_exception("Literal "+ yymsp[-5].minor.yy0->toString() + " not found.\n");
	}
	delete yymsp[-3].minor.yy91;
	unsigned int expectedArgs = (tree->variables.find(yymsp[-5].minor.yy0->toString()))->getSize();
	if (expectedArgs != vars.size()){
		delete yygotominor.yy24;
		throw invalid_arguments(expectedArgs, vars.size(), *(yymsp[-5].minor.yy0->token));
	}
}
        break;
      case 49: /* literal ::= string LBRACKET variables RBRACKET */
{
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-1].minor.yy91)
		vars.push_back(*v);
	Predicate p(yymsp[-3].minor.yy0->token);
	p.setTokens(vars, tree->domainList);
	yygotominor.yy24 = new BodyDef;
	yygotominor.yy24->addPredicate(p);
	delete yymsp[-1].minor.yy91;
	auto itr = tree->variables.find(yymsp[-3].minor.yy0->toString());
	if(itr == tree->variables.end()){
		delete yygotominor.yy24;
		throw syntax_exception("Literal "+ yymsp[-3].minor.yy0->toString() + " not found.\n");
	}
	unsigned int expectedArgs = itr->getSize();
	if (expectedArgs != vars.size()){
		delete yygotominor.yy24;
		throw invalid_arguments(expectedArgs, vars.size(), *(yymsp[-3].minor.yy0->token));
	}	
}
        break;
      case 50: /* literal ::= variable */
{
	Predicate p(yymsp[0].minor.yy0->token);
	auto itr = tree->variables.find(yymsp[0].minor.yy0->toString());
	yygotominor.yy24 = new BodyDef;
	/*Special Case: BodyDef does not have variables*/
	yygotominor.yy24->setHasVariables();
	yygotominor.yy24->addPredicate(p);
}
        break;
      case 51: /* literal ::= string EQUAL COUNT LPAREN aggregateCum RPAREN */
{
	std::string s = (*yymsp[-5].minor.yy0).toString();
	Util::toUpper(s);
	s = s + "= #count{" + yymsp[-1].minor.yy0->toString() + "}";
	Predicate p(yymsp[-5].minor.yy0->token);
	p.setString(s);
	yygotominor.yy24 = new BodyDef;
	yygotominor.yy24->addPredicate(p);
	delete yymsp[-1].minor.yy0;
}
        break;
      case 52: /* literal ::= string EQUAL SUM LPAREN aggregateCum RPAREN */
{
	std::string s = (*yymsp[-5].minor.yy0).toString();
	Util::toUpper(s);
	s = s + "= #sum{" + yymsp[-1].minor.yy0->toString() + "}";
	Predicate p(yymsp[-5].minor.yy0->token);
	p.setString(s);
	yygotominor.yy24 = new BodyDef;
	yygotominor.yy24->addPredicate(p);
	delete yymsp[-1].minor.yy0;
}
        break;
      case 53: /* aggregate ::= string COLON literal */
{
	yygotominor.yy0 = new Token(*(yymsp[-2].minor.yy0->token));
	std::string s1 = yygotominor.yy0->toString();
	Util::toUpper(s1);
	s1 = s1 + ":" + yymsp[0].minor.yy24->toString(tree->domainList);
	yygotominor.yy0->modifyToken(s1);
	delete yymsp[0].minor.yy24;
}
        break;
      case 54: /* aggregate ::= number COLON literal */
{
	yygotominor.yy0 = new Token(*(yymsp[-2].minor.yy0->token));
	std::string s1 = yygotominor.yy0->toString();
	s1 = s1 + ":" + yymsp[0].minor.yy24->toString(tree->domainList);
	yygotominor.yy0->modifyToken(s1);
	delete yymsp[0].minor.yy24;
}
        break;
      case 55: /* aggregate ::= string COMMA literal COLON literal */
{
	yygotominor.yy0 = new Token(*(yymsp[-4].minor.yy0->token));
	std::string s1 = yygotominor.yy0->toString();
	Util::toUpper(s1);
	s1 = s1 + "," + yymsp[-2].minor.yy24->toString(tree->domainList) + ":" + yymsp[0].minor.yy24->toString(tree->domainList);
	yygotominor.yy0->modifyToken(s1);
}
        break;
      case 56: /* aggregate ::= number COMMA literal COLON literal */
{
	yygotominor.yy0 = new Token(*(yymsp[-4].minor.yy0->token));
	std::string s1 = (*yymsp[-4].minor.yy0).toString();
	// Util::toUpper(s1);
	s1 = s1 + "," + yymsp[-2].minor.yy24->toString(tree->domainList)+ ":" + yymsp[0].minor.yy24->toString(tree->domainList);
	yygotominor.yy0->modifyToken(s1);
}
        break;
      case 57: /* aggregateCum ::= aggregate */
{
	yygotominor.yy0 = new Token(*(yymsp[0].minor.yy0->token));
	delete yymsp[0].minor.yy0;
}
        break;
      case 58: /* aggregateCum ::= aggregateCum SEMI_COLON aggregate */
{
	yygotominor.yy0 = yymsp[-2].minor.yy0;
	yygotominor.yy0->modifyToken(yymsp[-2].minor.yy0->toString() + ";" + yymsp[0].minor.yy0->toString());
	delete yymsp[0].minor.yy0;
}
        break;
      case 59: /* predicate ::= literal DOT */
{
	yygotominor.yy12 = new Predicate;
	*yygotominor.yy12 = yymsp[-1].minor.yy24->getPredicate();
	if(yymsp[-1].minor.yy24->getHasVariables() == false){
		/*Its a special case*/
		yygotominor.yy12->notToBeCompleted();	
	}
	
	auto itr = tree->variables.find(yygotominor.yy12->getVar());
	if(itr != tree->variables.end()){
		itr->setCompleted();
	}

	std::string s1,s2;
	if(tree->outputType == OutputType::OUTPUT_ALCHEMY || tree->outputType == OutputType::OUTPUT_TUFFY){
		cout<<yygotominor.yy12->toString(tree->domainList) + ".\n";
	}

	if(tree->outputType == OutputType::OUTPUT_ASP){
		s2 = yygotominor.yy12->getExtra(tree->variables);

		if(s2.length() > 0){
			s1 = yygotominor.yy12->toString(s1,false);
			s1 += ":-";
			s1 += s2;
			s1 += ".\n";
		}
		else{
			s1 = yygotominor.yy12->toString(s1,true);
		}
			

		
	}

	cout<<s1;

	delete yymsp[-1].minor.yy24;
}
        break;
      case 60: /* predicate ::= number literal */
{
	yygotominor.yy12 = new Predicate;
	*yygotominor.yy12 = yymsp[0].minor.yy24->getPredicate();

	if(yymsp[0].minor.yy24->getHasVariables() == false){
		/*Its a special case*/
		yygotominor.yy12->notToBeCompleted();	
	}
	
	auto itr = tree->variables.find(yygotominor.yy12->getVar());
	if(itr != tree->variables.end()){
		itr->setCompleted();
	}

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY || tree->outputType == OutputType::OUTPUT_TUFFY){
		cout<<yygotominor.yy12->toString(yymsp[-1].minor.yy0->toString()+SPACE, false);
	}
	if(tree->outputType == OutputType::OUTPUT_ROCKIT){
		cout<<yygotominor.yy12->toString(yymsp[-1].minor.yy0->toString()+SPACE, false)<<"\n";	
	}
	if(tree->outputType == OutputType::OUTPUT_ASP){
		std::set<std::string> uniqueSet = tree->findVariables(yygotominor.yy12->toString(tree->domainList));
		std::string uniqueSetStr;
		for(auto itr = uniqueSet.begin(); itr != uniqueSet.end(); ++itr){
			uniqueSetStr += *itr + ",";
		}
		if (uniqueSetStr.length() > 0)
		{
			uniqueSetStr.pop_back();
			uniqueSetStr = "," + uniqueSetStr; 
		}
		std::string temp  = yygotominor.yy12->getExtra(tree->variables);	
		if(temp.length() > 0){
			temp = ", "+ temp;
		}
		
		
		string unsatString = "unsat(" + std::to_string(tree->weak_constraint_counter) + ",0," + std::to_string((int)(std::stof(yymsp[-1].minor.yy0->toString())* 10000)) + uniqueSetStr + ")";
		std::cout << unsatString
					<< " :- "
					<< "not "
					<< yygotominor.yy12->toString(tree->domainList)
					<< temp
					<<LanguageConstants::LINE_END
					<<"\n"; 

		std::cout << yygotominor.yy12->toString(tree->domainList)
					<< " :- "
					<< "not "
					<< unsatString
					<< temp
					<< LanguageConstants::LINE_END
					<< "\n"; 

	
		std::cout   << " :~ "
					<< unsatString
					<< temp
					<< ". "
					<< "["
					<< std::to_string((int)(std::stof(yymsp[-1].minor.yy0->toString())* 10000))
					<<","
					<< tree->weak_constraint_counter
					<< uniqueSetStr
					<< "]"
					<<"\n";

		tree->weak_constraint_counter++; 

	}	
	delete yymsp[0].minor.yy24;
}
        break;
      case 61: /* predicate ::= number NEGATION NEGATION literal */
{
	yygotominor.yy12 = new Predicate;
	*yygotominor.yy12 = yymsp[0].minor.yy24->getPredicate();
	yygotominor.yy12->notToBeCompleted();

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY || tree->outputType == OutputType::OUTPUT_TUFFY){
		tree->statHasDblNeg = true;
		cout<<yygotominor.yy12->toString(yymsp[-3].minor.yy0->toString()+SPACE, false);	
	}
	else if(tree->outputType == OutputType::OUTPUT_ASP){
		// std::string str = yygotominor.yy12->toString(":~ not ", false);
		// std::string temp  = yygotominor.yy12->getExtra(tree->variables);	
		// if(temp.length() > 0)
		// 	str += ",";
		// str += temp;
		// std::string constants = yygotominor.yy12->getExtraConstants();
		// if (constants.length() > 0)
		// {
		// 	constants = "," + constants; 
		// }

		// std::set<std::string> uniqueSet = tree->findVariables(str);
		// std::string uniqueSetStr;
		// for(auto itr = uniqueSet.begin(); itr != uniqueSet.end(); ++itr){
		// 	uniqueSetStr += *itr + ",";
		// }
		// if (uniqueSetStr.length() > 0)
		// {
		// 	uniqueSetStr.pop_back();
		// 	uniqueSetStr = "," + uniqueSetStr; 
		// }

		// str += LanguageConstants::LINE_END;
		// str += " [" + 
		// 		std::to_string((int)(std::stof(yymsp[-3].minor.yy0->toString())* 10000)) + 
		// 		"," + 
		// 		std::to_string(tree->weak_constraint_counter++) + 
		// 		constants + 
		// 		"]\n";
		// cout<<str;
		std::set<std::string> uniqueSet = tree->findVariables(yygotominor.yy12->toString(tree->domainList));
		std::string uniqueSetStr;
		for(auto itr = uniqueSet.begin(); itr != uniqueSet.end(); ++itr){
			uniqueSetStr += *itr + ",";
		}
		if (uniqueSetStr.length() > 0)
		{
			uniqueSetStr.pop_back();
			uniqueSetStr = "," + uniqueSetStr; 
		}
		std::string temp  = yygotominor.yy12->getExtra(tree->variables);	
		if(temp.length() > 0){
			temp = ", "+ temp;
		}
		
		
		string unsatString = "unsat(" + std::to_string(tree->weak_constraint_counter) + ",0," + std::to_string((int)(std::stof(yymsp[-3].minor.yy0->toString())* 10000)) + uniqueSetStr + ")";
		std::cout << unsatString
					<< " :- "
					<< "not "
					<< yygotominor.yy12->toString(tree->domainList)
					<< temp
					<<LanguageConstants::LINE_END
					<<"\n"; 

		std::cout << "not not "
					<< yygotominor.yy12->toString(tree->domainList)
					<< " :- "
					<< "not "
					<< unsatString
					<< temp
					<< LanguageConstants::LINE_END
					<< "\n"; 

	
		std::cout   << " :~ "
					<< unsatString
					<< temp
					<< ". "
					<< "["
					<< std::to_string((int)(std::stof(yymsp[-3].minor.yy0->toString())* 10000))
					<<","
					<< tree->weak_constraint_counter
					<< uniqueSetStr
					<< "]"
					<<"\n";

		tree->weak_constraint_counter++; 
	}
	
	delete yymsp[0].minor.yy24;
}
        break;
      case 62: /* predicate ::= number NEGATION literal */
{
	yygotominor.yy12 = new Predicate;
	*yygotominor.yy12 = yymsp[0].minor.yy24->getPredicate();
	yygotominor.yy12->notToBeCompleted();

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY || tree->outputType == OutputType::OUTPUT_TUFFY){
		cout<<yygotominor.yy12->toString(yymsp[-2].minor.yy0->toString()+SPACE, false);
	}
	else if(tree->outputType == OutputType::OUTPUT_ASP){
		std::string str = yygotominor.yy12->toString(":~ ", false);	

		std::string temp  = yygotominor.yy12->getExtra(tree->variables);	
		if(temp.length() > 0){
			// temp.pop_back();
			temp = ", "+ temp;
		}

		// std::string temp  = yygotominor.yy12->getExtra(tree->variables);	
		// if(temp.length() > 0)
		// 	str += ",";

		std::string constants = yygotominor.yy12->getExtraConstants();
		if (constants.length() > 0){
			constants = "," + constants; 
		}

		std::set<std::string> uniqueSet = tree->findVariables(str);
		std::string uniqueSetStr;
		for(auto itr = uniqueSet.begin(); itr != uniqueSet.end(); ++itr){
			uniqueSetStr += *itr + ",";
		}
		if (uniqueSetStr.length() > 0){
			uniqueSetStr.pop_back();
			uniqueSetStr = "," + uniqueSetStr; 
		}
		



		// str += " [" + 
		// std::to_string((int)(std::stof(yymsp[-2].minor.yy0->toString())* 10000)) + 
		// "," + 
		// std::to_string(tree->weak_constraint_counter++) + 
		// constants + 
		// "]\n";

		string unsatString = "unsat(" + std::to_string(tree->weak_constraint_counter) + ",0," + std::to_string((int)(std::stof(yymsp[-2].minor.yy0->toString())* 10000)) + uniqueSetStr + ")";
		std::cout << unsatString
					<< " :- "
					<< "not not "
					<< yygotominor.yy12->toString(tree->domainList)
					<< temp
					<<LanguageConstants::LINE_END
					<<"\n"; 

		std::cout << yygotominor.yy12->toString(tree->domainList)
					<< " :- "
					<< "not "
					<< unsatString
					<< temp
					<< LanguageConstants::LINE_END
					<< "\n"; 

	
		std::cout   << " :~ "
					<< unsatString
					<< temp
					<< ". "
					<< "["
					<< std::to_string((int)(std::stof(yymsp[-2].minor.yy0->toString())* 10000))
					<<","
					<< tree->weak_constraint_counter
					<< uniqueSetStr
					<< "]"
					<<"\n";

		tree->weak_constraint_counter++; 

		// cout<<str;
	}

	
	delete yymsp[0].minor.yy24;
}
        break;
      case 63: /* predicate ::= NEGATION NEGATION literal DOT */
{
	yygotominor.yy12 = new Predicate;
	*yygotominor.yy12 = yymsp[-1].minor.yy24->getPredicate();
	yygotominor.yy12->notToBeCompleted();
	tree->statHasDblNeg = true;
	std::string s1; 

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY || tree->outputType == OutputType::OUTPUT_TUFFY){
		cout<<yygotominor.yy12->toString(s1, false);
	}
	else if(tree->outputType == OutputType::OUTPUT_ASP){
		cout<<yygotominor.yy12->toString(":- not ", true);		
	}


	
	delete yymsp[-1].minor.yy24;	
}
        break;
      case 64: /* variables ::= variable */
{
	yygotominor.yy91 = new std::vector<std::string*>();	
	yygotominor.yy91->push_back(yymsp[0].minor.yy0->token);
}
        break;
      case 65: /* variables ::= variables COMMA variable */
{
	yygotominor.yy91 = yymsp[-2].minor.yy91;
	yymsp[-2].minor.yy91->push_back(yymsp[0].minor.yy0->token);
}
        break;
      case 66: /* variable ::= string */
      case 67: /* variable ::= number */ yytestcase(yyruleno==67);
      case 68: /* string ::= STRING */ yytestcase(yyruleno==68);
{ yygotominor.yy0=yymsp[0].minor.yy0;}
        break;
      case 69: /* number ::= NUMBER */
{ yygotominor.yy0=yymsp[0].minor.yy0; }
        break;
      case 70: /* domain ::= string EQUAL domains */
{ 
	yygotominor.yy43 = yymsp[0].minor.yy43;
	yymsp[0].minor.yy43->setDomainVar(yymsp[-2].minor.yy0->token);
	tree->domains.insert(*yygotominor.yy43);
	for(auto& v : yygotominor.yy43->getVars()){
		tree->domainList.insert(v);	
	}
	// cout<<yygotominor.yy43->toString(false);
	// delete yygotominor.yy43;
}
        break;
      case 71: /* domains ::= LPAREN variables RPAREN */
{
	yygotominor.yy43 = new Domain();
	yygotominor.yy43->setVars(*yymsp[-1].minor.yy91);
	delete yymsp[-1].minor.yy91;
}
        break;
      case 72: /* decl ::= string LBRACKET variables RBRACKET */
{
	// D = new Variable;
	// std::map<int, Domain> posMap;
	// std::set<Domain>::iterator itr;
	// int i=0;
	// for(auto& v : *yymsp[-1].minor.yy91){
	// 	itr = tree->domains.find(*v);
	// 	if (itr == tree->domains.end()){
	// 		// std::cout<<"Error:Domain:"+ *v +" not found.\n";
	// 		throw syntax_exception("Syntax Error - Domain " + *v + " not found.\n");
	// 	}
	// 	else{
	// 		// itr = tree->domains.find(*v);
			
	// 		posMap[i++] = *itr;
	// 	}
	// }
	// D->setVar(yymsp[-3].minor.yy0->token);
	// D->setPosMap(posMap);
	// delete yymsp[-1].minor.yy91;


	Variable* va = new Variable;
	std::map<int, Domain> posMap;
	std::set<Domain>::iterator itr;
	int i=0;
	for(auto& v : *yymsp[-1].minor.yy91){
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
	delete yymsp[-1].minor.yy91;
	delete va;
}
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
      /* (25) prog ::= prog NEWLINE decl */ yytestcase(yyruleno==25);
      /* (26) prog ::= decl */ yytestcase(yyruleno==26);
      /* (27) prog ::= prog NEWLINE */ yytestcase(yyruleno==27);
      /* (28) prog ::= */ yytestcase(yyruleno==28);
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

    std::cout<<"Giving up.Parser is lost...\n";

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

	if (tree->outputType == OutputType::OUTPUT_ASP)
		std::cout<<("%parsing complete!\n");
	else
    	std::cout<<("//parsing complete!\n");
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

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
#define YYNRULE 73
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
#define YY_ACTTAB_COUNT (372)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   244,   55,  113,  110,  111,   82,   48,   54,   57,  154,
 /*    10 */    83,  136,  107,   34,  112,   75,  121,   93,   64,    2,
 /*    20 */    88,  147,  144,  145,   77,   44,   74,   57,   76,  130,
 /*    30 */   136,   34,   22,  146,   43,  121,   93,   64,    2,   88,
 /*    40 */    84,  104,  159,  164,   85,  108,   84,  105,  159,  163,
 /*    50 */    85,  108,   84,  158,  159,  162,   85,  108,   60,  158,
 /*    60 */   159,   58,   42,  150,  136,  158,   53,   58,   80,  124,
 /*    70 */   136,  158,  158,  141,   92,  124,   75,   58,  158,  141,
 /*    80 */   136,   46,  165,   58,   91,  124,  136,   74,  158,  141,
 /*    90 */   131,  121,   43,   69,  158,  141,  103,  159,   58,  101,
 /*   100 */   160,  136,   11,  137,   58,   68,  124,  136,  158,  158,
 /*   110 */   141,   63,  124,   37,   58,  158,  141,  136,  166,  157,
 /*   120 */    58,   52,  121,  136,   62,  158,  141,   61,  124,  219,
 /*   130 */    38,  158,  141,   12,  155,   58,  219,   81,  136,  159,
 /*   140 */    51,   23,  150,  121,  219,   71,  158,   65,   10,  170,
 /*   150 */   158,    4,  100,   97,  166,    1,   96,  100,   97,  166,
 /*   160 */    18,   47,   79,   40,  148,  136,   13,   38,   41,  166,
 /*   170 */   157,   33,   58,  158,  139,  136,   78,   30,  159,   58,
 /*   180 */   142,  150,  136,  158,  141,   58,   43,   70,  136,  158,
 /*   190 */   158,  141,    9,  122,   26,   58,  158,  141,  136,   79,
 /*   200 */    96,  109,  136,   90,   20,   27,  158,  141,   36,   79,
 /*   210 */   158,  135,  136,  166,  157,   79,  127,  102,  136,   79,
 /*   220 */   158,   99,  136,  100,   97,   79,  158,  134,  136,   79,
 /*   230 */   158,  133,  136,   75,   82,   31,  158,   98,  153,   83,
 /*   240 */   158,  132,  169,   86,   74,   79,   73,  130,  136,   79,
 /*   250 */    32,   89,  136,   59,   15,  159,  158,   94,  150,   72,
 /*   260 */   158,   87,  136,   95,   72,   96,  158,  136,   82,   21,
 /*   270 */   158,  140,  152,   83,   79,  158,   66,  136,  166,  157,
 /*   280 */   159,  159,   25,  106,  138,  158,   67,   35,    7,   19,
 /*   290 */    28,  158,  158,   43,   24,  114,  166,  157,  166,  157,
 /*   300 */    17,  166,  157,  166,  157,   29,  129,   49,    8,  143,
 /*   310 */   208,    6,  168,   86,   34,   16,   37,  208,   15,   17,
 /*   320 */   213,  212,  123,  211,    5,   17,   50,  213,  212,   43,
 /*   330 */   211,   14,   17,  120,  119,   45,   56,  117,  167,   86,
 /*   340 */    17,  118,   39,  115,    3,  245,  126,  116,  161,  166,
 /*   350 */   245,  166,  166,  157,  245,  245,  245,  245,  166,  245,
 /*   360 */   245,  156,  245,  245,  245,  151,  245,  149,  125,  245,
 /*   370 */   128,  126,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    25,   26,   27,   28,   29,   33,    2,   18,   33,   37,
 /*    10 */    38,   36,   16,    9,   39,   33,   41,   13,   43,   44,
 /*    20 */    45,   27,   28,   29,    2,    2,   44,   33,   46,   47,
 /*    30 */    36,    9,    9,   39,    3,   41,   13,   43,   44,   45,
 /*    40 */    31,   10,   33,   34,   35,   36,   31,   18,   33,   34,
 /*    50 */    35,   36,   31,   44,   33,   34,   35,   36,   31,   44,
 /*    60 */    33,   33,   16,   36,   36,   44,   18,   33,   40,   41,
 /*    70 */    36,   44,   44,   45,   40,   41,   33,   33,   44,   45,
 /*    80 */    36,   15,   16,   33,   40,   41,   36,   44,   44,   45,
 /*    90 */    47,   41,    3,   43,   44,   45,   18,   33,   33,   10,
 /*   100 */    36,   36,    6,    5,   33,   40,   41,   36,   44,   44,
 /*   110 */    45,   40,   41,   15,   33,   44,   45,   36,   22,   23,
 /*   120 */    33,   18,   41,   36,   43,   44,   45,   40,   41,    1,
 /*   130 */     2,   44,   45,   15,   16,   33,    8,   31,   36,   33,
 /*   140 */    18,    4,   36,   41,   16,   43,   44,   45,    1,    0,
 /*   150 */    44,    4,   20,   21,   22,    6,    9,   20,   21,   22,
 /*   160 */    13,   12,   33,   15,   16,   36,   17,    2,   19,   22,
 /*   170 */    23,    4,   33,   44,   45,   36,   31,   18,   33,   33,
 /*   180 */    41,   36,   36,   44,   45,   33,    3,   41,   36,   44,
 /*   190 */    44,   45,    1,   41,    4,   33,   44,   45,   36,   33,
 /*   200 */     9,   18,   36,   41,   13,   18,   44,   45,    9,   33,
 /*   210 */    44,   45,   36,   22,   23,   33,   10,   18,   36,   33,
 /*   220 */    44,   45,   36,   20,   21,   33,   44,   45,   36,   33,
 /*   230 */    44,   45,   36,   33,   33,    3,   44,   45,   37,   38,
 /*   240 */    44,   45,   32,   33,   44,   33,   46,   47,   36,   33,
 /*   250 */    18,    5,   36,   31,    8,   33,   44,   45,   36,   33,
 /*   260 */    44,   45,   36,   13,   33,    9,   44,   36,   33,   13,
 /*   270 */    44,   45,   37,   38,   33,   44,   45,   36,   22,   23,
 /*   280 */    33,   33,   13,   36,   36,   44,   45,   13,    9,   13,
 /*   290 */     3,   44,   44,    3,   13,    5,   22,   23,   22,   23,
 /*   300 */     7,   22,   23,   22,   23,   18,    5,    2,    1,   16,
 /*   310 */     1,    1,   32,   33,    9,    8,   15,    8,    8,    7,
 /*   320 */     1,    1,   10,    1,    1,    7,    2,    8,    8,    3,
 /*   330 */     8,    8,    7,   16,   16,    6,   10,   16,   32,   33,
 /*   340 */     7,   16,    6,   30,    1,   48,   33,   16,   33,   22,
 /*   350 */    48,   22,   22,   23,   48,   48,   48,   48,   22,   48,
 /*   360 */    48,   33,   48,   48,   48,   33,   48,   33,   33,   48,
 /*   370 */    33,   33,
};
#define YY_SHIFT_USE_DFLT (-12)
#define YY_SHIFT_COUNT (109)
#define YY_SHIFT_MIN   (-11)
#define YY_SHIFT_MAX   (343)
static const short yy_shift_ofst[] = {
 /*     0 */   147,  147,  191,  256,  256,  256,  256,  256,  256,  256,
 /*    10 */   256,   96,   96,   96,  256,  256,  256,  256,  281,  279,
 /*    20 */   276,  274,  330,  330,  330,  330,  330,  330,  330,  330,
 /*    30 */   330,  330,  330,  330,  330,  330,  330,  330,  330,  336,
 /*    40 */   336,  336,  330,  330,  137,  329,  329,  329,  132,  132,
 /*    50 */   327,  327,  327,  327,  327,  149,  128,   23,    4,  326,
 /*    60 */   290,  325,  246,  318,  323,  322,  320,  319,  312,  310,
 /*    70 */   309,  307,  305,  301,  287,  232,   98,  203,   89,   22,
 /*    80 */   293,   31,  199,  148,  183,  118,   66,  331,  321,  343,
 /*    90 */   317,  333,  333,  324,  206,  269,  250,  190,  187,  159,
 /*   100 */   167,  165,  122,  103,   78,   48,   29,   46,   -4,  -11,
};
#define YY_REDUCE_USE_DFLT (-29)
#define YY_REDUCE_COUNT (54)
#define YY_REDUCE_MIN   (-28)
#define YY_REDUCE_MAX   (338)
static const short yy_reduce_ofst[] = {
 /*     0 */   -25,   -6,  102,   87,   81,   71,   65,   50,   44,   34,
 /*    10 */    28,   21,   15,    9,  162,  152,  146,  139,  226,  241,
 /*    20 */   231,  226,  222,   27,  216,  212,  200,  196,  192,  186,
 /*    30 */   182,  176,  166,  -18,  145,  129,  106,   43,  248,  235,
 /*    40 */   201,  -28,  247,   64,  313,  306,  280,  210,  338,  337,
 /*    50 */   335,  334,  332,  328,  315,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   198,  197,  237,  243,  243,  243,  243,  243,  243,  243,
 /*    10 */   243,  243,  243,  243,  243,  243,  243,  243,  243,  243,
 /*    20 */   243,  243,  243,  243,  243,  243,  243,  243,  243,  243,
 /*    30 */   243,  243,  243,  243,  243,  243,  243,  243,  243,  243,
 /*    40 */   243,  243,  243,  243,  243,  243,  243,  243,  243,  243,
 /*    50 */   243,  243,  243,  243,  243,  243,  242,  236,  236,  243,
 /*    60 */   243,  243,  243,  243,  243,  230,  232,  231,  243,  243,
 /*    70 */   202,  243,  236,  243,  243,  243,  243,  243,  243,  236,
 /*    80 */   243,  243,  187,  243,  243,  243,  243,  213,  211,  243,
 /*    90 */   208,  204,  200,  243,  243,  243,  243,  243,  243,  243,
 /*   100 */   243,  219,  243,  243,  186,  243,  243,  243,  234,  243,
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
#line 125 "MVSMParserGrammar.y"
{
	std::string str = yymsp[-2].minor.yy0->toString();
	auto it = tree->domainNamesList.find(str);
	if(it != tree->domainNamesList.end())
		throw syntax_exception("Redeclaration of sort "+yymsp[-2].minor.yy0->toString()+"\n");
	else
		tree->domainNamesList.insert(yymsp[-2].minor.yy0->toString());
}
#line 991 "MVSMParserGrammar.c"
        break;
      case 4: /* sortdecl ::= string DOT */
#line 136 "MVSMParserGrammar.y"
{
	std::string str = yymsp[-1].minor.yy0->toString();
	auto it = tree->domainNamesList.find(str);
	if(it != tree->domainNamesList.end())
		throw syntax_exception("Redeclaration of sort "+yymsp[-1].minor.yy0->toString()+"\n");
	else
		tree->domainNamesList.insert(str);	
}
#line 1003 "MVSMParserGrammar.c"
        break;
      case 9: /* object ::= variables COLON COLON string */
#line 153 "MVSMParserGrammar.y"
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
#line 1032 "MVSMParserGrammar.c"
        break;
      case 10: /* object ::= variable DOT DOT variable COLON COLON string */
#line 179 "MVSMParserGrammar.y"
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
#line 1058 "MVSMParserGrammar.c"
        break;
      case 15: /* constant ::= string LBRACKET variables RBRACKET COLON COLON string */
#line 210 "MVSMParserGrammar.y"
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
#line 1101 "MVSMParserGrammar.c"
        break;
      case 16: /* constant ::= string LBRACKET variables RBRACKET */
#line 250 "MVSMParserGrammar.y"
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
#line 1130 "MVSMParserGrammar.c"
        break;
      case 17: /* constant ::= string */
#line 276 "MVSMParserGrammar.y"
{
	Variable* va = new Variable;
	va->setVar(yymsp[0].minor.yy0->toString());
	tree->variables.insert(*va);
	/*for ASP output we do not print constants */
	if(tree->outputType != OutputType::OUTPUT_ASP)
		cout<<va->toString()<<"\n";
	
	delete va;	
}
#line 1144 "MVSMParserGrammar.c"
        break;
      case 18: /* constant ::= string COLON COLON string */
#line 287 "MVSMParserGrammar.y"
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
#line 1173 "MVSMParserGrammar.c"
        break;
      case 19: /* prog ::= prog NEWLINE predicate */
#line 314 "MVSMParserGrammar.y"
{ 
	if(yymsp[0].minor.yy12->needsToBeCompleted()){	
		FactCompletion f(*yymsp[0].minor.yy12);
		tree->facts.insert(std::pair<std::string,FactCompletion>(f.getHead().getVar(),f)); 
	}

			
	delete yymsp[0].minor.yy12;
}
#line 1186 "MVSMParserGrammar.c"
        break;
      case 20: /* prog ::= predicate */
#line 324 "MVSMParserGrammar.y"
{ 
	if(yymsp[0].minor.yy12->needsToBeCompleted()){
		FactCompletion f(*yymsp[0].minor.yy12);
		tree->facts.insert(std::pair<std::string,FactCompletion>(f.getHead().getVar(),f)); 	
	}
	delete yymsp[0].minor.yy12;
}
#line 1197 "MVSMParserGrammar.c"
        break;
      case 21: /* prog ::= prog NEWLINE rule */
      case 22: /* prog ::= rule */ yytestcase(yyruleno==22);
#line 332 "MVSMParserGrammar.y"
{
	if((yymsp[0].minor.yy81->isHeadTop == false) && (yymsp[0].minor.yy81->toBeCompleted == true))
		tree->rules.insert(std::pair<std::string,RuleCompletion>(yymsp[0].minor.yy81->getHead().getVar(),*yymsp[0].minor.yy81));
	delete yymsp[0].minor.yy81;
}
#line 1207 "MVSMParserGrammar.c"
        break;
      case 23: /* prog ::= prog NEWLINE domain */
      case 24: /* prog ::= domain */ yytestcase(yyruleno==24);
#line 347 "MVSMParserGrammar.y"
{ 
	tree->domains.insert(*yymsp[0].minor.yy43); 
	tree->domainNamesList.insert(yymsp[0].minor.yy43->getDomainVar());
	for(auto& v : yymsp[0].minor.yy43->getVars()){
		tree->domainList.insert(v);	
	}
	cout<<yymsp[0].minor.yy43->toString(false);
	delete yymsp[0].minor.yy43;
}
#line 1221 "MVSMParserGrammar.c"
        break;
      case 29: /* rule ::= REVERSE_IMPLICATION body DOT */
#line 390 "MVSMParserGrammar.y"
{
	yygotominor.yy81 = new RuleCompletion;
	yygotominor.yy81->isHeadTop = true;
	
	if(tree->outputType != OutputType::OUTPUT_ASP){
		std::cout<<"("
					<<yymsp[-1].minor.yy1->toNNFString()
					<<")"
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
#line 1244 "MVSMParserGrammar.c"
        break;
      case 30: /* rule ::= number REVERSE_IMPLICATION body */
#line 411 "MVSMParserGrammar.y"
{
	yygotominor.yy81 = new RuleCompletion;
	yygotominor.yy81->isHeadTop = true;
	
	if(tree->outputType != OutputType::OUTPUT_ASP){
		std::cout<<yymsp[-2].minor.yy0->toString()<<SPACE
					<<"("
					<<yymsp[0].minor.yy1->toNNFString()
					<<")"
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
#line 1289 "MVSMParserGrammar.c"
        break;
      case 31: /* rule ::= head DISJUNCTION bodydef DOT */
#line 456 "MVSMParserGrammar.y"
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
#line 1327 "MVSMParserGrammar.c"
        break;
      case 32: /* rule ::= number head DISJUNCTION bodydef */
#line 494 "MVSMParserGrammar.y"
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
#line 1385 "MVSMParserGrammar.c"
        break;
      case 33: /* rule ::= head REVERSE_IMPLICATION body DOT */
#line 554 "MVSMParserGrammar.y"
{
	yygotominor.yy81 = new RuleCompletion;

	if (yymsp[-3].minor.yy65->getDisjunction()){
		// RULE_COMPLETION_HEAD_DIS_BODY_TOP(yymsp[-3].minor.yy65,yymsp[-1].minor.yy1)
		yygotominor.yy81->isHeadTop = true;
		RuleCompletion_HD_BC(yymsp[-3].minor.yy65,yymsp[-1].minor.yy1,true,tree);
		if(tree->outputType == OutputType::OUTPUT_ALCHEMY)
			std::cout<<yymsp[-1].minor.yy1->toString()
					<<" => "
					<<yymsp[-3].minor.yy65->toString()
					<<LanguageConstants::LINE_END
					<<"\n";
		if(tree->outputType == OutputType::OUTPUT_ASP)
			tree->printASPRuleHB(yymsp[-3].minor.yy65,yymsp[-1].minor.yy1);
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
		if(tree->outputType == OutputType::OUTPUT_ALCHEMY)
			std::cout<<yymsp[-1].minor.yy1->toString()
					<<" => "
					<<yymsp[-3].minor.yy65->toString()
					<<LanguageConstants::LINE_END
					<<"\n";
		if(tree->outputType == OutputType::OUTPUT_ASP)
			tree->printASPRuleHB(yymsp[-3].minor.yy65,yymsp[-1].minor.yy1);
	}
	delete yymsp[-1].minor.yy1;
	delete yymsp[-3].minor.yy65;
}
#line 1426 "MVSMParserGrammar.c"
        break;
      case 34: /* rule ::= number head REVERSE_IMPLICATION body */
#line 595 "MVSMParserGrammar.y"
{
	// RULE_COMPLETION_BH(yymsp[0].minor.yy1,yymsp[-2].minor.yy65);
	// yygotominor.yy81 = new RuleCompletion(yymsp[-2].minor.yy65->getPredicate(),predList, resultMap, varMap);
	try{
		yygotominor.yy81 = RuleCompletion_BH(yymsp[0].minor.yy1,yymsp[-2].minor.yy65,tree);
	}
	catch(const std::out_of_range& e){
			throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY)
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


	delete yymsp[0].minor.yy1;
	delete yymsp[-2].minor.yy65;
}
#line 1500 "MVSMParserGrammar.c"
        break;
      case 35: /* rule ::= number NEGATION NEGATION LBRACKET head REVERSE_IMPLICATION body RBRACKET */
#line 669 "MVSMParserGrammar.y"
{
	yygotominor.yy81 = new RuleCompletion;
	yygotominor.yy81->isHeadTop = true;	
	tree->statHasDblNeg = true;

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY)
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
	
	delete yymsp[-1].minor.yy1;
	delete yymsp[-3].minor.yy65;
}
#line 1529 "MVSMParserGrammar.c"
        break;
      case 36: /* rule ::= LPAREN head RPAREN REVERSE_IMPLICATION body DOT */
#line 695 "MVSMParserGrammar.y"
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

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY)
		std::cout<<COMMENT<<yymsp[-1].minor.yy1->toString()<<" => "<<yymsp[-4].minor.yy65->toString()<<"\n";
	if(tree->outputType == OutputType::OUTPUT_ASP)
		std::cout<<yymsp[-4].minor.yy65->toString()<<" :- "<<yymsp[-1].minor.yy1->toString()<<LanguageConstants::LINE_END<<"\n";
	delete yymsp[-1].minor.yy1;
	delete yymsp[-4].minor.yy65;
}
#line 1555 "MVSMParserGrammar.c"
        break;
      case 37: /* body ::= body CONJUNCTION bodydef */
#line 719 "MVSMParserGrammar.y"
{
	yygotominor.yy1 = yymsp[-2].minor.yy1;
	yymsp[-2].minor.yy1->addPredicate(yymsp[0].minor.yy24->getPredicate());
	yygotominor.yy1->appendStr(yymsp[0].minor.yy24->getPredicate(),false,false,true,tree->domainList);
	delete yymsp[0].minor.yy24;
}
#line 1565 "MVSMParserGrammar.c"
        break;
      case 38: /* head ::= head DISJUNCTION bodydef */
#line 726 "MVSMParserGrammar.y"
{
	yygotominor.yy65 = yymsp[-2].minor.yy65;
	yymsp[-2].minor.yy65->addPredicate(yymsp[0].minor.yy24->getPredicate());
	yygotominor.yy65->appendStr(yymsp[0].minor.yy24->getPredicate().toString(tree->domainList),false,true,false);
	yygotominor.yy65->setDisjunction(true);
	delete yymsp[0].minor.yy24;
}
#line 1576 "MVSMParserGrammar.c"
        break;
      case 39: /* head ::= bodydef */
#line 734 "MVSMParserGrammar.y"
{
	yygotominor.yy65 = new Head(yymsp[0].minor.yy24->getPredicate());
	// yygotominor.yy65->addPredicate(yymsp[0].minor.yy24->getPredicate());
	yygotominor.yy65->appendStr(yymsp[0].minor.yy24->getPredicate().toString(tree->domainList),false,false,false);
	delete yymsp[0].minor.yy24;
}
#line 1586 "MVSMParserGrammar.c"
        break;
      case 40: /* body ::= bodydef */
#line 741 "MVSMParserGrammar.y"
{
	yygotominor.yy1 = new Body;
	Predicate p = yymsp[0].minor.yy24->getPredicate();
	yygotominor.yy1->addPredicate(p);
	yygotominor.yy1->appendStr(p,false,false,false,tree->domainList);
	delete yymsp[0].minor.yy24;
}
#line 1597 "MVSMParserGrammar.c"
        break;
      case 41: /* bodydef ::= literal */
#line 752 "MVSMParserGrammar.y"
{	
	yygotominor.yy24 = yymsp[0].minor.yy24;
}
#line 1604 "MVSMParserGrammar.c"
        break;
      case 42: /* bodydef ::= NEGATION literal */
#line 757 "MVSMParserGrammar.y"
{	
	yygotominor.yy24 = yymsp[0].minor.yy24;
	Predicate p = yygotominor.yy24->getPredicate();
	p.setSingleNegation(true);
	yygotominor.yy24->addPredicate(p);
	// yygotominor.yy24->getPredicate().setSingleNegation(true);
}
#line 1615 "MVSMParserGrammar.c"
        break;
      case 43: /* bodydef ::= NEGATION NEGATION literal */
#line 766 "MVSMParserGrammar.y"
{	
	yygotominor.yy24 = yymsp[0].minor.yy24;
	tree->statHasDblNeg = true;
	yygotominor.yy24->getPredicate().setDoubleNegation(true);
}
#line 1624 "MVSMParserGrammar.c"
        break;
      case 44: /* bodydef ::= LBRACKET NEGATION NEGATION literal RBRACKET */
#line 775 "MVSMParserGrammar.y"
{	
	yygotominor.yy24 = yymsp[-1].minor.yy24;
	tree->statHasDblNeg = true;
	yygotominor.yy24->getPredicate().setDoubleNegation(true);
}
#line 1633 "MVSMParserGrammar.c"
        break;
      case 45: /* bodydef ::= string EQUAL string */
#line 782 "MVSMParserGrammar.y"
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
#line 1668 "MVSMParserGrammar.c"
        break;
      case 46: /* bodydef ::= NEGATION string EQUAL string */
#line 815 "MVSMParserGrammar.y"
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
#line 1687 "MVSMParserGrammar.c"
        break;
      case 47: /* bodydef ::= string NEGATION EQUAL string */
#line 831 "MVSMParserGrammar.y"
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
#line 1706 "MVSMParserGrammar.c"
        break;
      case 48: /* literal ::= string LBRACKET variables RBRACKET EQUAL variable */
#line 850 "MVSMParserGrammar.y"
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
#line 1731 "MVSMParserGrammar.c"
        break;
      case 49: /* literal ::= string LBRACKET variables RBRACKET */
#line 872 "MVSMParserGrammar.y"
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
#line 1755 "MVSMParserGrammar.c"
        break;
      case 50: /* literal ::= variable */
#line 893 "MVSMParserGrammar.y"
{
	Predicate p(yymsp[0].minor.yy0->token);
	auto itr = tree->variables.find(yymsp[0].minor.yy0->toString());
	yygotominor.yy24 = new BodyDef;
	/*Special Case: BodyDef does not have variables*/
	yygotominor.yy24->setHasVariables();
	yygotominor.yy24->addPredicate(p);
}
#line 1767 "MVSMParserGrammar.c"
        break;
      case 51: /* literal ::= string EQUAL COUNT LPAREN aggregateCum RPAREN */
#line 902 "MVSMParserGrammar.y"
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
#line 1781 "MVSMParserGrammar.c"
        break;
      case 52: /* literal ::= string EQUAL SUM LPAREN aggregateCum RPAREN */
#line 913 "MVSMParserGrammar.y"
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
#line 1795 "MVSMParserGrammar.c"
        break;
      case 53: /* aggregate ::= string COLON literal */
#line 925 "MVSMParserGrammar.y"
{
	yygotominor.yy0 = new Token(*(yymsp[-2].minor.yy0->token));
	std::string s1 = yygotominor.yy0->toString();
	Util::toUpper(s1);
	s1 = s1 + ":" + yymsp[0].minor.yy24->toString(tree->domainList);
	yygotominor.yy0->modifyToken(s1);
	delete yymsp[0].minor.yy24;
}
#line 1807 "MVSMParserGrammar.c"
        break;
      case 54: /* aggregate ::= number COLON literal */
#line 934 "MVSMParserGrammar.y"
{
	yygotominor.yy0 = new Token(*(yymsp[-2].minor.yy0->token));
	std::string s1 = yygotominor.yy0->toString();
	s1 = s1 + ":" + yymsp[0].minor.yy24->toString(tree->domainList);
	yygotominor.yy0->modifyToken(s1);
	delete yymsp[0].minor.yy24;
}
#line 1818 "MVSMParserGrammar.c"
        break;
      case 55: /* aggregate ::= string COMMA literal COLON literal */
#line 942 "MVSMParserGrammar.y"
{
	yygotominor.yy0 = new Token(*(yymsp[-4].minor.yy0->token));
	std::string s1 = yygotominor.yy0->toString();
	Util::toUpper(s1);
	s1 = s1 + "," + yymsp[-2].minor.yy24->toString(tree->domainList) + ":" + yymsp[0].minor.yy24->toString(tree->domainList);
	yygotominor.yy0->modifyToken(s1);
}
#line 1829 "MVSMParserGrammar.c"
        break;
      case 56: /* aggregate ::= number COMMA literal COLON literal */
#line 951 "MVSMParserGrammar.y"
{
	yygotominor.yy0 = new Token(*(yymsp[-4].minor.yy0->token));
	std::string s1 = (*yymsp[-4].minor.yy0).toString();
	// Util::toUpper(s1);
	s1 = s1 + "," + yymsp[-2].minor.yy24->toString(tree->domainList)+ ":" + yymsp[0].minor.yy24->toString(tree->domainList);
	yygotominor.yy0->modifyToken(s1);
}
#line 1840 "MVSMParserGrammar.c"
        break;
      case 57: /* aggregateCum ::= aggregate */
#line 959 "MVSMParserGrammar.y"
{
	yygotominor.yy0 = new Token(*(yymsp[0].minor.yy0->token));
	delete yymsp[0].minor.yy0;
}
#line 1848 "MVSMParserGrammar.c"
        break;
      case 58: /* aggregateCum ::= aggregateCum SEMI_COLON aggregate */
#line 964 "MVSMParserGrammar.y"
{
	yygotominor.yy0 = yymsp[-2].minor.yy0;
	yygotominor.yy0->modifyToken(yymsp[-2].minor.yy0->toString() + ";" + yymsp[0].minor.yy0->toString());
	delete yymsp[0].minor.yy0;
}
#line 1857 "MVSMParserGrammar.c"
        break;
      case 59: /* predicate ::= literal DOT */
#line 971 "MVSMParserGrammar.y"
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
	if(tree->outputType == OutputType::OUTPUT_ALCHEMY){
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
#line 1900 "MVSMParserGrammar.c"
        break;
      case 60: /* predicate ::= number literal */
#line 1011 "MVSMParserGrammar.y"
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

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY){
		cout<<yygotominor.yy12->toString(yymsp[-1].minor.yy0->toString()+SPACE, false);
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
#line 1973 "MVSMParserGrammar.c"
        break;
      case 61: /* predicate ::= number NEGATION NEGATION literal */
#line 1081 "MVSMParserGrammar.y"
{
	yygotominor.yy12 = new Predicate;
	*yygotominor.yy12 = yymsp[0].minor.yy24->getPredicate();
	yygotominor.yy12->notToBeCompleted();

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY){
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
#line 2069 "MVSMParserGrammar.c"
        break;
      case 62: /* predicate ::= number NEGATION literal */
#line 1174 "MVSMParserGrammar.y"
{
	yygotominor.yy12 = new Predicate;
	*yygotominor.yy12 = yymsp[0].minor.yy24->getPredicate();
	yygotominor.yy12->notToBeCompleted();

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY){
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
#line 2157 "MVSMParserGrammar.c"
        break;
      case 63: /* predicate ::= NEGATION NEGATION literal DOT */
#line 1259 "MVSMParserGrammar.y"
{
	yygotominor.yy12 = new Predicate;
	*yygotominor.yy12 = yymsp[-1].minor.yy24->getPredicate();
	yygotominor.yy12->notToBeCompleted();
	tree->statHasDblNeg = true;
	std::string s1; 

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY){
		cout<<yygotominor.yy12->toString(s1, false);
	}
	else if(tree->outputType == OutputType::OUTPUT_ASP){
		cout<<yygotominor.yy12->toString(":- not ", true);		
	}


	
	delete yymsp[-1].minor.yy24;	
}
#line 2179 "MVSMParserGrammar.c"
        break;
      case 64: /* variables ::= variable */
#line 1279 "MVSMParserGrammar.y"
{
	yygotominor.yy91 = new std::vector<std::string*>();	
	yygotominor.yy91->push_back(yymsp[0].minor.yy0->token);
}
#line 2187 "MVSMParserGrammar.c"
        break;
      case 65: /* variables ::= variables COMMA variable */
#line 1284 "MVSMParserGrammar.y"
{
	yygotominor.yy91 = yymsp[-2].minor.yy91;
	yymsp[-2].minor.yy91->push_back(yymsp[0].minor.yy0->token);
}
#line 2195 "MVSMParserGrammar.c"
        break;
      case 66: /* variable ::= string */
      case 67: /* variable ::= number */ yytestcase(yyruleno==67);
      case 68: /* string ::= STRING */ yytestcase(yyruleno==68);
#line 1289 "MVSMParserGrammar.y"
{ yygotominor.yy0=yymsp[0].minor.yy0;}
#line 2202 "MVSMParserGrammar.c"
        break;
      case 69: /* number ::= NUMBER */
#line 1297 "MVSMParserGrammar.y"
{ yygotominor.yy0=yymsp[0].minor.yy0; }
#line 2207 "MVSMParserGrammar.c"
        break;
      case 70: /* domain ::= string EQUAL domains */
#line 1300 "MVSMParserGrammar.y"
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
#line 2221 "MVSMParserGrammar.c"
        break;
      case 71: /* domains ::= LPAREN variables RPAREN */
#line 1313 "MVSMParserGrammar.y"
{
	yygotominor.yy43 = new Domain();
	yygotominor.yy43->setVars(*yymsp[-1].minor.yy91);
	delete yymsp[-1].minor.yy91;
}
#line 2230 "MVSMParserGrammar.c"
        break;
      case 72: /* decl ::= string LBRACKET variables RBRACKET */
#line 1321 "MVSMParserGrammar.y"
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
#line 2280 "MVSMParserGrammar.c"
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
#line 66 "MVSMParserGrammar.y"

    std::cout<<"Giving up.Parser is lost...\n";

#line 2347 "MVSMParserGrammar.c"
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
    
#line 2377 "MVSMParserGrammar.c"
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
#line 2402 "MVSMParserGrammar.c"
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

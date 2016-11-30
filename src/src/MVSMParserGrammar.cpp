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

#line 75 "MVSMParserGrammar.c"
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
#define MVSM_PARSE_TOKEN_SUM                            21
#define MVSM_PARSE_TOKEN_STRING                         22
#define MVSM_PARSE_TOKEN_NUMBER                         23
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
#define YYNOCODE 47
#define YYACTIONTYPE unsigned short int
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
#define YYNSTATE             103
#define YYNRULE              66
#define YY_MAX_SHIFT         102
#define YY_MIN_SHIFTREDUCE   157
#define YY_MAX_SHIFTREDUCE   222
#define YY_MIN_REDUCE        223
#define YY_MAX_REDUCE        288
#define YY_ERROR_ACTION      289
#define YY_ACCEPT_ACTION     290
#define YY_NO_ACTION         291
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
#define YY_ACTTAB_COUNT (335)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   290,   52,  177,   93,   90,  221,   53,  198,   71,  203,
 /*    10 */   219,  199,  179,  217,  192,  176,   57,    2,   81,   53,
 /*    20 */    10,  220,  203,    4,   68,  178,  221,  192,   89,   57,
 /*    30 */     2,   81,   18,  221,  222,   67,    5,   66,  210,  160,
 /*    40 */    79,  221,  222,   14,   53,   11,   77,  203,  219,  165,
 /*    50 */    78,  101,  192,  200,   64,  220,   58,   53,  175,  220,
 /*    60 */   203,  221,  222,   53,   54,  193,  203,   68,  220,  194,
 /*    70 */   216,  192,  205,   55,  220,  194,   53,    7,   67,  203,
 /*    80 */    69,  210,   35,   56,  193,   37,   53,  220,  194,  203,
 /*    90 */   221,  222,   53,   61,  193,  203,   82,  220,  194,   15,
 /*   100 */   192,  221,   62,  220,  194,   53,  172,   53,  203,  167,
 /*   110 */   203,   68,   84,  193,   85,  193,  220,  194,  220,  194,
 /*   120 */    53,   17,   67,  203,  188,  211,  166,   73,  193,  159,
 /*   130 */    79,  220,  194,   77,  212,  219,  163,   78,  101,    9,
 /*   140 */    77,   45,  219,  162,   78,  101,  220,   89,   32,  158,
 /*   150 */    79,   20,   86,  220,   26,   53,    3,   74,  203,  219,
 /*   160 */   221,  222,  217,   83,   42,   53,  220,  194,  203,   27,
 /*   170 */   220,   53,  184,  191,  203,   17,  220,  194,   53,   63,
 /*   180 */   221,  203,  220,  194,   89,   22,  190,  223,   21,  220,
 /*   190 */   194,  197,   17,    1,  221,  222,   23,  221,  222,   44,
 /*   200 */    65,  189,  260,  203,   13,   72,   39,  261,  203,  260,
 /*   210 */    65,  220,  195,  203,  261,   72,  220,   60,  203,   29,
 /*   220 */    72,  220,   59,  203,   47,   72,  220,   80,  203,   41,
 /*   230 */    72,  220,   87,  203,   30,   72,  220,  209,  203,  204,
 /*   240 */    72,  220,   91,  203,  102,   72,  220,  207,  203,   35,
 /*   250 */    72,  220,  208,  203,   19,   72,  220,   92,  203,   33,
 /*   260 */    88,  220,  206,  221,  222,  262,  220,  196,  221,  222,
 /*   270 */   219,   24,  262,  201,   75,   31,    6,   25,  171,   76,
 /*   280 */    75,  220,   75,   15,  169,   76,  168,   76,  219,  219,
 /*   290 */   257,   99,  218,   17,    8,   28,   46,  257,   36,  220,
 /*   300 */   220,   16,  186,   32,   93,   90,   41,   70,   17,   41,
 /*   310 */    48,   34,  225,   94,   32,   49,   97,  182,   96,  225,
 /*   320 */    95,  225,   38,  170,   12,  164,   50,   43,  161,   98,
 /*   330 */    40,  100,  225,  225,   51,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    25,   26,   27,   20,   21,   22,   31,   31,   29,   34,
 /*    10 */    31,   31,   37,   34,   39,   27,   41,   42,   43,   31,
 /*    20 */     1,   42,   34,    4,   31,   37,   22,   39,    9,   41,
 /*    30 */    42,   43,   13,   22,   23,   42,    1,   44,   45,   30,
 /*    40 */    31,   22,   23,    8,   31,    6,   29,   34,   31,   32,
 /*    50 */    33,   34,   39,   31,   41,   42,   43,   31,   31,   42,
 /*    60 */    34,   22,   23,   31,   38,   39,   34,   31,   42,   43,
 /*    70 */    16,   39,    5,   41,   42,   43,   31,    9,   42,   34,
 /*    80 */    44,   45,   15,   38,   39,    6,   31,   42,   43,   34,
 /*    90 */    22,   23,   31,   38,   39,   34,    5,   42,   43,    8,
 /*   100 */    39,   22,   41,   42,   43,   31,   31,   31,   34,   31,
 /*   110 */    34,   31,   38,   39,   38,   39,   42,   43,   42,   43,
 /*   120 */    31,    7,   42,   34,   10,   45,   31,   38,   39,   30,
 /*   130 */    31,   42,   43,   29,   16,   31,   32,   33,   34,    1,
 /*   140 */    29,    2,   31,   32,   33,   34,   42,    9,    9,   30,
 /*   150 */    31,   13,   13,   42,    3,   31,    1,   29,   34,   31,
 /*   160 */    22,   23,   34,   39,    6,   31,   42,   43,   34,   18,
 /*   170 */    42,   31,   16,   39,   34,    7,   42,   43,   31,   39,
 /*   180 */    22,   34,   42,   43,    9,   13,   39,    0,   13,   42,
 /*   190 */    43,   10,    7,    6,   22,   23,   13,   22,   23,   12,
 /*   200 */    31,   16,    1,   34,   17,   31,   19,    1,   34,    8,
 /*   210 */    31,   42,   43,   34,    8,   31,   42,   43,   34,    3,
 /*   220 */    31,   42,   43,   34,    2,   31,   42,   43,   34,    3,
 /*   230 */    31,   42,   43,   34,   18,   31,   42,   43,   34,    5,
 /*   240 */    31,   42,   43,   34,   18,   31,   42,   43,   34,   15,
 /*   250 */    31,   42,   43,   34,   13,   31,   42,   43,   34,   13,
 /*   260 */    13,   42,   43,   22,   23,    1,   42,   43,   22,   23,
 /*   270 */    31,    4,    8,   34,   31,    4,    1,   18,   35,   36,
 /*   280 */    31,   42,   31,    8,   35,   36,   35,   36,   31,   31,
 /*   290 */     1,   34,   34,    7,    1,   18,    2,    8,    2,   42,
 /*   300 */    42,    8,   16,    9,   20,   21,    3,    2,    7,    3,
 /*   310 */    18,    9,   46,   10,    9,   18,   10,   16,   18,   46,
 /*   320 */    18,   46,   15,   16,   15,   16,   18,   15,   16,   18,
 /*   330 */    16,   16,   46,   46,   18,
};
#define YY_SHIFT_USE_DFLT (-18)
#define YY_SHIFT_COUNT (102)
#define YY_SHIFT_MIN   (-17)
#define YY_SHIFT_MAX   (316)
static const short yy_shift_ofst[] = {
 /*     0 */    19,   19,  138,  175,  175,  175,  175,  175,  175,  175,
 /*    10 */   175,   39,   39,   39,  175,  175,  175,  175,  172,   68,
 /*    20 */   241,  246,   11,   11,   11,   11,   11,   11,   11,   11,
 /*    30 */    11,   11,   11,   11,   11,   11,   11,   79,   79,   79,
 /*    40 */    11,   11,  158,  158,  158,  -17,  -17,    4,    4,    4,
 /*    50 */     4,    4,  187,  139,  185,   91,  286,   35,  201,  206,
 /*    60 */   264,  114,  275,  289,  293,  294,   67,  151,  216,  234,
 /*    70 */   284,  303,  305,  301,  306,  302,  307,  226,  309,  312,
 /*    80 */    54,  118,  155,  156,  168,  168,  222,  181,  183,  247,
 /*    90 */   267,  259,  277,  271,  296,  292,  297,  300,  308,  311,
 /*   100 */   314,  315,  316,
};
#define YY_REDUCE_USE_DFLT (-26)
#define YY_REDUCE_COUNT (51)
#define YY_REDUCE_MIN   (-25)
#define YY_REDUCE_MAX   (258)
static const short yy_reduce_ofst[] = {
 /*     0 */   -25,  -12,   13,   26,   32,   45,   55,   61,   74,   76,
 /*    10 */    89,   17,  104,  111,  124,  134,  140,  147,  169,  174,
 /*    20 */   179,  169,  184,  189,   -7,  194,  199,  204,  209,  214,
 /*    30 */   219,   36,  -21,  224,  128,   80,  239,  243,  249,  251,
 /*    40 */   257,  258,    9,   99,  119,  -24,  -20,   22,   27,   75,
 /*    50 */    78,   95,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   247,  246,  286,  289,  289,  289,  289,  289,  289,  289,
 /*    10 */   289,  289,  289,  289,  289,  289,  289,  289,  289,  289,
 /*    20 */   289,  289,  289,  289,  289,  289,  289,  289,  289,  289,
 /*    30 */   289,  289,  289,  289,  289,  289,  289,  289,  289,  289,
 /*    40 */   289,  289,  289,  289,  289,  289,  289,  289,  289,  289,
 /*    50 */   289,  289,  289,  285,  289,  289,  289,  289,  279,  281,
 /*    60 */   280,  289,  289,  251,  289,  285,  289,  289,  289,  289,
 /*    70 */   289,  289,  285,  289,  289,  240,  289,  289,  289,  289,
 /*    80 */   262,  260,  289,  257,  253,  249,  289,  289,  289,  289,
 /*    90 */   289,  289,  289,  289,  268,  289,  289,  239,  289,  289,
 /*   100 */   289,  283,  289,
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
#line 121 "MVSMParserGrammar.y"
{
	std::string str = yymsp[-2].minor.yy0->toString();
	auto it = tree->domainNamesList.find(str);
	if(it != tree->domainNamesList.end())
		throw syntax_exception("Redeclaration of sort "+yymsp[-2].minor.yy0->toString()+"\n");
	else
		tree->domainNamesList.insert(yymsp[-2].minor.yy0->toString());
}
#line 1011 "MVSMParserGrammar.c"
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
#line 1023 "MVSMParserGrammar.c"
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
			cout<<d->toString(false);
			delete d;
		}
		else{
			throw syntax_exception("Domain " + yymsp[0].minor.yy0->toString() +" not declared.\n");
		}
	
	delete yymsp[-3].minor.yy7;
}
#line 1046 "MVSMParserGrammar.c"
        break;
      case 10: /* object ::= variable DOT DOT variable COLON COLON string */
#line 169 "MVSMParserGrammar.y"
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
#line 1072 "MVSMParserGrammar.c"
        break;
      case 15: /* constant ::= string LBRACKET variables RBRACKET COLON COLON string */
#line 200 "MVSMParserGrammar.y"
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
#line 1115 "MVSMParserGrammar.c"
        break;
      case 16: /* constant ::= string LBRACKET variables RBRACKET */
#line 240 "MVSMParserGrammar.y"
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
#line 1144 "MVSMParserGrammar.c"
        break;
      case 17: /* constant ::= string */
#line 266 "MVSMParserGrammar.y"
{
	Variable* va = new Variable;
	va->setVar(yymsp[0].minor.yy0->toString());
	tree->variables.insert(*va);
	/*for ASP output we do not print constants */
	if(tree->outputType != OutputType::OUTPUT_ASP)
		cout<<va->toString()<<"\n";
	
	delete va;	
}
#line 1158 "MVSMParserGrammar.c"
        break;
      case 18: /* constant ::= string COLON COLON string */
#line 277 "MVSMParserGrammar.y"
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
#line 1187 "MVSMParserGrammar.c"
        break;
      case 19: /* prog ::= prog NEWLINE predicate */
#line 304 "MVSMParserGrammar.y"
{ 
	if(yymsp[0].minor.yy16->needsToBeCompleted()){	
		FactCompletion f(*yymsp[0].minor.yy16);
		tree->facts.insert(std::pair<std::string,FactCompletion>(f.getHead().getVar(),f)); 
	}

			
	delete yymsp[0].minor.yy16;
}
#line 1200 "MVSMParserGrammar.c"
        break;
      case 20: /* prog ::= predicate */
#line 314 "MVSMParserGrammar.y"
{ 
	if(yymsp[0].minor.yy16->needsToBeCompleted()){
		FactCompletion f(*yymsp[0].minor.yy16);
		tree->facts.insert(std::pair<std::string,FactCompletion>(f.getHead().getVar(),f)); 	
	}
	delete yymsp[0].minor.yy16;
}
#line 1211 "MVSMParserGrammar.c"
        break;
      case 21: /* prog ::= prog NEWLINE rule */
      case 22: /* prog ::= rule */ yytestcase(yyruleno==22);
#line 322 "MVSMParserGrammar.y"
{
	if((yymsp[0].minor.yy57->isHeadTop == false) && (yymsp[0].minor.yy57->toBeCompleted == true))
		tree->rules.insert(std::pair<std::string,RuleCompletion>(yymsp[0].minor.yy57->getHead().getVar(),*yymsp[0].minor.yy57));
	delete yymsp[0].minor.yy57;
}
#line 1221 "MVSMParserGrammar.c"
        break;
      case 25: /* rule ::= REVERSE_IMPLICATION body DOT */
#line 355 "MVSMParserGrammar.y"
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
#line 1244 "MVSMParserGrammar.c"
        break;
      case 26: /* rule ::= number REVERSE_IMPLICATION body */
#line 376 "MVSMParserGrammar.y"
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
				+  std::to_string((int)(std::stof(yymsp[-2].minor.yy0->toString())* 10000))
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
#line 1289 "MVSMParserGrammar.c"
        break;
      case 27: /* rule ::= head DISJUNCTION bodydef DOT */
#line 421 "MVSMParserGrammar.y"
{
	//Doing this 
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
	}
	
	std::cout<<temp<<"."<<"\n";
	
	delete yymsp[-3].minor.yy77;
	delete yymsp[-1].minor.yy92;
}
#line 1324 "MVSMParserGrammar.c"
        break;
      case 28: /* rule ::= number head DISJUNCTION bodydef */
#line 456 "MVSMParserGrammar.y"
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
	yymsp[-2].minor.yy77->appendStr(yymsp[0].minor.yy92->getPredicate().toString(tree->domainList),false,true,false);
	std::cout<<yymsp[-3].minor.yy0->toString()<<SPACE<<yymsp[-2].minor.yy77->toString()<<"\n";
	delete yymsp[-2].minor.yy77;
	delete yymsp[0].minor.yy92;
}
#line 1345 "MVSMParserGrammar.c"
        break;
      case 29: /* rule ::= head REVERSE_IMPLICATION body DOT */
#line 479 "MVSMParserGrammar.y"
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
#line 1386 "MVSMParserGrammar.c"
        break;
      case 30: /* rule ::= number head REVERSE_IMPLICATION body */
#line 520 "MVSMParserGrammar.y"
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

		std::cout << "unsat(" << tree->weak_constraint_counter << ")"
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


	delete yymsp[0].minor.yy21;
	delete yymsp[-2].minor.yy77;
}
#line 1448 "MVSMParserGrammar.c"
        break;
      case 31: /* rule ::= number NEGATION NEGATION LBRACKET head REVERSE_IMPLICATION body RBRACKET */
#line 582 "MVSMParserGrammar.y"
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
#line 1477 "MVSMParserGrammar.c"
        break;
      case 32: /* rule ::= LPAREN head RPAREN REVERSE_IMPLICATION body DOT */
#line 608 "MVSMParserGrammar.y"
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
#line 1503 "MVSMParserGrammar.c"
        break;
      case 33: /* body ::= body CONJUNCTION bodydef */
#line 632 "MVSMParserGrammar.y"
{
	yygotominor.yy21 = yymsp[-2].minor.yy21;
	yymsp[-2].minor.yy21->addPredicate(yymsp[0].minor.yy92->getPredicate());
	yygotominor.yy21->appendStr(yymsp[0].minor.yy92->getPredicate(),false,false,true,tree->domainList);
	delete yymsp[0].minor.yy92;
}
#line 1513 "MVSMParserGrammar.c"
        break;
      case 34: /* head ::= head DISJUNCTION bodydef */
#line 639 "MVSMParserGrammar.y"
{
	yygotominor.yy77 = yymsp[-2].minor.yy77;
	yymsp[-2].minor.yy77->addPredicate(yymsp[0].minor.yy92->getPredicate());
	yygotominor.yy77->appendStr(yymsp[0].minor.yy92->getPredicate().toString(tree->domainList),false,true,false);
	yygotominor.yy77->setDisjunction(true);
	delete yymsp[0].minor.yy92;
}
#line 1524 "MVSMParserGrammar.c"
        break;
      case 35: /* head ::= bodydef */
#line 647 "MVSMParserGrammar.y"
{
	yygotominor.yy77 = new Head(yymsp[0].minor.yy92->getPredicate());
	// yygotominor.yy77->addPredicate(yymsp[0].minor.yy92->getPredicate());
	yygotominor.yy77->appendStr(yymsp[0].minor.yy92->getPredicate().toString(tree->domainList),false,false,false);
	delete yymsp[0].minor.yy92;
}
#line 1534 "MVSMParserGrammar.c"
        break;
      case 36: /* body ::= bodydef */
#line 654 "MVSMParserGrammar.y"
{
	yygotominor.yy21 = new Body;
	Predicate p = yymsp[0].minor.yy92->getPredicate();
	yygotominor.yy21->addPredicate(p);
	yygotominor.yy21->appendStr(p,false,false,false,tree->domainList);
	delete yymsp[0].minor.yy92;
}
#line 1545 "MVSMParserGrammar.c"
        break;
      case 37: /* bodydef ::= literal */
#line 665 "MVSMParserGrammar.y"
{	
	yygotominor.yy92 = yymsp[0].minor.yy92;
}
#line 1552 "MVSMParserGrammar.c"
        break;
      case 38: /* bodydef ::= NEGATION literal */
#line 670 "MVSMParserGrammar.y"
{	
	yygotominor.yy92 = yymsp[0].minor.yy92;
	Predicate p = yygotominor.yy92->getPredicate();
	p.setSingleNegation(true);
	yygotominor.yy92->addPredicate(p);
	// yygotominor.yy92->getPredicate().setSingleNegation(true);
}
#line 1563 "MVSMParserGrammar.c"
        break;
      case 39: /* bodydef ::= NEGATION NEGATION literal */
#line 679 "MVSMParserGrammar.y"
{	
	yygotominor.yy92 = yymsp[0].minor.yy92;
	tree->statHasDblNeg = true;
	yygotominor.yy92->getPredicate().setDoubleNegation(true);
}
#line 1572 "MVSMParserGrammar.c"
        break;
      case 40: /* bodydef ::= LBRACKET NEGATION NEGATION literal RBRACKET */
#line 688 "MVSMParserGrammar.y"
{	
	yygotominor.yy92 = yymsp[-1].minor.yy92;
	tree->statHasDblNeg = true;
	yygotominor.yy92->getPredicate().setDoubleNegation(true);
}
#line 1581 "MVSMParserGrammar.c"
        break;
      case 41: /* bodydef ::= string EQUAL string */
#line 695 "MVSMParserGrammar.y"
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
#line 1616 "MVSMParserGrammar.c"
        break;
      case 42: /* bodydef ::= NEGATION string EQUAL string */
#line 728 "MVSMParserGrammar.y"
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
#line 1635 "MVSMParserGrammar.c"
        break;
      case 43: /* bodydef ::= string NEGATION EQUAL string */
#line 744 "MVSMParserGrammar.y"
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
#line 1654 "MVSMParserGrammar.c"
        break;
      case 44: /* literal ::= string LBRACKET variables RBRACKET EQUAL variable */
#line 763 "MVSMParserGrammar.y"
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
#line 1679 "MVSMParserGrammar.c"
        break;
      case 45: /* literal ::= string LBRACKET variables RBRACKET */
#line 785 "MVSMParserGrammar.y"
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
#line 1703 "MVSMParserGrammar.c"
        break;
      case 46: /* literal ::= variable */
#line 806 "MVSMParserGrammar.y"
{
	Predicate p(yymsp[0].minor.yy0->token);
	auto itr = tree->variables.find(yymsp[0].minor.yy0->toString());
	yygotominor.yy92 = new BodyDef;
	/*Special Case: BodyDef does not have variables*/
	yygotominor.yy92->setHasVariables();
	yygotominor.yy92->addPredicate(p);
}
#line 1715 "MVSMParserGrammar.c"
        break;
      case 47: /* literal ::= string EQUAL COUNT LPAREN aggregateCum RPAREN */
#line 815 "MVSMParserGrammar.y"
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
#line 1729 "MVSMParserGrammar.c"
        break;
      case 48: /* literal ::= string EQUAL SUM LPAREN aggregateCum RPAREN */
#line 826 "MVSMParserGrammar.y"
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
#line 1743 "MVSMParserGrammar.c"
        break;
      case 49: /* aggregate ::= string COLON literal */
#line 838 "MVSMParserGrammar.y"
{
	yygotominor.yy0 = new Token(*(yymsp[-2].minor.yy0->token));
	std::string s1 = yygotominor.yy0->toString();
	Util::toUpper(s1);
	s1 = s1 + ":" + yymsp[0].minor.yy92->toString(tree->domainList);
	yygotominor.yy0->modifyToken(s1);
	delete yymsp[0].minor.yy92;
}
#line 1755 "MVSMParserGrammar.c"
        break;
      case 50: /* aggregate ::= number COLON literal */
#line 847 "MVSMParserGrammar.y"
{
	yygotominor.yy0 = new Token(*(yymsp[-2].minor.yy0->token));
	std::string s1 = yygotominor.yy0->toString();
	s1 = s1 + ":" + yymsp[0].minor.yy92->toString(tree->domainList);
	yygotominor.yy0->modifyToken(s1);
	delete yymsp[0].minor.yy92;
}
#line 1766 "MVSMParserGrammar.c"
        break;
      case 51: /* aggregate ::= string COMMA literal COLON literal */
#line 855 "MVSMParserGrammar.y"
{
	yygotominor.yy0 = new Token(*(yymsp[-4].minor.yy0->token));
	std::string s1 = yygotominor.yy0->toString();
	Util::toUpper(s1);
	s1 = s1 + "," + yymsp[-2].minor.yy92->toString(tree->domainList) + ":" + yymsp[0].minor.yy92->toString(tree->domainList);
	yygotominor.yy0->modifyToken(s1);
}
#line 1777 "MVSMParserGrammar.c"
        break;
      case 52: /* aggregate ::= number COMMA literal COLON literal */
#line 864 "MVSMParserGrammar.y"
{
	yygotominor.yy0 = new Token(*(yymsp[-4].minor.yy0->token));
	std::string s1 = (*yymsp[-4].minor.yy0).toString();
	// Util::toUpper(s1);
	s1 = s1 + "," + yymsp[-2].minor.yy92->toString(tree->domainList)+ ":" + yymsp[0].minor.yy92->toString(tree->domainList);
	yygotominor.yy0->modifyToken(s1);
}
#line 1788 "MVSMParserGrammar.c"
        break;
      case 53: /* aggregateCum ::= aggregate */
#line 872 "MVSMParserGrammar.y"
{
	yygotominor.yy0 = new Token(*(yymsp[0].minor.yy0->token));
	delete yymsp[0].minor.yy0;
}
#line 1796 "MVSMParserGrammar.c"
        break;
      case 54: /* aggregateCum ::= aggregateCum SEMI_COLON aggregate */
#line 877 "MVSMParserGrammar.y"
{
	yygotominor.yy0 = yymsp[-2].minor.yy0;
	yygotominor.yy0->modifyToken(yymsp[-2].minor.yy0->toString() + ";" + yymsp[0].minor.yy0->toString());
	delete yymsp[0].minor.yy0;
}
#line 1805 "MVSMParserGrammar.c"
        break;
      case 55: /* predicate ::= literal DOT */
#line 884 "MVSMParserGrammar.y"
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
#line 1846 "MVSMParserGrammar.c"
        break;
      case 56: /* predicate ::= number literal */
#line 922 "MVSMParserGrammar.y"
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

		std::cout << "unsat(" << tree->weak_constraint_counter << ")"
					<< " :- "
					<< "not "
					<< yygotominor.yy16->toString(tree->domainList)
					<<LanguageConstants::LINE_END
					<<"\n"; 

		std::cout << yygotominor.yy16->toString(tree->domainList)
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
	delete yymsp[0].minor.yy92;
}
#line 1899 "MVSMParserGrammar.c"
        break;
      case 57: /* predicate ::= number NEGATION NEGATION literal */
#line 972 "MVSMParserGrammar.y"
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
		str += LanguageConstants::LINE_END;
		str += " [" + 
				std::to_string((int)(std::stof(yymsp[-3].minor.yy0->toString())* 10000)) + 
				"," + 
				std::to_string(tree->weak_constraint_counter++) + 
				"," +
				yygotominor.yy16->getExtraConstants()+
				"]\n";
		cout<<str;
	}
	
	delete yymsp[0].minor.yy92;
}
#line 1931 "MVSMParserGrammar.c"
        break;
      case 58: /* predicate ::= number NEGATION literal */
#line 1001 "MVSMParserGrammar.y"
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
		str += " [" + 
		std::to_string((int)(std::stof(yymsp[-2].minor.yy0->toString())* 10000)) + 
		"," + 
		std::to_string(tree->weak_constraint_counter++) + 
		"," +
		yygotominor.yy16->getExtraConstants() + 
		"]\n";
		cout<<str;
	}

	
	delete yymsp[0].minor.yy92;
}
#line 1961 "MVSMParserGrammar.c"
        break;
      case 59: /* predicate ::= NEGATION NEGATION literal DOT */
#line 1028 "MVSMParserGrammar.y"
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
#line 1983 "MVSMParserGrammar.c"
        break;
      case 60: /* variables ::= variable */
#line 1048 "MVSMParserGrammar.y"
{
	yygotominor.yy7 = new std::vector<std::string*>();	
	yygotominor.yy7->push_back(yymsp[0].minor.yy0->token);
}
#line 1991 "MVSMParserGrammar.c"
        break;
      case 61: /* variables ::= variables COMMA variable */
#line 1053 "MVSMParserGrammar.y"
{
	yygotominor.yy7 = yymsp[-2].minor.yy7;
	yymsp[-2].minor.yy7->push_back(yymsp[0].minor.yy0->token);
}
#line 1999 "MVSMParserGrammar.c"
        break;
      case 62: /* variable ::= string */
      case 63: /* variable ::= number */ yytestcase(yyruleno==63);
      case 64: /* string ::= STRING */ yytestcase(yyruleno==64);
#line 1058 "MVSMParserGrammar.y"
{ yygotominor.yy0=yymsp[0].minor.yy0;}
#line 2006 "MVSMParserGrammar.c"
        break;
      case 65: /* number ::= NUMBER */
#line 1066 "MVSMParserGrammar.y"
{ yygotominor.yy0=yymsp[0].minor.yy0; }
#line 2011 "MVSMParserGrammar.c"
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
#line 66 "MVSMParserGrammar.y"

    std::cout<<"Giving up.Parser is lost...\n";

#line 2078 "MVSMParserGrammar.c"
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
    
#line 2110 "MVSMParserGrammar.c"
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
#line 58 "MVSMParserGrammar.y"

	if (tree->outputType == OutputType::OUTPUT_ASP)
		std::cout<<("%parsing complete!\n");
	else
    	std::cout<<("//parsing complete!\n");
#line 2137 "MVSMParserGrammar.c"
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

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

	struct cmp{
		bool operator()(const std::pair<std::string, std::string>& left, const std::pair<std::string, std::string>& right) const{
			return left.first < right.first;
		}
	};

#define RULE_COMPLETION_BH(B,H) \
	std::set<std::pair<std::string,std::string>> orphanVarsMap;  \
	std::set<std::pair<std::string,std::string>> orphanVarsHeadMap; \
	std::vector<Predicate> predList = B->getPredicate(); \
	for(auto& p : predList){ \
		int tempCount = 0; \
		for(auto& v : p.getTokens()){ \
			if(tree->variables.find(p.getVar()) == tree->variables.end()){ \
				undefined_predicate ex(p.getVar()); \
				throw ex; \
			} \
			else \
				orphanVarsMap.insert(std::pair<std::string, std::string>(v,tree->variables.find(p.getVar())->getPosMap().at(tempCount++).getDomainVar())); \
		} \
	} \
	int count = 0; \
	std::map<int,std::pair<int, std::string>> varMap; \
	int tempCount = 0; \
	for(auto& str : H->getPredicate().getTokens()){ \
		if(tree->isConstant(str)){ \
			varMap[count++] = std::pair<int, std::string>(count, str); \
		} \
		else \
			count++; \
		 \
		if(tree->variables.find(H->getPredicate().getVar()) == tree->variables.end()){ \
			undefined_predicate ex(H->getPredicate().getVar()); \
			throw ex; \
		} \
		else	 \
			orphanVarsHeadMap.insert(std::pair<std::string, std::string>(str,tree->variables.find(H->getPredicate().getVar())->getPosMap().at(tempCount++).getDomainVar())); \
	} \
	std::set<std::string> result; \
	tree->removeConstantsPair(orphanVarsMap); \
	tree->removeConstantsPair(orphanVarsHeadMap); \
	std::set<std::pair<std::string,std::string>> resultMap; \
	std::set_difference(orphanVarsMap.begin(), orphanVarsMap.end(), orphanVarsHeadMap.begin(), orphanVarsHeadMap.end(),std::inserter(resultMap, resultMap.end()), cmp())


#define RULE_COMPLETION_BODY_TOP(B,B1) \
	B->addPredicate(B1->getPredicate()); \
	std::vector<Predicate> pred = B->getPredicate(); \
	for(unsigned long int i=0;i<pred.size();i++){ \
		std::unique_ptr<Head> H(new Head(pred.at(i))); \
		std::vector<Predicate> temp; \
		for (unsigned long int j = 0; j < pred.size(); j++){ \
			if(j == i) continue; \
			bool singleN = pred.at(j).isSingleNegated(); \
			bool doubleN = pred.at(j).isDoubleNegated(); \
			if(pred.at(j).isSingleNegated()){ \
				pred.at(j).setSingleNegation(false); \
			} \
			else if(pred.at(j).isDoubleNegated()){ \
				pred.at(j).setDoubleNegation(false); \
				pred.at(j).setSingleNegation(true); \
			} \
			else{ \
				pred.at(j).setSingleNegation(true);	 \
			} \
			temp.push_back(pred.at(j)); \
			pred.at(j).setSingleNegation(singleN); \
			pred.at(j).setDoubleNegation(doubleN); \
		} \
		std::unique_ptr<Body> b(new Body(temp)); \
		RULE_COMPLETION_BH(b,H); \
		RuleCompletion* R1 = new RuleCompletion(H->getPredicate(),predList, resultMap, varMap); \
		tree->rules.insert(std::pair<std::string,RuleCompletion>(R1->head.getVar(),*R1)); \
		delete R1; \
	} 
	
	 
#include "ASPParserGrammar.h"
/**************** End of %include directives **********************************/
/* These constants specify the various numeric values for terminal symbols
** in a format understandable to "makeheaders".  This section is blank unless
** "lemon" is run with the "-m" command-line option.
***************** Begin makeheaders token definitions *************************/
#if INTERFACE
#define PARSE_TOKEN_EQUAL                           1
#define PARSE_TOKEN_COMMA                           2
#define PARSE_TOKEN_LPAREN                          3
#define PARSE_TOKEN_RPAREN                          4
#define PARSE_TOKEN_NEWLINE                         5
#define PARSE_TOKEN_CONJUNCTION                     6
#define PARSE_TOKEN_DISJUNCTION                     7
#define PARSE_TOKEN_LBRACKET                        8
#define PARSE_TOKEN_RBRACKET                        9
#define PARSE_TOKEN_IMPLICATION                    10
#define PARSE_TOKEN_REVERSE_IMPLICATION            11
#define PARSE_TOKEN_NEGATION                       12
#define PARSE_TOKEN_WS                             13
#define PARSE_TOKEN_DOT                            14
#define PARSE_TOKEN_STRING                         15
#define PARSE_TOKEN_NUMBER                         16
#define PARSE_TOKEN_MINUS                          17
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
**    ASPParserGrammarTOKENTYPE     is the data type used for minor type for terminal
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
**                       which is ASPParserGrammarTOKENTYPE.  The entry in the union
**                       for terminal symbols is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    ASPParserGrammarARG_SDECL     A static variable declaration for the %extra_argument
**    ASPParserGrammarARG_PDECL     A parameter declaration for the %extra_argument
**    ASPParserGrammarARG_STORE     Code to store %extra_argument into yypParser
**    ASPParserGrammarARG_FETCH     Code to extract %extra_argument from yypParser
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
#define YYNOCODE 39
#define YYACTIONTYPE unsigned short int
#if INTERFACE
#define ASPParserGrammarTOKENTYPE Token*
#endif
typedef union {
  int yyinit;
  ASPParserGrammarTOKENTYPE yy0;
  Variable* yy1;
  RuleCompletion* yy9;
  BodyDef* yy12;
  Tree* yy35;
  std::vector<std::string*>* yy36;
  Body* yy45;
  Predicate* yy52;
  Head* yy53;
  Domain* yy63;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#if INTERFACE
#define ASPParserGrammarARG_SDECL Tree* tree;
#define ASPParserGrammarARG_PDECL ,Tree* tree
#define ASPParserGrammarARG_FETCH Tree* tree = yypParser->tree
#define ASPParserGrammarARG_STORE yypParser->tree = tree
#endif
#define YYNSTATE             114
#define YYNRULE              53
#define YY_MAX_SHIFT         113
#define YY_MIN_SHIFTREDUCE   154
#define YY_MAX_SHIFTREDUCE   206
#define YY_MIN_REDUCE        207
#define YY_MAX_REDUCE        259
#define YY_ERROR_ACTION      260
#define YY_ACCEPT_ACTION     261
#define YY_NO_ACTION         262
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
#define YY_ACTTAB_COUNT (305)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   261,   80,  156,   83,  158,  160,  104,  162,   63,  179,
 /*    10 */    38,   84,  186,  201,    2,   51,  155,  109,  157,  159,
 /*    20 */   104,  161,   63,  179,   39,   84,  186,  201,    2,   51,
 /*    30 */    17,  109,   41,   23,   35,  201,   92,  201,  110,   48,
 /*    40 */    73,  179,   59,   96,  186,   95,  186,   54,   60,   94,
 /*    50 */   200,  199,  197,  109,   61,   85,  200,  199,  197,  109,
 /*    60 */    62,   57,  200,  199,  197,  109,   65,    5,  200,  199,
 /*    70 */   197,  109,   91,   66,  200,  199,  197,  109,   68,  201,
 /*    80 */   195,  200,  199,  197,  109,   69,  200,  199,  197,  109,
 /*    90 */    70,  106,  184,  200,  199,  197,  109,   74,  200,  199,
 /*   100 */   197,  109,   75,  235,  235,  200,  199,  197,  109,   76,
 /*   110 */   200,  199,  197,  109,   77,   30,   27,  200,  199,  197,
 /*   120 */   109,   78,  200,  199,  197,  109,  201,  110,   48,  200,
 /*   130 */   199,  197,  109,   19,   79,  179,  113,   37,  201,   87,
 /*   140 */   201,   57,   79,  179,   18,   79,  179,   90,   39,   57,
 /*   150 */    99,  201,   57,  200,  199,  198,  109,   79,  179,  206,
 /*   160 */   233,  233,  112,   40,   57,  240,  201,   81,  190,   52,
 /*   170 */   179,   64,  179,   56,  179,   88,   57,   20,   57,  196,
 /*   180 */    57,   57,   71,  179,   34,   30,   29,  233,  233,   57,
 /*   190 */    46,    6,  240,  174,  178,  107,   93,    7,  234,  234,
 /*   200 */    57,  107,  177,  241,   30,   29,   46,  176,   57,  204,
 /*   210 */    72,   98,  100,   16,  111,   26,   57,  107,   57,  102,
 /*   220 */    57,   36,  201,   42,  201,   44,  201,   20,  201,   20,
 /*   230 */    20,   20,   28,   29,   58,   20,   82,   50,   53,   20,
 /*   240 */    20,   20,   55,  203,   20,  172,   67,  188,  187,   30,
 /*   250 */    29,   97,   20,  231,  231,   30,   31,   20,   20,  101,
 /*   260 */    20,  207,    3,  241,  182,  181,    1,  180,  105,  185,
 /*   270 */   184,   33,   32,  205,    4,   22,  108,  168,   86,   89,
 /*   280 */     8,  171,  167,    9,   10,   11,   43,   47,   12,   24,
 /*   290 */    25,  183,  166,  223,   13,   14,   45,  103,   15,  209,
 /*   300 */   222,  165,   49,  258,   21,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    19,   20,   21,   34,   23,   24,    8,   26,   27,   28,
 /*    10 */    12,   30,   31,   15,   33,   34,   21,   36,   23,   24,
 /*    20 */     8,   26,   27,   28,   12,   30,   31,   15,   33,   34,
 /*    30 */     8,   36,   12,   11,   12,   15,   34,   15,   16,   17,
 /*    40 */    27,   28,   25,   30,   31,   30,   31,   34,   25,   34,
 /*    50 */    33,   34,   35,   36,   25,   28,   33,   34,   35,   36,
 /*    60 */    25,   34,   33,   34,   35,   36,   25,    3,   33,   34,
 /*    70 */    35,   36,   34,   25,   33,   34,   35,   36,   25,   15,
 /*    80 */    22,   33,   34,   35,   36,   25,   33,   34,   35,   36,
 /*    90 */    25,   34,   34,   33,   34,   35,   36,   25,   33,   34,
 /*   100 */    35,   36,   25,    6,    7,   33,   34,   35,   36,   25,
 /*   110 */    33,   34,   35,   36,   25,    6,    7,   33,   34,   35,
 /*   120 */    36,   25,   33,   34,   35,   36,   15,   16,   17,   33,
 /*   130 */    34,   35,   36,    8,   27,   28,   11,   12,   15,   32,
 /*   140 */    15,   34,   27,   28,    8,   27,   28,   32,   12,   34,
 /*   150 */    32,   15,   34,   33,   34,   35,   36,   27,   28,   16,
 /*   160 */     6,    7,   32,   12,   34,   11,   15,   34,   14,   27,
 /*   170 */    28,   27,   28,   27,   28,   28,   34,    2,   34,    4,
 /*   180 */    34,   34,   27,   28,    1,    6,    7,    6,    7,   34,
 /*   190 */     1,    8,   11,   14,   28,   12,   34,    8,    6,    7,
 /*   200 */    34,   12,   28,   11,    6,    7,    1,    9,   34,   37,
 /*   210 */    28,   34,   28,    8,   28,    8,   34,   12,   34,   34,
 /*   220 */    34,   12,   15,   12,   15,   12,   15,    2,   15,    2,
 /*   230 */     2,    2,    6,    7,    9,    2,    9,    9,    9,    2,
 /*   240 */     2,    2,    9,   37,    2,   14,    9,    9,    9,    6,
 /*   250 */     7,    9,    2,    6,    7,    6,    7,    2,    2,    9,
 /*   260 */     2,    0,    8,   11,    9,    9,    5,    9,   34,   34,
 /*   270 */    34,    6,    7,   16,    8,   11,   36,   14,    9,    9,
 /*   280 */     8,   14,   14,    8,    8,    8,   12,   14,    8,   11,
 /*   290 */    11,    9,    9,    9,    8,    8,    1,   12,    8,   38,
 /*   300 */     9,    9,   14,   14,    8,
};
#define YY_SHIFT_USE_DFLT (-3)
#define YY_SHIFT_COUNT (113)
#define YY_SHIFT_MIN   (-2)
#define YY_SHIFT_MAX   (296)
static const short yy_shift_ofst[] = {
 /*     0 */    22,   22,  125,  111,  111,  111,  111,  111,  111,  111,
 /*    10 */   111,  111,  111,  111,  111,  111,  111,   -2,   -2,   -2,
 /*    20 */   111,   12,   12,  136,   12,   12,   20,   12,   12,   12,
 /*    30 */    12,   12,   12,   12,   64,  151,  207,  209,  211,  213,
 /*    40 */   123,  123,  123,  123,  123,  123,  123,  143,  257,  143,
 /*    50 */   154,  183,  179,  181,  189,  192,  198,  205,   97,  225,
 /*    60 */   227,  175,  228,  109,  226,  229,  233,   97,  237,  238,
 /*    70 */   239,  243,  247,  249,  242,  250,  255,  256,  258,  265,
 /*    80 */   261,  254,  252,  266,  264,  231,  263,  269,  267,  268,
 /*    90 */   270,  272,  275,  276,  277,  278,  279,  282,  280,  283,
 /*   100 */   284,  282,  286,  274,  285,  287,  290,  295,  273,  288,
 /*   110 */   289,  291,  292,  296,
};
#define YY_REDUCE_USE_DFLT (-32)
#define YY_REDUCE_COUNT (49)
#define YY_REDUCE_MIN   (-31)
#define YY_REDUCE_MAX   (240)
static const short yy_reduce_ofst[] = {
 /*     0 */   -19,   -5,   13,   17,   23,   29,   35,   41,   48,   53,
 /*    10 */    60,   65,   72,   77,   84,   89,   96,  107,  115,  118,
 /*    20 */   120,  130,  142,  144,  146,  155,   15,   27,  147,  166,
 /*    30 */   174,  182,  184,  186,   58,  -31,    2,   38,   57,   57,
 /*    40 */   133,  162,  177,  185,  234,  235,  236,  172,  240,  206,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   217,  216,  260,  260,  260,  260,  260,  260,  260,  260,
 /*    10 */   260,  260,  260,  260,  260,  260,  260,  260,  260,  260,
 /*    20 */   260,  260,  260,  260,  260,  260,  260,  260,  260,  260,
 /*    30 */   260,  260,  260,  260,  260,  260,  260,  260,  260,  260,
 /*    40 */   260,  260,  260,  260,  260,  260,  260,  260,  260,  260,
 /*    50 */   242,  260,  260,  244,  260,  246,  260,  260,  247,  260,
 /*    60 */   260,  260,  260,  260,  260,  260,  260,  245,  260,  260,
 /*    70 */   260,  228,  226,  260,  260,  260,  260,  260,  260,  260,
 /*    80 */   260,  260,  234,  260,  260,  231,  260,  260,  230,  260,
 /*    90 */   260,  260,  260,  260,  260,  260,  260,  235,  260,  260,
 /*   100 */   231,  260,  260,  260,  260,  260,  260,  260,  260,  260,
 /*   110 */   255,  230,  260,  260,
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
  ASPParserGrammarARG_SDECL                /* A place to hold %extra_argument */
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
void ASPParserGrammarTrace(FILE *TraceFILE, char *zTracePrompt){
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
  "NEGATION",      "WS",            "DOT",           "STRING",      
  "NUMBER",        "MINUS",         "error",         "start",       
  "prog",          "domain",        "domains",       "predicate",   
  "decl",          "variables",     "rule",          "body",        
  "bodydef",       "bodydef2",      "head",          "headdef",     
  "ruleU",         "number",        "string",        "variable",    
  "lnumber",       "rnumber",     
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
 /*  11 */ "rule ::= number REVERSE_IMPLICATION LBRACKET ruleU RBRACKET",
 /*  12 */ "rule ::= number LBRACKET ruleU RBRACKET",
 /*  13 */ "rule ::= REVERSE_IMPLICATION LBRACKET ruleU RBRACKET DOT",
 /*  14 */ "rule ::= LBRACKET ruleU RBRACKET DOT",
 /*  15 */ "ruleU ::= body CONJUNCTION bodydef",
 /*  16 */ "ruleU ::= body DISJUNCTION bodydef",
 /*  17 */ "rule ::= REVERSE_IMPLICATION body CONJUNCTION bodydef DOT",
 /*  18 */ "rule ::= body DISJUNCTION bodydef DOT",
 /*  19 */ "rule ::= number body DISJUNCTION bodydef",
 /*  20 */ "rule ::= head REVERSE_IMPLICATION body DOT",
 /*  21 */ "rule ::= number head REVERSE_IMPLICATION body",
 /*  22 */ "rule ::= number NEGATION NEGATION LBRACKET head REVERSE_IMPLICATION body RBRACKET",
 /*  23 */ "body ::= body CONJUNCTION bodydef",
 /*  24 */ "body ::= body DISJUNCTION bodydef",
 /*  25 */ "body ::= bodydef",
 /*  26 */ "bodydef ::= string LBRACKET variables RBRACKET",
 /*  27 */ "bodydef ::= NEGATION string LBRACKET variables RBRACKET",
 /*  28 */ "bodydef ::= NEGATION NEGATION string LBRACKET variables RBRACKET",
 /*  29 */ "bodydef ::= LBRACKET NEGATION NEGATION string LBRACKET variables RBRACKET RBRACKET",
 /*  30 */ "bodydef ::= string EQUAL string",
 /*  31 */ "bodydef ::= string NEGATION EQUAL string",
 /*  32 */ "head ::= headdef",
 /*  33 */ "headdef ::= string LBRACKET variables RBRACKET",
 /*  34 */ "headdef ::= NEGATION string LBRACKET variables RBRACKET",
 /*  35 */ "decl ::= string LBRACKET variables RBRACKET",
 /*  36 */ "predicate ::= string LBRACKET variables RBRACKET DOT",
 /*  37 */ "predicate ::= number string LBRACKET variables RBRACKET",
 /*  38 */ "predicate ::= number NEGATION NEGATION string LBRACKET variables RBRACKET",
 /*  39 */ "predicate ::= number NEGATION string LBRACKET variables RBRACKET",
 /*  40 */ "predicate ::= NEGATION NEGATION string LBRACKET variables RBRACKET",
 /*  41 */ "domain ::= string EQUAL domains",
 /*  42 */ "domains ::= LPAREN variables RPAREN",
 /*  43 */ "variables ::= variable",
 /*  44 */ "variables ::= variables COMMA variable",
 /*  45 */ "variable ::= string",
 /*  46 */ "variable ::= number",
 /*  47 */ "string ::= STRING",
 /*  48 */ "number ::= NUMBER",
 /*  49 */ "number ::= lnumber DOT rnumber",
 /*  50 */ "number ::= MINUS lnumber DOT rnumber",
 /*  51 */ "lnumber ::= NUMBER",
 /*  52 */ "rnumber ::= NUMBER",
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
** second argument to ASPParserGrammarAlloc() below.  This can be changed by
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
** to ASPParserGrammar and ASPParserGrammarFree.
*/
void *ASPParserGrammarAlloc(void *(*mallocProc)(YYMALLOCARGTYPE)){
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
  ASPParserGrammarARG_FETCH;
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
void ASPParserGrammarFree(
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
int ASPParserGrammarStackPeak(void *p){
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
   ASPParserGrammarARG_FETCH;
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
   ASPParserGrammarARG_STORE; /* Suppress warning about unused %extra_argument var */
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
  { 20, 2 },
  { 20, 0 },
  { 26, 5 },
  { 26, 4 },
  { 26, 5 },
  { 26, 4 },
  { 32, 3 },
  { 32, 3 },
  { 26, 5 },
  { 26, 4 },
  { 26, 4 },
  { 26, 4 },
  { 26, 4 },
  { 26, 8 },
  { 27, 3 },
  { 27, 3 },
  { 27, 1 },
  { 28, 4 },
  { 28, 5 },
  { 28, 6 },
  { 28, 8 },
  { 28, 3 },
  { 28, 4 },
  { 30, 1 },
  { 31, 4 },
  { 31, 5 },
  { 24, 4 },
  { 23, 5 },
  { 23, 5 },
  { 23, 7 },
  { 23, 6 },
  { 23, 6 },
  { 21, 3 },
  { 22, 3 },
  { 25, 1 },
  { 25, 3 },
  { 35, 1 },
  { 35, 1 },
  { 34, 1 },
  { 33, 1 },
  { 33, 3 },
  { 33, 4 },
  { 36, 1 },
  { 37, 1 },
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
  ASPParserGrammarARG_FETCH;
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
	tree->domains.insert(*yymsp[0].minor.yy63); 
	tree->domainNamesList.insert(yymsp[0].minor.yy63->getDomainVar());
	for(auto& v : yymsp[0].minor.yy63->getVars()){
		tree->domainList.insert(v);	
	}
	cout<<yymsp[0].minor.yy63->toString(false);
	delete yymsp[0].minor.yy63;
}
        break;
      case 3: /* prog ::= prog NEWLINE predicate */
{ 
	if(yymsp[0].minor.yy52->needsToBeCompleted()){	
		FactCompletion f(*yymsp[0].minor.yy52);
		tree->facts.insert(std::pair<std::string,FactCompletion>(f.head.getVar(),f)); 
	}	
	delete yymsp[0].minor.yy52;
}
        break;
      case 4: /* prog ::= predicate */
{ 
	if(yymsp[0].minor.yy52->needsToBeCompleted()){
		FactCompletion f(*yymsp[0].minor.yy52);
		tree->facts.insert(std::pair<std::string,FactCompletion>(f.head.getVar(),f)); 	
	}
	delete yymsp[0].minor.yy52;
}
        break;
      case 5: /* prog ::= prog NEWLINE decl */
      case 6: /* prog ::= decl */ yytestcase(yyruleno==6);
{
	tree->variables.insert(*yymsp[0].minor.yy1);
	cout<<yymsp[0].minor.yy1->toString();
	delete yymsp[0].minor.yy1;
}
        break;
      case 7: /* prog ::= prog NEWLINE rule */
      case 8: /* prog ::= rule */ yytestcase(yyruleno==8);
{
	if((yymsp[0].minor.yy9->isHeadTop == false) && (yymsp[0].minor.yy9->toBeCompleted == true))
		tree->rules.insert(std::pair<std::string,RuleCompletion>(yymsp[0].minor.yy9->head.getVar(),*yymsp[0].minor.yy9));
	delete yymsp[0].minor.yy9;
}
        break;
      case 11: /* rule ::= number REVERSE_IMPLICATION LBRACKET ruleU RBRACKET */
{
	yygotominor.yy9 = yymsp[-1].minor.yy9;
	yygotominor.yy9->toBeCompleted = false;
	if(yymsp[-1].minor.yy9->getBodyType() == BodyType::DISJUNCTION){
		throw syntax_exception("Unexpected DISJUNCTION in BODY of RULE.\n");
	}
	cout<<yymsp[-4].minor.yy0->toString()<<SPACE<<"!("<<yymsp[-1].minor.yy9->toString()<<")"<<"\n";
}
        break;
      case 12: /* rule ::= number LBRACKET ruleU RBRACKET */
{
	yygotominor.yy9 = yymsp[-1].minor.yy9;
	yygotominor.yy9->toBeCompleted = false;
	if(yymsp[-1].minor.yy9->getBodyType() == BodyType::CONJUNCTION){
		throw syntax_exception("Unexpected CONJUNCTION in HEAD of RULE.\n");
	}
	cout<<yymsp[-3].minor.yy0->toString()<<SPACE<<"("<<yymsp[-1].minor.yy9->toString()<<")"<<"\n";
}
        break;
      case 13: /* rule ::= REVERSE_IMPLICATION LBRACKET ruleU RBRACKET DOT */
{
	yygotominor.yy9 = yymsp[-2].minor.yy9;
	yymsp[-2].minor.yy9->toBeCompleted = false;
	if(yymsp[-2].minor.yy9->getBodyType() == BodyType::DISJUNCTION){
		throw syntax_exception("Unexpected DISJUNCTION in BODY of RULE.\n");
	}
	cout<<"!("<<yymsp[-2].minor.yy9->toString()<<")."<<"\n";
}
        break;
      case 14: /* rule ::= LBRACKET ruleU RBRACKET DOT */
{
	yygotominor.yy9 = yymsp[-2].minor.yy9;
	yygotominor.yy9->toBeCompleted = false;
	if(yymsp[-2].minor.yy9->getBodyType() == BodyType::CONJUNCTION){
		throw syntax_exception("Unexpected CONJUNCTION in HEAD of RULE.\n");
	}
	cout<<"("<<yymsp[-2].minor.yy9->toString()<<")."<<"\n";
}
        break;
      case 15: /* ruleU ::= body CONJUNCTION bodydef */
{
	yygotominor.yy9 = new RuleCompletion;
	yymsp[-2].minor.yy45->appendStr(yymsp[0].minor.yy12->getPredicate().toString(),false,false,true);
	yygotominor.yy9->appendStr(yymsp[-2].minor.yy45->toString());
	yygotominor.yy9->setBodyType(BodyType::CONJUNCTION);
	delete yymsp[-2].minor.yy45;
	delete yymsp[0].minor.yy12;
}
        break;
      case 16: /* ruleU ::= body DISJUNCTION bodydef */
{
	yygotominor.yy9 = new RuleCompletion;	
	yygotominor.yy9->isHeadTop = true;
	RULE_COMPLETION_BODY_TOP(yymsp[-2].minor.yy45,yymsp[0].minor.yy12)
	yymsp[-2].minor.yy45->appendStr(yymsp[0].minor.yy12->getPredicate().toString(),false,true,false);
	yygotominor.yy9->appendStr(yymsp[-2].minor.yy45->toString());
	yygotominor.yy9->setBodyType(BodyType::DISJUNCTION);
	delete yymsp[-2].minor.yy45;
	delete yymsp[0].minor.yy12;
}
        break;
      case 17: /* rule ::= REVERSE_IMPLICATION body CONJUNCTION bodydef DOT */
{
	yygotominor.yy9 = new RuleCompletion;
	yygotominor.yy9->isHeadTop = true;
	yymsp[-3].minor.yy45->appendStr(yymsp[-1].minor.yy12->getPredicate().toString(),false,false,true);
	std::cout<<"!("<<yymsp[-3].minor.yy45->toString()<<")."<<"\n";	
	delete yymsp[-3].minor.yy45;
	delete yymsp[-1].minor.yy12;
}
        break;
      case 18: /* rule ::= body DISJUNCTION bodydef DOT */
{
	//Doing this 
	yygotominor.yy9 = new RuleCompletion;
	yygotominor.yy9->isHeadTop = true;
	RULE_COMPLETION_BODY_TOP(yymsp[-3].minor.yy45,yymsp[-1].minor.yy12)
	yymsp[-3].minor.yy45->appendStr(yymsp[-1].minor.yy12->getPredicate().toString(),false,true,false);
	std::cout<<yymsp[-3].minor.yy45->toString()<<"."<<"\n";
	delete yymsp[-3].minor.yy45;
	delete yymsp[-1].minor.yy12;
}
        break;
      case 19: /* rule ::= number body DISJUNCTION bodydef */
{
	//Doing this 
	yygotominor.yy9 = new RuleCompletion;
	yygotominor.yy9->isHeadTop = true;
	RULE_COMPLETION_BODY_TOP(yymsp[-2].minor.yy45,yymsp[0].minor.yy12)
	yymsp[-2].minor.yy45->appendStr(yymsp[0].minor.yy12->getPredicate().toString(),false,true,false);
	std::cout<<yymsp[-3].minor.yy0->toString()<<SPACE<<yymsp[-2].minor.yy45->toString()<<"\n";
	delete yymsp[-2].minor.yy45;
	delete yymsp[0].minor.yy12;
}
        break;
      case 20: /* rule ::= head REVERSE_IMPLICATION body DOT */
{
	
	RULE_COMPLETION_BH(yymsp[-1].minor.yy45,yymsp[-3].minor.yy53);
	yygotominor.yy9 = new RuleCompletion(yymsp[-3].minor.yy53->getPredicate(),predList, resultMap, varMap);
	std::cout<<yymsp[-1].minor.yy45->toString()<<" => "<<yymsp[-3].minor.yy53->toString()<<"."<<"\n";
	delete yymsp[-1].minor.yy45;
	delete yymsp[-3].minor.yy53;
}
        break;
      case 21: /* rule ::= number head REVERSE_IMPLICATION body */
{
	RULE_COMPLETION_BH(yymsp[0].minor.yy45,yymsp[-2].minor.yy53);
	yygotominor.yy9 = new RuleCompletion(yymsp[-2].minor.yy53->getPredicate(),predList, resultMap, varMap);
	std::cout<< yymsp[-3].minor.yy0->toString()<<SPACE<<yymsp[0].minor.yy45->toString()<<" => "<<yymsp[-2].minor.yy53->toString()<<"\n";
	delete yymsp[0].minor.yy45;
	delete yymsp[-2].minor.yy53;
}
        break;
      case 22: /* rule ::= number NEGATION NEGATION LBRACKET head REVERSE_IMPLICATION body RBRACKET */
{
	yygotominor.yy9 = new RuleCompletion;
	yygotominor.yy9->isHeadTop = true;	
	tree->statHasDblNeg = true;
	std::cout<< yymsp[-7].minor.yy0->toString() << SPACE <<"!!("<<yymsp[-1].minor.yy45->toString()<<" => "<<yymsp[-3].minor.yy53->toString()<<"\n"; 
	delete yymsp[-1].minor.yy45;
	delete yymsp[-3].minor.yy53;
}
        break;
      case 23: /* body ::= body CONJUNCTION bodydef */
{
	yygotominor.yy45 = yymsp[-2].minor.yy45;
	yymsp[-2].minor.yy45->addPredicate(yymsp[0].minor.yy12->getPredicate());
	yygotominor.yy45->appendStr(yymsp[0].minor.yy12->getPredicate().toString(),false,false,true);
	delete yymsp[0].minor.yy12;
}
        break;
      case 24: /* body ::= body DISJUNCTION bodydef */
{
	yygotominor.yy45 = yymsp[-2].minor.yy45;
	yymsp[-2].minor.yy45->addPredicate(yymsp[0].minor.yy12->getPredicate());
	yygotominor.yy45->appendStr(yymsp[0].minor.yy12->getPredicate().toString(),false,true,false);
	delete yymsp[0].minor.yy12;
}
        break;
      case 25: /* body ::= bodydef */
{
	yygotominor.yy45 = new Body;
	yygotominor.yy45->addPredicate(yymsp[0].minor.yy12->getPredicate());
	yygotominor.yy45->appendStr(yymsp[0].minor.yy12->getPredicate().toString(),false,false,false);
	delete yymsp[0].minor.yy12;
}
        break;
      case 26: /* bodydef ::= string LBRACKET variables RBRACKET */
{	
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-1].minor.yy36)
		vars.push_back(*v);
	
	Predicate p(yymsp[-3].minor.yy0->token, vars);
	yygotominor.yy12 = new BodyDef;
	yygotominor.yy12->addPredicate(p);
	delete yymsp[-1].minor.yy36;
}
        break;
      case 27: /* bodydef ::= NEGATION string LBRACKET variables RBRACKET */
{	
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-1].minor.yy36)
		vars.push_back(*v);
	
	Predicate p(yymsp[-3].minor.yy0->token, vars);
	p.setSingleNegation(true);
	yygotominor.yy12 = new BodyDef;
	yygotominor.yy12->addPredicate(p);
	delete yymsp[-1].minor.yy36;
}
        break;
      case 28: /* bodydef ::= NEGATION NEGATION string LBRACKET variables RBRACKET */
{	
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-1].minor.yy36)
		vars.push_back(*v);
	
	Predicate p(yymsp[-3].minor.yy0->token, vars);
	p.setDoubleNegation(true);
	yygotominor.yy12 = new BodyDef;
	yygotominor.yy12->addPredicate(p);
	tree->statHasDblNeg = true;
	delete yymsp[-1].minor.yy36;
}
        break;
      case 29: /* bodydef ::= LBRACKET NEGATION NEGATION string LBRACKET variables RBRACKET RBRACKET */
{	
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-2].minor.yy36)
		vars.push_back(*v);
	
	Predicate p(yymsp[-4].minor.yy0->token, vars);
	p.setDoubleNegation(true);
	tree->statHasDblNeg = true;
	yygotominor.yy12 = new BodyDef;
	yygotominor.yy12->addPredicate(p);
	delete yymsp[-2].minor.yy36;
}
        break;
      case 30: /* bodydef ::= string EQUAL string */
{
	Predicate p(yymsp[-2].minor.yy0->token,yymsp[0].minor.yy0->token);
	p.setEquality();
	yygotominor.yy12 = new BodyDef;
	yygotominor.yy12->addPredicate(p);
}
        break;
      case 31: /* bodydef ::= string NEGATION EQUAL string */
{
	Predicate p(yymsp[-3].minor.yy0->token,yymsp[0].minor.yy0->token);
	p.setInEquality();
	yygotominor.yy12 = new BodyDef;
	yygotominor.yy12->addPredicate(p);
}
        break;
      case 32: /* head ::= headdef */
{ 
	yygotominor.yy53 = yymsp[0].minor.yy53;
}
        break;
      case 33: /* headdef ::= string LBRACKET variables RBRACKET */
{
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-1].minor.yy36)
		vars.push_back(*v);
	
	Predicate p(yymsp[-3].minor.yy0->token, vars);
	yygotominor.yy53 = new Head(p);
	// yygotominor.yy53->addPredicate(p);
	delete yymsp[-1].minor.yy36;
}
        break;
      case 34: /* headdef ::= NEGATION string LBRACKET variables RBRACKET */
{
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-1].minor.yy36)
		vars.push_back(*v);
	
	Predicate p(yymsp[-3].minor.yy0->token, vars);
	p.setSingleNegation(true);
	yygotominor.yy53 = new Head(p);
	yygotominor.yy53->addPredicate(p);
	delete yymsp[-1].minor.yy36;
}
        break;
      case 35: /* decl ::= string LBRACKET variables RBRACKET */
{
	yygotominor.yy1 = new Variable;
	std::map<int, Domain> posMap;
	std::set<Domain>::iterator itr;
	int i=0;
	for(auto& v : *yymsp[-1].minor.yy36){
		itr = tree->domains.find(*v);
		if (itr == tree->domains.end()){
			std::cout<<"Error:Domain:"+ *v +" not found.\n";
			//Exit
		}
		else{
			// itr = tree->domains.find(*v);
			yygotominor.yy1->setVar(yymsp[-3].minor.yy0->token);
			posMap[i++] = *itr;
		}
	}
	yygotominor.yy1->setPosMap(posMap);
	delete yymsp[-1].minor.yy36;
}
        break;
      case 36: /* predicate ::= string LBRACKET variables RBRACKET DOT */
{
	yygotominor.yy52 = new Predicate;
	yygotominor.yy52->setVar(yymsp[-4].minor.yy0->token);
	yygotominor.yy52->setTokens(*yymsp[-2].minor.yy36);
	std::string s1;
	cout<<yygotominor.yy52->toString(s1,true);
	delete yymsp[-2].minor.yy36;
}
        break;
      case 37: /* predicate ::= number string LBRACKET variables RBRACKET */
{
	yygotominor.yy52 = new Predicate;
	yygotominor.yy52->setVar(yymsp[-3].minor.yy0->token);
	yygotominor.yy52->setTokens(*yymsp[-1].minor.yy36);
	cout<<yygotominor.yy52->toString(yymsp[-4].minor.yy0->toString()+SPACE, false);
	delete yymsp[-1].minor.yy36;
}
        break;
      case 38: /* predicate ::= number NEGATION NEGATION string LBRACKET variables RBRACKET */
{
	yygotominor.yy52 = new Predicate;
	yygotominor.yy52->notToBeCompleted();
	tree->statHasDblNeg = true;
	yygotominor.yy52->setVar(yymsp[-3].minor.yy0->token);
	yygotominor.yy52->setTokens(*yymsp[-1].minor.yy36);
	cout<<yygotominor.yy52->toString(yymsp[-6].minor.yy0->toString()+SPACE, false);
	delete yymsp[-1].minor.yy36;
}
        break;
      case 39: /* predicate ::= number NEGATION string LBRACKET variables RBRACKET */
{
	yygotominor.yy52 = new Predicate;
	yygotominor.yy52->notToBeCompleted();
	yygotominor.yy52->setVar(yymsp[-3].minor.yy0->token);
	yygotominor.yy52->setTokens(*yymsp[-1].minor.yy36);
	cout<<yygotominor.yy52->toString(yymsp[-5].minor.yy0->toString()+SPACE+"!", false);
	delete yymsp[-1].minor.yy36;
}
        break;
      case 40: /* predicate ::= NEGATION NEGATION string LBRACKET variables RBRACKET */
{
	yygotominor.yy52 = new Predicate;
	yygotominor.yy52->notToBeCompleted();
	tree->statHasDblNeg = true;
	yygotominor.yy52->setVar(yymsp[-3].minor.yy0->token);
	yygotominor.yy52->setTokens(*yymsp[-1].minor.yy36);
	std::string s1; 
	cout<<yygotominor.yy52->toString(s1, false);
	delete yymsp[-1].minor.yy36;
}
        break;
      case 41: /* domain ::= string EQUAL domains */
{ 
	yygotominor.yy63 = yymsp[0].minor.yy63;
	yymsp[0].minor.yy63->setDomainVar(yymsp[-2].minor.yy0->token);
}
        break;
      case 42: /* domains ::= LPAREN variables RPAREN */
{
	yygotominor.yy63 = new Domain();
	yygotominor.yy63->setVars(*yymsp[-1].minor.yy36);
	delete yymsp[-1].minor.yy36;
}
        break;
      case 43: /* variables ::= variable */
{
	yygotominor.yy36 = new std::vector<std::string*>();
	yygotominor.yy36->push_back(yymsp[0].minor.yy0->token);
}
        break;
      case 44: /* variables ::= variables COMMA variable */
{
	yygotominor.yy36 = yymsp[-2].minor.yy36;
	yymsp[-2].minor.yy36->push_back(yymsp[0].minor.yy0->token);
}
        break;
      case 45: /* variable ::= string */
      case 46: /* variable ::= number */ yytestcase(yyruleno==46);
      case 47: /* string ::= STRING */ yytestcase(yyruleno==47);
      case 48: /* number ::= NUMBER */ yytestcase(yyruleno==48);
{ yygotominor.yy0=yymsp[0].minor.yy0;}
        break;
      case 49: /* number ::= lnumber DOT rnumber */
{ 
	// yygotominor.yy0 = new Token(*(yymsp[-2].minor.yy0->token)+"."+*(yymsp[0].minor.yy0->token));
	yygotominor.yy0 = yymsp[-2].minor.yy0;
	yygotominor.yy0->modifyToken(*(yymsp[-2].minor.yy0->token)+"."+*(yymsp[0].minor.yy0->token));
}
        break;
      case 50: /* number ::= MINUS lnumber DOT rnumber */
{
	yygotominor.yy0 = yymsp[-2].minor.yy0;
	yygotominor.yy0->modifyToken("-"+*(yymsp[-2].minor.yy0->token)+"."+*(yymsp[0].minor.yy0->token));
}
        break;
      case 51: /* lnumber ::= NUMBER */
      case 52: /* rnumber ::= NUMBER */ yytestcase(yyruleno==52);
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
  ASPParserGrammarARG_FETCH;
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
  ASPParserGrammarARG_STORE; /* Suppress warning about unused %extra_argument variable */
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
  ASPParserGrammarARG_FETCH;
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
  ASPParserGrammarARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  ASPParserGrammarARG_FETCH;
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
  ASPParserGrammarARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "ASPParserGrammarAlloc" which describes the current state of the parser.
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
void ASPParserGrammar(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  ASPParserGrammarTOKENTYPE yyminor       /* The value for the token */
  ASPParserGrammarARG_PDECL               /* Optional %extra_argument parameter */
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
  ASPParserGrammarARG_STORE;

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

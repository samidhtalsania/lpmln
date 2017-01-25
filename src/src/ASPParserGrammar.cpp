/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is included that follows the "include" declaration
** in the input grammar file. */
#include <stdio.h>
#line 2 "ASPParserGrammar.y"

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

#line 111 "ASPParserGrammar.y"


	RuleCompletion* RuleCompletion_BH(Body* B, Head* H, Tree* tree){
		std::set<std::pair<std::string,std::string>> orphanVarsMap;  
		std::set<std::pair<std::string,std::string>> orphanVarsHeadMap; 
		std::vector<Predicate> predList = B->getPredicate(); 
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
		for(auto& str : H->getPredicate().getTokens()){ 
			if(tree->isConstant(str)){ 
				varMap[count++] = std::pair<int, std::string>(count, str); 
			} 
			else 
				count++; 
			 
			if(tree->variables.find(H->getPredicate().getVar()) == tree->variables.end()){ 
				undefined_predicate ex(H->getPredicate().getVar()); 
				throw ex; 
			} 
			else	 
				orphanVarsHeadMap.insert(std::pair<std::string, std::string>(str,tree->variables.find(H->getPredicate().getVar())->getPosMap().at(tempCount++).getDomainVar())); 
		} 
		std::set<std::string> result; 
		tree->removeConstantsPair(orphanVarsMap); 
		tree->removeConstantsPair(orphanVarsHeadMap); 
		std::set<std::pair<std::string,std::string>> resultMap; 
		std::set_difference(orphanVarsMap.begin(), orphanVarsMap.end(), orphanVarsHeadMap.begin(), orphanVarsHeadMap.end(),std::inserter(resultMap, resultMap.end()), cmp());
		RuleCompletion* rule = new RuleCompletion(H->getPredicate(),predList, resultMap, varMap);
		return rule;
	}
		
	void RuleCompletion_HD_BT(Head* B, Tree* tree){
		std::vector<Predicate> pred = B->getPredicateList(); 
		for(unsigned long int i=0;i<pred.size();i++){ 
			Head* H = new Head(pred.at(i)); 
			std::vector<Predicate> temp; 
			for (unsigned long int j = 0; j < pred.size(); j++){ 
				if(j == i) continue; 
				bool singleN = pred.at(j).isSingleNegated(); 
				bool doubleN = pred.at(j).isDoubleNegated(); 
				if(pred.at(j).isSingleNegated()){ 
					pred.at(j).setSingleNegation(false); 
					pred.at(j).setDoubleNegation(true); 
				} 
				else if(pred.at(j).isDoubleNegated()){ 
					pred.at(j).setDoubleNegation(false); 
					pred.at(j).setSingleNegation(true); 
				} 
				else{ 
					pred.at(j).setSingleNegation(true);	 
				} 
				temp.push_back(pred.at(j)); 
				pred.at(j).setSingleNegation(singleN); 
				pred.at(j).setDoubleNegation(doubleN); 
			} 
			Body* b = new Body(temp); 
			// RULE_COMPLETION_BH(b,H); 
			// RuleCompletion* R1 = new RuleCompletion(H->getPredicate(),predList, resultMap, varMap); 
			RuleCompletion* R1 = RuleCompletion_BH(b,H,tree); 
			tree->rules.insert(std::pair<std::string,RuleCompletion>(R1->getHead().getVar(),*R1)); 
			delete R1; 
			delete b;
			delete H;
		}
	}

	void RuleCompletion_HD_BC(Head* H, Body* B, bool hard, Tree* tree){
		std::vector<Predicate> pred = H->getPredicateList(); 
		std::vector<Predicate> bp = B->getPredicate(); 
		for(unsigned long int i=0;i<pred.size();i++){ 
			Head* H = new Head(pred.at(i)); 
			std::vector<Predicate> temp;
			for (unsigned long int j = 0; j < pred.size(); j++){ 
				if(j == i) continue; 
				bool singleN = pred.at(j).isSingleNegated(); 
				bool doubleN = pred.at(j).isDoubleNegated(); 
				if(pred.at(j).isSingleNegated()){ 
					pred.at(j).setSingleNegation(false); 
				} 
				else if(pred.at(j).isDoubleNegated()){ 
					pred.at(j).setDoubleNegation(false); 
					pred.at(j).setSingleNegation(true); 
				} 
				else{ 
					pred.at(j).setSingleNegation(true);	 
				} 
				temp.push_back(pred.at(j)); 
				pred.at(j).setSingleNegation(singleN); 
				pred.at(j).setDoubleNegation(doubleN); 
			}

			for (unsigned long int j = 0; j < bp.size(); ++j){ 
				temp.push_back(bp.at(j)); 
			} 
			
			Body* b = new Body(temp); 
			// RULE_COMPLETION_BH(b,H); 
			// RuleCompletion* R1 = new RuleCompletion(H->getPredicate(),predList, resultMap, varMap); 
			RuleCompletion* R1 = RuleCompletion_BH(b,H,tree); 
			tree->rules.insert(std::pair<std::string,RuleCompletion>(R1->getHead().getVar(),*R1)); 
			delete R1; 
			// std::string op;
			// op = b->toString() + "=>" + H->toString(); 
			// if(hard) 
			// 	op += "."; 
			// op += "\n";
			// cout << op; 

			delete b;
			delete H;
		}
	}
#line 175 "ASPParserGrammar.c"
#include "ASPParserGrammar.h"
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
#define ASP_PARSE_TOKEN_EQUAL                           1
#define ASP_PARSE_TOKEN_COMMA                           2
#define ASP_PARSE_TOKEN_LPAREN                          3
#define ASP_PARSE_TOKEN_RPAREN                          4
#define ASP_PARSE_TOKEN_NEWLINE                         5
#define ASP_PARSE_TOKEN_CONJUNCTION                     6
#define ASP_PARSE_TOKEN_DISJUNCTION                     7
#define ASP_PARSE_TOKEN_LBRACKET                        8
#define ASP_PARSE_TOKEN_RBRACKET                        9
#define ASP_PARSE_TOKEN_IMPLICATION                    10
#define ASP_PARSE_TOKEN_REVERSE_IMPLICATION            11
#define ASP_PARSE_TOKEN_NEGATION                       12
#define ASP_PARSE_TOKEN_WS                             13
#define ASP_PARSE_TOKEN_DOT                            14
#define ASP_PARSE_TOKEN_STRING                         15
#define ASP_PARSE_TOKEN_NUMBER                         16
#define ASP_PARSE_TOKEN_MINUS                          17
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
**    ASPParserGrammarTOKENTYPE     is the data type used for minor tokens given 
**                       directly to the parser from the tokenizer.
**    YYMINORTYPE        is the data type used for all minor tokens.
**                       This is typically a union of many types, one of
**                       which is ASPParserGrammarTOKENTYPE.  The entry in the union
**                       for base tokens is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    ASPParserGrammarARG_SDECL     A static variable declaration for the %extra_argument
**    ASPParserGrammarARG_PDECL     A parameter declaration for the %extra_argument
**    ASPParserGrammarARG_STORE     Code to store %extra_argument into yypParser
**    ASPParserGrammarARG_FETCH     Code to extract %extra_argument from yypParser
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
*/
#define YYCODETYPE unsigned char
#define YYNOCODE 38
#define YYACTIONTYPE unsigned char
#if INTERFACE
#define ASPParserGrammarTOKENTYPE Token*
#endif
typedef union {
  int yyinit;
  ASPParserGrammarTOKENTYPE yy0;
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
#if INTERFACE
#define ASPParserGrammarARG_SDECL Tree* tree;
#define ASPParserGrammarARG_PDECL ,Tree* tree
#define ASPParserGrammarARG_FETCH Tree* tree = yypParser->tree
#define ASPParserGrammarARG_STORE yypParser->tree = tree
#endif
#define YYNSTATE 146
#define YYNRULE 52
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
#define YY_ACTTAB_COUNT (293)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   199,   74,  109,  146,  108,  107,   29,  106,    1,  120,
 /*    10 */    25,   57,   17,   18,   48,  145,  100,  144,  143,  140,
 /*    20 */   142,  171,  120,  112,   57,  171,   18,   48,   20,  100,
 /*    30 */   120,   17,   66,    5,  130,   50,   22,   33,  128,   16,
 /*    40 */   136,  101,   45,  103,   89,   28,   91,  104,   73,   50,
 /*    50 */    27,   31,   72,  118,   23,  137,  138,  131,  100,  137,
 /*    60 */   138,  131,  100,   71,  120,   28,   55,   70,  122,   50,
 /*    70 */   137,  138,  131,  100,  137,  138,  131,  100,   17,  141,
 /*    80 */   103,   89,   69,   91,   88,  127,   50,   64,  161,  137,
 /*    90 */   138,  131,  100,   62,  137,  138,  131,  100,   60,  196,
 /*   100 */   137,  138,  131,  100,   17,  137,  138,  131,  100,  103,
 /*   110 */    89,   92,   91,   82,   28,   50,   42,  103,   89,   53,
 /*   120 */    91,   80,  115,   50,   52,  102,  137,  138,  131,  100,
 /*   130 */    50,  137,  138,  131,  100,   51,  137,  138,  139,  100,
 /*   140 */    17,   43,  137,  138,  131,  100,   43,   86,   15,   46,
 /*   150 */    44,   11,   98,    7,  105,   35,   32,   98,  136,   14,
 /*   160 */   176,  174,   94,    4,  176,  174,   95,   98,  113,   13,
 /*   170 */    37,   85,  123,  136,   65,  123,   77,   50,  175,   27,
 /*   180 */    50,    6,  175,   58,  123,   37,   56,  123,  136,   50,
 /*   190 */    40,   17,   50,   54,  123,  120,   12,   68,   63,   50,
 /*   200 */    49,  136,  101,   45,   95,   17,   17,   28,   36,  126,
 /*   210 */    17,  136,   61,   59,  174,  114,   26,   47,  174,   17,
 /*   220 */    21,  111,   17,   41,   39,   34,  136,  136,  136,   75,
 /*   230 */    24,   38,    3,   90,  136,   30,  162,  136,   50,  172,
 /*   240 */   125,   10,   67,  124,  136,   28,  121,   50,   50,   78,
 /*   250 */     9,   50,    8,  134,   50,   81,   79,  119,    2,  117,
 /*   260 */    19,  135,  116,  200,  200,  110,  133,  200,  132,   99,
 /*   270 */   136,  130,  200,  129,   96,  200,  200,  200,  200,  200,
 /*   280 */   200,  200,  200,  200,  200,  200,   93,   87,  200,   76,
 /*   290 */    97,   83,   84,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    19,   20,   21,    0,   23,   24,    7,   26,    5,   28,
 /*    10 */    11,   30,    2,   32,   33,   21,   35,   23,   24,    9,
 /*    20 */    26,    7,   28,   22,   30,   11,   32,   33,    3,   35,
 /*    30 */    28,    2,   30,    8,   33,   33,   11,   12,    9,    8,
 /*    40 */    15,   16,   17,   27,   28,    6,   30,   31,   25,   33,
 /*    50 */     7,    6,   25,   14,   11,   32,   33,   34,   35,   32,
 /*    60 */    33,   34,   35,   25,   28,    6,   30,   25,    9,   33,
 /*    70 */    32,   33,   34,   35,   32,   33,   34,   35,    2,    9,
 /*    80 */    27,   28,   25,   30,   31,    9,   33,   25,    9,   32,
 /*    90 */    33,   34,   35,   25,   32,   33,   34,   35,   25,   14,
 /*   100 */    32,   33,   34,   35,    2,   32,   33,   34,   35,   27,
 /*   110 */    28,    9,   30,   31,    6,   33,    1,   27,   28,   25,
 /*   120 */    30,   31,   14,   33,   25,   28,   32,   33,   34,   35,
 /*   130 */    33,   32,   33,   34,   35,   25,   32,   33,   34,   35,
 /*   140 */     2,    1,   32,   33,   34,   35,    1,    9,    8,   14,
 /*   150 */    14,    8,   12,    8,   11,   12,    1,   12,   15,    8,
 /*   160 */     7,    7,   12,    8,   11,   11,    8,   12,   14,    8,
 /*   170 */    12,   27,   28,   15,   27,   28,    4,   33,    7,    7,
 /*   180 */    33,    8,   11,   27,   28,   12,   27,   28,   15,   33,
 /*   190 */    12,    2,   33,   27,   28,   28,    8,   30,    9,   33,
 /*   200 */    33,   15,   16,   17,    8,    2,    2,    6,   12,    9,
 /*   210 */     2,   15,    9,    9,    7,   14,    7,    9,   11,    2,
 /*   220 */    11,    4,    2,   12,   12,   12,   15,   15,   15,    9,
 /*   230 */     8,   12,    3,   28,   15,    7,    9,   15,   33,    7,
 /*   240 */     9,    8,   28,   28,   15,    6,   28,   33,   33,   28,
 /*   250 */     8,   33,    8,   16,   33,    9,    9,   14,    8,   14,
 /*   260 */    11,   36,   14,   37,   37,   14,   36,   37,   16,   35,
 /*   270 */    15,   33,   37,   33,   33,   37,   37,   37,   37,   37,
 /*   280 */    37,   37,   37,   37,   37,   37,   33,   33,   37,   33,
 /*   290 */    33,   33,   33,
};
#define YY_SHIFT_USE_DFLT (-2)
#define YY_SHIFT_COUNT (105)
#define YY_SHIFT_MIN   (-1)
#define YY_SHIFT_MAX   (255)
static const short yy_shift_ofst[] = {
 /*     0 */    25,   25,  186,  186,  186,  196,  196,  186,  186,  186,
 /*    10 */   186,  196,  186,  186,  186,  186,  158,  186,  143,  158,
 /*    20 */   158,  158,  173,  158,  158,  158,  158,  158,  158,  158,
 /*    30 */   158,  158,  229,  219,  222,  213,  212,  211,  255,  255,
 /*    40 */   255,  255,  255,  255,  237,  252,  237,  154,  155,  145,
 /*    50 */   140,  220,  217,  208,  201,  172,  108,  209,   39,  207,
 /*    60 */   204,  171,  203,  153,  189,   59,   43,   14,   -1,  138,
 /*    70 */   102,   76,   29,   10,    3,  251,  250,  249,  248,  245,
 /*    80 */   247,  243,  246,  244,  242,  239,  200,  233,  231,  232,
 /*    90 */   227,  228,  200,  188,  178,  150,  161,  151,  115,  136,
 /*   100 */   135,   85,   79,   45,   70,   31,
};
#define YY_REDUCE_USE_DFLT (-20)
#define YY_REDUCE_COUNT (46)
#define YY_REDUCE_MIN   (-19)
#define YY_REDUCE_MAX   (259)
static const short yy_reduce_ofst[] = {
 /*     0 */   -19,   -6,  110,   99,   94,   90,   82,   73,   68,   62,
 /*    10 */    57,   53,   42,   38,   27,   23,   16,  104,  167,  166,
 /*    20 */    36,  159,  156,  147,    2,  144,  221,  218,  215,  214,
 /*    30 */   205,   97,    1,  257,  259,  258,  257,  257,  256,  254,
 /*    40 */   253,  241,  240,  238,  230,  234,  225,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   156,  155,  198,  198,  198,  198,  198,  198,  198,  198,
 /*    10 */   198,  198,  198,  198,  198,  198,  198,  198,  198,  198,
 /*    20 */   198,  198,  198,  198,  198,  198,  198,  198,  198,  198,
 /*    30 */   198,  198,  198,  198,  198,  198,  198,  198,  198,  198,
 /*    40 */   198,  198,  198,  198,  198,  198,  198,  180,  198,  198,
 /*    50 */   198,  198,  198,  198,  198,  198,  198,  198,  198,  182,
 /*    60 */   198,  184,  198,  183,  198,  198,  198,  165,  198,  198,
 /*    70 */   198,  198,  198,  198,  198,  176,  198,  198,  171,  198,
 /*    80 */   198,  198,  198,  198,  198,  167,  176,  198,  198,  173,
 /*    90 */   171,  198,  198,  198,  198,  198,  198,  198,  198,  198,
 /*   100 */   198,  193,  170,  198,  198,  198,  154,  152,  150,  148,
 /*   110 */   185,  187,  186,  181,  169,  166,  164,  160,  163,  159,
 /*   120 */   172,  171,  168,  173,  170,  158,  177,  176,  175,  179,
 /*   130 */   178,  188,  196,  195,  197,  194,  192,  191,  190,  189,
 /*   140 */   174,  157,  153,  151,  149,  147,
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
  "bodydef",       "bodydef2",      "head",          "ruleU",       
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
 /*  11 */ "rule ::= number REVERSE_IMPLICATION LBRACKET ruleU RBRACKET",
 /*  12 */ "rule ::= number LBRACKET ruleU RBRACKET",
 /*  13 */ "rule ::= REVERSE_IMPLICATION LBRACKET ruleU RBRACKET DOT",
 /*  14 */ "rule ::= LBRACKET ruleU RBRACKET DOT",
 /*  15 */ "ruleU ::= body CONJUNCTION bodydef",
 /*  16 */ "ruleU ::= head DISJUNCTION bodydef",
 /*  17 */ "rule ::= REVERSE_IMPLICATION body DOT",
 /*  18 */ "rule ::= head DISJUNCTION bodydef DOT",
 /*  19 */ "rule ::= number head DISJUNCTION bodydef",
 /*  20 */ "rule ::= head REVERSE_IMPLICATION body DOT",
 /*  21 */ "rule ::= number head REVERSE_IMPLICATION body",
 /*  22 */ "rule ::= number NEGATION NEGATION LBRACKET head REVERSE_IMPLICATION body RBRACKET",
 /*  23 */ "rule ::= LPAREN head RPAREN REVERSE_IMPLICATION body DOT",
 /*  24 */ "body ::= body CONJUNCTION bodydef",
 /*  25 */ "head ::= head DISJUNCTION bodydef",
 /*  26 */ "head ::= bodydef",
 /*  27 */ "body ::= bodydef",
 /*  28 */ "bodydef ::= string LBRACKET variables RBRACKET",
 /*  29 */ "bodydef ::= NEGATION string LBRACKET variables RBRACKET",
 /*  30 */ "bodydef ::= NEGATION NEGATION string LBRACKET variables RBRACKET",
 /*  31 */ "bodydef ::= LBRACKET NEGATION NEGATION string LBRACKET variables RBRACKET RBRACKET",
 /*  32 */ "bodydef ::= string EQUAL string",
 /*  33 */ "bodydef ::= string NEGATION EQUAL string",
 /*  34 */ "decl ::= string LBRACKET variables RBRACKET",
 /*  35 */ "predicate ::= string LBRACKET variables RBRACKET DOT",
 /*  36 */ "predicate ::= number string LBRACKET variables RBRACKET",
 /*  37 */ "predicate ::= number NEGATION NEGATION string LBRACKET variables RBRACKET",
 /*  38 */ "predicate ::= number NEGATION string LBRACKET variables RBRACKET",
 /*  39 */ "predicate ::= NEGATION NEGATION string LBRACKET variables RBRACKET DOT",
 /*  40 */ "domain ::= string EQUAL domains",
 /*  41 */ "domains ::= LPAREN variables RPAREN",
 /*  42 */ "variables ::= variable",
 /*  43 */ "variables ::= variables COMMA variable",
 /*  44 */ "variable ::= string",
 /*  45 */ "variable ::= number",
 /*  46 */ "string ::= STRING",
 /*  47 */ "number ::= NUMBER",
 /*  48 */ "number ::= lnumber DOT rnumber",
 /*  49 */ "number ::= MINUS lnumber DOT rnumber",
 /*  50 */ "lnumber ::= NUMBER",
 /*  51 */ "rnumber ::= NUMBER",
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
** to ASPParserGrammar and ASPParserGrammarFree.
*/
void *ASPParserGrammarAlloc(void *(*mallocProc)(size_t)){
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
  ASPParserGrammarARG_FETCH;
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
**       obtained from ASPParserGrammarAlloc.
** <li>  A pointer to a function used to reclaim memory obtained
**       from malloc.
** </ul>
*/
void ASPParserGrammarFree(
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
int ASPParserGrammarStackPeak(void *p){
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
   ASPParserGrammarARG_STORE; /* Suppress warning about unused %extra_argument var */
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
  { 31, 3 },
  { 31, 3 },
  { 26, 3 },
  { 26, 4 },
  { 26, 4 },
  { 26, 4 },
  { 26, 4 },
  { 26, 8 },
  { 26, 6 },
  { 27, 3 },
  { 30, 3 },
  { 30, 1 },
  { 27, 1 },
  { 28, 4 },
  { 28, 5 },
  { 28, 6 },
  { 28, 8 },
  { 28, 3 },
  { 28, 4 },
  { 24, 4 },
  { 23, 5 },
  { 23, 5 },
  { 23, 7 },
  { 23, 6 },
  { 23, 7 },
  { 21, 3 },
  { 22, 3 },
  { 25, 1 },
  { 25, 3 },
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
  ASPParserGrammarARG_FETCH;
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
      case 1: /* prog ::= prog NEWLINE domain */
      case 2: /* prog ::= domain */ yytestcase(yyruleno==2);
#line 241 "ASPParserGrammar.y"
{ 
	tree->domains.insert(*yymsp[0].minor.yy51); 
	tree->domainNamesList.insert(yymsp[0].minor.yy51->getDomainVar());
	for(auto& v : yymsp[0].minor.yy51->getVars()){
		tree->domainList.insert(v);	
	}
	cout<<yymsp[0].minor.yy51->toString(false);
	delete yymsp[0].minor.yy51;
}
#line 1044 "ASPParserGrammar.c"
        break;
      case 3: /* prog ::= prog NEWLINE predicate */
#line 260 "ASPParserGrammar.y"
{ 
	if(yymsp[0].minor.yy26->needsToBeCompleted()){	
		FactCompletion f(*yymsp[0].minor.yy26);
		tree->facts.insert(std::pair<std::string,FactCompletion>(f.getHead().getVar(),f)); 
	}	
	delete yymsp[0].minor.yy26;
}
#line 1055 "ASPParserGrammar.c"
        break;
      case 4: /* prog ::= predicate */
#line 268 "ASPParserGrammar.y"
{ 
	if(yymsp[0].minor.yy26->needsToBeCompleted()){
		FactCompletion f(*yymsp[0].minor.yy26);
		tree->facts.insert(std::pair<std::string,FactCompletion>(f.getHead().getVar(),f)); 	
	}
	delete yymsp[0].minor.yy26;
}
#line 1066 "ASPParserGrammar.c"
        break;
      case 5: /* prog ::= prog NEWLINE decl */
      case 6: /* prog ::= decl */ yytestcase(yyruleno==6);
#line 276 "ASPParserGrammar.y"
{
	tree->variables.insert(*yymsp[0].minor.yy57);
	cout<<yymsp[0].minor.yy57->toString();
	delete yymsp[0].minor.yy57;
}
#line 1076 "ASPParserGrammar.c"
        break;
      case 7: /* prog ::= prog NEWLINE rule */
      case 8: /* prog ::= rule */ yytestcase(yyruleno==8);
#line 287 "ASPParserGrammar.y"
{
	if((yymsp[0].minor.yy21->isHeadTop == false) && (yymsp[0].minor.yy21->toBeCompleted == true))
		tree->rules.insert(std::pair<std::string,RuleCompletion>(yymsp[0].minor.yy21->getHead().getVar(),*yymsp[0].minor.yy21));
	delete yymsp[0].minor.yy21;
}
#line 1086 "ASPParserGrammar.c"
        break;
      case 11: /* rule ::= number REVERSE_IMPLICATION LBRACKET ruleU RBRACKET */
#line 320 "ASPParserGrammar.y"
{
	yygotominor.yy21 = yymsp[-1].minor.yy21;
	yygotominor.yy21->toBeCompleted = false;
	if(yymsp[-1].minor.yy21->getBodyType() == BodyType::DISJUNCTION){
		throw syntax_exception("Unexpected DISJUNCTION in BODY of RULE.\n");
	}
	cout<<yymsp[-4].minor.yy0->toString()<<SPACE<<"!("<<yymsp[-1].minor.yy21->toString()<<")"<<"\n";
}
#line 1098 "ASPParserGrammar.c"
        break;
      case 12: /* rule ::= number LBRACKET ruleU RBRACKET */
#line 330 "ASPParserGrammar.y"
{
	yygotominor.yy21 = yymsp[-1].minor.yy21;
	yygotominor.yy21->toBeCompleted = false;
	if(yymsp[-1].minor.yy21->getBodyType() == BodyType::CONJUNCTION){
		throw syntax_exception("Unexpected CONJUNCTION in HEAD of RULE.\n");
	}
	cout<<yymsp[-3].minor.yy0->toString()<<SPACE<<"("<<yymsp[-1].minor.yy21->toString()<<")"<<"\n";
}
#line 1110 "ASPParserGrammar.c"
        break;
      case 13: /* rule ::= REVERSE_IMPLICATION LBRACKET ruleU RBRACKET DOT */
#line 341 "ASPParserGrammar.y"
{
	yygotominor.yy21 = yymsp[-2].minor.yy21;
	yymsp[-2].minor.yy21->toBeCompleted = false;
	if(yymsp[-2].minor.yy21->getBodyType() == BodyType::DISJUNCTION){
		throw syntax_exception("Unexpected DISJUNCTION in BODY of RULE.\n");
	}
	cout<<"!("<<yymsp[-2].minor.yy21->toString()<<")."<<"\n";
}
#line 1122 "ASPParserGrammar.c"
        break;
      case 14: /* rule ::= LBRACKET ruleU RBRACKET DOT */
#line 352 "ASPParserGrammar.y"
{
	yygotominor.yy21 = yymsp[-2].minor.yy21;
	yygotominor.yy21->toBeCompleted = false;
	if(yymsp[-2].minor.yy21->getBodyType() == BodyType::CONJUNCTION){
		throw syntax_exception("Unexpected CONJUNCTION in HEAD of RULE.\n");
	}
	cout<<"("<<yymsp[-2].minor.yy21->toString()<<")."<<"\n";
}
#line 1134 "ASPParserGrammar.c"
        break;
      case 15: /* ruleU ::= body CONJUNCTION bodydef */
#line 363 "ASPParserGrammar.y"
{
	yygotominor.yy21 = new RuleCompletion;
	yymsp[-2].minor.yy53->appendStr(yymsp[0].minor.yy20->getPredicate(),false,false,true, tree->domainList);
	yygotominor.yy21->appendStr(yymsp[-2].minor.yy53->toString());
	yygotominor.yy21->setBodyType(BodyType::CONJUNCTION);
	delete yymsp[-2].minor.yy53;
	delete yymsp[0].minor.yy20;
}
#line 1146 "ASPParserGrammar.c"
        break;
      case 16: /* ruleU ::= head DISJUNCTION bodydef */
#line 374 "ASPParserGrammar.y"
{
	yygotominor.yy21 = new RuleCompletion;	
	yygotominor.yy21->isHeadTop = true;
	yymsp[-2].minor.yy1->addPredicate(yymsp[0].minor.yy20->getPredicate());
	// RULE_COMPLETION_HEAD_DIS_BODY_TOP(yymsp[-2].minor.yy1,yymsp[0].minor.yy20)
	try{
		RuleCompletion_HD_BT(yymsp[-2].minor.yy1,tree);
	}
	catch(const std::out_of_range& e){
		throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}

	yymsp[-2].minor.yy1->appendStr(yymsp[0].minor.yy20->getPredicate().toString(tree->domainList),false,true,false);
	yygotominor.yy21->appendStr(yymsp[-2].minor.yy1->toString());
	yygotominor.yy21->setBodyType(BodyType::DISJUNCTION);
	delete yymsp[-2].minor.yy1;
	delete yymsp[0].minor.yy20;
}
#line 1168 "ASPParserGrammar.c"
        break;
      case 17: /* rule ::= REVERSE_IMPLICATION body DOT */
#line 397 "ASPParserGrammar.y"
{
	yygotominor.yy21 = new RuleCompletion;
	yygotominor.yy21->isHeadTop = true;
	// yymsp[-1].minor.yy53->appendStr(yymsp[-1].minor.yy53->getPredicate().toString(),false,false,true);
	std::cout<<"!("<<yymsp[-1].minor.yy53->toString()<<")."<<"\n";	
	delete yymsp[-1].minor.yy53;
	// delete B1;
}
#line 1180 "ASPParserGrammar.c"
        break;
      case 18: /* rule ::= head DISJUNCTION bodydef DOT */
#line 409 "ASPParserGrammar.y"
{
	//Doing this 
	yygotominor.yy21 = new RuleCompletion;
	yygotominor.yy21->isHeadTop = true;
	yymsp[-3].minor.yy1->addPredicate(yymsp[-1].minor.yy20->getPredicate());
	// RULE_COMPLETION_HEAD_DIS_BODY_TOP(yymsp[-3].minor.yy1,yymsp[-1].minor.yy20)
	try{
		RuleCompletion_HD_BT(yymsp[-3].minor.yy1,tree);
	}
	catch(const std::out_of_range& e){
		throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}
	yymsp[-3].minor.yy1->appendStr(yymsp[-1].minor.yy20->getPredicate().toString(tree->domainList),false,true,false);
	std::cout<<yymsp[-3].minor.yy1->toString()<<"."<<"\n";
	delete yymsp[-3].minor.yy1;
	delete yymsp[-1].minor.yy20;
}
#line 1201 "ASPParserGrammar.c"
        break;
      case 19: /* rule ::= number head DISJUNCTION bodydef */
#line 430 "ASPParserGrammar.y"
{
	//Doing this 
	yygotominor.yy21 = new RuleCompletion;
	yygotominor.yy21->isHeadTop = true;
	yymsp[-2].minor.yy1->addPredicate(yymsp[0].minor.yy20->getPredicate());
	// RULE_COMPLETION_HEAD_DIS_BODY_TOP(yymsp[-2].minor.yy1,yymsp[0].minor.yy20)
	try{
		RuleCompletion_HD_BT(yymsp[-2].minor.yy1,tree);
	}
	catch(const std::out_of_range& e){
		throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}
	yymsp[-2].minor.yy1->appendStr(yymsp[0].minor.yy20->getPredicate().toString(tree->domainList),false,true,false);
	std::cout<<yymsp[-3].minor.yy0->toString()<<SPACE<<yymsp[-2].minor.yy1->toString()<<"\n";
	delete yymsp[-2].minor.yy1;
	delete yymsp[0].minor.yy20;
}
#line 1222 "ASPParserGrammar.c"
        break;
      case 20: /* rule ::= head REVERSE_IMPLICATION body DOT */
#line 451 "ASPParserGrammar.y"
{
	yygotominor.yy21 = new RuleCompletion;

	if (yymsp[-3].minor.yy1->getDisjunction()){
		// RULE_COMPLETION_HEAD_DIS_BODY_TOP(yymsp[-3].minor.yy1,yymsp[-1].minor.yy53)
		yygotominor.yy21->isHeadTop = true;
		RuleCompletion_HD_BC(yymsp[-3].minor.yy1,yymsp[-1].minor.yy53,true,tree);
		std::cout<<yymsp[-1].minor.yy53->toString()<<" => "<<yymsp[-3].minor.yy1->toString()<<"."<<"\n";
		// std::cout << op;
	}
	else{
		// RULE_COMPLETION_BH(yymsp[-1].minor.yy53,yymsp[-3].minor.yy1);
		// yygotominor.yy21 = new RuleCompletion(yymsp[-3].minor.yy1->getPredicate(),predList, resultMap, varMap);
		try{
			yygotominor.yy21 = RuleCompletion_BH(yymsp[-1].minor.yy53,yymsp[-3].minor.yy1,tree);
		}
		catch(const std::out_of_range& e){
			throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
		}
		std::cout<<yymsp[-1].minor.yy53->toString()<<" => "<<yymsp[-3].minor.yy1->toString()<<"."<<"\n";
	}
	delete yymsp[-1].minor.yy53;
	delete yymsp[-3].minor.yy1;
}
#line 1250 "ASPParserGrammar.c"
        break;
      case 21: /* rule ::= number head REVERSE_IMPLICATION body */
#line 479 "ASPParserGrammar.y"
{
	// RULE_COMPLETION_BH(yymsp[0].minor.yy53,yymsp[-2].minor.yy1);
	// yygotominor.yy21 = new RuleCompletion(yymsp[-2].minor.yy1->getPredicate(),predList, resultMap, varMap);
	try{
		yygotominor.yy21 = RuleCompletion_BH(yymsp[0].minor.yy53,yymsp[-2].minor.yy1,tree);
	}
	catch(const std::out_of_range& e){
			throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}
	std::cout<< yymsp[-3].minor.yy0->toString()<<SPACE<<yymsp[0].minor.yy53->toString()<<" => "<<yymsp[-2].minor.yy1->toString()<<"\n";
	delete yymsp[0].minor.yy53;
	delete yymsp[-2].minor.yy1;
}
#line 1267 "ASPParserGrammar.c"
        break;
      case 22: /* rule ::= number NEGATION NEGATION LBRACKET head REVERSE_IMPLICATION body RBRACKET */
#line 505 "ASPParserGrammar.y"
{
	yygotominor.yy21 = new RuleCompletion;
	yygotominor.yy21->isHeadTop = true;	
	tree->statHasDblNeg = true;
	std::cout<< yymsp[-7].minor.yy0->toString() << SPACE <<"!!("<<yymsp[-1].minor.yy53->toString()<<" => "<<yymsp[-3].minor.yy1->toString()<<"\n"; 
	delete yymsp[-1].minor.yy53;
	delete yymsp[-3].minor.yy1;
}
#line 1279 "ASPParserGrammar.c"
        break;
      case 23: /* rule ::= LPAREN head RPAREN REVERSE_IMPLICATION body DOT */
#line 514 "ASPParserGrammar.y"
{
	
	if (yymsp[-4].minor.yy1->getPredicate().checkEquality() != 0){
		throw syntax_exception("Cannot have equality/Inequlity as a part of choice rule\n");
	}

	// RULE_COMPLETION_BH(yymsp[-1].minor.yy53,yymsp[-4].minor.yy1);
	// yygotominor.yy21 = new RuleCompletion(yymsp[-4].minor.yy1->getPredicate(),predList, resultMap, varMap);
	try{
		yygotominor.yy21 = RuleCompletion_BH(yymsp[-1].minor.yy53,yymsp[-4].minor.yy1,tree);
	}
	catch(const std::out_of_range& e){
			throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}
	std::cout<<COMMENT<<yymsp[-1].minor.yy53->toString()<<" => "<<yymsp[-4].minor.yy1->toString()<<"\n";
	delete yymsp[-1].minor.yy53;
	delete yymsp[-4].minor.yy1;
}
#line 1301 "ASPParserGrammar.c"
        break;
      case 24: /* body ::= body CONJUNCTION bodydef */
#line 535 "ASPParserGrammar.y"
{
	yygotominor.yy53 = yymsp[-2].minor.yy53;
	yymsp[-2].minor.yy53->addPredicate(yymsp[0].minor.yy20->getPredicate());
	yygotominor.yy53->appendStr(yymsp[0].minor.yy20->getPredicate(),false,false,true,tree->domainList);
	delete yymsp[0].minor.yy20;
}
#line 1311 "ASPParserGrammar.c"
        break;
      case 25: /* head ::= head DISJUNCTION bodydef */
#line 549 "ASPParserGrammar.y"
{
	yygotominor.yy1 = yymsp[-2].minor.yy1;
	yymsp[-2].minor.yy1->addPredicate(yymsp[0].minor.yy20->getPredicate());
	yygotominor.yy1->appendStr(yymsp[0].minor.yy20->getPredicate().toString(tree->domainList),false,true,false);
	yygotominor.yy1->setDisjunction(true);
	delete yymsp[0].minor.yy20;
}
#line 1322 "ASPParserGrammar.c"
        break;
      case 26: /* head ::= bodydef */
#line 557 "ASPParserGrammar.y"
{
	yygotominor.yy1 = new Head(yymsp[0].minor.yy20->getPredicate());
	// yygotominor.yy1->addPredicate(yymsp[0].minor.yy20->getPredicate());
	yygotominor.yy1->appendStr(yymsp[0].minor.yy20->getPredicate().toString(tree->domainList),false,false,false);
	delete yymsp[0].minor.yy20;
}
#line 1332 "ASPParserGrammar.c"
        break;
      case 27: /* body ::= bodydef */
#line 564 "ASPParserGrammar.y"
{
	yygotominor.yy53 = new Body;
	yygotominor.yy53->addPredicate(yymsp[0].minor.yy20->getPredicate());
	yygotominor.yy53->appendStr(yymsp[0].minor.yy20->getPredicate(),false,false,false,tree->domainList);
	delete yymsp[0].minor.yy20;
}
#line 1342 "ASPParserGrammar.c"
        break;
      case 28: /* bodydef ::= string LBRACKET variables RBRACKET */
#line 574 "ASPParserGrammar.y"
{	
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-1].minor.yy45)
		vars.push_back(*v);
	
	Predicate p(yymsp[-3].minor.yy0->token);
	p.setTokens(vars, tree->domainList);
	yygotominor.yy20 = new BodyDef;
	yygotominor.yy20->addPredicate(p);
	delete yymsp[-1].minor.yy45;
	auto itr = tree->variables.find(*(yymsp[-3].minor.yy0->token));
	if(itr != tree->variables.end()){
		unsigned int expectedArgs = itr->getSize();
		if (expectedArgs != vars.size()){
			delete yygotominor.yy20;
			throw invalid_arguments(expectedArgs, vars.size(), *(yymsp[-3].minor.yy0->token));
		}
	}
	else{
		delete yygotominor.yy20;
		throw syntax_exception(*(yymsp[-3].minor.yy0->token) + " not declared.\n");
	}
	

}
#line 1371 "ASPParserGrammar.c"
        break;
      case 29: /* bodydef ::= NEGATION string LBRACKET variables RBRACKET */
#line 601 "ASPParserGrammar.y"
{	
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-1].minor.yy45)
		vars.push_back(*v);
	
	Predicate p(yymsp[-3].minor.yy0->token);
	p.setTokens(vars, tree->domainList);
	p.setSingleNegation(true);
	yygotominor.yy20 = new BodyDef;
	yygotominor.yy20->addPredicate(p);
	delete yymsp[-1].minor.yy45;
	auto itr = tree->variables.find(*(yymsp[-3].minor.yy0->token));
	if(itr != tree->variables.end()){
		unsigned int expectedArgs = itr->getSize();
		if (expectedArgs != vars.size()){
			delete yygotominor.yy20;
			throw invalid_arguments(expectedArgs, vars.size(), *(yymsp[-3].minor.yy0->token));
		}
	}
	else{
		delete yygotominor.yy20;
		throw syntax_exception(*(yymsp[-3].minor.yy0->token) + " not declared.\n");
	}

}
#line 1400 "ASPParserGrammar.c"
        break;
      case 30: /* bodydef ::= NEGATION NEGATION string LBRACKET variables RBRACKET */
#line 628 "ASPParserGrammar.y"
{	
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-1].minor.yy45)
		vars.push_back(*v);
	
	Predicate p(yymsp[-3].minor.yy0->token);
	p.setTokens(vars, tree->domainList);
	p.setDoubleNegation(true);
	yygotominor.yy20 = new BodyDef;
	yygotominor.yy20->addPredicate(p);
	tree->statHasDblNeg = true;
	delete yymsp[-1].minor.yy45;
	auto itr = tree->variables.find(*(yymsp[-3].minor.yy0->token));
	if(itr != tree->variables.end()){
		unsigned int expectedArgs = itr->getSize();
		if (expectedArgs != vars.size()){
			delete yygotominor.yy20;
			throw invalid_arguments(expectedArgs, vars.size(), *(yymsp[-3].minor.yy0->token));
		}
	}
	else{
		delete yygotominor.yy20;
		throw syntax_exception(*(yymsp[-3].minor.yy0->token) + " not declared.\n");
	}

}
#line 1430 "ASPParserGrammar.c"
        break;
      case 31: /* bodydef ::= LBRACKET NEGATION NEGATION string LBRACKET variables RBRACKET RBRACKET */
#line 658 "ASPParserGrammar.y"
{	
	std::vector<std::string> vars;
	for(auto& v : *yymsp[-2].minor.yy45)
		vars.push_back(*v);
	
	Predicate p(yymsp[-4].minor.yy0->token);
	p.setTokens(vars, tree->domainList);
	p.setDoubleNegation(true);
	tree->statHasDblNeg = true;
	yygotominor.yy20 = new BodyDef;
	yygotominor.yy20->addPredicate(p);
	delete yymsp[-2].minor.yy45;
	auto itr = tree->variables.find(*(yymsp[-4].minor.yy0->token));
	if(itr != tree->variables.end()){
		unsigned int expectedArgs = itr->getSize();
		if (expectedArgs != vars.size()){
			delete yygotominor.yy20;
			throw invalid_arguments(expectedArgs, vars.size(), *(yymsp[-4].minor.yy0->token));
		}
	}
	else{
		delete yygotominor.yy20;
		throw syntax_exception(*(yymsp[-4].minor.yy0->token) + " not declared.\n");
	}

}
#line 1460 "ASPParserGrammar.c"
        break;
      case 32: /* bodydef ::= string EQUAL string */
#line 686 "ASPParserGrammar.y"
{
	Predicate p(yymsp[-2].minor.yy0->token,yymsp[0].minor.yy0->token);
	p.setEquality();
	yygotominor.yy20 = new BodyDef;
	yygotominor.yy20->addPredicate(p);
}
#line 1470 "ASPParserGrammar.c"
        break;
      case 33: /* bodydef ::= string NEGATION EQUAL string */
#line 694 "ASPParserGrammar.y"
{
	
	Predicate p(yymsp[-3].minor.yy0->token,yymsp[0].minor.yy0->token);
	p.setInEquality();
	yygotominor.yy20 = new BodyDef;
	yygotominor.yy20->addPredicate(p);
}
#line 1481 "ASPParserGrammar.c"
        break;
      case 34: /* decl ::= string LBRACKET variables RBRACKET */
#line 731 "ASPParserGrammar.y"
{
	yygotominor.yy57 = new Variable;
	std::map<int, Domain> posMap;
	std::set<Domain>::iterator itr;
	int i=0;
	for(auto& v : *yymsp[-1].minor.yy45){
		itr = tree->domains.find(*v);
		if (itr == tree->domains.end()){
			// std::cout<<"Error:Domain:"+ *v +" not found.\n";
			throw syntax_exception("Syntax Error - Domain " + *v + " not found.\n");
		}
		else{
			// itr = tree->domains.find(*v);
			
			posMap[i++] = *itr;
		}
	}
	yygotominor.yy57->setVar(yymsp[-3].minor.yy0->token);
	yygotominor.yy57->setPosMap(posMap);
	delete yymsp[-1].minor.yy45;
}
#line 1506 "ASPParserGrammar.c"
        break;
      case 35: /* predicate ::= string LBRACKET variables RBRACKET DOT */
#line 755 "ASPParserGrammar.y"
{
	yygotominor.yy26 = new Predicate;
	yygotominor.yy26->setVar(yymsp[-4].minor.yy0->token);
	yygotominor.yy26->setTokens(*yymsp[-2].minor.yy45,tree->domainList);
	std::string s1;
	cout<<yygotominor.yy26->toString(s1,true);
	delete yymsp[-2].minor.yy45;
}
#line 1518 "ASPParserGrammar.c"
        break;
      case 36: /* predicate ::= number string LBRACKET variables RBRACKET */
#line 765 "ASPParserGrammar.y"
{
	yygotominor.yy26 = new Predicate;
	yygotominor.yy26->setVar(yymsp[-3].minor.yy0->token);
	yygotominor.yy26->setTokens(*yymsp[-1].minor.yy45,tree->domainList);
	cout<<yygotominor.yy26->toString(yymsp[-4].minor.yy0->toString()+SPACE, false);
	delete yymsp[-1].minor.yy45;
}
#line 1529 "ASPParserGrammar.c"
        break;
      case 37: /* predicate ::= number NEGATION NEGATION string LBRACKET variables RBRACKET */
#line 775 "ASPParserGrammar.y"
{
	yygotominor.yy26 = new Predicate;
	yygotominor.yy26->notToBeCompleted();
	tree->statHasDblNeg = true;
	yygotominor.yy26->setVar(yymsp[-3].minor.yy0->token);
	yygotominor.yy26->setTokens(*yymsp[-1].minor.yy45,tree->domainList);
	cout<<yygotominor.yy26->toString(yymsp[-6].minor.yy0->toString()+SPACE, false);
	delete yymsp[-1].minor.yy45;
}
#line 1542 "ASPParserGrammar.c"
        break;
      case 38: /* predicate ::= number NEGATION string LBRACKET variables RBRACKET */
#line 786 "ASPParserGrammar.y"
{
	yygotominor.yy26 = new Predicate;
	yygotominor.yy26->notToBeCompleted();
	yygotominor.yy26->setVar(yymsp[-3].minor.yy0->token);
	yygotominor.yy26->setTokens(*yymsp[-1].minor.yy45,tree->domainList);
	cout<<yygotominor.yy26->toString(yymsp[-5].minor.yy0->toString()+SPACE+"!", false);
	delete yymsp[-1].minor.yy45;
}
#line 1554 "ASPParserGrammar.c"
        break;
      case 39: /* predicate ::= NEGATION NEGATION string LBRACKET variables RBRACKET DOT */
#line 795 "ASPParserGrammar.y"
{
	yygotominor.yy26 = new Predicate;
	yygotominor.yy26->notToBeCompleted();
	tree->statHasDblNeg = true;
	yygotominor.yy26->setVar(yymsp[-4].minor.yy0->token);
	yygotominor.yy26->setTokens(*yymsp[-2].minor.yy45,tree->domainList);
	std::string s1; 
	cout<<yygotominor.yy26->toString(s1, false);
	delete yymsp[-2].minor.yy45;
}
#line 1568 "ASPParserGrammar.c"
        break;
      case 40: /* domain ::= string EQUAL domains */
#line 807 "ASPParserGrammar.y"
{ 
	yygotominor.yy51 = yymsp[0].minor.yy51;
	yymsp[0].minor.yy51->setDomainVar(yymsp[-2].minor.yy0->token);
}
#line 1576 "ASPParserGrammar.c"
        break;
      case 41: /* domains ::= LPAREN variables RPAREN */
#line 814 "ASPParserGrammar.y"
{
	yygotominor.yy51 = new Domain();
	yygotominor.yy51->setVars(*yymsp[-1].minor.yy45);
	delete yymsp[-1].minor.yy45;
}
#line 1585 "ASPParserGrammar.c"
        break;
      case 42: /* variables ::= variable */
#line 821 "ASPParserGrammar.y"
{
	yygotominor.yy45 = new std::vector<std::string*>();
	yygotominor.yy45->push_back(yymsp[0].minor.yy0->token);
}
#line 1593 "ASPParserGrammar.c"
        break;
      case 43: /* variables ::= variables COMMA variable */
#line 826 "ASPParserGrammar.y"
{
	yygotominor.yy45 = yymsp[-2].minor.yy45;
	yymsp[-2].minor.yy45->push_back(yymsp[0].minor.yy0->token);
}
#line 1601 "ASPParserGrammar.c"
        break;
      case 44: /* variable ::= string */
      case 45: /* variable ::= number */ yytestcase(yyruleno==45);
      case 46: /* string ::= STRING */ yytestcase(yyruleno==46);
      case 47: /* number ::= NUMBER */ yytestcase(yyruleno==47);
#line 831 "ASPParserGrammar.y"
{ yygotominor.yy0=yymsp[0].minor.yy0;}
#line 1609 "ASPParserGrammar.c"
        break;
      case 48: /* number ::= lnumber DOT rnumber */
#line 840 "ASPParserGrammar.y"
{ 
	// yygotominor.yy0 = new Token(*(yymsp[-2].minor.yy0->token)+"."+*(yymsp[0].minor.yy0->token));
	yygotominor.yy0 = yymsp[-2].minor.yy0;
	yygotominor.yy0->modifyToken(*(yymsp[-2].minor.yy0->token)+"."+*(yymsp[0].minor.yy0->token));
}
#line 1618 "ASPParserGrammar.c"
        break;
      case 49: /* number ::= MINUS lnumber DOT rnumber */
#line 847 "ASPParserGrammar.y"
{
	yygotominor.yy0 = yymsp[-2].minor.yy0;
	yygotominor.yy0->modifyToken("-"+*(yymsp[-2].minor.yy0->token)+"."+*(yymsp[0].minor.yy0->token));
}
#line 1626 "ASPParserGrammar.c"
        break;
      case 50: /* lnumber ::= NUMBER */
      case 51: /* rnumber ::= NUMBER */ yytestcase(yyruleno==51);
#line 851 "ASPParserGrammar.y"
{ yygotominor.yy0=yymsp[0].minor.yy0; }
#line 1632 "ASPParserGrammar.c"
        break;
      default:
      /* (0) start ::= prog */ yytestcase(yyruleno==0);
      /* (9) prog ::= prog NEWLINE */ yytestcase(yyruleno==9);
      /* (10) prog ::= */ yytestcase(yyruleno==10);
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
  ASPParserGrammarARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
#line 57 "ASPParserGrammar.y"

    // std::cout<<"Giving up.  Parser is lost...\n";

#line 1687 "ASPParserGrammar.c"
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
#line 63 "ASPParserGrammar.y"

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
    
#line 1716 "ASPParserGrammar.c"
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
#line 52 "ASPParserGrammar.y"

    std::cout<<("//parsing complete!\n");
#line 1738 "ASPParserGrammar.c"
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
  ASPParserGrammarARG_STORE;

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

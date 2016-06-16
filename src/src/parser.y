%include 
{
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


	using namespace std;

	struct cmp{
		bool operator()(const std::pair<std::string, std::string>& left, const std::pair<std::string, std::string>& right) const{
			return left.first < right.first;
		}
	};
}


%start_symbol start
%token_prefix PARSE_TOKEN_

%extra_argument { Tree* tree}

%parse_accept 
{
    std::cout<<("//parsing complete!\n");
}

%parse_failure 
{
    std::cout<<"Giving up.  Parser is lost...\n";
}

%syntax_error
{
	 std::cout << "syntax error - ";
    int n = sizeof(yyTokenName) / sizeof(yyTokenName[0]);
    for (int i = 0; i < n; ++i) {
            int a = yy_find_shift_action(yypParser, (YYCODETYPE)i);
            if (a < YYNSTATE + YYNRULE) {
                    std::cout << "expected " << yyTokenName[i] << std::endl;
            }
    }
}


%nonassoc EQUAL.
%nonassoc COMMA.
%nonassoc LPAREN RPAREN.


%right NEWLINE.
%right CONJUNCTION.
%right DISJUNCTION.

%nonassoc LBRACKET RBRACKET.
%nonassoc IMPLICATION.
%right NEGATION.

%nonassoc WS.

%token_type {Token*}
// %token_destructor {delete $$;}


%type start {Tree*}

%type prog {Tree*}

%type domain {Domain*}
// %destructor domain { delete $$;}
%type domains {Domain*}
// %destructor domains { delete $$;}
%type predicate {Predicate*}

%type decl {Variable*}

%type variables {std::vector<std::string*>*}

start ::= prog.


prog ::= prog NEWLINE domain(D). { 
	tree->domains.insert(*D); 
	tree->domainNamesList.insert(D->getDomainVar());
	for(auto& v : D->getVars()){
		tree->domainList.insert(v);	
	}
	delete D;
}
prog ::= domain(D). { 
	tree->domains.insert(*D); 
	tree->domainNamesList.insert(D->getDomainVar());
	for(auto& v : D->getVars()){
		tree->domainList.insert(v);	
	}
	delete D;
}

prog ::= prog NEWLINE predicate(P). { 
	if(P->needsToBeCompleted()){	
		FactCompletion f(*P);
		tree->facts.insert(std::pair<std::string,FactCompletion>(f.head.getVar(),f)); 
	}	
	delete P;
}

prog ::= predicate(P). { 
	if(P->needsToBeCompleted()){
		FactCompletion f(*P);
		tree->facts.insert(std::pair<std::string,FactCompletion>(f.head.getVar(),f)); 	
	}
	delete P;
}

prog ::= prog NEWLINE decl(D). {
	tree->variables.insert(*D);
	delete D;
}
prog ::= decl(D). {
	tree->variables.insert(*D);
	delete D;
}

prog ::= prog NEWLINE rule(R). {
	if(R->isHeadTop == false)
		tree->rules.insert(std::pair<std::string,RuleCompletion>(R->head.getVar(),*R));
	delete R;
}
prog ::= rule(R).{
	if(R->isHeadTop == false)
		tree->rules.insert(std::pair<std::string,RuleCompletion>(R->head.getVar(),*R));
	delete R;
}

prog ::= prog NEWLINE ruleU(R). {
	
	//random
	delete R;
}

prog ::= ruleU(R). {
	//random
	delete R;
}

prog ::= prog NEWLINE.

prog ::= .



%type body {Body*}

%type bodydef {BodyDef*} 
%type bodydef2 {BodyDef*} 

%type head {Head*}

%type headdef {Head*}


%type rule {RuleCompletion*}
%type ruleU {RuleCompletion*}


//ex !(alive(x,True,t) ^ alive(x,False,t))
ruleU ::= LBRACKET ruleI RBRACKET DOT.

ruleU ::= NEGATION LBRACKET ruleI RBRACKET DOT.

ruleI ::= body CONJUNCTION bodydef2(B2).{
	delete B2;
}

ruleI ::= body DISJUNCTION bodydef2(B2). {
	delete B2;
}

rule(R) ::= body(B) CONJUNCTION bodydef(B1) DOT.{
	R = new RuleCompletion;
	R->isHeadTop = true;	
	delete B;
	delete B1;
}


rule(R) ::= body(B) DISJUNCTION bodydef(B1) DOT.{
	R = new RuleCompletion;
	R->isHeadTop = true;	
	delete B;
	delete B1;
}

//Parse hard rules
rule(R) ::= body(B) IMPLICATION head(H) DOT.{
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

	R = new RuleCompletion(H->getPredicate(),predList, resultMap, varMap);
	delete B;
	delete H;
}

//Parse soft rules
rule(R) ::= number body(B) IMPLICATION head(H). {
	std::set<std::pair<std::string,std::string>> orphanVarsMap;
	std::set<std::pair<std::string,std::string>> orphanVarsHeadMap;
	std::vector<Predicate> predList = B->getPredicate();
	for(auto& p : predList){
		int tempCount = 0;
		for(auto& v : p.getTokens()){
			orphanVarsMap.insert(std::pair<std::string, std::string>(v,tree->variables.find(p.getVar())->getPosMap().at(tempCount++).getDomainVar()));
		}
	}

	int count = 0;
	std::map<int,std::pair<int, std::string>> varMap;
	int tempCount = 0;

	for(auto& str : H->getPredicate().getTokens()){
		if(tree->isConstant(str)){
			varMap[count] = std::pair<int, std::string>(count, str);
		}
		else
			count++;
			
		orphanVarsHeadMap.insert(std::pair<std::string, std::string>(str,tree->variables.find(H->getPredicate().getVar())->getPosMap().at(tempCount++).getDomainVar()));
	}

	
	
	std::set<std::string> result;
		
	tree->removeConstantsPair(orphanVarsMap);
	tree->removeConstantsPair(orphanVarsHeadMap);
	
	std::set<std::pair<std::string,std::string>> resultMap;
	std::set_difference(orphanVarsMap.begin(), orphanVarsMap.end(), orphanVarsHeadMap.begin(), orphanVarsHeadMap.end(),std::inserter(resultMap, resultMap.end()), cmp());

	R = new RuleCompletion(H->getPredicate(),predList, resultMap, varMap);
	delete B;
	delete H;
}

//Parse soft exogenity rules (not to be completed)
//Ex. 0.8536 !!<body> => head.
rule(R) ::= number NEGATION NEGATION body(B) IMPLICATION head(H). {
	tree->statHasDblNeg = true;
	R = new RuleCompletion;
	R->isHeadTop = true;	
	delete B;
	delete H;
}

rule(R) ::= number NEGATION NEGATION LBRACKET body(B) IMPLICATION head(H) RBRACKET. {
	R = new RuleCompletion;
	R->isHeadTop = true;	
	tree->statHasDblNeg = true;
	delete B;
	delete H;
}

//Parses body of rules
body(B) ::= body(B1) CONJUNCTION bodydef(Bd).{
	B = B1;
	B1->addPredicate(Bd->getPredicate());
	delete Bd;
}

body(B) ::= body(B1) DISJUNCTION bodydef(Bd).{
	B = B1;
	delete Bd;
}
body(B) ::= bodydef(Bd).{
	B = new Body;
	B->addPredicate(Bd->getPredicate());
	delete Bd;
}

//BodyDef without negation in front
bodydef(B) ::= string(S) LBRACKET variables(Ve) RBRACKET.{	
	std::vector<std::string> vars;
	for(auto& v : *Ve)
		vars.push_back(*v);
	
	Predicate p(S->token, vars);
	B = new BodyDef;
	B->addPredicate(p);
	delete Ve;
}

//BodyDef with negation in front
bodydef(B) ::= NEGATION string(S) LBRACKET variables(Ve) RBRACKET.{	
	std::vector<std::string> vars;
	for(auto& v : *Ve)
		vars.push_back(*v);
	
	Predicate p(S->token, vars);
	B = new BodyDef;
	B->addPredicate(p);
	delete Ve;
}

//parses bodydef of the form a=b
bodydef(B) ::= string(S) EQUAL string(S1).{
	Predicate p(S->token,S1->token);
	p.setEquality();
	B = new BodyDef;
	B->addPredicate(p);
}

//parses bodydef of the form a!=b
bodydef(B) ::= string(S) NEGATION EQUAL string(S1).{
	Predicate p(S->token,S1->token);
	p.setInEquality();
	B = new BodyDef;
	B->addPredicate(p);
}



//BodyDef2 without negation in front
bodydef2 ::= string LBRACKET variables(Ve) RBRACKET. {delete Ve;}
//BodyDef2 with negation in front
bodydef2 ::= NEGATION string LBRACKET variables(Ve) RBRACKET. {delete Ve;}

bodydef2 ::= string EQUAL string.

bodydef2 ::= string NEGATION EQUAL string.

//Parses head of rules
head(H) ::= headdef(H1). { 
	H = H1;
}

//Head without negation in front
headdef(H) ::= string(S) LBRACKET variables(Ve) RBRACKET.{
	std::vector<std::string> vars;
	for(auto& v : *Ve)
		vars.push_back(*v);
	
	Predicate p(S->token, vars);
	H = new Head;
	H->addPredicate(p);
	delete Ve;
}

//Head with negation in front
headdef(H) ::= NEGATION string(S) LBRACKET variables(Ve) RBRACKET.{
	std::vector<std::string> vars;
	for(auto& v : *Ve)
		vars.push_back(*v);
	
	Predicate p(S->token, vars);
	H = new Head;
	H->addPredicate(p);
	delete Ve;
}

//Parses declarations ex. next(step,step)
decl(D) ::= string(S) LBRACKET variables(Ve) RBRACKET.{
	D = new Variable;
	std::map<int, Domain> posMap;
	std::set<Domain>::iterator itr;
	int i=0;
	for(auto& v : *Ve){
		itr = tree->domains.find(*v);
		if (itr == tree->domains.end()){
			std::cout<<"Error:Domain:"+ *v +" not found.\n";
			//Exit
		}
		else{
			// itr = tree->domains.find(*v);
			D->setVar(S->token);
			posMap[i++] = *itr;
		}
	}
	D->setPosMap(posMap);
	delete Ve;
}

//Parses hard facts ex. next(0,1).
predicate(P) ::= string(S) LBRACKET variables(Ve) RBRACKET DOT. {
	P = new Predicate;
	P->setVar(S->token);
	P->setTokens(*Ve);
	delete Ve;
}

//Parses weighted/soft facts ex. 12 next(0,1)
predicate(P) ::= number string(S) LBRACKET variables(Ve) RBRACKET. {
	P = new Predicate;
	P->setVar(S->token);
	P->setTokens(*Ve);
	delete Ve;
}

//Parses weighted/soft constraints ex. 0.4536 !!next(0,1)
predicate(P) ::= number NEGATION NEGATION string LBRACKET variables(Ve) RBRACKET. {
	P = new Predicate;
	P->notToBeCompleted();
	tree->statHasDblNeg = true;
	delete Ve;
}


//Parses domains ex. step={1,2,3}
domain(D) ::= string(S) EQUAL domains(Ds).{ 
	D = Ds;
	Ds->setDomainVar(S->token);
}


//Parses RHS of domains
domains(D) ::= LPAREN variables(Ve) RPAREN.{
	D = new Domain();
	D->setVars(*Ve);
	delete Ve;
}

//Parses variables between () or {}
variables(Ve) ::= variable(V).{
	Ve = new std::vector<std::string*>();
	Ve->push_back(V->token);
}

variables(Ve) ::= variables(Ve2) COMMA variable(V).{
	Ve = Ve2;
	Ve2->push_back(V->token);
}

variable(V) ::= string(S). { V=S;}  
variable(V) ::= number(N). { V=N;} 

variable(V) ::= PLUS string(S). { V=S;}  

string(S) ::= STRING(S1). { S=S1;}
number(N) ::= NUMBER(N1). { N=N1;}

//Parses decimals
number(N) ::= lnumber(L) DOT rnumber(R). { 
	N = new Token(*(L->token)+"."+*(R->token));
}

//Parses negative decimals
number(N) ::= MINUS lnumber(L) DOT rnumber(R). { 
	N = new Token("-"+*(L->token)+"."+*(R->token));
}
lnumber(L) ::= NUMBER(N). { L=N; }
rnumber(R) ::= NUMBER(N). { R=N; }


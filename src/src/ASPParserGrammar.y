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

}

%name ASPParserGrammar
%start_symbol start
%token_prefix ASP_PARSE_TOKEN_

%extra_argument {Tree* tree}

%parse_accept 
{
    std::cout<<("//parsing complete!\n");
}

%parse_failure 
{
    // std::cout<<"Giving up.  Parser is lost...\n";

}

%syntax_error
{
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
    
}


%nonassoc EQUAL.
%nonassoc COMMA.
%nonassoc LPAREN RPAREN.


%right NEWLINE.
%right CONJUNCTION.
%right DISJUNCTION.

%nonassoc LBRACKET RBRACKET.
%nonassoc IMPLICATION.
%nonassoc REVERSE_IMPLICATION.
%right NEGATION.

%nonassoc WS.

%token_type {Token*}

%type start {Tree*}

%type prog {Tree*}

%type domain {Domain*}

%type domains {Domain*}

%type predicate {Predicate*}

%type decl {Variable*}

%type variables {std::vector<std::string*>*}

%include{

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
}



start ::= prog.

prog ::= prog NEWLINE domain(D). { 
	tree->domains.insert(*D); 
	tree->domainNamesList.insert(D->getDomainVar());
	for(auto& v : D->getVars()){
		tree->domainList.insert(v);	
	}
	cout<<D->toString(false);
	delete D;
}
prog ::= domain(D). { 
	tree->domains.insert(*D); 
	tree->domainNamesList.insert(D->getDomainVar());
	for(auto& v : D->getVars()){
		tree->domainList.insert(v);	
	}
	cout<<D->toString(false);
	delete D;
}

prog ::= prog NEWLINE predicate(P). { 
	if(P->needsToBeCompleted()){	
		FactCompletion f(*P);
		tree->facts.insert(std::pair<std::string,FactCompletion>(f.getHead().getVar(),f)); 
	}	
	delete P;
}

prog ::= predicate(P). { 
	if(P->needsToBeCompleted()){
		FactCompletion f(*P);
		tree->facts.insert(std::pair<std::string,FactCompletion>(f.getHead().getVar(),f)); 	
	}
	delete P;
}

prog ::= prog NEWLINE decl(D). {
	tree->variables.insert(*D);
	cout<<D->toString();
	delete D;
}
prog ::= decl(D). {
	tree->variables.insert(*D);
	cout<<D->toString();
	delete D;
}

prog ::= prog NEWLINE rule(R). {
	if((R->isHeadTop == false) && (R->toBeCompleted == true))
		tree->rules.insert(std::pair<std::string,RuleCompletion>(R->getHead().getVar(),*R));
	delete R;
}
prog ::= rule(R).{
	if((R->isHeadTop == false) && (R->toBeCompleted == true))
		tree->rules.insert(std::pair<std::string,RuleCompletion>(R->getHead().getVar(),*R));
	delete R;
}

prog ::= prog NEWLINE.

prog ::= .



%type body {Body*}

%type bodydef {BodyDef*} 
%type bodydef2 {BodyDef*} 

%type head {Head*}



%type rule {RuleCompletion*}

//RuleU are rules with head bottom
%type ruleU {RuleCompletion*}

//ex 0.8536 <= (ruleU)
//Test case covered
rule(R) ::= number(N) REVERSE_IMPLICATION LBRACKET ruleU(R1) RBRACKET.{
	R = R1;
	R->toBeCompleted = false;
	if(R1->getBodyType() == BodyType::DISJUNCTION){
		throw syntax_exception("Unexpected DISJUNCTION in BODY of RULE.\n");
	}
	cout<<N->toString()<<SPACE<<"!("<<R1->toString()<<")"<<"\n";
}

//ex 0.8536 (ruleU)
rule(R) ::= number(N) LBRACKET ruleU(R1) RBRACKET.{
	R = R1;
	R->toBeCompleted = false;
	if(R1->getBodyType() == BodyType::CONJUNCTION){
		throw syntax_exception("Unexpected CONJUNCTION in HEAD of RULE.\n");
	}
	cout<<N->toString()<<SPACE<<"("<<R1->toString()<<")"<<"\n";
}

//ex <= (ruleU).
//Test case wrong
rule(R) ::= REVERSE_IMPLICATION LBRACKET ruleU(R1) RBRACKET DOT.{
	R = R1;
	R1->toBeCompleted = false;
	if(R1->getBodyType() == BodyType::DISJUNCTION){
		throw syntax_exception("Unexpected DISJUNCTION in BODY of RULE.\n");
	}
	cout<<"!("<<R1->toString()<<")."<<"\n";
}

//ex (ruleU).
//Test case covered
rule(R) ::= LBRACKET ruleU(R1) RBRACKET DOT.{
	R = R1;
	R->toBeCompleted = false;
	if(R1->getBodyType() == BodyType::CONJUNCTION){
		throw syntax_exception("Unexpected CONJUNCTION in HEAD of RULE.\n");
	}
	cout<<"("<<R1->toString()<<")."<<"\n";
}


//B=>bottom
ruleU(R) ::= body(B) CONJUNCTION bodydef(B1).{
	R = new RuleCompletion;
	B->appendStr(B1->getPredicate(),false,false,true);
	R->appendStr(B->toString());
	R->setBodyType(BodyType::CONJUNCTION);
	delete B;
	delete B1;
}

//ruleU's are all in brackets so no need for DOT, Number
//Top => H
ruleU(R) ::= head(B) DISJUNCTION bodydef(B1).{
	R = new RuleCompletion;	
	R->isHeadTop = true;
	B->addPredicate(B1->getPredicate());
	// RULE_COMPLETION_HEAD_DIS_BODY_TOP(B,B1)
	try{
		RuleCompletion_HD_BT(B,tree);
	}
	catch(const std::out_of_range& e){
		throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}

	B->appendStr(B1->getPredicate().toString(),false,true,false);
	R->appendStr(B->toString());
	R->setBodyType(BodyType::DISJUNCTION);
	delete B;
	delete B1;
}


//Parse Hard rule
//<= B.
//Test case covered
rule(R) ::= REVERSE_IMPLICATION body(B) DOT.{
	R = new RuleCompletion;
	R->isHeadTop = true;
	// B->appendStr(B->getPredicate().toString(),false,false,true);
	std::cout<<"!("<<B->toString()<<")."<<"\n";	
	delete B;
	// delete B1;
}

//Parse Hard rule
//H.
//Test case covered
rule(R) ::= head(B) DISJUNCTION bodydef(B1) DOT.{
	//Doing this 
	R = new RuleCompletion;
	R->isHeadTop = true;
	B->addPredicate(B1->getPredicate());
	// RULE_COMPLETION_HEAD_DIS_BODY_TOP(B,B1)
	try{
		RuleCompletion_HD_BT(B,tree);
	}
	catch(const std::out_of_range& e){
		throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}
	B->appendStr(B1->getPredicate().toString(),false,true,false);
	std::cout<<B->toString()<<"."<<"\n";
	delete B;
	delete B1;
}

//Parse soft rule
//0.8536 H.
//Test case covered
rule(R) ::= number(N) head(B) DISJUNCTION bodydef(B1).{
	//Doing this 
	R = new RuleCompletion;
	R->isHeadTop = true;
	B->addPredicate(B1->getPredicate());
	// RULE_COMPLETION_HEAD_DIS_BODY_TOP(B,B1)
	try{
		RuleCompletion_HD_BT(B,tree);
	}
	catch(const std::out_of_range& e){
		throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}
	B->appendStr(B1->getPredicate().toString(),false,true,false);
	std::cout<<N->toString()<<SPACE<<B->toString()<<"\n";
	delete B;
	delete B1;
}

//Parse hard rules
//B => H.
//Test case covered
rule(R) ::= head(H) REVERSE_IMPLICATION body(B) DOT.{
	R = new RuleCompletion;

	if (H->getDisjunction()){
		// RULE_COMPLETION_HEAD_DIS_BODY_TOP(H,B)
		R->isHeadTop = true;
		RuleCompletion_HD_BC(H,B,true,tree);
		std::cout<<B->toString()<<" => "<<H->toString()<<"."<<"\n";
		// std::cout << op;
	}
	else{
		// RULE_COMPLETION_BH(B,H);
		// R = new RuleCompletion(H->getPredicate(),predList, resultMap, varMap);
		try{
			R = RuleCompletion_BH(B,H,tree);
		}
		catch(const std::out_of_range& e){
			throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
		}
		std::cout<<B->toString()<<" => "<<H->toString()<<"."<<"\n";
	}
	delete B;
	delete H;
}

//Parse soft rules
//0.8536 B => H
//Test case covered
rule(R) ::= number(N) head(H) REVERSE_IMPLICATION body(B). {
	// RULE_COMPLETION_BH(B,H);
	// R = new RuleCompletion(H->getPredicate(),predList, resultMap, varMap);
	try{
		R = RuleCompletion_BH(B,H,tree);
	}
	catch(const std::out_of_range& e){
			throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}
	std::cout<< N->toString()<<SPACE<<B->toString()<<" => "<<H->toString()<<"\n";
	delete B;
	delete H;
}

//Parse soft exogenity rules (not to be completed)
//Ex. 0.8536 !!<body> => head.
// rule(R) ::= number NEGATION NEGATION body(B) IMPLICATION head(H). {
// 	tree->statHasDblNeg = true;
// 	R = new RuleCompletion;
// 	R->isHeadTop = true;	
// 	delete B;
// 	delete H;
// }

//Ex. 0.8536 !!(B => H)
//Test case covered
rule(R) ::= number(N) NEGATION NEGATION LBRACKET head(H) REVERSE_IMPLICATION body(B) RBRACKET. {
	R = new RuleCompletion;
	R->isHeadTop = true;	
	tree->statHasDblNeg = true;
	std::cout<< N->toString() << SPACE <<"!!("<<B->toString()<<" => "<<H->toString()<<"\n"; 
	delete B;
	delete H;
}

rule(R) ::= LPAREN head(H) RPAREN REVERSE_IMPLICATION body(B) DOT.{
	
	if (H->getPredicate().checkEquality() != 0){
		throw syntax_exception("Cannot have equality/Inequlity as a part of choice rule\n");
	}

	// RULE_COMPLETION_BH(B,H);
	// R = new RuleCompletion(H->getPredicate(),predList, resultMap, varMap);
	try{
		R = RuleCompletion_BH(B,H,tree);
	}
	catch(const std::out_of_range& e){
			throw syntax_exception("Error : Invalid number of arguments in some literal in the Rule.\n");
	}
	std::cout<<COMMENT<<B->toString()<<" => "<<H->toString()<<"\n";
	delete B;
	delete H;
}


//Parses body of rules
body(B) ::= body(B1) CONJUNCTION bodydef(Bd).{
	B = B1;
	B1->addPredicate(Bd->getPredicate());
	B->appendStr(Bd->getPredicate(),false,false,true);
	delete Bd;
}

// body(B) ::= body(B1) DISJUNCTION bodydef(Bd).{
// 	B = B1;
// 	B1->addPredicate(Bd->getPredicate());
// 	B->appendStr(Bd->getPredicate().toString(),false,true,false);
// 	delete Bd;
// }

head(H) ::= head(H1) DISJUNCTION bodydef(Hd).{
	H = H1;
	H1->addPredicate(Hd->getPredicate());
	H->appendStr(Hd->getPredicate().toString(),false,true,false);
	H->setDisjunction(true);
	delete Hd;
}

head(H) ::= bodydef(Bd).{
	H = new Head(Bd->getPredicate());
	// H->addPredicate(Bd->getPredicate());
	H->appendStr(Bd->getPredicate().toString(),false,false,false);
	delete Bd;
}

body(B) ::= bodydef(Bd).{
	B = new Body;
	B->addPredicate(Bd->getPredicate());
	B->appendStr(Bd->getPredicate(),false,false,false);
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
	auto itr = tree->variables.find(*(S->token));
	if(itr != tree->variables.end()){
		int expectedArgs = itr->getSize();
		if (expectedArgs != vars.size()){
			delete B;
			throw invalid_arguments(expectedArgs, vars.size(), *(S->token));
		}
	}
	else{
		delete B;
		throw syntax_exception(*(S->token) + " not declared.\n");
	}
	

}

//BodyDef with negation in front
bodydef(B) ::= NEGATION string(S) LBRACKET variables(Ve) RBRACKET.{	
	std::vector<std::string> vars;
	for(auto& v : *Ve)
		vars.push_back(*v);
	
	Predicate p(S->token, vars);
	p.setSingleNegation(true);
	B = new BodyDef;
	B->addPredicate(p);
	delete Ve;
	auto itr = tree->variables.find(*(S->token));
	if(itr != tree->variables.end()){
		int expectedArgs = itr->getSize();
		if (expectedArgs != vars.size()){
			delete B;
			throw invalid_arguments(expectedArgs, vars.size(), *(S->token));
		}
	}
	else{
		delete B;
		throw syntax_exception(*(S->token) + " not declared.\n");
	}

}

//BodyDef with double negation in front
bodydef(B) ::= NEGATION NEGATION string(S) LBRACKET variables(Ve) RBRACKET.{	
	std::vector<std::string> vars;
	for(auto& v : *Ve)
		vars.push_back(*v);
	
	Predicate p(S->token, vars);
	p.setDoubleNegation(true);
	B = new BodyDef;
	B->addPredicate(p);
	tree->statHasDblNeg = true;
	delete Ve;
	auto itr = tree->variables.find(*(S->token));
	if(itr != tree->variables.end()){
		int expectedArgs = itr->getSize();
		if (expectedArgs != vars.size()){
			delete B;
			throw invalid_arguments(expectedArgs, vars.size(), *(S->token));
		}
	}
	else{
		delete B;
		throw syntax_exception(*(S->token) + " not declared.\n");
	}

}


//BodyDef with double negation in front
//Bodydefs of the form (!!Load(A,B)) => Load(A,B). which needs to be completed. 
bodydef(B) ::= LBRACKET NEGATION NEGATION string(S) LBRACKET variables(Ve) RBRACKET RBRACKET.{	
	std::vector<std::string> vars;
	for(auto& v : *Ve)
		vars.push_back(*v);
	
	Predicate p(S->token, vars);
	p.setDoubleNegation(true);
	tree->statHasDblNeg = true;
	B = new BodyDef;
	B->addPredicate(p);
	delete Ve;
	auto itr = tree->variables.find(*(S->token));
	if(itr != tree->variables.end()){
		int expectedArgs = itr->getSize();
		if (expectedArgs != vars.size()){
			delete B;
			throw invalid_arguments(expectedArgs, vars.size(), *(S->token));
		}
	}
	else{
		delete B;
		throw syntax_exception(*(S->token) + " not declared.\n");
	}

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




//Head without negation in front
// headdef(H) ::= string(S) LBRACKET variables(Ve) RBRACKET.{
// 	std::vector<std::string> vars;
// 	for(auto& v : *Ve)
// 		vars.push_back(*v);
	
// 	Predicate p(S->token, vars);
// 	H = new HeadDef(p);
// 	H->addPredicate(p);
// 	delete Ve;
// }

// //Head with negation in front
// headdef(H) ::= NEGATION string(S) LBRACKET variables(Ve) RBRACKET.{
// 	std::vector<std::string> vars;
// 	for(auto& v : *Ve)
// 		vars.push_back(*v);
	
// 	Predicate p(S->token, vars);
// 	p.setSingleNegation(true);
// 	H = new HeadDef();
// 	H->addPredicate(p);
// 	delete Ve;
// }

//Parses declarations ex. next(step,step)
decl(D) ::= string(S) LBRACKET variables(Ve) RBRACKET.{
	D = new Variable;
	std::map<int, Domain> posMap;
	std::set<Domain>::iterator itr;
	int i=0;
	for(auto& v : *Ve){
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
	D->setVar(S->token);
	D->setPosMap(posMap);
	delete Ve;
}


//Parses hard facts ex. next(0,1).
predicate(P) ::= string(S) LBRACKET variables(Ve) RBRACKET DOT. {
	P = new Predicate;
	P->setVar(S->token);
	P->setTokens(*Ve);
	std::string s1;
	cout<<P->toString(s1,true);
	delete Ve;
}

//Parses weighted/soft facts ex. 12 next(0,1)
predicate(P) ::= number(N) string(S) LBRACKET variables(Ve) RBRACKET. {
	P = new Predicate;
	P->setVar(S->token);
	P->setTokens(*Ve);
	cout<<P->toString(N->toString()+SPACE, false);
	delete Ve;
}

//Parses weighted/soft constraints ex. 
// 0.4536 !!next(0,1)
predicate(P) ::= number(N) NEGATION NEGATION string(S) LBRACKET variables(Ve) RBRACKET. {
	P = new Predicate;
	P->notToBeCompleted();
	tree->statHasDblNeg = true;
	P->setVar(S->token);
	P->setTokens(*Ve);
	cout<<P->toString(N->toString()+SPACE, false);
	delete Ve;
}

//0.8536 !load(T,T)
predicate(P) ::= number(N) NEGATION string(S) LBRACKET variables(Ve) RBRACKET. {
	P = new Predicate;
	P->notToBeCompleted();
	P->setVar(S->token);
	P->setTokens(*Ve);
	cout<<P->toString(N->toString()+SPACE+"!", false);
	delete Ve;
}
//!!load(T,T).
predicate(P) ::= NEGATION NEGATION string(S) LBRACKET variables(Ve) RBRACKET DOT. {
	P = new Predicate;
	P->notToBeCompleted();
	tree->statHasDblNeg = true;
	P->setVar(S->token);
	P->setTokens(*Ve);
	std::string s1; 
	cout<<P->toString(s1, false);
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

// variable(V) ::= PLUS string(S). { V=S;}  

string(S) ::= STRING(S1). { S=S1;}
number(N) ::= NUMBER(N1). { N=N1;}

//Parses decimals
number(N) ::= lnumber(L) DOT rnumber(R). { 
	// N = new Token(*(L->token)+"."+*(R->token));
	N = L;
	N->modifyToken(*(L->token)+"."+*(R->token));
}

//Parses negative decimals
number(N) ::= MINUS lnumber(L) DOT rnumber(R). {
	N = L;
	N->modifyToken("-"+*(L->token)+"."+*(R->token));
}
lnumber(L) ::= NUMBER(N). { L=N; }
rnumber(R) ::= NUMBER(N). { R=N; }


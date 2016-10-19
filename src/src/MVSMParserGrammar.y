/*TODO Check predicates ASP translation*/
/*TODO Translation of not not predicates in ASP*/
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

}

%name MVSMParserGrammar
%start_symbol start
%token_prefix MVSM_PARSE_TOKEN_

%extra_argument {Tree* tree}

%parse_accept {
	if (tree->outputType == OutputType::OUTPUT_ASP)
		std::cout<<("%parsing complete!\n");
	else
    	std::cout<<("//parsing complete!\n");
}

%parse_failure 
{
    std::cout<<"Giving up.Parser is lost...\n";

}

%syntax_error{
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
    
}

%left REVERSE_IMPLICATION.
%nonassoc EQUAL.
%nonassoc COMMA.
%nonassoc LPAREN RPAREN.


%right NEWLINE.
%right CONJUNCTION.
%right DISJUNCTION.

%nonassoc LBRACKET RBRACKET.
%nonassoc IMPLICATION.

%nonassoc SORTS.
%right NEGATION.
%nonassoc WS.

%token_type {Token*}

%type start {Tree*}

%type prog {Tree*}

%type predicate {Predicate*}

%type decl {Variable*}

%type variables {std::vector<std::string*>*}


start ::= prog.

prog ::= prog SORTS sortdecl.

sortdecl ::= string(S) SEMI_COLON sortdecl.{
	std::string str = S->toString();
	auto it = tree->domainNamesList.find(str);
	if(it != tree->domainNamesList.end())
		throw syntax_exception("Redeclaration of sort "+S->toString()+"\n");
	else
		tree->domainNamesList.insert(S->toString());
}

sortdecl ::= NEWLINE sortdecl.

sortdecl ::= string(S) DOT.{
	std::string str = S->toString();
	auto it = tree->domainNamesList.find(str);
	if(it != tree->domainNamesList.end())
		throw syntax_exception("Redeclaration of sort "+S->toString()+"\n");
	else
		tree->domainNamesList.insert(str);	
}

prog ::= prog OBJECTS objectdecl.

objectdecl ::= object SEMI_COLON objectdecl.

objectdecl ::= object DOT.

objectdecl ::= NEWLINE objectdecl.

object ::= variables(Ve) COLON COLON string(S).{
	// if(tree->cdp == Tree::Current_Decl_Part::DECL_OBJECTS){
		auto itr = tree->domainNamesList.find(S->toString());
		if(itr != tree->domainNamesList.end()){
			Domain* d  = new Domain(S->toString());
			d->setVars(*Ve);
			tree->domains.insert(*d);
			for(auto& v : d->getVars()){
				tree->domainList.insert(v);	
			}
			cout<<d->toString(false);
			delete d;
		}
		else{
			throw syntax_exception("Domain " + S->toString() +" not declared.\n");
		}
	
	delete Ve;
}

prog ::= prog CONSTANTS constantdecl.

constantdecl ::= constant SEMI_COLON constantdecl.

constantdecl ::= constant DOT.

constantdecl ::= NEWLINE constantdecl. 

constant ::= string(S) LBRACKET variables(Ve) RBRACKET COLON COLON string(S1).{
	Variable* va = new Variable;
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
			// va->setVar(S->token);
			posMap[i++] = *itr;
		}
	}

	itr = tree->domains.find(S1->toString());
	if (itr == tree->domains.end()){
		throw syntax_exception("Syntax Error - Domain " + S1->toString() + " not found.\n");
	}
	else{
		posMap[i] = *itr;
		va->setRhsDomain(*itr);
	}

	va->setVar(S->toString());
	va->setPosMap(posMap);
	tree->variables.insert(*va);
	

	/*for ASP output we do not print constants */
	if(tree->outputType != OutputType::OUTPUT_ASP)
		cout<<va->toString();

	delete va;
	delete Ve;
}

constant ::= string(S) LBRACKET variables(Ve) RBRACKET.{
	Variable* va = new Variable;
	std::map<int, Domain> posMap;
	std::set<Domain>::iterator itr;
	int i=0;
	for(auto& v : *Ve){
		itr = tree->domains.find(*v);
		if (itr == tree->domains.end()){
			throw syntax_exception("Syntax Error - Domain " + *v + " not found.\n");
		}
		else{
			posMap[i++] = *itr;
		}
	}

	va->setVar(S->toString());
	va->setPosMap(posMap);
	tree->variables.insert(*va);

	/*for ASP output we do not print constants */
	if(tree->outputType != OutputType::OUTPUT_ASP)
		cout<<va->toString();
	delete Ve;
	delete va;
}

constant ::= string(S).{
	Variable* va = new Variable;
	va->setVar(S->toString());
	tree->variables.insert(*va);
	/*for ASP output we do not print constants */
	if(tree->outputType != OutputType::OUTPUT_ASP)
		cout<<va->toString()<<"\n";
	
	delete va;	
}

constant ::= string(S) COLON COLON string(S1).{
	Variable* va = new Variable;
	std::map<int, Domain> posMap;
	std::set<Domain>::iterator itr;
	int i=0;
	

	itr = tree->domains.find(S1->toString());
	if (itr == tree->domains.end()){
		throw syntax_exception("Syntax Error - Domain " + S1->toString() + " not found.\n");
	}
	else{
		posMap[i] = *itr;
		va->setRhsDomain(*itr);
	}

	va->setVar(S->toString());
	va->setPosMap(posMap);
	tree->variables.insert(*va);
	/*for ASP output we do not print constants */
	if(tree->outputType != OutputType::OUTPUT_ASP)
		cout<<va->toString();
	
	delete va;	
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

//Parse Hard rule
//<= B.
//Test case covered
rule(R) ::= REVERSE_IMPLICATION body(B) DOT.{
	R = new RuleCompletion;
	R->isHeadTop = true;
	
	if(tree->outputType != OutputType::OUTPUT_ASP){
		std::cout<<"("
					<<B->toNNFString()
					<<")"
					<<LanguageConstants::LINE_END
					<<"\n";
	}
	else{
		std::cout<<LanguageConstants::IMPL
				<<B->toString()
				<<LanguageConstants::LINE_END
				<<"\n";
	}
	delete B;
}

/*TODO? Weighted Constraint. For ASP follow rules from the paper*/
rule(R) ::= number(N) REVERSE_IMPLICATION body(B).{
	R = new RuleCompletion;
	R->isHeadTop = true;
	
	if(tree->outputType != OutputType::OUTPUT_ASP){
		std::cout<<N->toString()<<SPACE
					<<"("
					<<B->toNNFString()
					<<")"
					<<"\n";
	}
	else{
		std::string str = ":~"
				+ B->toString()
				+ " , "
				+ B->getExtra(tree->variables) 
				+ LanguageConstants::LINE_END
				+ " "
				+ "["
				+  std::to_string((int)(std::stof(N->toString())* 10000))
				+  ","
				+  std::to_string(tree->weak_constraint_counter);

		std::string temp = B->getExtraConstants();
		if(temp.length() > 0){
			str += ","
				+ temp;
		}
				
		str += std::string("]") + std::string("\n");

		cout << str;
		tree->weak_constraint_counter++;
	
	}
	// std::cout<<N->toString()<<SPACE<<"("<<B->toNNFString()<<")"<<"\n";
	delete B;
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
	
	std::string temp;
	if(tree->outputType == OutputType::OUTPUT_ASP){
		temp = B->getExtra(tree->variables);
		if(temp.length() > 0){
			temp = B->toString() + ":-" + temp;
		}
		else{
			temp = B->toString();
		}
	}
	
	std::cout<<temp<<"."<<"\n";
	
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
//ASP
// H :- B
//Test case covered
rule(R) ::= head(H) REVERSE_IMPLICATION body(B) DOT.{
	R = new RuleCompletion;

	if (H->getDisjunction()){
		// RULE_COMPLETION_HEAD_DIS_BODY_TOP(H,B)
		R->isHeadTop = true;
		RuleCompletion_HD_BC(H,B,true,tree);
		if(tree->outputType == OutputType::OUTPUT_ALCHEMY)
			std::cout<<B->toString()
					<<" => "
					<<H->toString()
					<<LanguageConstants::LINE_END
					<<"\n";
		if(tree->outputType == OutputType::OUTPUT_ASP)
			tree->printASPRuleHB(H,B);
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
		if(tree->outputType == OutputType::OUTPUT_ALCHEMY)
			std::cout<<B->toString()
					<<" => "
					<<H->toString()
					<<LanguageConstants::LINE_END
					<<"\n";
		if(tree->outputType == OutputType::OUTPUT_ASP)
			tree->printASPRuleHB(H,B);
	}
	delete B;
	delete H;
}

//Parse soft rules
//0.8536 H <= B
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

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY)
		std::cout<< N->toString()
				<<SPACE
				<<B->toString()
				<<" => "
				<<H->toString()
				<<"\n";
	
	if(tree->outputType == OutputType::OUTPUT_ASP){

		std::cout << "unsat(" << tree->weak_constraint_counter << ")"
					<< " :- "
					<< B->toString()
					<< " , "
					/*Change this to NNF String*/
					<< H->toNNFString()
					<<LanguageConstants::LINE_END
					<<"\n"; 

		std::cout << H->toString()
					<< " :- "
					<< B->toString()
					<< " , "
					<< "not "
					<< "unsat(" << tree->weak_constraint_counter << ")"
					<<LanguageConstants::LINE_END
					<<"\n"; 

	
		std::cout   << " :~ "
					<< "unsat(" << tree->weak_constraint_counter << ")"
					<< ". "
					<< "["
					<< std::to_string((int)(std::stof(N->toString())* 10000))
					<<","
					<< tree->weak_constraint_counter
					<< "]"
					<<"\n";

		tree->weak_constraint_counter++; 


	}


	delete B;
	delete H;
}


//Ex. 0.8536 !!(B => H)
//Test case covered
rule(R) ::= number(N) NEGATION NEGATION LBRACKET head(H) REVERSE_IMPLICATION body(B) RBRACKET. {
	R = new RuleCompletion;
	R->isHeadTop = true;	
	tree->statHasDblNeg = true;

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY)
		std::cout<< N->toString() 
				<< SPACE 
				<<"!!("
				<<B->toString()
				<<" => "
				<<H->toString()
				<<"\n"; 
	if(tree->outputType == OutputType::OUTPUT_ASP)
		std::cout<< N->toString() 
				<< SPACE 
				<<H->toString()
				<<" :- "
				<<B->toString()
				<<LanguageConstants::LINE_END
				<<"\n"; 
	
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

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY)
		std::cout<<COMMENT<<B->toString()<<" => "<<H->toString()<<"\n";
	if(tree->outputType == OutputType::OUTPUT_ASP)
		std::cout<<H->toString()<<" :- "<<B->toString()<<LanguageConstants::LINE_END<<"\n";
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
	Predicate p = Bd->getPredicate();
	B->addPredicate(p);
	B->appendStr(p,false,false,false);
	delete Bd;
}



// BodyDef without negation in front
bodydef(B) ::= literal(L).{	
	B = L;
}

// //BodyDef with negation in front
bodydef(B) ::= NEGATION literal(L).{	
	B = L;
	Predicate p = B->getPredicate();
	p.setSingleNegation(true);
	B->addPredicate(p);
	// B->getPredicate().setSingleNegation(true);
}

// //BodyDef with double negation in front
bodydef(B) ::= NEGATION NEGATION literal(L).{	
	B = L;
	tree->statHasDblNeg = true;
	B->getPredicate().setDoubleNegation(true);
}


// // BodyDef with double negation in front
// // Bodydefs of the form (!!Load(A,B)) => Load(A,B). which needs to be completed. 
bodydef(B) ::= LBRACKET NEGATION NEGATION literal(L) RBRACKET.{	
	B = L;
	tree->statHasDblNeg = true;
	B->getPredicate().setDoubleNegation(true);
}

//parses bodydef of the form a=b
bodydef(B) ::= string(S) EQUAL string(S1).{
	B = new BodyDef;
	auto itr = tree->variables.find(*(S->token));
	if (itr != tree->variables.end()){
		/*Treat it as a bodydef with 1 variable*/

		/* 
		Check if S1 is a valid value of it's domain.
		If it is not throw syntax_exception.
		Why? It could be a variable also which is not a part of the domain. 
		Not required in this case.
		*/
		
		std::vector<std::string> vars;
		vars.push_back(*(S1->token));
		Predicate p(S->token);
		p.setTokens(vars, tree->domainList);
		B->addPredicate(p);
		int expectedArgs = (tree->variables.find(*(S->token)))->getSize();
		if (expectedArgs != vars.size()){
			delete B;
			throw invalid_arguments(expectedArgs, vars.size(), *(S->token));
		}
	}
	
	else{
		Predicate p(S->token,S1->token);
		p.setEquality();
		B->addPredicate(p);
	}
}

//not HiddenIn=P1
bodydef(B) ::= NEGATION string(S) EQUAL string(S1).{
	std::vector<std::string> vars;
	vars.push_back(S1->toString());
	Predicate p(S->token);
	p.setTokens(vars, tree->domainList);
	p.setSingleNegation(true);
	B = new BodyDef;
	B->addPredicate(p);
	// delete Ve;
	int expectedArgs = (tree->variables.find(*(S->token)))->getSize();
	if (expectedArgs != vars.size()){
		delete B;
		throw invalid_arguments(expectedArgs, vars.size(), *(S->token));
	}
}
//parses bodydef of the form a!=b
bodydef(B) ::= string(S) NEGATION EQUAL string(S1).{
	
	/*check if S is declared in constant section
	 if it is then it's a syntax error 
	 Cannot have HiddeIn != P1 */
	auto itr = tree->variables.find(*(S->token));
	if (itr != tree->variables.end()){
		throw syntax_exception("!= cannot be used with a constant on LHS.\n");
	}

	Predicate p(S->token,S1->token);
	p.setInEquality();
	B = new BodyDef;
	B->addPredicate(p);
}


%type literal{BodyDef*}

literal(L) ::= string(S) LBRACKET variables(Ve) RBRACKET EQUAL variable(R).{
	std::vector<std::string> vars;
	for(auto& v : *Ve)
		vars.push_back(*v);
	vars.push_back(*(R->token));
	Predicate p(S->token);
	p.setTokens(vars, tree->domainList);
	L = new BodyDef;
	L->addPredicate(p);
	auto itr = tree->variables.find(S->toString());
	if(itr == tree->variables.end()){
		delete L;
		throw syntax_exception("Literal "+ S->toString() + " not found.\n");
	}
	delete Ve;
	int expectedArgs = (tree->variables.find(S->toString()))->getSize();
	if (expectedArgs != vars.size()){
		delete L;
		throw invalid_arguments(expectedArgs, vars.size(), *(S->token));
	}
}

literal(L) ::= string(S) LBRACKET variables(Ve) RBRACKET.{
	std::vector<std::string> vars;
	for(auto& v : *Ve)
		vars.push_back(*v);
	Predicate p(S->token);
	p.setTokens(vars, tree->domainList);
	L = new BodyDef;
	L->addPredicate(p);
	delete Ve;
	auto itr = tree->variables.find(S->toString());
	if(itr == tree->variables.end()){
		delete L;
		throw syntax_exception("Literal "+ S->toString() + " not found.\n");
	}
	int expectedArgs = itr->getSize();
	if (expectedArgs != vars.size()){
		delete L;
		throw invalid_arguments(expectedArgs, vars.size(), *(S->token));
	}	
}

literal(L) ::= variable(V).{
	Predicate p(V->token);
	auto itr = tree->variables.find(V->toString());
	L = new BodyDef;
	/*Special Case: BodyDef does not have variables*/
	L->setHasVariables();
	L->addPredicate(p);
}

literal(L) ::= string(S) EQUAL COUNT LPAREN aggregateCum(A) RPAREN.{
	std::string s = (*S).toString();
	Util::toUpper(s);
	s = s + "= #count{" + A->toString() + "}";
	Predicate p(S->token);
	p.setString(s);
	L = new BodyDef;
	L->addPredicate(p);
	delete A;
}


aggregate(A) ::= string(S1) COLON literal(L1).{
	A = new Token(*(S1->token));
	std::string s1 = A->toString();
	Util::toUpper(s1);
	s1 = s1 + ":" + L1->toString();
	A->modifyToken(s1);
	delete L1;
}

aggregate(A) ::= number(S1) COLON literal(L1).{
	A = new Token(*(S1->token));
	std::string s1 = A->toString();
	s1 = s1 + ":" + L1->toString();
	A->modifyToken(s1);
	delete L1;
}

aggregate(A) ::= string(S1) COMMA literal(L2) COLON literal(L1).{
	A = new Token(*(S1->token));
	std::string s1 = A->toString();
	Util::toUpper(s1);
	s1 = s1 + "," + L2->toString() + ":" + L1->toString();
	A->modifyToken(s1);
}


aggregate(A) ::= number(S1) COMMA literal(L2) COLON literal(L1).{
	A = new Token(*(S1->token));
	std::string s1 = (*S1).toString();
	// Util::toUpper(s1);
	s1 = s1 + "," + L2->toString()+ ":" + L1->toString();
	A->modifyToken(s1);
}

aggregateCum(A) ::= aggregate(A1).{
	A = new Token(*(A1->token));
	delete A1;
}

aggregateCum(A) ::= aggregateCum(A1) SEMI_COLON aggregate(A2).{
	A = A1;
	A->modifyToken(A1->toString() + ";" + A2->toString());
	delete A2;
}


predicate(P) ::= literal(L) DOT.{
	P = new Predicate;
	*P = L->getPredicate();
	if(L->getHasVariables() == false){
		/*Its a special case*/
		P->notToBeCompleted();	
	}
	
	auto itr = tree->variables.find(P->getVar());
	if(itr != tree->variables.end()){
		itr->setCompleted();
	}

	std::string s1,s2;
	

	if(tree->outputType == OutputType::OUTPUT_ASP){
		s2 = P->getExtra(tree->variables);

		if(s2.length() > 0){
			s1 = P->toString(s1,false);
			s1 += ":-";
			s1 += s2;
			s1 += ".\n";
		}
		else{
			s1 = P->toString(s1,true);
		}
			

		
	}

	cout<<s1;

	delete L;
}

predicate(P) ::= number(N) literal(L).{
	P = new Predicate;
	*P = L->getPredicate();

	if(L->getHasVariables() == false){
		/*Its a special case*/
		P->notToBeCompleted();	
	}
	
	auto itr = tree->variables.find(P->getVar());
	if(itr != tree->variables.end()){
		itr->setCompleted();
	}

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY){
		cout<<P->toString(N->toString()+SPACE, false);
	}
	if(tree->outputType == OutputType::OUTPUT_ASP){

		std::cout << "unsat(" << tree->weak_constraint_counter << ")"
					<< " :- "
					<< "not "
					<< P->toString()
					<<LanguageConstants::LINE_END
					<<"\n"; 

		std::cout << P->toString()
					<< " :- "
					<< "not "
					<< "unsat(" << tree->weak_constraint_counter << ")"
					<<LanguageConstants::LINE_END
					<<"\n"; 

	
		std::cout   << " :~ "
					<< "unsat(" << tree->weak_constraint_counter << ")"
					<< ". "
					<< "["
					<< std::to_string((int)(std::stof(N->toString())* 10000))
					<<","
					<< tree->weak_constraint_counter
					<< "]"
					<<"\n";

		tree->weak_constraint_counter++; 

	}	
	delete L;
}

predicate(P) ::= number(N) NEGATION NEGATION literal(L).{
	P = new Predicate;
	*P = L->getPredicate();
	P->notToBeCompleted();

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY){
		tree->statHasDblNeg = true;
		cout<<P->toString(N->toString()+SPACE, false);	
	}
	else if(tree->outputType == OutputType::OUTPUT_ASP){
		std::string str = P->toString(":~ not ", false);
		std::string temp  = P->getExtra(tree->variables);	
		if(temp.length() > 0)
			str += ",";
		str += temp;
		str += LanguageConstants::LINE_END;
		str += " [" + 
				std::to_string((int)(std::stof(N->toString())* 10000)) + 
				"," + 
				std::to_string(tree->weak_constraint_counter++) + 
				"," +
				P->getExtraConstants()+
				"]\n";
		cout<<str;
	}
	
	delete L;
}

predicate(P) ::= number(N) NEGATION literal(L).{
	P = new Predicate;
	*P = L->getPredicate();
	P->notToBeCompleted();

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY){
		cout<<P->toString(N->toString()+SPACE, false);
	}
	else if(tree->outputType == OutputType::OUTPUT_ASP){
		std::string str = P->toString(":~ ", false);		
		std::string temp  = P->getExtra(tree->variables);	
		if(temp.length() > 0)
			str += ",";
		str += " [" + 
		std::to_string((int)(std::stof(N->toString())* 10000)) + 
		"," + 
		std::to_string(tree->weak_constraint_counter++) + 
		"," +
		P->getExtraConstants() + 
		"]\n";
		cout<<str;
	}

	
	delete L;
}

predicate(P) ::= NEGATION NEGATION literal(L) DOT.{
	P = new Predicate;
	*P = L->getPredicate();
	P->notToBeCompleted();
	tree->statHasDblNeg = true;
	std::string s1; 

	if(tree->outputType == OutputType::OUTPUT_ALCHEMY){
		cout<<P->toString(s1, false);
	}
	else if(tree->outputType == OutputType::OUTPUT_ASP){
		cout<<P->toString(":- not ", true);		
	}


	
	delete L;	
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

string(S) ::= STRING(S1).{ S=S1;}


number(N) ::= NUMBER(N1).{ N=N1; }


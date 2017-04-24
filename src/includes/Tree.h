#pragma once

#include <set>
#include <string>
#include <iostream>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <queue>          // std::queue

#include <boost/algorithm/string.hpp>

#include "Domain.h"
#include "FactCompletion.h"
#include "Predicate.h"
#include "Variable.h"
#include "RuleCompletion.h"
#include "Head.h"
#include "Body.h"

#include "Config.h"

#include "exceptions/undefined_key.h"
#include "exceptions/invalid_arguments.h"


class Tree
{
public:
	Tree(OptimizationLevel,OutputType);
	~Tree();

	/* Required for MVSM parsing*/
	enum Current_Decl_Part{
		DECL_NONE,
		DECL_SORTS,
		DECL_OBJECTS,
		DECL_CONSTANTS
	};

	bool statHasDblNeg = false;

	std::set<Domain> domains;
	std::multimap<std::string, FactCompletion> facts;
	std::map<std::string, std::string> completedLiterals;

	std::set<std::string> domainNamesList;
	
	std::set<std::string> domainList;
	/*ASP requires domain to be in lower cse exactly opposite of what Alchemy requires.
	So in the case of ASP parsing, we keep one more set of domain non capitalized*/
	// std::set<std::string> domainList;

	std::set<Variable> variables;

	std::multimap<std::string, RuleCompletion> rules;

	// std::string uniqueVars[14] = {"_a","_b","_c","_d","_e","_f","_g","_h","_i","_j","_k","_l","_m","_n"};
	std::string uniqueVars[14] = {"aa","bb","cc","dd","ee","ff","gg","hh","ii","jj","kk","ll","mm","nn"};

	OptimizationLevel level;
	OutputType outputType;

	int auxCount = 0;

	std::string tuffyAuxHeaders;

	
	/* Required for MVSM Parsing */
	// std::set<std::string> sorts;
	Current_Decl_Part cdp = Current_Decl_Part::DECL_NONE;

	void completeFacts();

	void completeRules();

	void completeDeclarations();

	inline bool hasConstant(Predicate p){
		for(unsigned int i=0;i<p.getTokens().size();i++){
			std::set<std::string>::iterator itr = domainList.find(p.getTokens().at(i));
			if(itr != domainList.end())
				return true;
		}
		return false;
	}

	inline std::string getTuffyAuxHeaders(){
		return tuffyAuxHeaders;
	}

	inline bool isConstant(std::string str){
		std::set<std::string>::iterator itr = domainList.find(str);
		if(itr != domainList.end())
			return true;
		else
			return false;
	}

	inline void removeConstantsPair(std::set<std::pair<std::string, std::string>>& vec){
		std::set<std::string>::iterator itr; 
		for ( auto iter = vec.begin(); iter != vec.end(); /* Empty on purpose*/ ){
			if(domainList.find(iter->first) != domainList.end()){
				iter = vec.erase(iter);
			}
			else{
				++iter;
			}
		}
	}


	bool useAux(bool hasOrphan, int vectorCount){
		if (level == OptimizationLevel::OPTI_NONE){
			return false;
		}
		else if (level == OptimizationLevel::ORPHAN_AUX){
			return hasOrphan;
		}
		else{
			//This returns true even if there is only a single literal on the right hand side.
           //This is unnecessary and artificially inflates the number of total atoms
           if(vectorCount > 1)
                   return true;
           else
                   return hasOrphan;

		}
	}

	void printTuffyAux(std::string& LHS, std::string& RHS, std::queue<int>& posVector);
	void printTuffyAux(std::string& LHS, std::string& RHS);

	void printTuffyExist(const std::string& LHS, std::string& RHS);

	int weak_constraint_counter = 1;
	/*Required for turning weighted programs into clingo*/
	// int unsatCount = 0;

	void printASPRuleHB(Head*, Body*);

	std::set<std::string> findVariables(const std::string&);
	std::set<std::string> findFreeVariables(const std::string&, const std::string&);
};
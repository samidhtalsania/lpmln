#include <set>
#include <string>
#include <iostream>
#include <algorithm>
#include <map>
#include <unordered_map>

#include "Domain.h"
#include "FactCompletion.h"
#include "Predicate.h"
#include "Variable.h"
#include "RuleCompletion.h"

class Tree
{
public:
	Tree();
	~Tree();

	bool statHasDblNeg = false;

	std::set<Domain> domains;
	std::multimap<std::string, FactCompletion> facts;


	std::set<std::string> domainNamesList;
	
	std::set<std::string> domainList;
	std::set<Variable> variables;

	std::multimap<std::string, RuleCompletion> rules;

	std::string uniqueVars[14] = {"_a","_b","_c","_d","_e","_f","_g","_h","_i","_j","_k","_l","_m","_n"};

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


};
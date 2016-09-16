#pragma once
#include <set>
#include "Variable.h"
#include "Predicate.h"

class Body
{
public:
	Body();
	~Body();
	Body(std::vector<Predicate> _predList):predList(_predList){}

	void addPredicate(Predicate p){
		predList.push_back(p);
	}

	std::string toString() const{
		return bodyStr;
	}

	std::string toNNFString() const{
		return NNFbodyStr;
	}


	void appendStr(Predicate, bool, bool, bool);

	bool bodyHasNegation(){
		return bodyNegation;
	}

	std::string getExtra(); 

	inline std::vector<Predicate> getPredicate(){ return predList; } 

	std::string getExtra(const std::set<Variable>& variable);

private:
	std::set<std::pair<std::string,std::string>> orphanVarsMap;
	std::set<std::pair<std::string,std::string>> orphanVarsHeadMap;
	std::vector<Predicate> predList;
	
	std::string bodyStr;	
	std::string NNFbodyStr;

	bool bodyNegation = false;
};
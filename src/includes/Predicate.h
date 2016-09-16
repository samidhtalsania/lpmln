#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>

#include "Variable.h"

class Predicate
{
public:
	
	
	Predicate(std::string* _lvar, std::string* _rvar):
				lVar(*_lvar),rVar(*_rvar){};
	Predicate(std::string* _var):var(*_var){};
	Predicate();				
	~Predicate();
	
	bool operator< (const Predicate &right) const;
	bool operator== (const Predicate &right) const;
	
	std::string getVar() const { return var; }
	
	std::vector<std::string> getTokens() const {return tokens;}

	void setTokens(std::vector<std::string*> domainVariables, const std::set<std::string>& domainList){
		for(auto& v: domainVariables){
			checkConstant(*v, domainList);
			tokens.push_back(*v);
		}
	}

	void setTokens(std::vector<std::string> domainVariables, const std::set<std::string>& domainList){
		for(auto& v: domainVariables){
			checkConstant(v, domainList);
			tokens.push_back(v);
		}
	}		

	void setVar(std::string* domainVariable){
		var = *domainVariable;
	}

	std::vector<std::string> getTokens(){ return tokens;}

	int checkEquality(){ 
		if(isEquality)
			return 1;
		else if(isInEquality)
			return 2;
		else
			return 0;
	}

	void insertToken(std::string str, const std::set<std::string>& domainList){
		checkConstant(str,domainList);
		tokens.push_back(str);
	}

	std::string getLvar() const { return lVar;}
	std::string getRvar() const { return rVar;}

	void setEquality() { isEquality = true;}
	void setInEquality() { isInEquality = true;}
	void setSingleNegation(bool val) { singleNegation = val;}
	void setDoubleNegation(bool val) { doubleNegation = val;}

	bool isNegated(){
		if(singleNegation || doubleNegation)
			return true;
	}

	bool isSingleNegated() { return singleNegation; }
	bool isDoubleNegated() { return doubleNegation; }
	bool needsToBeCompleted() { return toBeCompleted; }

	void notToBeCompleted() { toBeCompleted = false;} 

	std::set<std::string> getConstants(){
		return constantLocation;
	}
	
	/*Called by parser to print facts*/
	std::string toString(const std::string& s, bool period) const;

	/*Called by bodyDef to print body*/
	std::string toString() const;

	/*Prints Negation Normal Form String*/
	std::string toNNFString() const;

	std::string  getExtra(const std::set<Variable>& variable);

private:
	std::string var;
	std::string lVar;
	std::string rVar;

	std::string extraASPString;
	
	std::vector<std::string> tokens;
	std::set<std::string> constantLocation;
	std::set<int> variableLocation;

	bool isEquality = false;
	bool isInEquality = false;
	bool toBeCompleted = true;
	bool singleNegation = false;
	bool doubleNegation = false; 

	void checkConstant(std::string str,  const std::set<std::string>& domainList){
		auto it = domainList.find(str);
		if (it != domainList.end()){
			constantLocation.insert(str);
		}
	}
};


#pragma once
#include <string>
#include <vector>
#include <map>


class Predicate
{
public:
	Predicate(std::string* _var, std::vector<std::string> _tokens): var(*_var), tokens(_tokens){};
	Predicate(std::string* _lvar, std::string* _rvar):
				lVar(*_lvar),rVar(*_rvar){};
	Predicate();				
	~Predicate();
	
	bool operator< (const Predicate &right) const;
	bool operator== (const Predicate &right) const;
	
	std::string getVar() const { return var; }
	
	std::vector<std::string> getTokens() const {return tokens;}

	void setTokens(std::vector<std::string*> domainVariables)
	{
		for(auto& v: domainVariables)
			tokens.push_back(*v);
	}	

	void setVar(std::string* domainVariable)
	{
		var = *domainVariable;
	}

	std::vector<std::string> getTokens(){ return tokens;}

	int checkEquality() 
	{ 
		if(isEquality)
			return 1;
		else if(isInEquality)
			return 2;
		else
			return 0;
	}

	std::string getLvar() const { return lVar;}
	std::string getRvar() const { return rVar;}

	void setEquality() { isEquality = true;}
	void setInEquality() { isInEquality = true;}
	void setSingleNegation(bool val) { singleNegation = val;}
	void setDoubleNegation(bool val) { doubleNegation = val;}

	bool isSingleNegated() { return singleNegation; }
	bool isDoubleNegated() { return doubleNegation; }

	bool needsToBeCompleted() { return toBeCompleted; }

	void notToBeCompleted() { toBeCompleted = true;} 

	std::string toString() const;

private:
	std::string var;
	std::string lVar;
	std::string rVar;
	std::vector<std::string> tokens;
	bool isEquality = false;
	bool isInEquality = false;
	bool toBeCompleted = true;
	bool singleNegation = false;
	bool doubleNegation = false; 
};


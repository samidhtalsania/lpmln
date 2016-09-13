#include "Predicate.h"
#include "LanguageConstants.h"
#include <set>
#include <algorithm>
#include <string>

bool Predicate::operator< (const Predicate &right) const
{
	if(this->var != right.var)
		return this->var < right.var;
	else{
		std::set<std::string> s1(this->tokens.begin(), this->tokens.end());
		std::set<std::string> s2(right.tokens.begin(), right.tokens.end());
		
		std::set<std::string> res;
		std::set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(),std::inserter(res, res.end()));
		
		if(res.size() > 0)
			return true;
		return false;
	}
    
}

bool Predicate::operator== (const Predicate &right) const{
	return this->var == right.var;
}

Predicate::Predicate()
{
}


Predicate::~Predicate()
{
}

std::string Predicate::toString() const{
	std::string str;

	if(isEquality){
		str += lVar + "=" + rVar;
		return str;
	}

	if(isInEquality){
		str += lVar + "!=" + rVar;
		return str;
	}
	


	if(singleNegation) str += LanguageConstants::NOT;
	// else if(doubleNegation) str += "!!";

	str += var;

	if(tokens.size() != 0){
		str += "(";

		for (auto i = tokens.begin(); i != tokens.end(); ++i)
		{
			str += *i;
			str += ",";
		}

		str = str.substr(0,str.size()-1);
		str += ")";
	}

	return str;
}


std::string Predicate::toNNFString() const{
	std::string str;

	if(isEquality){
		str += "(" + lVar + "!=" + rVar + ")";
		return str;
	}

	if(isInEquality){
		str +=  "(" + lVar + "=" + rVar + ")";
		return str;
	}
	


	if(singleNegation) str += "";
	else if(doubleNegation) str += LanguageConstants::NOT;
	else str += LanguageConstants::NOT;

	str += var;

	if(tokens.size() != 0){
		str += "(";

		for (auto i = tokens.begin(); i != tokens.end(); ++i)
		{
			str += *i;
			str += ",";
		}

		str = str.substr(0,str.size()-1);
		str += ")";
	}

	return str;
}


std::string Predicate::toString(const std::string& s, bool period) const{
	std::string str;
	str += s;
	str += var;
	if(tokens.size() != 0){
		str += "(";
		for(auto it=tokens.begin();it != tokens.end(); ++it){
			str += *it;
			str += ",";
		}
		str = str.substr(0, str.size()-1);
		str += ")";
	}
	if(period || LanguageConstants::TYPE == OutputType::OUTPUT_ASP)
		str += ".\n";
	else
		str += "\n";
	return str;
}


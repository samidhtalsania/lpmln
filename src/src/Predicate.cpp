#include "Predicate.h"
#include "Util.h"
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

std::string Predicate::toString(const std::set<std::string>& domainList) const {

	if (isAggregate){
		return aggregateString;
	}

	std::string str;

	if(isEquality){
		std::string left = lVar;
		std::string right = rVar;
		if(LanguageConstants::TYPE == OutputType::OUTPUT_ASP){
			
			if(domainList.find(left) != domainList.end())
				Util::toLower(left);
			else
				Util::toUpper(left);
			
			if(domainList.find(right) != domainList.end())
				Util::toLower(right);
			else
				Util::toUpper(right);
				
			
		}	
		str += left + "=" + right;
		return str;
	}

	if(isInEquality){
		std::string left = lVar;
		std::string right = rVar;
		if(LanguageConstants::TYPE == OutputType::OUTPUT_ASP){
			
			if(domainList.find(left) != domainList.end())
				Util::toLower(left);
			else
				Util::toUpper(left);
			
			if(domainList.find(right) != domainList.end())
				Util::toLower(right);
			else
				Util::toUpper(right);
				
			
		}	
		str += left + "!=" + right;
		return str;
	}
	


	if(singleNegation) str += LanguageConstants::NOT;
	// else if(doubleNegation) str += "!!";

	std::string tempStr = var;
	if(LanguageConstants::TYPE == OutputType::OUTPUT_ASP){
		Util::toLower(tempStr);
	}

	str += tempStr;

	if(tokens.size() != 0){
		str += "(";
		int count = 0;
		for (auto i = tokens.begin(); i != tokens.end(); ++i)
		{
			tempStr = *i;
			
			if(LanguageConstants::TYPE == OutputType::OUTPUT_ASP){
				if(constantLocation.find(*i) != constantLocation.end())
					Util::toLower(tempStr);
				else{
					/*This is a variable. 
					Its' component would be added to extraASPString*/
					Util::toUpper(tempStr);

				}
				
			}

			if(LanguageConstants::TYPE == OutputType::OUTPUT_ROCKIT){
				if(constantLocation.find(*i) != constantLocation.end())
					tempStr = "\"" + tempStr + "\"";
			}
			
			str += tempStr;
			str += ",";	
			count++;
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
			std::string tempStr = *i;
			if(LanguageConstants::TYPE == OutputType::OUTPUT_ROCKIT){
				if(constantLocation.find(*i) != constantLocation.end())
					tempStr = "\"" + tempStr + "\"";
			}
			str += tempStr;
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

	std::string tempStr = var;
	if(LanguageConstants::TYPE == OutputType::OUTPUT_ASP){
		Util::toLower(tempStr);
	}

	str += tempStr;
	if(tokens.size() != 0){
		str += "(";
		for(auto it=tokens.begin();it != tokens.end(); ++it){

			tempStr = *it;
			
			if(LanguageConstants::TYPE == OutputType::OUTPUT_ASP){
				if(constantLocation.find(*it) != constantLocation.end())
					Util::toLower(tempStr);
				else{
					/*This is a variable. 
					Its' component would be added to extraASPString*/
					Util::toUpper(tempStr);
				}
			}

			if(LanguageConstants::TYPE == OutputType::OUTPUT_ROCKIT){
				if(constantLocation.find(*it) != constantLocation.end())
					tempStr = "\"" + tempStr + "\"";
			}

			str += tempStr;
			str += ",";
		}
		str = str.substr(0, str.size()-1);
		str += ")";
	}

	if(LanguageConstants::TYPE == OutputType::OUTPUT_ASP){
		if(period)
			str += ".\n";
		// else
		// 	str += ".";
	}

	if(LanguageConstants::TYPE == OutputType::OUTPUT_ALCHEMY 
		|| LanguageConstants::TYPE == OutputType::OUTPUT_TUFFY){
		
		if(period)
			str += ".\n";
		else 
			str += "\n";	
	}


	
	return str;
}

std::string  Predicate::getExtra(const std::set<Variable>& variable){
	auto itr = variable.find(var);
	std::string str;
	int count = 0;
	for (auto i = tokens.begin(); i != tokens.end(); ++i){
		std::string tempStr = *i;
		if(constantLocation.find(*i) == constantLocation.end()){
			auto itr2 = itr->getPosMap().find(count);
			std::string t = itr2->second.getDomainVar();
			Util::toLower(t);
			str += t;
			str += "(";
			Util::toUpper(tempStr);
			str += tempStr;
			str += ")";
			str += " , ";

			/*We need this set to put into weight in ASP*/
			extraConstants.insert(tempStr);
		}
		count++;
	}

	str = str.substr(0,str.size()-3);
	return str;
}

std::string Predicate::getExtraConstants() const{
	std::string str;
	for (auto it=extraConstants.begin(); it!=extraConstants.end(); ++it){
			str += *it;
			str += " , ";
	}
	str = str.substr(0,str.size()-3);
	return str;
}


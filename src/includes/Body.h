#pragma once
#include <set>
#include "Variable.h"
#include "Predicate.h"
#include "LanguageConstants.h"

#define langCheck LanguageConstants::TYPE==OutputType::OUTPUT_TUFFY

class Body
{
public:
	Body();
	~Body();
	Body(std::vector<Predicate> _predList):predList(_predList){}

	void addPredicate(Predicate p){
		predList.push_back(p);
	}

	std::string toString() {
		if (langCheck){
			//5 is size of  " AND "
			if(tuffyEqualityStr.length() > 0){
				tuffyEqualityStr = tuffyEqualityStr.substr(5, tuffyEqualityStr.length());
				bodyStr += " , [" + tuffyEqualityStr + "]";  
			}
			return bodyStr;
		}
		return bodyStr;
	}

	std::string toNNFString() {
		if (langCheck){
			//4 is size of " OR "
			if(tuffyNNFEqualityStr.length() > 0){
				tuffyNNFEqualityStr = tuffyNNFEqualityStr.substr(4, tuffyNNFEqualityStr.length());
				NNFbodyStr += " v [" + tuffyNNFEqualityStr + "]";
			}
			return NNFbodyStr ;
		}
		return NNFbodyStr;
	}


	void appendStr(Predicate, bool, bool, bool,const std::set<std::string>& domainList);

	bool bodyHasNegation(){
		return bodyNegation;
	}

	std::string getExtra(); 

	inline std::vector<Predicate> getPredicate(){ return predList; } 

	std::string getExtra(const std::set<Variable>& variable);

	std::string getExtraConstants();

private:
	std::set<std::pair<std::string,std::string>> orphanVarsMap;
	std::set<std::pair<std::string,std::string>> orphanVarsHeadMap;
	std::vector<Predicate> predList;
	std::string extraConstants;
	
	std::string bodyStr;	
	std::string NNFbodyStr;
	std::string tuffyEqualityStr;
	std::string tuffyNNFEqualityStr;

	bool bodyNegation = false;
};
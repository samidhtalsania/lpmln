#include "Body.h"


#define langCheck LanguageConstants::TYPE==OutputType::OUTPUT_TUFFY

Body::Body(){}
Body::~Body(){}


void Body::appendStr(Predicate pred, bool trim, bool disjunction, bool conjunction, const std::set<std::string>& domainList){

	int stat = pred.checkEquality();

	if(disjunction){
		if(stat != 0 && langCheck){
			tuffyEqualityStr += " OR ";
			tuffyNNFEqualityStr += " AND ";
		}
		else{
			bodyStr += LanguageConstants::DIS;
			NNFbodyStr += LanguageConstants::CON;
		}
	}
	else if(conjunction){
		if(stat != 0 && langCheck){
			tuffyEqualityStr += " AND ";
			tuffyNNFEqualityStr += " OR ";
		}
		else{
			bodyStr += LanguageConstants::CON;
			NNFbodyStr += LanguageConstants::DIS;
		}
	}

	if (pred.isNegated()){
		bodyNegation = true;
	}

	if (stat !=0 && langCheck){
		tuffyEqualityStr += pred.toString(domainList);
		tuffyNNFEqualityStr += pred.toNNFString();
	}
	else{
		bodyStr += pred.toString(domainList);
		NNFbodyStr += pred.toNNFString();
	}
	
	if(trim){
		bodyStr = bodyStr.substr(0,bodyStr.size()-3); 
		NNFbodyStr = NNFbodyStr.substr(0,bodyStr.size()-3); 
	}
}

std::string Body::getExtra(const std::set<Variable>& variable){
	std::string str;
	for (std::vector<Predicate>::iterator i = predList.begin(); i != predList.end(); ++i){
		std::string s = i->getExtra(variable);

		std::string temp = i->getExtraConstants();
		if(temp.length() > 0){
			extraConstants += temp + " , ";
		}
		if(s.length() != 0){
			str += s;
			str += " , ";
		}
	}
	if(str.length() > 3)
		str = str.substr(0,str.size()-3);
	return str;
}

std::string Body::getExtraConstants(){
	if(extraConstants.length() > 0){
		extraConstants = extraConstants.substr(0,extraConstants.size()-3);
	}
	return extraConstants;
}
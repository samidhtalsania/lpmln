#include "Body.h"
#include "LanguageConstants.h"

Body::Body(){}
Body::~Body(){}


void Body::appendStr(Predicate pred, bool trim, bool disjunction, bool conjunction){

	if(disjunction){
		bodyStr += LanguageConstants::DIS;
		NNFbodyStr += LanguageConstants::CON;
	}
	else if(conjunction){
		bodyStr += LanguageConstants::CON;
		NNFbodyStr += LanguageConstants::DIS;
	}

	if (pred.isNegated()){
		bodyNegation = true;
	}

	bodyStr += pred.toString();
	NNFbodyStr += pred.toNNFString();
	
	if(trim){
		bodyStr = bodyStr.substr(0,bodyStr.size()-3); 
		NNFbodyStr = NNFbodyStr.substr(0,bodyStr.size()-3); 
	}
}

std::string Body::getExtra(const std::set<Variable>& variable){
	std::string str;
	for (std::vector<Predicate>::iterator i = predList.begin(); i != predList.end(); ++i){
		std::string s = i->getExtra(variable);
		if(s.length() != 0){
			str += s;
			str += " , ";
		}
	}
	if(str.length() > 3)
		str = str.substr(0,str.size()-3);
	return str;
}
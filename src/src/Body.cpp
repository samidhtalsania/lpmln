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


	bodyStr += pred.toString();
	NNFbodyStr += pred.toNNFString();
	
	if(trim){
		bodyStr = bodyStr.substr(0,bodyStr.size()-3); 
		NNFbodyStr = NNFbodyStr.substr(0,bodyStr.size()-3); 
	}
}
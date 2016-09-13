#include "Head.h"
#include "LanguageConstants.h"

// Head::Head(){}
Head::~Head(){}


void Head::appendStr(std::string str, bool trim, bool disjunction, bool conjunction){

	if(disjunction){
		headStr += LanguageConstants::DIS;
	}
	else if(conjunction){
		headStr += LanguageConstants::CON;
	}

	headStr += str;
	
	if(trim){
		headStr = headStr.substr(0,headStr.size()-3); 
	}
}
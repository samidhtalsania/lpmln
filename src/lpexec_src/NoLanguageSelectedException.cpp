#include "exceptions/NoLanguageSelectedException.h"

NoLanguageSelectedException::~NoLanguageSelectedException(){}

NoLanguageSelectedException::NoLanguageSelectedException(std::string _str){
	str = _str;
}

NoLanguageSelectedException::NoLanguageSelectedException(){}
#include "Token.h"

Token::Token(std::string _c){
	token = new std::string;
	*token = _c; 
}

void Token::modifyToken(std::string _c){
	*token = _c;
}


Token::~Token(){
	delete token;
}


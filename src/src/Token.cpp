#include "Token.h"

Token::Token(std::string _c){
	token = new std::string;
	*token = _c; 
}

Token::Token(){
	
}

Token::~Token(){
	delete token;
}


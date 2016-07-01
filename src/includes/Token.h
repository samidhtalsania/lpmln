#pragma once
#include <string>

class Token
{
public:
	Token(std::string);
	void modifyToken(std::string);
	// Token();
	~Token();

	std::string* token;
	std::string toString(){ return *token;}		
};
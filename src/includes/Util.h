#pragma once

#include <algorithm>
#include <string>

class Util
{
public:
	Util();
	~Util();

	static void toLower(std::string& str){
		transform(str.begin(), str.end(), str.begin(), tolower);
	}
	
	static void toUpper(std::string& str){
		transform(str.begin(), str.end(), str.begin(), toupper);
	}
	
};
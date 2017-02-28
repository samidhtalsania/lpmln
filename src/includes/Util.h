#pragma once

#include <algorithm>
#include <string>

#include <stdio.h>
#include <stdlib.h>

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
	
	static void merge(std::string fname1, std::string fname2, std::string fname3){
		std::string str = "cat " + fname1 + " " + fname2 + " > " + fname3; 
		system(str.c_str());
	}
};
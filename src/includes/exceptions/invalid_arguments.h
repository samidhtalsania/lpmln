#include <string>
#include "syntax_exception.h"

#pragma once

class invalid_arguments : public syntax_exception{
	public:
		invalid_arguments(int,int,std::string);
		
		~invalid_arguments();

		const char* what() const throw(){
			return str.c_str();
		}

	private:
		std::string str; 
};


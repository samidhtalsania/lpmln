#include <string>
#include <exception>
#pragma once

class undefined_predicate : public std::exception{
	public:
		undefined_predicate(std::string);
		
		~undefined_predicate();

		const char* what() const throw(){
			return str.c_str();
		}

	private:
		std::string str; 
};


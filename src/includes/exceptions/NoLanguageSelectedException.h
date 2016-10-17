#include <string>
#include <exception>

#pragma once

class NoLanguageSelectedException : public std::exception{
	public:
		NoLanguageSelectedException(std::string);
		NoLanguageSelectedException();
		~NoLanguageSelectedException();

		const char* what() const throw(){
			return str.c_str();
		}

	private:
		std::string str; 
};


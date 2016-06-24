#include <string>
#include <exception>


class syntax_exception : public std::exception{
	public:
		syntax_exception(std::string);
		
		~syntax_exception();

		const char* what() const throw(){
			return str.c_str();
		}

	private:
		std::string str; 
};


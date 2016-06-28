#include <string>
#include <exception>


class undefined_key : public std::exception{
	public:
		undefined_key();
		
		~undefined_key();

		const char* what() const throw(){
			return str.c_str();
		}

	private:
		std::string str = "Internal error."
				"This is usually thrown when there is "
				 "a disjunctive statement with an equality "
				 "of the form a=b. This is only allowed in body "
				 "and not in the head of any statement. "
				 "Head does not have conjunctions."; 
};


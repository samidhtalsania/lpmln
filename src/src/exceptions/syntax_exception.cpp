#include "exceptions/syntax_exception.h"

syntax_exception::~syntax_exception(){}

syntax_exception::syntax_exception(std::string _str){
	str = _str;
}
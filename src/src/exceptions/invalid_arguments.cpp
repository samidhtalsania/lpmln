#include "exceptions/invalid_arguments.h"

invalid_arguments::~invalid_arguments(){}

invalid_arguments::invalid_arguments(int expected, int given, std::string _str){
	str = "Expected "+ std::to_string(expected) + " arguments, found "+ std::to_string(given) + " for literal "+_str+"\n";
}
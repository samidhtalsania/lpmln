#include "exceptions/undefined_predicate.h"

undefined_predicate::~undefined_predicate(){}

undefined_predicate::undefined_predicate(std::string _str){
	str = _str+ " : Predicate Undefined.\n";
}
#include "ParserFactory.h"

Parser* ParserFactory::getParser(ParserType parser){
	if(parser == ParserType::FOL){
		FOLParser* folParser = new FOLParser;
		p = folParser;
	}
	else if(parser == ParserType::ASP){
		ASPParser* aspParser = new ASPParser;
		p = aspParser;
	}
	else if(parser == ParserType::MVSM){
		MVSMParser* mvsmParser = new MVSMParser;
		p = mvsmParser;
	}
	/*Default to FOL parser*/
	else{
		FOLParser* folParser = new FOLParser;
		p = folParser;
	}
	return p; 
}

void ParserFactory::free(){
	delete p;
}

Parser* ParserFactory::p;

#include "ParserFactory.h"

Parser* ParserFactory::getParser(ParserType parser){
	if(parser == ParserType::FOL){
		FOLParser* folParser = new FOLParser;
		p = folParser;
	}
	else{
		ASPParser* aspParser = new ASPParser;
		p = aspParser;
	}
	return p; 
}

Parser* ParserFactory::p;

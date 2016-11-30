#include "LexerFactory.h"

LexerFactory::LexerFactory(){}

Lexer* LexerFactory::getLexer(ParserType parser){
	if(parser == ParserType::FOL){
		FOLLexer* follexer = new FOLLexer;
		l = follexer;
	}
	else if(parser == ParserType::ASP){
		ASPLexer* asplexer = new ASPLexer;
		l = asplexer;
	}
	else if(parser == ParserType::MVSM){
		MVSMLexer* mvsmlexer = new MVSMLexer;
		l = mvsmlexer;
	}
	else if(parser == ParserType::F2LP){
		F2LPLexer* f2lplexer = new F2LPLexer;
		l = f2lplexer;
	}
	/*Default to FOL parser*/
	else{
		FOLLexer* follexer = new FOLLexer;
		l = follexer;
	}
	return l; 
}

void LexerFactory::free(){
	delete l;
}

Lexer* LexerFactory::l;
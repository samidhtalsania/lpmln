#include "ParserWrapper.h"
#include "lexer.h"
#include "Domain.h"
#include "parser.h"
#include "Token.h"
#include "exceptions/undefined_predicate.h"
#include "exceptions/syntax_exception.h"


#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h> 
#include <stdio.h>
#include <memory>
#include <fstream>
#include <algorithm>

#include <boost/iostreams/filtering_stream.hpp>


using namespace std;

namespace io = boost::iostreams; 

#define ParseTOKENTYPE Token*
#define ParseARG_PDECL , Tree* tree

void Parse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  ParseTOKENTYPE yyminor       /* The value for the token */
  ParseARG_PDECL               /* Optional %extra_argument parameter */
);


void *ParseAlloc(void *(*mallocProc)(size_t));

void ParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
);

void ParseTrace(FILE *TraceFILE, char *zTracePrompt);

ParserWrapper::ParserWrapper(Config c){
	translation = c.getTranslation();
	inputFile = c.getFile();
	debug = c.getDebug();

	tree = new Tree;

	parser = ParseAlloc(malloc);
}

int ParserWrapper::parse(){
	
	std::ifstream file(inputFile, std::ios_base::in | std::ios_base::binary);
	int hTokenId;
	// void *parser = ParseAlloc(malloc);

	if(debug){
		pFile = fopen ("op.txt" , "w");
		const char* debug_prefix = "_";
		ParseTrace(pFile,const_cast<char*>(debug_prefix));
	}


	lexeme_t lexeme;


	// Tree* tree = new Tree;
	
  std::string str;
  int lineCount = 0;
  int columnCount = 0;

	if(file){
    
    try{
      io::filtering_istream in;

      in.push(file);

      for(str; std::getline(in, str); ){
        lineCount++;
        columnCount = 0;
        if(!str.empty()){
          //Left trim the input tring
          auto it2 =  std::find_if( str.begin() , str.end() , [](char ch){ return !std::isspace<char>(ch , std::locale::classic() ) ; } );
          str.erase( str.begin() , it2);
          

          //If its a comment print it and go to next statement
          if(str.substr(0,2).compare("//") == 0){
            cout<<str<<"\n";
            continue;
          }

          //If its a double negation at start continue doing our stuff since its a constraint and not needed for completion
          // The user possibly wants to pass this statement directly to alchemy.
          else if(str.substr(0,2).compare("!!") == 0){
            cout<<str.substr(2,str.size()-1)<<"\n";
            continue;
          }

          //If it is a uniqueness statement print it oout and go to next
		      else if(str.substr(0,2).compare("!(") == 0){
            cout<<str<<"\n";
            continue;
          }


          str += "\n";
          
          char* buffer;
          buffer = const_cast<char*>(str.c_str());
          int len = str.size();
          lexeme.start = buffer;
          lexeme.current = buffer;
          lexeme.begin = buffer;
          // lexeme.col = 0;
          while( (hTokenId = lexer::tokenize(buffer, len, &lexeme)) != 0 ){
            if(hTokenId != PARSE_TOKEN_WS){
              unsigned long int pos = static_cast<unsigned long int>(lexeme.current - lexeme.start);
              string substr(lexeme.start, pos);
              Token* tok = new Token(substr);
              v.push_back(tok);
              Parse(parser, hTokenId, tok, tree);
            }
          }

          if(tree->statHasDblNeg){
            tree->statHasDblNeg = false;
            // Remove double neg from program
            remove_copy(str.begin(), str.end(),
                 ostream_iterator<char>(std::cout), '!');
          }
          else{
            cout<<str;
          }

        }
        else
          std::cout << "\n";        
      }

      Token* tok = new Token("0");
      
      
      Parse(parser, 0, tok, tree);
 
      // ParseFree(parser, free);
      delete tok;
    
      //Do completion
      ParserWrapper::parseComplete();
      
    }
    catch(const syntax_exception& e){
      cout<<str;
      std::cout << e.what();
      std::cout<<"Line:"<<lineCount<<" Column:"<<lexeme.current - lexeme.begin<<"\n";
      throw e;
    }
    catch(const std::exception& e) {
      std::cout << e.what() << '\n';
      throw e;
    }
  }
  else{
    std::cerr << "Some error ocurred while processing this file!\n";
    return -1;
  }

  return 0;
}

void ParserWrapper::parseComplete(){
	//Do completion
	tree->completeFacts();
	tree->completeRules();
}

ParserWrapper::~ParserWrapper(){
	delete tree;
	ParseFree(parser, free);
  for(auto& ve : v)
    delete ve;
	if(pFile != NULL && debug)
		fclose(pFile);
}
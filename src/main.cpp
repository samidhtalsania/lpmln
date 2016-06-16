#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h> 
#include <stdio.h>
#include <memory>
#include <fstream>
#include <algorithm>


#include <boost/iostreams/filtering_stream.hpp>

#include "lexer.h"
#include "Domain.h"
#include "parser.h"
#include "Token.h"
#include "Tree.h"
#include "exceptions/undefined_predicate.h"

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

int main(int argc, char **argv)
{

  const char *input_file_name;
  input_file_name = argv[1];
  std::ifstream file(input_file_name, std::ios_base::in | std::ios_base::binary);

  int hTokenId;
  void *parser = ParseAlloc(malloc);

  FILE* pFile;
  pFile = fopen ("op.txt" , "w");
  const char* debug_prefix = "_";
  ParseTrace(pFile,const_cast<char*>(debug_prefix));
  lexeme_t lexeme;
  
  
  Tree* tree = new Tree;
  std::vector<Token*> v;
  
  if(file){
    
    try{
      io::filtering_istream in;

      in.push(file);

      for(std::string str; std::getline(in, str); ){
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
          while( (hTokenId = lexer::tokenize(buffer, len, &lexeme)) != 0 ){
            if(hTokenId != PARSE_TOKEN_WS){
              unsigned long int pos = static_cast<unsigned long int>(lexeme.current - lexeme.start);
              string substr(lexeme.start, pos);
              Token* tok = new Token(substr);
              // std::cout<<hTokenId<<":"<<*(tok->token)<<std::endl;
              v.push_back(tok);
              try{
                Parse(parser, hTokenId, tok, tree);
              }
              catch(const exception& e){
                cout << e.what();
              }
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
      
      try{
        Parse(parser, 0, tok, tree);
      }
      catch(const exception& e){
        // const char* c = e.what();
        cout << e.what();
      }
      ParseFree(parser, free);
      delete tok;
    
      //Do completion
      tree->completeFacts();
      tree->completeRules();


      fclose (pFile);
    
      for(auto& ve : v)
        delete ve;
      delete tree;
    }
    catch(std::exception& e) {
      std::cout << e.what() << '\n';
      return -1;
    }
  }
  else{
    std::cerr << "File could not be opened!\n";
  }
	return 0;
}

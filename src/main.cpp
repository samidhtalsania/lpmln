#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h> 
#include <stdio.h>
#include <memory>
#include <fstream>


#include <boost/iostreams/filtering_stream.hpp>

#include "lexer.h"
#include "Domain.h"
#include "parser.h"
#include "Token.h"
#include "Tree.h"

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
  // ParseTrace(pFile,"D_");
  lexeme_t lexeme;
  
  
  Tree* tree = new Tree;
  std::vector<Token*> v;
  
  if(file){
    
    try{
      io::filtering_istream in;

      in.push(file);

      for(std::string str; std::getline(in, str); ){
        if(!str.empty()){
          // str.erase(std::remove(str.begin(),str.end(),' '),str.end());
          
          //If its a comment print it and go about doing our stuff
          //If its a double negation at start continue doing our stuff since its a constraint and not needed for completion
          if(str.substr(0,2).compare("//") == 0 || str.substr(0,2).compare("!!") == 0){
            cout<<str<<"\n";
            continue;
          }
          str += "\n";
          cout<<str;
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
              v.push_back(tok);
              // cout<<*(tok->token);
              Parse(parser, hTokenId, tok, tree);
            }
          }
        }
        else
          std::cout << "\n";        
      }

      Token* tok = new Token("0");
      Parse(parser, 0, tok, tree);
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
      //outfile.close();
      return -1;
    }
  }
  else{
    std::cerr << "File could not be opened!\n";
  }

 //  string str1("step = {0,1,2}\n");
 //  string str2("next(step,step)\n");
 // //  char buffer [] = "step = {0,1,2}\nnext(step,step)\n t(step,step)";//next(0,1).\nnext(1,2).\n\nboolean={True,False}";
	// // int len = strlen(buffer);
	// int hTokenId;
	// void *parser = ParseAlloc(malloc);

	// FILE* pFile;
	// pFile = fopen ("op.txt" , "w");
	// ParseTrace(pFile,"D_");
	// lexeme_t lexeme;
  
	
	// Tree* tree = new Tree;
	// std::vector<Token*> v;


 //  char* buffer = const_cast<char*>(str1.c_str());
 //  int len = strlen(buffer);

 //  lexeme.start = buffer;
 //  lexeme.current = buffer;
	// while( (hTokenId = lexer::tokenize(buffer, len, &lexeme)) != 0 ){
 //    	if(hTokenId != PARSE_TOKEN_WS)
 //    	{
 //    		string str(lexeme.start, lexeme.current - lexeme.start);
 //    		Token* tok = new Token(str);
 //    		v.push_back(tok);
 //    		cout<<*(tok->token);
 //        Parse(parser, hTokenId, tok, tree);
 //    	}
 //    }

 //    buffer = const_cast<char*>(str2.c_str());
 //     len = strlen(buffer);

 //  lexeme.start = buffer;
 //  lexeme.current = buffer;
 //    while( (hTokenId = lexer::tokenize(buffer, len, &lexeme)) != 0 ){
 //      if(hTokenId != PARSE_TOKEN_WS)
 //      {
 //        string str(lexeme.start, lexeme.current - lexeme.start);
 //        Token* tok = new Token(str);
 //        v.push_back(tok);
 //        cout<<*(tok->token);
 //        Parse(parser, hTokenId, tok, tree);
 //      }
 //    }
  
 //    Token* tok = new Token("0");
 //    Parse(parser, 0, tok, tree);
	// ParseFree(parser, free);
	// delete tok;
    
	// fclose (pFile);
    
 //    delete tree;
    
	// for(auto& ve : v){
	// 	delete ve;
	// }
    	
	

	return 0;
}

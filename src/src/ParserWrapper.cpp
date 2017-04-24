#include "ParserWrapper.h"
// #include "lexer.h"
#include "LexerFactory.h"
#include "Domain.h"
#include "ParserFactory.h"
#include "exceptions/undefined_predicate.h"
#include "exceptions/syntax_exception.h"
#include "Util.h"


#include <iostream>
#include <string.h>
#include <stdlib.h> 
#include <stdio.h>

#include <fstream>
#include <algorithm>

#include <boost/iostreams/filtering_stream.hpp>


using namespace std;

namespace io = boost::iostreams; 




ParserWrapper::ParserWrapper(Config c){
	translation = c.getTranslation();
	inputFile = c.getFile();
	debug = c.getDebug();
  parserType = c.getParser();
  level = c.getLevel();
  outputType = c.getOutputType();

  

	tree = new Tree(level, outputType);

  parser = ParserFactory::getParser(c.getParser()); 
  lexer = LexerFactory::getLexer(c.getParser());
  
  parser->ParseAlloc();
  ofs.open(tuffyOutFile);
  if(c.getParser() == ParserType::FOL){
    isFOLlexer = true;
  }
}

int ParserWrapper::parse(){
	
	std::ifstream file(inputFile, std::ios_base::in | std::ios_base::binary);

  //Tuffy related settings
 
  
  if(outputType == OutputType::OUTPUT_TUFFY){
    coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(ofs.rdbuf()); //redirect std::cout to out.txt!
  }
  
	int hTokenId;

	if(debug){
		pFile = fopen ("op.txt" , "w");
		const char* debug_prefix = "_";
		parser->ParseTrace(pFile,const_cast<char*>(debug_prefix));
	}


	lexeme_t lexeme;
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

          //Right trim the input string  
          auto it1 =  std::find_if( str.rbegin() , str.rend() , [](char ch){ return !std::isspace<char>(ch , std::locale::classic() ) ; } );
          str.erase( it1.base() , str.end() );

          //Left trim the input tring
          auto it2 =  std::find_if( str.begin() , str.end() , [](char ch){ return !std::isspace<char>(ch , std::locale::classic() ) ; } );
          str.erase( str.begin() , it2);
            

          //If its a comment print it and go to next statement
          if(str.substr(0,2).compare("//") == 0){
            //if output type is ASP then comment is different
            if(outputType == OutputType::OUTPUT_ASP)
              cout<<"%"<<str<<"\n";
            else
              cout<<str<<"\n";
            continue;
          }

          //If its a double negation at start continue doing our stuff since its a constraint and not needed for completion
          // The user possibly wants to pass this statement directly to alchemy.
          else if(str.substr(0,3).compare("!!(") == 0){
            int s = str.size();
            cout<<str.substr(3 ,s-3-1)<<"\n";
            continue;
          }
          //temporary hack to allow passing of hard facts which need not be completed.
          //!!p(0,1).
          //TODO add this to grammar. Let the grammar handle this.
          else if(str.substr(0,2).compare("!!") == 0 && isFOLlexer){
            int s = str.size();
            cout<<str.substr(2 ,s-2)<<"\n";
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
          while( (hTokenId = lexer->Tokenize(buffer, len, &lexeme)) != 0 ){
            /* -1 is whitespace. Skip over whitespaces*/
            if(hTokenId != -1){
              unsigned long int pos = static_cast<unsigned long int>(lexeme.current - lexeme.start);
              string substr(lexeme.start, pos);
              Token* tok = new Token(substr);
              v.push_back(tok);
              parser->Parse(hTokenId, tok, tree);
            }
          }
          print(str);  
        }
        
        else
          std::cout << "\n";        
      }

      Token* tok = new Token("0");
      parser->Parse(0, tok, tree);
      delete tok;
    
      //Do completion
      //only in case of MLN
      if(outputType != OutputType::OUTPUT_ASP)
        ParserWrapper::parseComplete();
      
    }
    catch(const syntax_exception& e){
      cout<<str;/*Prints the erroneous line*/
      std::cout.rdbuf(coutbuf);
      std::cout << e.what();
      std::cerr<<"Line:"<<lineCount<<" Column:"<<lexeme.current - lexeme.begin<<"\n";
      throw e;
    }
    catch(const std::exception& e) {
      std::cerr << e.what() << '\n';
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
  tree->completeDeclarations();
  if(outputType == OutputType::OUTPUT_TUFFY){
    ofstream myfile;
    myfile.open ("tuffy-out-headers.mln");
    myfile << tree->getTuffyAuxHeaders();
    myfile.close();
    ofs.close();
    Util::merge(std::string("tuffy-out-headers.mln"), tuffyOutFile, std::string("input.mln"));
    std::cout.rdbuf(coutbuf);

  }
}

ParserWrapper::~ParserWrapper(){
	delete tree;
	parser->ParseFree();
  LexerFactory::free();
  ParserFactory::free();
  for(auto& ve : v)
    delete ve;
	if(pFile != NULL && debug)
		fclose(pFile);
}

void ParserWrapper::print(std::string str){
  if(parserType == ParserType::FOL){
    if(tree->statHasDblNeg && str.find("!!") != string::npos){
        tree->statHasDblNeg = false;
        str.erase(str.find("!!"),2);
    }
    cout<<str;
  }
}
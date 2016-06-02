%token_type {char*}  
   
%left PLUS MINUS.   
%left DIVIDE TIMES.  
   
%include {   
#include <iostream>  
#include "lemon.h"
#include <cassert>
using namespace std;
}  
   
%syntax_error {  
  std::cout << "Syntax error!" << std::endl;  
}   
   
program ::= expr(A).   { cout << "Result=" << A << endl; }  
   
expr(A) ::= expr(B) MINUS  expr(C).   { cout<<A<<B<<C; }    

expr(A) ::= INTEGER(B). { A = B; } 
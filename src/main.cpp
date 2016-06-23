#include <iostream>
#include "Config.h"
#include "ParserWrapper.h"


using namespace std;

int main(int argc, char **argv)
{

  Config config(argc, argv);

  if(config.configFailed()){
    cerr<< "Program terminated due to errors\n";
    return 1;
  }

  if(config.configReturn()){
    return 0;
  }


  ParserWrapper pw(config);
  try {
    pw.parse();
  }
  
  catch(const exception& e){
    return -1;
  }
    
  return 0;
}

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <stdio.h>
#include <cstring> 
#include <uuid/uuid.h>
#include <map>
#include <string>
#include <set>
#include <fstream>

#include <sys/stat.h>
#include <unistd.h>

#include "FileConfig.h"
#include "exceptions/NoLanguageSelectedException.h"

#define SPACE " "

// Requires sudo apt-get install uuid-dev

#define DEBUG

using namespace std;

void runProcess(string);
void printHelp();
void printVersion();
bool file_exists(const string&);

void runProcess(string command){
   FILE *fpipe;
   char line[512];

   if ( !(fpipe = (FILE*)popen(command.c_str(),"r")) )
   {  // If fpipe is NULL
      perror("Problems with pipe");
      exit(1);
   }

   while ( fgets( line, sizeof(line), fpipe) != NULL)
   {
     printf("%s", line);
   }
   pclose(fpipe);

}

void printHelp(){

   std::cout << "lpmln v1.0\n"
               "\n"
               "Usage:\n"
               "lpmln [LPMLN Options] [FILE] -[mln|clingo] [Alchemy/clingo Options]\n"
               "\n"
               "LPMLN Options:\n"
               "  -h Show this message\n"
               "  -mln Invoke alchemy for solving. All the options after this would be passed to alchemy. \n"
               "  -clingo Invoke clingo for solving. All the options after this would be passed to clingo.\n"
               "\n"
               "Options:\n"
               "\n"
               "LPMLN-Compiler Options:\n"
               "\n"
               "Usage: lpmlncompiler [options] [file]\n"
               "Options:\n"
               "   \n"
               "   -A Compile for Clingo 4\n"
               "   -M Compile for Alchemy\n"
               "   -m Input in First Order Logic Syntax\n"
               "   -p Input in CCALC (MVSM) Syntax\n"
               "   -a Input in ASP Syntax\n"
               "   -o0 No Optimization (use only for debug purposes)\n"
               "   -o1 Optimization level 1\n"
               "   -o2 Optimization Level 2\n"
               "   -h Show this Message\n"
               "   -v Display Version\n"
               "\n"
               "Alchemy Options:\n"
               "Call infer -h from command prompt.\n"
               "\n"
               "Clingo Options:\n"
               "Call clingo -h from command prompt.\n"
               "\n";
}

void printVersion(){
   std::cout<< "lpmln v 1.0\n";
}

bool file_exists (const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}


int main(int argc, char **argv)
{
   Region region = NONE;

   bool pickUpFromCommandLine = false;


   string lpmln = "lpmlncompiler ";
   string alchemy = "infer ";
   string clingo = "clingo ";
   string tuffy = " ";

   string help = "-h";
   string version = "-v";

   string alch = "-a";
   string cli = "-c";
   string tuf = "-t";


   map<string, string> loptions ;
   map<string, string> aoptions ;
   map<string, string> coptions ;

  

   bool execute_alch = false;
   bool execute_cli = false;
   bool execute_tuf = false;

   set<string> lpset;
   set<string> alchset;
   set<string> clingoset;
   set<string> tuffyset;

 
   FileConfig cf;

   if(cf.allGood){
      loptions = cf.getloptions();
      aoptions = cf.getaoptions();
      coptions = cf.getcoptions();
        
      // Execute cli is true by default
      execute_alch = cf.getExecuteAlch();
      execute_cli = cf.getExecuteCli();
      execute_tuf = false;
   }
   else{

      // No solver is specified in the config file. Need to pick it up from command line.

      //Default for lpmln: Solver is MLN, Input is MVSM
      loptions.insert(pair<string,string>("input","mvsm"));
      
      //loptions.insert(pair<string,string>("solver","alchemy"));
      //max number of solutions for clingo
      coptions.insert(pair<string,string>("solutions","0"));

      pickUpFromCommandLine = true;

      execute_cli = false;
      execute_alch = false;
      execute_tuf = false;
   }

   uuid_t uuid;
   uuid_generate_random ( uuid );
   char s[37];
   uuid_unparse ( uuid, s );

   string fileName = string(s);
   
   bool isEvidenceUsed = false;   

   alchemy += " -i " + string("/tmp/") + fileName + " -r " + string("/tmp/") + fileName + string(".res") ;
   clingo += string("/tmp/") + fileName + " ";

   if(argc == 1){
      printHelp();
      exit(0);
   }

   string inputFileName;
   bool inputFileFound = false;

   int count = 0;
   for(int i=0 ; i < argc ; i++){

      string arg = string(argv[i]);

      if(arg.compare(help) == 0){
         printHelp();
         exit(0);
      }

      if(arg.compare(version) == 0){
         printVersion();
         exit(0);
      }



      if(i == 0){
         region = LPMLN;
         continue;
      }

      if(arg.compare(alch) == 0){
         region = ALCH;
         execute_alch = true;
         execute_cli = false;
         // loptions
         loptions["solver"] = "alchemy";
         pickUpFromCommandLine = false;
         continue;
      }

      if(arg.compare(cli) == 0){
         region = CLINGO;
         execute_cli = true;
         execute_alch = false;
         // loptions.insert(pair<string,string>("solver","clingo"));
         loptions["solver"] = "clingo";
         pickUpFromCommandLine = false;
         continue;
      }

      if(arg.compare(tuf) == 0){
         region = TUFFY;
         execute_tuf = true;
         loptions["solver"] = "tuffy";
         continue;
      }

      switch(region){
         case LPMLN:
            {
               
               if(arg.compare("-A") == 0 || arg.compare("-M") == 0){
                  lpset.insert("solver");
                  lpmln += SPACE + string(argv[i]) + SPACE;
                  if(arg.compare("-A") == 0){
                     execute_cli = true;
                     execute_alch = false;
                  }
                  else{
                     execute_alch = true;
                     execute_cli = false;
                  }
               }

               else if(arg.compare("-a") == 0 || arg.compare("-m") == 0 || arg.compare("-p") == 0){
                  lpset.insert("input");
                  lpmln += SPACE + string(argv[i]) + SPACE;
               }
               
               else if(arg.compare("-o0") == 0 || arg.compare("-o1") == 0 || arg.compare("-o2") == 0){
                  lpset.insert("optimization");
                  lpmln += SPACE + string(argv[i]) + SPACE;
               }
               else{
                  // Its the input file
                  inputFileName = string(argv[i]);
                  //confirm that it is a legit input file.
                  if(!file_exists(inputFileName)){
                     cerr << "Invalid argument at position:" << i;
                     exit(0);
                  }
               }
            }
            break;

         case ALCH:
            {
               if(arg.compare("-e") == 0){
                  isEvidenceUsed = true;
                  // alchemyoptions.insert(argv[i]);
                  alchset.insert("evidence");
               }
               if(arg.compare("-q") == 0){
                  // isEvidenceUsed = true;
                  alchset.insert("query");
               }
               //probably an input file. Check if it an input file.
               if(file_exists(arg) && !inputFileFound){
                  inputFileName = arg;
                  inputFileFound = true;
                  
               }
               else{
                  alchemy  += SPACE + string(argv[i]) + SPACE;
               }
            }
            break;

         case TUFFY:
            {
               // if(arg.compare("-e") == 0){
               //    isEvidenceUsed = true;
               //    // alchemyoptions.insert(argv[i]);
               //    tuffyset.insert("evidence");
               // }
               // if(arg.compare("-queryFile") == 0){
               //    // isEvidenceUsed = true;
               //    tuffyset.insert("query");
               // }

               //probably an input file. Check if it an input file.
               if(file_exists(arg) && !inputFileFound){
                  inputFileName = arg;
                  inputFileFound = true;
                  
               }
               else{
                  tuffy  += SPACE + string(argv[i]) + SPACE;
               }
            }
            
            break;

         case CLINGO:
            {
               int temp = 0;
               try{
                  temp = std::stoi(argv[i]);
                  clingoset.insert("solutions");
               }
               catch(...){}
               clingo += SPACE + string(argv[i]) + SPACE;
            }
            break;

         default:
            break;
      }
   }


   for (auto it=loptions.begin(); it!=loptions.end(); ++it){
      string str ;
      auto itr = lpset.find(it->first);
      if(itr == lpset.end()){
         if (it->first.compare("solver") == 0){
            if(it->second.compare("clingo") == 0){
               str = "-A";
            }
            if(it->second.compare("alchemy") == 0){
               str = "-M";
            }
            if(it->second.compare("tuffy") == 0){
               str = "-T";
            }
         }
         if(it->first.compare("input") == 0){
            if(it->second.compare("mvsm") == 0){
               str = "-p";
            }
            if(it->second.compare("asp") == 0){
               str = "-a";
            }
            if(it->second.compare("fol") == 0){
               str = "-m";
            }
         }
         if(it->first.compare("optimization") == 0){
            str = it->second;
         }

         lpmln += SPACE + str + SPACE;
      }
   }

   lpmln += inputFileName;

   if(pickUpFromCommandLine){
      // std::cout<<"No input language and solver specified in command line and config file.\nUsing ASP Solver.\n";
      std::cout << "Using MLN Solver";
   }


   for (auto it=aoptions.begin(); it!=aoptions.end(); ++it){
      string str = it->first;
      string first;
      auto itr = alchset.find(str);
      if(itr == alchset.end()){
         if(str.compare("evidence") == 0){
            first = " -e ";
            isEvidenceUsed = true;
         }
         else if(str.compare("query") == 0)
            first = " -q ";

         alchemy += first + SPACE + it->second + SPACE;
      }
   }

   for (auto it=coptions.begin(); it!=coptions.end(); ++it){
      string str = it->first;
      auto itr = clingoset.find(str);
      if(itr == clingoset.end()){
         clingo += SPACE + it->second + SPACE;
      }
   }

   lpmln += SPACE + string(">") + SPACE + string("/tmp/") + fileName;
   std::cout<<"Lpmln Executed with Command:\n"+lpmln+"\n";
   runProcess(lpmln);

   if(!isEvidenceUsed && execute_alch == true){
      //Make empty db
      alchemy += string(" -e ") + string("/tmp/")+ fileName + string(".db ");
      string str = "touch /tmp/" + fileName + ".db";
      runProcess(str);
   }

   
   if(execute_alch == true){
      // std::cout<<alchemy;
      std::cout<<"Alchemy Executed with Command:\n"+alchemy+"\n";
      runProcess(alchemy);
      string str = "cat /tmp/" + fileName + ".res";
      runProcess(str);
   }

   if(execute_cli == true){
      clingo += " --warn=no-atom-undefined";
      std::cout<<"Clingo Executed with Command:\n"+clingo+"\n";
      runProcess(clingo);
   }


   if(execute_tuf == true){
      tuffy = "java -jar /usr/local/share/lpmln/tuffy.jar -conf /usr/local/share/lpmln/tuffy.conf -i input.mln -r output.txt " + tuffy;
      std::cout<<"Tuffy Executed with Command:\n"+ tuffy +"\n";
      runProcess(tuffy);
      string str = "cat output.txt";
      runProcess(str);
   }

   
   std::string revInputFileName(inputFileName.rbegin(), inputFileName.rend());
   std::size_t found = revInputFileName.find("/");
   string destination = inputFileName.substr(0,found);

   std::ifstream  src("/tmp/"+fileName, std::ios::binary);
   std::ofstream  dst(destination+"/.lpmln-output",   std::ios::binary);
   
   dst << src.rdbuf();

   src.close();
   dst.close();
   return 0;
}


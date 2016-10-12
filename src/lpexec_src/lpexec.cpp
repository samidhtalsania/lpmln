#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <stdio.h>
#include <cstring> 
#include <uuid/uuid.h>

#define SPACE " "

// Requires sudo apt-get install uuid-dev

using namespace std;

void runProcess(string);
void printHelp();

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


int main(int argc, char **argv)
{

   enum Region{
      NONE,
      LPMLN,
      ALCH,
      TUFFY,
      CLINGO
   };

   Region region = NONE;
  
   
   string lpmln = "lpmlncompiler ";
   string alchemy = "infer ";
   string clingo = "clingo ";
   string tuffy = "tuffy ";

   string help = "-h";

   // string lpmln = "lpmln";
   // string lpmln2 = "./lpmln";
   
   string alch = "-mln";
   string cli = "-clingo";
   string tuf = "-tuffy";

   bool execute_alch = false;
   bool execute_cli = false;
   bool execute_tuf = false;

   
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

   for(int i=0 ; i < argc ; i++){

      string arg = string(argv[i]);

      if(arg.compare(help) == 0){
         printHelp();
         exit(0);
      }

      if(i == 0){
         region = LPMLN;
         continue;
      }

      if(arg.compare(alch) == 0){
         region = ALCH;
         execute_alch = true;
         continue;
      }

      if(arg.compare(cli) == 0){
         region = CLINGO;
         execute_cli = true;
         continue;
      }

      if(arg.compare(tuf) == 0){
         region = TUFFY;
         execute_tuf = true;
         continue;
      }

      switch(region){
         case LPMLN:
            lpmln += SPACE + string(argv[i]) + SPACE;
            break;
         case ALCH:
            if(arg.compare("-e") == 0)
               isEvidenceUsed = true;
            alchemy  += SPACE + string(argv[i]) + SPACE;
            break;
         case TUFFY:
            tuffy  += SPACE + string(argv[i]) + SPACE;
            break;
         case CLINGO:
            clingo += SPACE + string(argv[i]) + SPACE;
            break;
         default:
            break;
      }
   }

   lpmln += SPACE + string(">") + SPACE + string("/tmp/") + fileName;

   if(!isEvidenceUsed){
      //Make empty db
      alchemy += string(" -e ") + string("/tmp/")+ fileName + string(".db ");
      string str = "touch /tmp/" + fileName + ".db";
      runProcess(str);
   }

   runProcess(lpmln);
   
   // cout <<alchemy<<endl;

   if(execute_alch == true){
      runProcess(alchemy);
      string str = "cat /tmp/" + fileName + ".res";
      runProcess(str);
   }

   if(execute_cli == true){

      runProcess(clingo);
   }


   if(execute_tuf == true){
      runProcess(tuffy);
   }

   return 0;
}


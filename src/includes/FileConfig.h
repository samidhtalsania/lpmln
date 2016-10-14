enum Region{
   NONE,
   LPMLN,
   ALCH,
   TUFFY,
   CLINGO
};

#include <map>
#include <string>

class FileConfig
{
public:
   FileConfig();

   std::map<std::string, std::string> getloptions(){
      return loptions;
   }

   std::map<std::string, std::string> getaoptions(){
      return aoptions;
   }
   std::map<std::string, std::string> getcoptions(){
      return coptions;
   }

   inline bool getExecuteAlch(){
      return execute_alch;
   }
   inline bool getExecuteCli(){
      return execute_cli;
   }

private:
   std::map<std::string, std::string> loptions;
   std::map<std::string, std::string> aoptions;
   std::map<std::string, std::string> coptions;

   bool execute_alch = false;
   bool execute_cli = false;
   bool execute_tuf = false;


   std::string & rtrim(std::string & str);
   std::string & ltrim(std::string & str);
   bool equalsIgnoreCase(std::string const& s1, std::string const& s2);

   Region region = Region::NONE;
};
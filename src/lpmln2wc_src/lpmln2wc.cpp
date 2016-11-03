#include <iostream>
#include <string>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <exception>
#include <set>
#include <stack>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <stdexcept>      // std::invalid_argument

using namespace std;
using namespace boost;
namespace io = boost::iostreams; 

//build
//g++ -g -std=c++11 lpmln2wc.cpp -o lpmln2wc -L /usr/lib -lboost_regex

// TODO: variables in unsat

set<string> findVariables(const string&);
set<string> findFreeVariables(const string&, const string&);

set<string> findVariables(const string& head){
	
	set<string> s;

	stack<int> stack;
	for(unsigned int i=0;i<head.length();i++){
		if(head.at(i) == '('){
			stack.push(0);
		}

		else if(head.at(i) == '#'){
			while(head.at(i) != '}')
				i++;
			i++;
		}

		string tempStr;
		while(!stack.empty()){
			i++;
			if(i == head.length()) break;
			
			if( (int)head.at(i) >= 65 && // A
				(int)head.at(i) <= 90 && // Z
				( 	(int)head.at(i-1) == 44 || //comma
					(int) head.at(i-1) == 40) ||  // opening paren
					(int) head.at(i-1) == 32 ) { //space 
				
				while(true){
					
					tempStr += head.at(i);
					i++;
					if(head.at(i) == ',')
						break;
					
					if(head.at(i) == '('){
						stack.push(0);	
					}

					if(head.at(i) == ')'){
						stack.pop();
						break;	
					}
					
					if(i == head.length()){
						break;
					}
				}

				s.insert(tempStr);
				tempStr = "";
			}

			if(!stack.empty() && head.at(i) == ')'){
				stack.pop();
			}
		}
	}
	return s;
}



set<string> findFreeVariables(const string& head,const string& body){
	set<string> s = findVariables(head);
	set<string> s1 = findVariables(body);	
	s.insert(s1.begin(), s1.end());
	return s;
}


int main(int argc, char **argv){
	
	ifstream file(argv[1], ios_base::in | ios_base::binary);

	int mode = 0;

	if(argc == 3)
		mode = *argv[2] - '0';

	int unsatcount = 0;
	string str;

	if(file){
    
	    try{
			io::filtering_istream in;

			in.push(file);
			bool f = false; 
			for(str; getline(in, str); ){

				if(str[0] == '%'){
					//ignore comments
					cout<<str+"\n";
					continue;
				}

				
				std::size_t found;
				if(!f){
					found = str.find("python");
					if(found != std::string::npos) {
						f = true;
					}
				}
				
				
				if(f){
					// found = std::string::npos;
					// f = true;
					// while(found == std::string::npos){
					// 	cout<<str;
					// 	found = str.find("end");
					// }
					cout<<str + "\n";
					found = str.find("end");
					if(found != std::string::npos)
						f = false;
					continue;
				}

				trim(str);
				
				vector<string> splitVec;
				

				boost::algorithm::split_regex(splitVec, str, regex(":-"));
				vector<string> splitVecSpace;
				int weight = 0;


				if(splitVec.size() == 1){
					//process it if its of the form 
					// W H.

					split(splitVecSpace, splitVec[0], is_any_of(" "), token_compress_on);
					try{

						weight = (int)(stof(splitVecSpace[0]));
						
						string newStr;

						for(unsigned int i=1;i<splitVecSpace.size();i++){
							newStr += splitVecSpace[i] + " ";
						}
						string tempstr;

						set<string> s = findVariables(newStr);
						string vars;
						for(auto itr = s.begin(); itr!=s.end();++itr)
							vars += *itr + ",";
						if(vars.length() != 0){
							vars.pop_back();
							vars = "," + vars;
						}

						splitVecSpace[1].pop_back();
						trim(newStr);
						newStr.pop_back();

						tempstr = "unsat(" + to_string(unsatcount) + vars + ") :-";
						
						tempstr +=  "not " + newStr + ".\n" + newStr + ":-" ;
						
						tempstr += "not unsat(" + to_string(unsatcount) + vars + ")";
						tempstr +=  ".\n:~ unsat(" + to_string(unsatcount) + vars +"). [" + to_string(weight) + "@0,"+ to_string(unsatcount)+vars +"]\n";


						cout<<tempstr;
						unsatcount++;
					}
					catch(const std::exception& ex){

						cout << str + "\n";
					}


					// dont process it
					// cout<<str + "\n";
				}
				else{
					
					trim(splitVec[0]);
					split(splitVecSpace, splitVec[0], is_any_of(" "), token_compress_on);

					string newStr;

					for(unsigned int i=1;i<splitVecSpace.size();i++){
						newStr += splitVecSpace[i] + " ";
					}
					string tempstr;
					string weightString;
					set<string> s;					
					try{
						weight = (int)(stof(splitVecSpace[0]));
						weightString = to_string(weight) + "@0";
						s = findFreeVariables(newStr, splitVec[1]);
					}
					catch (const std::invalid_argument& ia) {
						weightString = "1@1";
						s = findFreeVariables(splitVec[0], splitVec[1]);
						splitVecSpace.clear();
						newStr = splitVec[0];
					}
					catch(...){
						weightString = "1@1";
						s = findFreeVariables(splitVec[0], splitVec[1]);
						splitVecSpace.clear();
						newStr = splitVec[0];
					};

					// set<string> s = findFreeVariables(newStr, splitVec[1]);
					string vars;
					for(auto itr = s.begin(); itr!=s.end();++itr)
						vars += *itr + ",";
					if(vars.length() != 0){
						vars.pop_back();
						vars = "," + vars;
					}


					splitVec[1].pop_back();

					if(splitVecSpace.size() == 1){
						//W :- B

						tempstr = ":~ "+ splitVec[1]+ "." + "["+ weightString +","+ to_string(unsatcount)+ vars +"]\n" ;

					}
					else{
						if(newStr.empty())
							tempstr = ":~ "+ splitVec[1]+ "." + "["+ weightString +","+ to_string(unsatcount)+ vars +"]\n" ;							
						else
							if(mode == 1)
								tempstr = "unsat(" + to_string(unsatcount) + vars + ") :-" + splitVec[1] + ",not " + newStr + ".\n" + newStr + ":-" + splitVec[1] + ", " + "not unsat(" + to_string(unsatcount) + vars + ")" + ".\n"+":~" + "unsat(" + to_string(unsatcount) + vars +")." + " [" + weightString + ","+ to_string(unsatcount)+vars +"]\n";
							else
								tempstr = str;
					}
					cout<<tempstr;
					unsatcount++;
				} 

			}
		}
		catch(const std::exception& ia) {
	    	cout<<"Error: "<<ia.what();
	    	return -1;
    	}
    }
    else{
    	cerr << "Some error ocurred while processing this file!\n";
    	return -1;
    }
}
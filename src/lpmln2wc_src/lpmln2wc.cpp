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
#include <cmath>

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

		else if(head.at(i) == '#' || head.at(i) == '{'){
			while(head.at(i) != '}')
				i++;
			i++;
		}

		else if(head.at(i) == ':'){
			while(head.at(i) != ',' && head.at(i) != ';' && head.at(i) != '.' && head.at(i) != '-'){
				i++;
				if(i >= head.length()) break;
			}
			i++;
		}

		string tempStr;
		while(!stack.empty()){
			i++;
			if(i == head.length()) break;
			
			if( (int)head.at(i) >= 65 && // A
				(int)head.at(i) <= 90 && // Z
				( 	(int)head.at(i-1) == 44 || //comma
					(int) head.at(i-1) == 40 ||  // opening paren
					(int) head.at(i-1) == 32 )
				) { //space 
				
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
	// set<string> intersect;
	// set_intersection(s.begin(), s.end(), s1.begin(), s1.end(),inserter(intersect, intersect.begin()));
	s.insert(s1.begin(), s1.end());
	// return intersect;
	s.insert(s1.begin(), s1.end());
	return s;
}


int main(int argc, char **argv){
	
	ifstream file(argv[1], ios_base::in | ios_base::binary);

	// int mode = 0;

	// if(argc == 3)
	// 	mode = *argv[2] - '0';

	int unsatcount = 0;
	string str;

	//Default mode is 0, which translates all rules.
	//Mode 1 translates only soft rules.
	int mode = 0;

	if(argc >= 3){
		std::stringstream ss(argv[2]);
		ss >> mode;
		if(mode != 0 && mode != 1){
			cout << "Invalid 3rd argument. Can be either 0 or 1.\n";
			exit(1);
		}

	}

	if(file){
    
	    try{
			io::filtering_istream in;

			in.push(file);
			bool f = false; 
			for(str; getline(in, str); ){

				if(str.length() == 0) continue;

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
				//splits the rule to head and body
				vector<string> splitVec;
				

				boost::algorithm::split_regex(splitVec, str, regex(":-"));
				//splits the head into weight part and rule part
				vector<string> splitVecSpace;
				int weight = 0;


				if(splitVec.size() == 1){
					//process it if its of the form 
					// W H. or H.

					split(splitVecSpace, splitVec[0], is_any_of(" "), token_compress_on);
					//Process soft rules of form W H.
					try{
						std::string::size_type sz;
						float floatVal = stof(splitVecSpace[0],&sz); 
						if(isinf(floatVal) || isnan(floatVal) || sz != splitVecSpace[0].length()) throw std::runtime_error("inf/nan error");
						
						weight = (int)floatVal;
						
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

						string oldVars = vars;
						vars = ",0,"+ to_string(weight) + vars ;


						tempstr = "unsat(" + to_string(unsatcount) + vars + ") :-";
						
						tempstr +=  "not " + newStr + ".\n" + newStr + ":-" ;
						
						tempstr += "not unsat(" + to_string(unsatcount) + vars + ")";
						tempstr +=  ".\n:~ unsat(" + to_string(unsatcount) + vars +"). [" + to_string(weight) + "@0,"+ to_string(unsatcount)+ oldVars +"]\n";


						cout<<tempstr;
						unsatcount++;
					}
					//Process hard rules of form H.
					catch(const std::exception& ex){
						// It could be of type H. Process it.
						
						if(mode == 1){
							//Hard facts are untouched in Mode 1
							cout << str + "\n";
							continue;
						}

						//Remove . at the end
						str.pop_back();

						set<string> s = findVariables(str);
						string vars;
						for(auto itr = s.begin(); itr!=s.end();++itr)
							vars += *itr + ",";
						if(vars.length() != 0){
							vars.pop_back();
							vars = "," + vars;
						}

						string oldVars = vars;
						vars = ",1" + vars ;

						string tempstr = "unsat("+to_string(unsatcount)+vars+") :- not " + str + ".\n" +
											str + " :- not unsat(" + to_string(unsatcount) +vars+ ").\n" +
											":~ unsat(" + to_string(unsatcount) +vars+"). [1@1," + to_string(unsatcount) + oldVars + "]";
								unsatcount++;
						cout << tempstr + "\n";
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
					bool issoft = false;	
								
					try{
						std::string::size_type sz;
						float floatVal = stof(splitVecSpace[0],&sz); 
						if(isinf(floatVal) || isnan(floatVal) || sz != splitVecSpace[0].length()) throw std::runtime_error("inf/nan error");
						weight = (int)(floatVal);
						// if(sz != splitVecSpace[0].length())
						// 	throw std::invalid_argument( "the number is not a weight" );;
						weightString = to_string(weight) + "@0";
						issoft = true;
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
					string probString = "";

					if(issoft) probString += ",0,"+to_string(weight);
					else probString += ",1";

					string oldVars = vars;
					vars = probString + vars;

					if(splitVecSpace.size() == 1){
						//W :- B

						tempstr = ":~ "+ splitVec[1]+ "." + "["+ weightString +","+ to_string(unsatcount)+ oldVars +"]\n" ;

					}
					// Hard rules/constraints are ignored.
					else{
						if(newStr.empty()){
							//if soft rule translate it irrespective of the mode.
							if(issoft || (!issoft && mode == 0))
								tempstr = ":~ "+ splitVec[1]+ "." + "["+ weightString +","+ to_string(unsatcount)+ oldVars +"]\n" ;
							else{
								tempstr = str + "\n";
							}
						}
						else if(issoft || (!issoft && mode == 0)){
							//Soft rules are translated irespective of the mode
							//Hard rules are translated only in mode 0
							tempstr = "unsat(" + to_string(unsatcount) + vars + ") :-" + splitVec[1] + ",not " + newStr + ".\n" + newStr + ":-" + splitVec[1] + ", " + "not unsat(" + to_string(unsatcount) + vars + ")" + ".\n"+":~" + "unsat(" + to_string(unsatcount) + vars +")." + " [" + weightString + ","+ to_string(unsatcount)+ oldVars +"]\n";
						}
						else if(!issoft && mode == 1){
							//Hard rules are translated only in mode 0
							// cout << str + "\n";
							tempstr = str + "\n";
						}
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

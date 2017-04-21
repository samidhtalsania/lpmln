#include "Tree.h"
#include "LanguageConstants.h"

#include <stack> 
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>


Tree::Tree(OptimizationLevel _level, OutputType _type){
	level = _level;
	outputType = _type;
	LanguageConstants::init(_type);
}

Tree::~Tree()
{}

void Tree::completeRules(){

	// Rule Completion
	std::vector<std::pair<std::string,RuleCompletion>> keys_dedup2;
	std::unique_copy(std::begin(rules),
				  std::end(rules),
					std::back_inserter(keys_dedup2),
				  [](const std::pair<std::string,RuleCompletion> &entry1,
					 const std::pair<std::string,RuleCompletion> &entry2) {
					   return (entry1.first == entry2.first);
				   }
				 );
				 
				 
	std::multimap<std::string, RuleCompletion> rules2;
	rules2 = rules;

	for(auto &key : keys_dedup2)
	{
		std::string strLhs;
		std::string strRhs;
		
		std::pair<int,int> auxPos;
		
		std::pair <std::multimap<std::string,RuleCompletion>::iterator, std::multimap<std::string, RuleCompletion>::iterator> ret;

		if(key.first.empty()){
			//Key is empty. This will throw a segfault.
			throw undefined_key();
		}

		ret = rules.equal_range(key.first);
		
		//Based on key, from variables set find out its domains.
		//Assign a variable to each of the domain of the key.
		//Use this variable in constructing strLhs and strRhs 
		std::set<Variable>::iterator itrV = variables.find(key.first);

		if(itrV != variables.end()) itrV->setCompleted();

		std::map<std::string, int> varMapVarCount; /* Maps how many times a particular argument is occuring*/
		std::map<std::string, std::string> varMapAssociate; 
		std::unordered_multimap<int, std::pair<std::string, std::string> > varMap; /* Maps every position of argument in a predicate to the argument type and the variable to be used in its place */
		std::vector<std::string> vtemp = key.second.getHead().getTokens();

		long unsigned int count = 0;
		if(itrV->getPosMap().size() != vtemp.size()){
			throw invalid_arguments(itrV->getPosMap().size(), vtemp.size(), key.first);
		}
		for(auto &var : itrV->getPosMap()){
			varMapAssociate[vtemp.at(count)] = uniqueVars[count];
			std::pair<int, std::pair<std::string, std::string>> pa(var.first, std::pair<std::string, std::string>(var.second.getDomainVar(), uniqueVars[count]));
			varMap.insert(pa);
			varMapVarCount[pa.second.first] = varMapVarCount[pa.second.first] + 1;
			count++;
		}
		
		RuleCompletion r;

		strLhs.append(key.first);
		/*TODO put this opening brace in an if condition*/
		if(varMap.size() != 0){
			strLhs.append("(");
			
			std::vector<std::string> v(varMap.size());
			long unsigned int ii;
			for(auto &vm : varMap){
				ii = static_cast<long unsigned int>(vm.first);
				v[ii] = vm.second.second;
			}
				
			for(auto &vm : v)
				strLhs.append(vm).append(",");
			
			strLhs = strLhs.substr(0,strLhs.size()-1);
			strLhs.append(")");
		}
		
		
		// int auxCount = 0;
		for (std::multimap<std::string,RuleCompletion>::iterator it=ret.first; it!=ret.second; ++it)
		{
			r = it->second;
			std::set<std::pair<std::string,std::string>> orphanVarsSet;
			if(outputType == OutputType::OUTPUT_ALCHEMY){
				strRhs.append("(");
			}
			

			
			//append exist and associated variables to string.
			if(r.checkOrphan())
			{
				orphanVarsSet = r.getOrphanVars();
				strRhs.append("EXIST ");
				for(auto &orphanVars : r.getOrphanVars())
				{
					strRhs.append(orphanVars.first).append(",");
				}
				strRhs = strRhs.substr(0,strRhs.size()-1);
				strRhs.append(" (");
			}
			
			auxPos.first = strRhs.size() ;
			//std::vector<std::pair<int, std::string>> constantPos;
			//Append constants to strRhs
			for(auto &constant : r.getConstantMap())
			{
				//constantPos.push_back(std::pair<int,std::string>(constant.first, constant.second.first));
				//localPos[constant.first] = constant.second.first;
				//strRhs.append("=").append(" ^ ");
				for(auto &constantInner : varMap)
				{
					if(constantInner.first == constant.first){
						strRhs.append(constantInner.second.second).append("=").append(constant.second.second).append(LanguageConstants::SPLIT_CON);
					}
				}
			}
			
			int bodyVecCount = 0;
			for(auto &pred : r.getBody())
			{
				/*		
					if(isEquality)
						return 1;
					else if(isInEquality)
						return 2;
					else
						return 0;
				*/
				int e = pred.checkEquality();
				if(e != 0)
				{
					/*Check if LHS is in the orphanVarsSet */
					auto itr = std::find_if(orphanVarsSet.begin(), orphanVarsSet.end(), [&](const std::pair<std::string, std::string>& val) -> bool{
						return val.first == pred.getLvar();
					});

					//If it is then simply add it
					if(itr != orphanVarsSet.end()){
						strRhs.append(pred.getLvar());
					}

					//Otherwise find out which internal variable is the LHS replaced with
					else
					{
						Predicate predicateWeWant;
						//search all predicates innerVariables to find out its domain
						int pos = 0;
						//TODO Optimize this 
						for(auto innerPred: r.getBody()){
							int found = 0;

							if(innerPred.checkEquality()==0){
								std::vector<std::string> tok = innerPred.getTokens();
								pos = 0;
								for(auto &tokenStr:tok){
									if(tokenStr == pred.getLvar()){
										predicateWeWant = innerPred;
										found = 1;
										break;
									}
									pos++;
								}
							}
							if(found == 1) break;
						}


						if(!predicateWeWant.getVar().empty()){
							
							std::set<Variable>::iterator itrInner = variables.find(predicateWeWant.getVar());
							//Finds variable with var=next
							Domain d = itrInner->getPosMap().at(pos);
							std::string varType(d.getDomainVar());

							auto pa = variables.find(predicateWeWant.getVar())->getPosMap()[pos].getDomainVar();
							for(auto it3=varMap.begin(); it3!=varMap.end();++it3){
								if(it3->second.first.compare(pa) == 0)
									strRhs.append(it3->second.second);	

							}
						}
						else{
							std::cout<<"Error: Cannot find predicate containing "<<pred.getLvar();
						}

					}

					if(e == 1) strRhs.append("=");
					else if(e == 2) strRhs.append("!=");

					itr = std::find_if(orphanVarsSet.begin(), orphanVarsSet.end(), [&](const std::pair<std::string, std::string>& val) -> bool{
						return val.first == pred.getRvar();
					});

					if(itr != orphanVarsSet.end())
					{
						strRhs.append(pred.getRvar());
					}
					else
					{
						//search all predicates innerVariables to find out its domain
						Predicate* predicateWeWant;
						//search all predicates innerVariables to find out its domain
						int pos = 0; 
						for(auto &innerPred: r.getBody()){
							int found = 0;

							if(innerPred.checkEquality()==0){
								std::vector<std::string> tok = innerPred.getTokens();
								pos = 0;
								for(auto &tokenStr:tok){
									if(tokenStr == pred.getRvar()){
										predicateWeWant = &innerPred;
										found = 1;
										break;
									}
									pos++;
								}
							}
							if(found == 1) break;
						}

						if(predicateWeWant == NULL){
							std::cout<<"Error: Cannot find predicate containing "<<pred.getRvar();
						}
						else{
							std::set<Variable>::iterator itrInner = variables.find(Variable(predicateWeWant->getVar()));
							//Finds variable with var=next
							Domain d = (*itrInner).getPosMap().at(pos);
							std::string varType(d.getDomainVar());

							auto pa = variables.find(predicateWeWant->getVar())->getPosMap()[pos].getDomainVar();
							for(auto it3=varMap.begin(); it3!=varMap.end();++it3){
								if(it3->second.first.compare(pa) == 0)
									strRhs.append(it3->second.second);	

							}
						}
					}
					strRhs.append(LanguageConstants::SPLIT_CON);
					continue;
				}

				if(pred.isSingleNegated()){
					strRhs.append("!");
				}
				strRhs.append(pred.getVar());
				strRhs.append("(");
				//If pred.getVar is the same as that of our key
				//Then in that case we make use of localPos to fill variables.
				//Otherwise we just use its own variables

				//The above strat caused a bug. Now always we use its own variables.
				
				//std::set<std::string>::iterator itr;
				//auto itr;
				int pos = 0;
				//Iterate over all the tokens of the predicate
				for(auto &vars : pred.getTokens())
				{
					//auto itr = orphanVarsSet.find(vars);
					auto itr = std::find_if(orphanVarsSet.begin(), orphanVarsSet.end(), [&](const std::pair<std::string, std::string>& val) -> bool{
						return val.first == vars;
					});
					
					if(itr != orphanVarsSet.end())
					{
						strRhs.append(vars).append(",");
					}
					else
					{
						if(domainList.find(vars) != domainList.end()){
							strRhs.append(vars).append(",");
							pos++;
							continue;	
						}

						if(!varMapAssociate[vars].empty()){
							strRhs.append(varMapAssociate[vars]).append(",");	
							pos++;
							continue;
						}
						std::set<Variable>::iterator itrInner = variables.find(Variable(pred.getVar()));
						//Finds domain of the predicate at position pos
						Domain d = (*itrInner).getPosMap().at(pos);
						std::string varType(d.getDomainVar());

						//Check if the value is a constant
						if(isConstant(vars)){
							strRhs.append(vars).append(",");	
						}
						else{
							//find out the domain at position pos of the predicateq pred
							auto pa = variables.find(pred.getVar())->getPosMap()[pos].getDomainVar();
							for(auto it3=varMap.begin(); it3!=varMap.end();++it3){
								if(it3->second.first.compare(pa) == 0){


									if(varMapVarCount[pa] > 1){
										varMapVarCount[pa] = varMapVarCount[pa] - 1;
										continue;
									}
									varMapVarCount[pa] = varMapVarCount[pa] - 1;


									strRhs.append(it3->second.second).append(",");	
									break;
									
								}
							}
							
						}
					}
					pos++;
				}
				
				strRhs = strRhs.substr(0,strRhs.size()-1);
				
				/*Condition added for singletons*/
				if(pred.getTokens().size() != 0){
					strRhs.append(")");
				}
				//splits between literals.
				strRhs.append(LanguageConstants::SPLIT_CON);
				
				bodyVecCount++;
			}
			

			strRhs = strRhs.substr(0,strRhs.size()-3);

			strRhs.append(")");
			// if(r.checkOrphan())
			if(r.checkOrphan())
			{
				auxPos.second = strRhs.size()-1;
				if(outputType == OutputType::OUTPUT_ALCHEMY){
					strRhs.append(")");
				}
			}
			else{
				// strRhs.append(")");
				auxPos.second = strRhs.size()-1;
			}
			strRhs.append(" v ");
			
			//Add code for aux stuff
			//Aux variables needed only in case of orphans
			//Update: check out schedule example
			//Better to use aux variables for all cases
			// if(r.checkOrphan())
			/*
			TODO
			Fix aux not working correclty when there are no orphan variables
			*/

			//Empty queue for printTuffyAux call
			std::queue<int> emptyQueue;


			if(useAux(r.checkOrphan()))
			{
				std::string auxVar;
				std::map<std::string,std::string> auxDeclMap;
				
				//First add declaration
				auxVar.append("aux").append(key.first).append("").append(std::to_string(auxCount++));
				std::string auxLhs(auxVar);
				std::string auxRhs(auxVar);
				std::string auxDecl(auxVar);
				
				
				//Figure out domains to be added in aux declaration
				//parse strRhs. Add all variables to auxLhs such that
				// ex: (EXIST t1 (_b=False ^ shoot(t1) ^ next(t1,_c) ^ target(_a,_b,t1)))
				// _b,t1,_c,_a should be added.
				
				auxDecl.append("(");
				auxLhs.append("(");
				
				for(auto &auxDeclVar : varMap)
				{
					auxDecl.append(auxDeclVar.second.first).append(",");
					auxLhs.append(auxDeclVar.second.second).append(",");
				}
				
				for(auto &auxDeclVar : r.getOrphanVars())
				{
					auxDecl.append(auxDeclVar.second).append(",");
					auxLhs.append(auxDeclVar.first).append(",");
				}
				
				auxDecl = auxDecl.substr(0,auxDecl.size()-1);
				auxLhs = auxLhs.substr(0,auxLhs.size()-1);
				
				//If aux has no arguments we need not close it
				//Since a paren is added by default line 415,416 would inevitable remove it in all cases.
				if (varMap.size() != 0)
				{
					auxDecl.append(")");
					auxLhs.append(")");
				}
				
				
				size_t ar1 = static_cast<size_t>(auxPos.first);
				size_t ar2 = static_cast<size_t>(auxPos.second-auxPos.first);
				auxRhs = strRhs.substr(ar1, ar2);
				
				ar1 = static_cast<size_t>(auxPos.first);
				ar2 = static_cast<size_t>(auxPos.second-auxPos.first);

				if(outputType == OutputType::OUTPUT_ALCHEMY){
					strRhs.replace(ar1,ar2, auxLhs);
				}
				//TODO fix this
				else if(outputType == OutputType::OUTPUT_TUFFY){
					if(ar1 == 0)
						strRhs.replace(ar1, ar2+1, auxLhs);
					else if(strRhs.compare(ar1-1,1,"(") == 0)
						strRhs.replace(ar1-1, ar2+2, auxLhs);
					else
						strRhs.replace(ar1, ar2+1, auxLhs);

				}
				
				if(outputType == OutputType::OUTPUT_ALCHEMY){
					std::cout << auxDecl << "\n";
				}
				else if(outputType == OutputType::OUTPUT_TUFFY){
					tuffyAuxHeaders += auxDecl + "\n";
				}
				if(outputType == OutputType::OUTPUT_ALCHEMY){
					std::cout << auxLhs << " <=> " << auxRhs << ".\n";
				}

				else if(outputType == OutputType::OUTPUT_TUFFY){
					printTuffyAux(auxLhs, auxRhs);
				}
			}
		}
		
		
		strRhs = strRhs.substr(0,strRhs.size()-3);
		// std::cout<<strLhs<<" => "<<strRhs<<"."<<std::endl;

		std::string completedStr = completedLiterals[strLhs];
		if(completedStr.empty())
			completedLiterals[strLhs] = strRhs;
		else
			completedLiterals[strLhs] = completedLiterals[strLhs] + " v " + strRhs;
	}

}

void Tree::completeFacts(){
	//Fact completion
	
	/* Create vector of deduplicated entries: */
	std::vector<std::pair<std::string,FactCompletion>> keys_dedup;
	std::unique_copy(std::begin(facts),
				  std::end(facts),
					std::back_inserter(keys_dedup),
				  [](const std::pair<std::string,FactCompletion> &entry1,
					 const std::pair<std::string,FactCompletion> &entry2) {
					   return (entry1.first == entry2.first);
				   }
				 );

	// All unique keys are in keys_dedup now.
	for(auto &key : keys_dedup){
		std::string strLhs;
		std::string strRhs; 
		std::pair <std::multimap<std::string,FactCompletion>::iterator, std::multimap<std::string, FactCompletion>::iterator> ret;
		ret = facts.equal_range(key.first);

		strLhs.append(key.first);
		int count;
		std::string auxRhs;

		std::vector<std::string> tuffySingleConst;

		FactCompletion f;
		for (std::multimap<std::string,FactCompletion>::iterator it=ret.first; it!=ret.second; ++it){
			//it.second are FactCompletions
			
			std::string auxVar;
			auxVar.append("aux").append(key.first).append("").append(std::to_string(auxCount++));
			std::string auxLhs(auxVar);
			
			std::string auxDecl(auxVar);
						
			auxDecl.append("(");
			auxLhs.append("(");

			std::set<Variable>::iterator itrV = variables.find(key.first);


			f = it->second;
			std::vector<std::string> v = f.getHead().getTokens();
			count = 0;

			if(outputType == OutputType::OUTPUT_ALCHEMY){
				strRhs.append("(");
			}

			//Keeps track of which variable has equality
			std::queue<int> posVector;
			int posVecCount = 0;

			for(auto &str : v){
				if(isConstant(str)){

					if (level == OptimizationLevel::ALL_CLAUSES_AUX){
						auxDecl.append(itrV->getPosMap().at(count).getDomainVar()).append(",");
						auxLhs.append(uniqueVars[count]).append(",");
					}
					/*TODO fix tuffy = */
					posVector.push(posVecCount++);
					strRhs.append(uniqueVars[count++]);
					strRhs.append("=");
					strRhs.append(str);
					strRhs.append(LanguageConstants::SPLIT_CON);		
				}
				else{
					count++;
				}
			}

			auxDecl = auxDecl.substr(0,auxDecl.size()-1);
			auxLhs = auxLhs.substr(0,auxLhs.size()-1);

			auxDecl.append(")");
			auxLhs.append(")");

			

			strRhs = strRhs.substr(0,strRhs.size()-3);
			if(outputType == OutputType::OUTPUT_ALCHEMY){
				strRhs.append(")");
			}
			//if strRhs = "()" it did not find anything
			if(strRhs.size() == 2){
				strRhs.clear();
			}
			else{
				if(level != OptimizationLevel::ALL_CLAUSES_AUX){
					strRhs.append(" v ");
				}
			}

			if(strRhs.size() == 0) continue;
			
			if(level == OptimizationLevel::ALL_CLAUSES_AUX){
				bool appendAuxRhs = false;
				if(outputType == OutputType::OUTPUT_ALCHEMY){
					std::cout << auxDecl << "\n";
				}
				else if(outputType == OutputType::OUTPUT_TUFFY){
					tuffyAuxHeaders += auxDecl + "\n";
				}
				if(outputType == OutputType::OUTPUT_ALCHEMY)
					std::cout << auxLhs << " <=> " << strRhs << ".\n";
				else{
					//optimize this
					//same thing happening in the function call
					std::vector<std::string> strs;
					boost::split(strs, strRhs, boost::is_any_of(LanguageConstants::SPLIT_CON), boost::token_compress_on);

					if(strs.size()>1){
						printTuffyAux(auxLhs, strRhs, posVector);
					}
					else{
						tuffySingleConst.push_back(strRhs);
						appendAuxRhs = true;
					}

				}
				if(!appendAuxRhs)
					auxRhs.append(auxLhs).append(" v ");
				strRhs.clear();
			}

		}
		//if there is no strRhs the this rule was not supposed to be completed
		//Go to next rule.
		
		if(level == OptimizationLevel::ALL_CLAUSES_AUX){
			strRhs = auxRhs;
		}

		std::string tempStr = "[";
		if(tuffySingleConst.size() > 0){
			for(std::string& s: tuffySingleConst)
				tempStr += s + " OR ";
		}
		

		if(tempStr.length() > 1){
			tempStr = tempStr.substr(0,tempStr.length()-4);
			tempStr += "]";
			if(strRhs.length() > 0)
				strRhs += " v " + tempStr;
			else
				strRhs = tempStr;

			strRhs += "   ";
		}


		
		if(strRhs.size() == 0) continue;
		


		strRhs = strRhs.substr(0,strRhs.size()-3);
		
		strLhs.append("(");
		count=0;
		for(unsigned int i=0;i<f.getHead().getTokens().size();i++)
			strLhs.append(uniqueVars[count++]).append(",");
		strLhs = strLhs.substr(0,strLhs.size()-1);
		strLhs.append(")");

		
		std::string completedStr = completedLiterals[strLhs];
		if(completedStr.empty())
			completedLiterals[strLhs] = strRhs;
		else
			completedLiterals[strLhs] = completedLiterals[strLhs] + " v " + strRhs;
		// std::cout<<strLhs<<" => "<<strRhs<<"."<<std::endl;
	}
}

void Tree::completeDeclarations(){
	for(auto itr = completedLiterals.begin(); itr != completedLiterals.end() ; ++itr){
		if(outputType == OutputType::OUTPUT_ALCHEMY){
			std::cout << itr->first << LanguageConstants::IMPL << itr->second << ".\n"; 
		}

		else if(outputType == OutputType::OUTPUT_TUFFY){
			printTuffyExist(itr->first, itr->second);
		}

	}

	for(auto itr = variables.begin(); itr != variables.end(); ++itr){

		if (!itr->isCompleted()){
			//There is a declaration that is not completed. Complete it
			std::string str;
			str += LanguageConstants::NOT;
			str += itr->getVar();
			unsigned int varSize = itr->getPosMap().size();

			if(varSize > 0)
				str += "(";

			for(unsigned int i=0;i<itr->getPosMap().size();++i){
				str += uniqueVars[i];
				str += ",";
			}
			if(varSize > 0){
				str = str.substr(0, str.size()-1);
				str += ")";
			}
			str += ".\n";
			std::cout<<str;
		}
	}
}

void Tree::printASPRuleHB(Head* H, Body* B){
	// std::set<std::string> intermediateConstantSet = H->getConstantSet();
	/*TODO add in body the names of domains for those only present in head.*/
	std::string str;
	if(B->bodyHasNegation()){
		std::string s = B->getExtra(variables);
		if(s.length() > 0)
			str += "," + B->getExtra(variables);
	}

	std::string temp = H->getExtra(variables);
	if(temp.length() > 0){
		str += "," + temp;
	}

	std::cout<<H->toString()
					<<" :- "
					<<B->toString()
					<<str
					<<LanguageConstants::LINE_END
					<<"\n";	
}

std::set<std::string> Tree::findVariables(const std::string& head){
	
	std::set<std::string> s;

	std::stack<int> stack;
	for(unsigned int i=0;i<head.length();i++){
		if(head.at(i) == '('){
			stack.push(0);
		}

		else if(head.at(i) == '#'){
			while(head.at(i) != '}')
				i++;
			i++;
		}

		std::string tempStr;
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



std::set<std::string> Tree::findFreeVariables(const std::string& head,const std::string& body){
	std::set<std::string> s = findVariables(head);
	std::set<std::string> s1 = findVariables(body);	
	s.insert(s1.begin(), s1.end());
	return s;
}

//Prints biimplication in tuffy style syntax
void Tree::printTuffyAux(std::string& LHS, std::string& RHS, std::queue<int>& posVector){

	std::vector<std::string> strs;
	int pos = -1;
	std::string left;
	std::string OR = " OR ";
	if(!posVector.empty()){
		pos = posVector.front();
		posVector.pop();
	}


	boost::split(strs, RHS, boost::is_any_of(LanguageConstants::SPLIT_CON), boost::token_compress_on);

	if(strs.size() == 1){
		LHS = std::string("[") + RHS + std::string("]");
		return;
	}

	int count = 0;
	for(std::string &s : strs){
		if(pos != count){
			std::cout << LHS << " => " << s <<".\n";
		}
		//It is a constant. Display it in tuffy syntax.
		else{
			std::cout << "!" <<LHS << " v [" << s <<"].\n";	
			pos = posVector.front();
			posVector.pop();
			if(s.find("!=") != std::string::npos){
				left += s.replace(s.find("!="),2,"=") + OR;	
			}
			else{
				left += s.replace(s.find("="),1,"!=") + OR;
			}
		}
		count++;
	}

	left = "[" + left.substr(0, left.length() - OR.length()) + "]";

	std::replace( RHS.begin(), RHS.end(), '*', ',');

	if(pos != -1)
		std::cout << LHS << " v " << left <<".\n";
	else
		std::cout << RHS << " => " << LHS <<".\n";
}


//Prints biimplication in tuffy style syntax
void Tree::printTuffyAux(std::string& LHS, std::string& RHS){

	std::vector<std::string> strs;
	std::string left;
	std::string leftPart2;
	std::string OR = " OR ";
	bool equalFound = false;
	
	boost::split(strs, RHS, boost::is_any_of(LanguageConstants::SPLIT_CON), boost::token_compress_on);

	int count = 0;
	for(std::string &s : strs){
		if(s.find("!=") != std::string::npos){
			std::cout << "!" <<LHS << " v [" << s <<"].\n";	

			left += s.replace(s.find("!="),2,"=") + OR;
			equalFound = true;
		}
		else if(s.find("=") != std::string::npos){
			std::cout << "!" <<LHS << " v [" << s <<"].\n";	

			left += s.replace(s.find("="),1,"!=") + OR;
			equalFound = true;
		}
		else{
			std::cout << LHS << " => " << s <<".\n";
			leftPart2 += s + " v ";
		}
		// if(pos != count){
		// 	std::cout << LHS << " => " << s <<".\n";
		// }
		// //It is a constant. Display it in tuffy syntax.
		// else{
		// 	std::cout << "!" <<LHS << " v [" << s <<"].\n";	
		// 	left += s.replace(s.find("="),1,"!=") + OR;
		// }
		// count++;
	}

	left = "[" + left.substr(0, left.length() - OR.length()) + "]";
	

	std::replace( RHS.begin(), RHS.end(), '*', ',');

	if(equalFound)
		std::cout << LHS << " v " << leftPart2 << left <<".\n";
	else
		std::cout << RHS << " => " << LHS <<".\n";
}


void Tree::printTuffyExist(const std::string& LHS, std::string& RHS){
	// std::cout << LHS << " => " << RHS << ".\n";
	std::set<std::string> orphanVars;
	std::vector<std::string> holder;
	boost::split(holder, RHS, boost::is_any_of("v"), boost::token_compress_on);
	
	std::string newRhs;
	std::string newRhsPart2;
	std::string tuffyConstants;

	bool isOrphanVars = false;
	bool preIsOrphanVars = false;
	bool preConstant = false;

	for(auto it = holder.begin(); it != holder.end(); ++it){
		std::string s = *it;
		if (s.compare("EXIST") == 0){
			isOrphanVars = true;
			preIsOrphanVars = true;
		}
		else if (isOrphanVars){
			std::vector<std::string> tempVector;
			boost::split(tempVector,s,boost::is_any_of(","), boost::token_compress_on);
			std::copy(tempVector.begin(), tempVector.end(), std::inserter(orphanVars, orphanVars.end()));
			isOrphanVars = false;
		}
		else{
			// if(preConstant){
			// 	tuffyConstants += s + " ";
			// 	preConstant = false;
			// }
			if(s.find("[") == 0){
				tuffyConstants += s;
				// preConstant = true;
			}
			else
				newRhsPart2 += s + " v ";
		}
	}

	if(tuffyConstants.length() == 0){
		newRhsPart2 = newRhsPart2.substr(0,newRhsPart2.length()-3);
	}

	if(preIsOrphanVars)
		newRhs += "EXIST ";
	for (auto it = orphanVars.begin(); it != orphanVars.end(); ++it){
		newRhs += *it + ",";
	}
	newRhs = newRhs.substr(0, newRhs.length()-1);
	std::cout << newRhs << " " << LHS << " => " << newRhsPart2 << tuffyConstants <<".\n";



}


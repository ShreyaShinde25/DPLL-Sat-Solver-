#include <iostream>
#include "tseitinTransformer.h"
#include "satSolver.h"
#include <string>
#include <map>
#include "parser.h"
#include "treeNode.h"
#include<fstream>
#include<string.h>
#include "tokenizer.h"

std::string print(std::vector<std::vector<int>> cnf)  {
  // std::string result = "";
  // your code starts here
  std::string result;
  // std::cout<<"Hiii string "<<std::endl;
  for (auto c:cnf)
   {
    result += "["; 
    for (auto l:c)
    {
     result.append(std::to_string(l) + ", ");
    }
    result.pop_back();
    result.pop_back();
     result.append("]");
     }
// result.erase(std::remove_if(result.begin(), result.end(), ::isspace),
//         result.end());

     // Space and comma hatana hai last wala
  return result;
}


// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
void parseLine(const std::string &line,std::string &formulaStr) 
{
  // your code starts here

  std::string delimiter=";";
  int open=0;
  int close=0;
  formulaStr.assign(line);       //formulaStr=line
  if(formulaStr.find(delimiter)!= std::string::npos)
  {
    throw std::invalid_argument("invalid input");
  }
  else if (formulaStr.empty())
    {
      throw std::invalid_argument("invalid input");
    }
    else 
    { int i=0;
       while(i<(int)formulaStr.size())
         { 
           if (formulaStr[i]=='(')
            open++;
            else if (formulaStr[i]==')')
            close++;
            i++;
         if(close>open)
         {
            throw std::invalid_argument("invalid input");
         } 
         }
         
      if( open!=close)
      {
        throw std::invalid_argument("invalid input");     
      }
    }
  
  }
  // else
    // throw std::invalid_argument("invalid input");
  


int main() 
{
  // while (true) // continuously asking for new inputs from standard input
   std::string formulaStr;
   std::string line; // store each input line
    // your code starts here
   std::vector<std::vector<int>> result;
   std::string finalResult;
   bool satres;
   std::vector<std::vector<int>> plpResult ;

    while(getline(std::cin, line))
    {
      TreeNode* gettree = NULL;
     try{

          if(line.size()==0)
          { throw std::invalid_argument("invalid input");}
            parseLine(line, formulaStr);

             
             FormulaParser formParse (formulaStr);
             gettree= formParse.getTreeRoot();     //Tree root
             TseitinTransformer tseitin(gettree);
             result= tseitin.transform();
             finalResult=tseitin.cnfString(result);
             //std::cout<<"Formula : "<<finalResult<<std::endl;
            //  std::cout<<tseitin.getVarNum()<<"THIS IS GETVAR COUNTERR:"<<std::endl;
            //  bool satRes= satCallingMiniSat(tseitin.getVarNum(),result);
            //  if (satRes==1)
            //  {
            //   std::cout<<"sat"<<std::endl;
            //  }
            //  else
            //  {
            //   std::cout<<"unsat"<<std::endl;
            //  }
            // //  std::cout<<evaluate(gettree,assignParse.parseAssignment())<<std::endl; 
            // // std::cout<<"HELLLOOOO";
             
            std::map<int,bool> A;
            A.insert({1,true});
            satres= DPLL(result,A);
            if(satres==true)
            {
              std::cout<<"sat"<<std::endl;
            }
            else
            {
              std::cout<<"unsat"<<std::endl;
            }
            // std::cout<<"HEYYYYYYYYYYYYYYYYYYYYY";

            // bcp print..........................................................
            // std::string bcpsolverResult=print(satres);
            // std::cout<<"BCP : "<<bcpsolverResult<<std::endl;
            //plp call ....................................................................
            // plpResult= plp(satres,A,tseitin.getVarNum());
            // std::string plpsolverResult=print(plpResult);
            // std::cout<<"PLP : "<<plpsolverResult<<std::endl;

            delete gettree;
        }
    catch(const std::invalid_argument& ia)
    {
	  std::cout << "Error: "<< ia.what() << '\n';
     delete gettree;
    }
    }
  return 0;
}

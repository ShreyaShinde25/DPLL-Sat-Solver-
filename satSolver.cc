#include "satSolver.h"
// #include "minisat/core/SolverTypes.h"
// #include "minisat/core/Solver.h"
#include <map>
#include <iostream>
#include<vector>
#include<algorithm>
#include <memory>


std::string printsat(std::vector<std::vector<int>> cnf)  {

  std::string result;
  
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
  return result;
}

int highestElem(std::map<int,bool> & assignMap, std::vector<std::vector<int>> &formula)
{
  std::map<int,int> mp;
  for(int i=0; i< formula.size(); i++)
  {
    for (int j=0; j<formula[i].size(); j++)
    {
      if(mp.find(abs(formula[i][j]))!=mp.end() )
      {
        //found
        mp[abs(formula[i][j])]++;
      }
      else
      {
        mp.insert({abs(formula[i][j]),1});
      }
    }
  }
  int highestElem = 0;
  int highestCount = 0;
  for (const auto &pair : mp)
  {
    if (pair.second > highestCount)
    {
      highestElem = pair.first;
      highestCount = pair.second;
    }
  }
  return highestElem;
}


//BCP ********************************************************************************************************
bool bcp(std::vector<std::vector<int>> &formula,std::map<int, bool> &assignMap ) {
   for(auto it =assignMap.begin(); it!=assignMap.end(); it++)                                       //(auto a:assignMap) 
{
// { std::cout<<printsat(formula)<<std::endl;
  // std::cout<<"FOR MAP VALue:"<<it->first<<"   "<<it->second<<std::endl;
  for (int i=0;i<formula.size();i++)
 {//  std::cout<<"*******************************************"<<std::endl;
    for (int j=0; j<formula[i].size();j++)
    {    
      //std::cout<<"i :"<<i<<"  j:"<<j<<" "<<printsat(formula)<<std::endl;
       if((it->first==formula[i][j] && it->second) || (it->first==-1*formula[i][j] && !it->second ))
       {
       
        formula.erase(formula.begin()+i);
        i--;
        break;
       }
       else if((it->first==formula[i][j] && !it->second)|| (it->first==-1*formula[i][j] && it->second))
        { if(formula[i].size()==1 && formula.size()>=1)
        { // std::cout<<"Unsat boll "<<std::endl;
         return false;
        }
        
        formula[i].erase(formula[i].begin()+j);  //literal dropped
        
        j--;   
        
       } 
    }
     if(formula[i].size()==1)
     { 
        if(formula[i][0]>0)
        { 
          // std::cout<<"inserting "<<formula[i][0]<<" as "<<true<<"\n";
         
          assignMap.insert({formula[i][0],true});
          // formula.erase(formula.begin()+i);
          //  i--;  
        }

        else
        {  
         
         // std::cout<<"inserting "<<formula[i][0]*-1<<" as "<<false<<"\n";    
          assignMap.insert({formula[i][0]*-1,false});
            //  formula.erase(formula.begin()+i);
            //  i--;   
        }
        
         if((formula[i][0]>0 && assignMap.at(formula[i][0])==false)|| (formula[i][0]<0 && assignMap.at(-1*formula[i][0])==true))
        { 
          
          return false;
        }

      }
      
  }
       
  // std::cout<<"FORMULAA SIZE IS : "<<formula.size()<<std::endl;

}


return true;
}



//PLP *****************************************************************************************************************************
bool plp(std::vector<std::vector<int>> &formula,std::map<int, bool> &assignMap, int varNum ) {

std::vector<int> L;

// std::cout<<"formula size:"<<formula.size();
for (int i=1 ; i<varNum-1; i++)
{  int positive=0;
   int negative=0;
  for (int j=0; j<formula.size(); j++)
  {
    for(int k=0; k<formula[j].size(); k++)
    { 
      if (i == formula[j][k])
     { 
        positive++;
      }
      else if(-1*i==formula[j][k])
      {
        negative++;
      }
    }
  }
  if(negative==0)
    { 
     assignMap.insert({i,true});
    //  std::cout<<"heyyyyyyy::"<<i<<std::endl;
     L.push_back(i);
    }
    else if(positive==0)
    {
      assignMap.insert({-1*i,false});
      L.push_back(-1*i);
    }
  

}

for (int i=0; i<L.size();i++)
{
  for (int j=0; j<formula.size();j++)
  {
    for(int k=0; k<formula[j].size(); k++)
    {
      if(L[i]==formula[j][k])
      {formula.erase(formula.begin()+j);
      j--;
      }
    }
  }
}

if(formula.size()==0)
return true;
else
return false;
}

bool DPLL(std::vector<std::vector<int>> &formula,std::map<int, bool> &assignMap)
{ std::map<int, int> varCount;
std::map<int,bool> assignCopy;
  bool bcpRes= bcp(formula, assignMap);


  if (bcpRes==true && formula.size()==0)
   return true;
  else
    if(bcpRes==false)
    { 
     return false;
    }
  else {
  int p= highestElem(assignMap,formula);  
  assignMap.insert({p,true});
  // for(auto it:assignMap)
  // {
  //  // std::cout<<"dpll map: "<<it.first<<" "<<it.second<<std::endl;
  // }
  assignCopy.insert(assignMap.begin(),assignMap.end());
  std::vector<std::vector<int>> transform= formula;
  if(DPLL(formula,assignMap) && formula.size()==0)
    {
      return true;
    }

  else
  { //std::cout<<"now p is :"<<p<<std::endl;

    assignCopy[p]=false;
    
    return DPLL(transform,assignCopy);
    }
  }
  //  for(auto it = assignMap.cbegin(); it != assignMap.cend(); ++it)
  // {
  //   //std::cout << it->first << " " << it->second<< "\n";
  // }

}
 





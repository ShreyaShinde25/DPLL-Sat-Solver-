#include "tseitinTransformer.h"
#include<iostream>
// #include "treeNode.h"
#include<string>
#include<stdio.h>
#include<algorithm>

TseitinTransformer::TseitinTransformer(TreeNode *root): formulaRoot{root} {}


int TseitinTransformer::transSubformula(TreeNode* subRoot) {
  // your code starts here
  int id;
int leftChildId;
int rightChildId;
  if (subRoot->getContent()=="+")
  { 
    id=varIdCounter;
    // std::cout<<"I am inside +"<<id<<std::endl;
    varIdCounter++;
    leftChildId= transSubformula(subRoot->getLeftChild());
    // std::cout<<"leftchildd"<<id<<std::endl;
    rightChildId= transSubformula(subRoot->getRightChild());
    // std::cout<<"id is:"<<id<<std::endl;
    addOrEq(id, leftChildId, rightChildId );
    return id;
  } 
  if( subRoot->getContent()=="*")
  { 
    id=varIdCounter;
    varIdCounter++;
    leftChildId= transSubformula(subRoot->getLeftChild());
    rightChildId= transSubformula(subRoot->getRightChild());
    addAndEq(id, leftChildId, rightChildId );
    return id;
  }

  if( subRoot->getContent()=="-")
  {
    id=varIdCounter;
    varIdCounter++;
    leftChildId=transSubformula(subRoot->getLeftChild());
    addNegEq(id, leftChildId);
    return id;
  }
  else 
  {
    if(varIdTable.find(subRoot->getContent())==varIdTable.end())
    {
      //not found
      id=varIdCounter;
      varIdCounter++;
      varIdTable.insert({subRoot->getContent(),id});
      
      return id;
    }                                               
    else
    return varIdTable[subRoot->getContent()];             
  }

  return 0;
}

void TseitinTransformer::addNegEq(int curID, int childID) {
  // your code starts here
   cnf.push_back({-1*curID,-1*childID});
   cnf.push_back({curID,childID});
}

void TseitinTransformer::addOrEq(int curID, int leftID, int rightID) {
  // your code starts here
  // std::cout<<"Adding elements to vectotr"<<std::endl;
  cnf.push_back({-1*curID,leftID,rightID});
  cnf.push_back({-1*leftID,curID});
  cnf.push_back({-1*rightID,curID});
}

void TseitinTransformer::addAndEq(int curID, int leftID, int rightID) {
  // your code starts here
  cnf.push_back({-1*curID, leftID});
  cnf.push_back({-1*curID, rightID});
  cnf.push_back({-1*leftID, -1*rightID, curID});

}

std::vector<std::vector<int>> TseitinTransformer::transform() {
  // your code starts here
  
  int n=transSubformula(formulaRoot);
  cnf.push_back({n});
  return cnf;
}

std::string TseitinTransformer::cnfString(std::vector<std::vector<int>> cnf) const {
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

unsigned int TseitinTransformer::getVarNum() const {
  // your code starts here
   
  return varIdCounter ;
}

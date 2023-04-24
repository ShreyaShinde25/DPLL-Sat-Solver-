#include "parser.h"
#include "treeNode.h"
#include "tokenizer.h"
#include<iostream>
#include<stdio.h>

FormulaParser::FormulaParser(std::string ln) 
{ 
  this->tknzr = new Tokenizer(ln);
   std::vector<Token> ftoken = tknzr->getTokens(); 
     
}
TreeNode * FormulaParser::getTreeRoot() 
{
  // your code starts here
   TreeNode* Root= parseFormula();
   ///TreeNode* test;
  //  test->printDFS_post(Root);
   if (tknzr->hasToken())
   { 
      throw std::invalid_argument("invalid input");
   }
  return Root;
}


TreeNode *FormulaParser::parseFormula() 
{
  // your code starts here
TreeNode *leftchildconj =parseConjTerm();
while(tknzr->hasToken()&&tknzr->getToken().content=="+")
{ TreeNode* ornode= new OperatorNode("+");
  tknzr->advanceToken();
  TreeNode* Rightchildconj = parseFormula();
  ornode->updateChildren(leftchildconj,Rightchildconj);
  return ornode;
}

return leftchildconj;
}

TreeNode *FormulaParser::parseConjTerm() {
  // your code starts here
 TreeNode* leftchildterm = parseTerm();
 while(tknzr->hasToken()&& tknzr->getToken().content=="*")
 { tknzr->advanceToken();
  TreeNode* andnode = new OperatorNode("*");
   TreeNode* Rightchildterm = parseConjTerm();
   andnode->updateChildren(leftchildterm,Rightchildterm);
   return andnode;
 }
  return leftchildterm;
}

TreeNode *FormulaParser::parseTerm() 
{
  // your code starts here
if (tknzr->hasToken()&&tknzr->getToken().content=="(")
  { tknzr->advanceToken();
    TreeNode* leftchildfinal= parseFormula();
    if (tknzr->getToken().content==")")
    {
      tknzr->advanceToken();
      return leftchildfinal;
    }
    else 
      throw std::invalid_argument("invalid input");
      
  } 
  else if (tknzr->hasToken()&&tknzr->getToken().type=="Constant")
   {  TreeNode* constnode= new ConstantNode(tknzr->getToken().content);
      tknzr->advanceToken();
      return constnode;
   }
  else if(tknzr->hasToken()&&tknzr->getToken().type=="VarName")     
  { TreeNode* varnode=new VariableNode(tknzr->getToken().content);
    tknzr->advanceToken();
    return varnode;
  } 
  
  else if (tknzr->hasToken()&& tknzr->getToken().content=="-")
  { 
    TreeNode* notNode = new OperatorNode(tknzr->getToken().content);
    tknzr->advanceToken();
    TreeNode* term= parseTerm();
    notNode->updateLeftChild(term);
    return notNode;

  }
 else
 { 
  throw std::invalid_argument("invalid input");
 }

}


FormulaParser::~FormulaParser() {
  // your code starts here   
  delete tknzr;
}

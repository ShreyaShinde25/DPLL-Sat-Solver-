#include "tokenizer.h"
#include<iostream>
#include<stdio.h>
#include<string>
#include<regex>
#include<iterator>
#include<vector>

Tokenizer::Tokenizer(std::string  ln)
{
  Token t;
  std::regex regexpF ("[A-Za-z][A-Za-z0-9]{0,9}|[0-1]|[*]|[+]|[-]|[(]|[)]");
  std::string strcpy=ln;

  for (std::sregex_iterator it=std::sregex_iterator(ln.begin(),ln.end(),regexpF); it!= std::sregex_iterator(); it++)
   {
        // std::cout<<ln<<std::endl;
       
       std::smatch match= *it;
       
       if (match.str(0)=="*")
            { t.content= match.str(0);
             t.type="AND";
            }
          
        else if (match.str(0)=="+")
         { t.content= match.str(0);
          t.type= "OR";}
         
        else if (match.str(0)=="-")
        { t.content= match.str(0);
          t.type ="NOT";

        } 
        else if (match.str(0)==",")
        { t.content= match.str(0);
          t.type ="COMMA";

        } 

         
        else if (match.str(0)=="(")
        {  t.content= match.str(0);
           t.type="OPEN"; 
        }
          
        else if (match.str(0)==")")
         {
          t.content= match.str(0);
          t.type="CLOSE";
         } 
        
        
        else if (match.str(0)=="1" || match.str(0)=="0")
         { throw std::invalid_argument("invalid input");
          
           t.content=match.str(0); 
          t.type= "Constant";
         }
        
        // else if (match.str(0)== "->")
        // {
        //     t.content=match.str(0);
        //     t.type= "implies";
        // }
        
        // else if(match.str(0)=="<->")
        // {
        //     t.content= match.str(0);
        //     t.type ="iff";
        // }

        else
         { t.content= match.str(0);
          t.type= "VarName";
         }
         
         tokens.push_back(t);

         strcpy= strcpy.replace(strcpy.find(match.str(0)),match.str(0).size(),"");  //replacing the acceptable elements with the empty string
        // std::cout<< strcpy<<std::endl;
   }
  strcpy.erase(std::remove_if(strcpy.begin(), strcpy.end(), ::isspace),
            strcpy.end());
  if(strcpy.size()!=0)
  {
     throw std::invalid_argument("invalid input");
  }

  j=0;
}

bool Tokenizer::advanceToken() {
  // your code starts here
   
   j++;
   if(j<(int)tokens.size()){
    
    return true;
   }

  return false;
}

bool Tokenizer::hasToken() const 
{
  // your code starts here

  if ( j< (int)tokens.size() )
   return true;
  else
   return false;
}

// only can be called when hasToken() is true
Token Tokenizer::getToken() 
{
   Token resultToken;  
   if (hasToken())
   resultToken=tokens.at(j);
  // your code starts there
 
   return resultToken;
}
std::vector<Token> Tokenizer::getTokens()
{
  return tokens;
}


#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include<vector>

struct Token
{
    std::string content;
    std::string type;
};

// a tokenzier breaks a stream of string into tokens
class Tokenizer
{
  // your code starts here
  private:
    std::vector<Token> tokens;
    int j;
  public:
    

    Tokenizer(std::string ln);
    bool advanceToken(); // advance to the next token; return false if no more token exist
    bool hasToken() const; // check whether there is a current token
    Token getToken(); // returns the token being processed
    std::vector<Token> getTokens();
};

#endif

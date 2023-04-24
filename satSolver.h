#ifndef SAT_H
#define SAT_H

#include <vector>
#include<map>

bool bcp(std::vector<std::vector<int>> &formula,std::map<int, bool> &assignMap ) ;
 // return the SAT result of cnf by calling MiniSAT
bool plp(std::vector<std::vector<int>> &formula,std::map<int, bool> &assignMap, int varNum  ) ;
bool DPLL(std::vector<std::vector<int>> &formula,std::map<int, bool> &assignMap);



#endif

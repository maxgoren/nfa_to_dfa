#ifndef actions_hpp
#define actions_hpp
#include <vector>
#include <iostream>
#include "ast.hpp"
using namespace std;


astnode* pass(vector<astnode*>& r);
astnode* mkLeaf(vector<astnode*>& r) ;
astnode* mkConcat(vector<astnode*>& r);
astnode* mkKleene(vector<astnode*>& r) ;
astnode* mkOr(vector<astnode*>& r);
astnode* mkOpt(vector<astnode*>& r);
astnode* mkList(vector<astnode*>& r);
astnode* mkCCLRange(vector<astnode*>& r);
astnode* mkCcl(vector<astnode*>& r);
astnode* mkEscaped(vector<astnode*>& r);

#endif
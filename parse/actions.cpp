#include "actions.hpp"
using namespace std;

void preorder(astnode* ast, int n) {
    if (ast != nullptr) {
        for (int i = 0; i < n; i++) cout<<" ";
        cout<<ast->token.getString()<<endl;
        preorder(ast->children[0], n+1);
        preorder(ast->children[1], n+1);
        preorder(ast->next, n);
    }
}

astnode* pass(vector<astnode*>& r) {
    return r[1];
}

astnode* mkLeaf(vector<astnode*>& r) {
    r[0]->type = CONST_EXPR;
    return r[0];    
}

astnode* mkKleene(vector<astnode*>& r) {
    r[1]->type = KLEENE_EXPR;
    r[1]->children[0] = r[0];
    return r[1];
}

astnode* mkOpt(vector<astnode*>& r) {
    r[1]->type = OPT_EXPR;
    r[1]->children[0] = r[0];
    return r[1];
}

astnode* mkConcat(vector<astnode*>& r) {
    cout<<"Concat from "<<r.size()<<" items: "<<endl;
    astnode* cc = new astnode(r[0]->token);
    cc->token.setString("@");
    cc->type = CONCAT_EXPR;
    cc->children[0] = r[0];
    cc->children[1] = r[1];
    return cc;
}
astnode* mkOr(vector<astnode*>& r) {
    astnode* cc = r[1];
    cc->type = OR_EXPR;
    cc->children[0] = r[0];
    cc->children[1] = r[2];
    return cc;
}
astnode* mkList(vector<astnode*>& r) {
    auto it = r[0];
    while (it->next != nullptr) it = it->next;
    it->next = r[1];
    return r[0];
}

astnode* mkCCLRange(vector<astnode*>& r) {
    r[1]->children[0] = r[0];
    r[1]->children[1] = r[2];
    r[1]->type = RANGE_EXPR;
    return r[1];
}

astnode* mkCcl(vector<astnode*>& r) {
    r[0]->children[0] = r[2];
    r[0]->type = CCL_EXPR;
    if (r[1]->token.getString() != "Epsilon")
        r[0]->children[1] = r[1];
    return r[0];
}
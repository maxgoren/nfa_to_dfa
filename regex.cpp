#include <iostream>
#include <queue>
#include <map>
#include "parse/lexer.hpp"
#include "parse/parser.hpp"
#include "parse/buffer.hpp"
#include "nfa.hpp"
#include "dfa.hpp"
#include "powerset.hpp"
using namespace std;


bool matchNFA(NFA& nfa, string text) {
    set<NFAState*> states = {nfa.start};
    states = e_closure(states);
    int i = 0;
    int matchFrom = 0;
    int matchLen = 0;
    char c;
    bool didFind = false;
    for (int i = 0; (c = text[i]) != '\0'; i++) {
        if (states.empty() || c == '\n')
            return didFind;
        states = e_closure(move(c, states));
        if (states.find(nfa.accept) != states.end()) {
            cout<<"Match Found: ";
            for (int t = matchFrom; t <= i; t++) {
                cout<<text[t];
            }
            cout<<endl;
            didFind = true;
            matchLen = i - matchFrom;
        }
    }
    if (states.find(nfa.accept) != states.end())
        didFind = true;
    return didFind;
}



bool matchDFA(DFA& dfa, string expr) {
    DFAState* state = dfa.states[0];
    for (int i = 0; i < expr.size(); i++) {
        cout<<state->label<<" "<<expr[i]<<endl;;
        DFAState* next = nullptr;
        if (state->trans.find(expr[i]) != state->trans.end()) {
            next = state->trans[expr[i]];
        }
        if (next == nullptr) {
            return false;
        } else if (next->accepts) {
            return true;
        } else state = next;
    }
    return state != nullptr;
}

void repl(string pattern, string text) {
    Lexer lexer;
    Parser parser(false);
    bool running = true;
    string buffer;
    StringBuffer sb;
    sb.init(pattern);
    auto tokens = lexer.lex(&sb);
    auto ret = parser.parse(tokens);
    preorder(ret, 1);
    RECompiler rec;
    NFA nfa = rec.compile(ret);
    DFA dfa = makeDeterministic(nfa, pattern);
    if (matchDFA(dfa, text)) {
        cout<<"Yep, match found."<<endl;
    }
}

    
    

int main(int argc, char* argv[]) {
    if (argc < 3) return -1;
    repl(argv[1], argv[2]);
}
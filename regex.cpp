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
        cout<<state->label<<" "<<expr[i]<<" -> ";
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
    cout<<endl;
    return state != nullptr && state->accepts;
}

DFA makeDFA(string pattern) {
    Lexer lexer(true);
    Parser parser(true);
    bool running = true;
    string buffer;
    StringBuffer sb;
    sb.init(pattern);
    auto tokens = lexer.lex(&sb);
    auto ret = parser.parse(tokens);
    preorder(ret, 1);
    RECompiler rec;
    NFA nfa = rec.compile(ret);
    return makeDeterministic(nfa, pattern);
}

void match(string pattern, string text) {
    DFA dfa = makeDFA(pattern);
    if (matchDFA(dfa, text)) {
        cout<<"Match Found."<<endl;
    }
}


void match_from_stdin(string pattern) {
    DFA dfa = makeDFA(pattern);
    char buffer[1028];
    while (fgets(buffer, 1024, stdin)) {
        if (matchDFA(dfa, buffer)) {
            cout<<buffer<<endl;
        } else {
            cout<<"(X) - Failed."<<endl;
        }
    }
}
    
    

int main(int argc, char* argv[]) {
    if (argc < 2) return -1;
    if (argc < 3) match_from_stdin(argv[1]);
    else match(argv[1], argv[2]);
}
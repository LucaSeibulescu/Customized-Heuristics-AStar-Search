#ifndef STATE_H
#define STATE_H

#include <queue>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>

using namespace std;

class State {
    private:
        vector< vector<char> > curr;
    public:
        State(vector< vector<char> > init);
        void print();
        bool match(State*);
        string hash();
        vector<State*> successors();
        void getBlockPos(char, int&, int&);
        float heuristic0(State&);
        float heuristic1(State&);
        float heuristic2(State&);
        float heuristic3(State&);
};

#endif
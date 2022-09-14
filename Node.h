#ifndef NODE_H
#define NODE_H

#include "State.h"
#include <queue>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Node {
    private:
        State* curr;
        Node* parent;
        State* goal;
    public:
        int depth;
        int moves;
        float score;
        Node(State*, Node*, State*);
        bool goal_test(State*);
        vector<Node*> successors();
        string hash();
        int print_path();
};

#endif
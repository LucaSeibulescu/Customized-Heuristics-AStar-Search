#include "Node.h"

using namespace std;

Node::Node(State* newSt, Node* prev, State* goal) {
    curr = newSt;
    parent = prev;
    this->goal = goal;
    depth = (prev == nullptr) ? 0 : prev->depth + 1;
    //score = newSt->heuristic0(*goal) + ((1 + (prev == nullptr)) ? 0 : prev->depth);
    score = newSt->heuristic3(*goal) + depth;
    //cout << "Score: " << score << " Depth: " << depth << endl;
}

bool Node::goal_test(State* curr) {
    return this->curr->match(curr);
}

vector<Node*> Node::successors() {
    vector<State*> stSuccess;
    vector<Node*>  nSuccess;
    stSuccess = this->curr->successors();
    for(int i = 0; i < stSuccess.size(); i++) {
        Node* newN = new Node(stSuccess.at(i), this, goal);
        //newN->depth = this->depth + 1;
        /*cout << "Mem address: " << endl;
        cout << this << endl;*/
        nSuccess.push_back(newN);
        /*cout << "new Successors: " << endl;
        stSuccess.at(i)->print();
        cout << endl;*/
    }
    return nSuccess;
}

string Node::hash() {
    return curr->hash();
}

int Node::print_path() {
    if(this->parent == nullptr) {
        //cout << "Condition" << endl;
        cout << "move " << depth << ", pathcost=" << depth << ", heuristic=" << score - depth << ", f(n)=g(n)+h(n)=" << score << endl;
        this->curr->print();
        cout << ">>>>>>>>>>" << endl;
    }
    else {
        //cout << "Recursion" << endl;
        this->parent->print_path();
        cout << "move " << depth << ", pathcost=" << depth << ", heuristic=" << score - depth << ", f(n)=g(n)+h(n)=" << score << endl;
        this->curr->print();
        cout << ">>>>>>>>>>" << endl;
    }
    return depth;
}
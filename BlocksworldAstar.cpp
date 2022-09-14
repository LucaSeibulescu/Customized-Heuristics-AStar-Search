#include "State.h"
#include "Node.h"
#include <queue>
#include <unordered_map>

using namespace std;

#define MAX_ITERS 100000

struct lessThanByScore {
    bool operator()(const Node* a, const Node* b) {
        return a->score > b->score;
    }
};

void pqPrint(priority_queue<Node*, vector<Node*>, lessThanByScore> pq) {
    while(!pq.empty()) {
        cout << "Score: " << pq.top()->score << endl;
        pq.pop();
    }
    cout << "DONE" << endl;
}

Node* BFS(State* init, State* fin) {
    int iter = 0;
    int max_queue = 0;
    unordered_map<string, Node*> reached;
    Node* curr = new Node(init, nullptr, fin);
    iter++;
    if(curr->goal_test(fin)) {
        //cout << "<<<<<<<<<" << endl;
        curr->print_path();
        //cout << "<<<<<<<<<<" << endl;
        return curr;
    }
    priority_queue<Node*, vector<Node*>, lessThanByScore> priorityQueue;
    priorityQueue.push(curr);
    max_queue++;
    pair<string, Node*> insertPair = make_pair(curr->hash(), curr);
    reached.insert(insertPair);
    while(priorityQueue.size() != 0) {
        Node* curr = priorityQueue.top();
        priorityQueue.pop();
        vector<Node*> vNode = curr->successors();
        for(int i = 0; i < vNode.size(); i++) {
            if((reached.find(vNode.at(i)->hash()) == reached.end()) || ((vNode.at(i)->depth) < (reached.at(vNode.at(i)->hash())->depth))) {
                //pqPrint(priorityQueue);
                if(++iter > MAX_ITERS) {
                    cout << "Failure: Max iterations reaached" << endl;
                    return nullptr;
                }
                if(vNode.at(i)->goal_test(fin)) {
                    /*cout << "Goal: " << endl;
                    fin->print();
                    cout << "vNode: " << endl;
                    vNode.at(i)->curr->print();*/
                    //cout << ">>>>>>>>>>" << endl;
                    cout << "success! iter=" << iter << ", depth=" << vNode.at(i)->depth << ", max queue size=" << max_queue << endl;
                    vNode.at(i)->print_path();
                    //cout << ">>>>>>>>>>" << endl;
                    return vNode.at(i);
                }
                //if(reached.find(vNode.at(i)->hash()) == reached.end()) {
                pair<string, Node*> insertPair = make_pair(vNode.at(i)->hash(), vNode.at(i));
                reached.insert(insertPair);
                priorityQueue.push(vNode.at(i));
                if(priorityQueue.size() > max_queue) {
                    max_queue = priorityQueue.size();
                }
            //}
            }
            /*else {
                cout << "Already Reached" << endl;
            }*/
        }
    }
    cout << "Failure: No solutions found after " << iter << " iterations" << endl;
    return nullptr;
}


int main(int argc, char *argv[]) {
    vector< vector<char> > initV;
    vector< vector<char> > goalV;
    string fname = argv[1];
    ifstream rFile;
    rFile.open(fname);
    string line;
    if(rFile.is_open()) {
        char c;
        getline(rFile, line);
        int num = stoi(line);
        //c = line[0];
        //int num = c-48;
        //cout << "Num=" << num << endl;
        //rFile.seekg(10);
        //rFile.ignore('\n');
        //rFile.ignore('\n');
        //getline(rFile, line);
        getline(rFile, line);
        //getline(rFile, line);
        //line = "";
        //cout << line << endl;
        for(int i = 0; i < num; i++) {
            getline(rFile, line);
            //cout << line << endl;
            vector<char> temp;
            for(int j = 0; j < line.length(); j++) {
                temp.push_back(line[j]);
            }
            initV.push_back(temp);
        }
        getline(rFile, line);
        for(int i = 0; i < num; i++) {
            getline(rFile, line);
            //cout << line << endl;
            vector<char> temp;
            for(int j = 0; j < line.length(); j++) {
                temp.push_back(line[j]);
            }
            goalV.push_back(temp);
        }
        /*for(int i = 0; i < goal.size(); i ++) {
            for(int j = 0; j < goal.at(i).size(); j++) {
                cout << goal.at(i).at(j);
            }
            cout << endl;
        }*/
    }
    //cout << line;
    //curr.insert(letter);
    State* init = new State(initV);
    //init->print();
    State* goal = new State(goalV);
    //cout << "init hash:" << endl;
    //cout << init->hash() << endl;
    //cout << "goal hash:" << endl;
    //cout << goal->hash() << endl;
    //init->print();
    //goal->print();
    init->successors();
    BFS(init, goal);
    //cout << "END" << endl;
}
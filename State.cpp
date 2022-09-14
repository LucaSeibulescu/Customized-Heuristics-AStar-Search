#include "State.h"

using namespace std;

State::State(vector< vector<char> > init) {
    for(int i = 0; i < init.size(); i++) {
        vector<char> temp;
        for(int j = 0; j < init.at(i).size(); j++) {
            temp.push_back(init.at(i).at(j));
        }
        curr.push_back(temp);
    }
}

void State::print() {
    for(int i = 0; i < curr.size(); i ++) {
        for(int j = 0; j < curr.at(i).size(); j++) {
            cout << curr.at(i).at(j);
        }
        cout << endl;
    }
}

bool State::match(State* goalState) {
    /*cout << "Bool: " << endl;
    cout << (curr == goalState->curr) << endl;
    for(int i = 0; i < curr.size(); i++) {
        if(curr.at(i) == goalState->curr.at(i)) {
            return true;
        }
    }
    return false;*/
    return curr == goalState->curr;
}

string State::hash() {
    string hashKey;
    for(int i = 0; i < curr.size(); i++) {
        for(int j = 0; j < curr.at(i).size(); j++) {
            hashKey +=  curr.at(i).at(j);
        }
        if(i != curr.size() - 1) {
            hashKey += ";";
        }
    }
    //cout << hashKey << endl;
    return hashKey;
}

vector<State*> State::successors() {
    vector<State*> children;
    for(int i = 0; i < curr.size(); i++) {
        vector< vector <char> > vTemp = curr;
        int k = i + 1;
        if(k == vTemp.size()) {
            k = 0;
        }
        char temp = ' ';
        if(vTemp.at(i).size() != 0) {
            temp = vTemp.at(i).at(vTemp.at(i).size() - 1);
        }
        else {
            continue;
        }    
        //cout << "vTemp size:" << vTemp.size() << endl;
        //cout << "second" << endl;
        for(int j = 0; j < vTemp.size() - 1; j++) {
            //cout << "first first" << endl;
            //cout << i << " " << k << endl;
            vTemp.at(k).push_back(temp);
            //cout << vTemp.at(k).at(vTemp.at(k).size() - 1);
            if(k != 0) {
                vTemp.at(k - 1).pop_back();
            }
            else {
                vTemp.at(vTemp.size() - 1).pop_back();
            }
            //cout << vTemp.at(1).size() << endl;
            State* sTemp = new State(vTemp);
            /*cout << "New Board: "  << j << endl;
            sTemp->print();
            cout << "Orig Board: " << endl;
            this->print();*/
            //cout << "Hello" << endl;
            children.push_back(sTemp);
            k++;
            if(k == vTemp.size()) {
                k = 0;
            }
            //cout << "last last" << endl;
        }
    }
    /*int k = 0;
    for(int i = 0; i < curr.size()*(curr.size()-1); i++) {
        if(k == curr.size()) {
            k = 0;
        }
        int j = k + 1;
        if(k == curr.size() - 1) {
            j = 0;
        }
        //cout << "Here" << endl;
        //cout << k << " " << j << endl;
        char temp = curr.at(k).at(curr.at(k).size() - 1);
        curr.at(j).push_back(temp);
        curr.at(k).pop_back();
        State* sTemp = new State(curr);
        children.push_back(sTemp);
        k++;
    }*/
    /*for(int i = 0; i < children.size(); i++) {
        //cout << children.size() << endl;
        children.at(i)->print();
    }*/
    //cout << "END Function" << endl;
    //cout << "Finished" << endl;
    return children;
}

float State::heuristic0(State& goal) {
    return 0;
}

void State::getBlockPos(char block, int& col, int& pos) {
    for(int i = 0; i < curr.size(); i++) {
        for(int j = 0; j < curr.at(i).size(); j++) {
            if(curr.at(i).at(j) == block) {
                col = i;
                pos = j;
            }
        }
    }
}

float State::heuristic1(State& goal) {
    float hScore = 0;
    for(int i = 0; i < curr.size(); i++) {
        for(int j = 0; j < curr.at(i).size(); j++) {
            int goalCol;
            int goalPos;
            char currChar = curr.at(i).at(j);
            goal.getBlockPos(currChar, goalCol, goalPos);
            if(i != goalCol || j != goalPos) {
                hScore += 1;
            }
        }
    }
    return hScore;
}

float State::heuristic2(State& goal) {
    float hScore = 0;
    for(int i = 0; i < curr.size(); i++) {
        for(int j = 0; j < curr.at(i).size(); j++) {
            int goalCol;
            int goalPos;
            char currChar = curr.at(i).at(j);
            goal.getBlockPos(currChar, goalCol, goalPos);
            if(i != goalCol || j != goalPos) {
                if((j != (curr.at(i).size() - 1))) {
                    hScore += abs(int(1 + (curr.at(i).size() - 1) - j));
                }
                if(i != goalCol) {
                    hScore += curr.at(goalCol).size();
                }
                if(curr.at(i).size() != goal.curr.size()) {
                    hScore += abs(int(curr.at(i).size() - goal.curr.size()));
                }
                /*if(j != 0 && goalPos != 0) {
                    if(curr.at(i).at(j - 1) == goal.curr.at(goalCol).at(goalPos - 1)) {
                        hScore += 4;
                    }
                }*/
                /*else {
                    hScore += abs(int(curr.at(goalCol).size() - goalPos));
                }*/
                /*if((curr.at(goalCol).size() - 1) > goalPos) {
                    hScore += (curr.at(goalCol).size() - 1) - goalPos;
                }
                if((curr.at(goalCol).size() - 1) < goalPos) {
                    hScore += goalPos - (curr.at(goalCol).size() - 1);
                }
                if(i != goalCol) {
                    hScore += 1;
                }
                if(j != goalPos) {
                    hScore += abs(int(j - goalPos));
                }
                hScore += 1;
                hScore += curr.at(goalCol).size();
                if(i == goalCol && j < goalPos) {
                    hScore += goalPos - j;
                }*/
            }
        }
    }
    return hScore;
}

float State::heuristic3(State& goal) {
    float hScore = 0;
    for(int i = 0; i < curr.size(); i++) {
        for(int j = 0; j < curr.at(i).size(); j++) {
            int goalCol;
            int goalPos;
            char currChar = curr.at(i).at(j);
            goal.getBlockPos(currChar, goalCol, goalPos);
            if(i != goalCol || j != goalPos) {
                if((j != (curr.at(i).size() - 1))) {
                    hScore += abs(int(1 + (curr.at(i).size() - 1) - j));
                }
            }
            for(int k = 0; k < curr.at(goalCol).size(); k++) {
                int newGoalCol;
                int newGoalPos;
                goal.getBlockPos(curr.at(goalCol).at(k), newGoalCol, newGoalPos);
                if(newGoalCol == goalCol && newGoalPos == k) {
                    continue;
                }
                else {
                    hScore += 2;
                }
            }
        }
    }
    return hScore;
}
#include <iostream>
#include <string>
#include <vector>
#include "Bowler.h"
using namespace std;

Bowler::Bowler() { //default constructor
    fname = "Elmo";
    lname = "Crispy";
    scores = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
}

Bowler::Bowler(string f, string l, vector<int> aScore) { // construct with given values
    fname = f;
    lname = l;
    scores = aScore;
}

string Bowler::getfName() const {
    return fname;
}

string Bowler::getlName() const {
    return lname;
}

vector<int> Bowler::getScores() const {
    return scores;
}

int Bowler::getFinalScore() {
    int total = 0;
        for (int l=0; l<scores.size(); l++) {
            if (scores[l] == 10) {
                if ((scores[l+1]+scores[l+2])==10) {
                    total += 20;
                    string o = to_string(total);
                    string s(3-o.size(),' ');
                    l++;
                } else {
                    total += (10+scores[l+1]);
                    string o = to_string(total);
                    string s(3-o.size(),' ');
                    l++;
                }
            } else if (scores[l]+scores[l+1]==10) {
                total += (10 + scores[l+2]);
                string o = to_string(total);
                string s(3-o.size(),' ');
                l++;
            } else {
                total += (scores[l]+scores[l+1]);
                string o = to_string(total);
                string s(3-o.size(),' ');
                l++;
            }
        }
    return total;
}

void Bowler::setfName(string f) {
    fname = f;
}

void Bowler::setlName(string l) {
    lname = l;
}

void Bowler::setScores(vector<int> s) {
    scores = s;
}
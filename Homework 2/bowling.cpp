#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Bowler.h"
using namespace std;

bool sort_bowlers(const Bowler& bowler1, const Bowler& bowler2) { // method sorts the bowlers when called in alphabetical order
    return bowler1.getlName() < bowler2.getfName() || (bowler1.getlName() == bowler2.getlName()
    && bowler1.getfName() < bowler2.getfName());
}

bool sort_scores(Bowler& bowler1, Bowler& bowler2) { // method sorts bowlers when called in order of their scores from largest to smallest
    return bowler2.getFinalScore() < bowler1.getFinalScore();
}

void standard (vector<Bowler> bowlers, ofstream & outputf) { // standard function that prints the bowling frames and ending score
    int size = 0;
    sort(bowlers.begin(), bowlers.end(), sort_bowlers);
    for (int i=0; i <bowlers.size(); i++) {
        int s = (bowlers[i].getfName()).size() + (bowlers[i].getlName()).size();
        if (s>size) {
            size = s;
        }
    }
    string boxline(size+4+63, '-');
    outputf << boxline << endl;
    for (int j=0; j<bowlers.size(); j++) {
        outputf << "| " << bowlers[j].getfName() << " " << bowlers[j].getlName();
        if (((bowlers[j].getfName()).size() + (bowlers[j].getlName()).size()) != size) {
            int sp = bowlers[j].getfName().size() + bowlers[j].getlName().size();
            string space(size-sp, ' ');
            outputf << space << " | ";
        } else {
            outputf << " | ";
        }
        vector<int> scores = bowlers[j].getScores(); // this for loop mainly works on outputting the scores into the table
        for (int k=0; k<scores.size(); k++) {
            if (k == scores.size()-1) {
                if (scores[k] == 0) {
                    outputf << "- ";
                } else {
                    outputf << scores[k] << " ";
                }
                if (scores[k+1] == 0) {
                    outputf << "  |";
                } else {
                    outputf << scores[k+1] << "  |";
                }
            } else {
                 if (scores[k]==0) {
                    outputf << "-" << " ";
                    if (k%2==1) {
                        outputf << "| ";
                    }
                else if(scores[k-1] ==10){
                    if (scores[k]+scores[k-1]==10 && k%2==1) {
                    outputf << "/" << " ";
                    if (k%2==1) {
                        outputf << "| ";
                    }
                    } else if (scores[k]!=10 && scores[k]!=0) {
                        outputf << scores[k] << " ";
                        if (k%2==1) {
                        outputf << "| ";
                    }
                    } else {
                    if (scores[k]==10) {
                        outputf << "  X" << " | ";
                    }
                    }
                }
                } else if (scores[k]+scores[k-1]==10 && k%2==1) {
                    outputf << "/" << " ";
                    if (k%2==1) {
                        outputf << "| ";
                    }
                } else if (scores[k]!=10 && scores[k]!=0) {
                    outputf << scores[k] << " ";
                    if (k%2==1) {
                        outputf << "| ";
                    }
                } else {
                    if (scores[k]==10) {
                        outputf << "  X" << " | ";
                    }
                }
            }
        }
        outputf << endl;
        int x = (bowlers[j].getfName()).size()+ (bowlers[j].getlName()).size();
        string filler((size-x)+x+1, ' ');
        outputf << "| " << filler << " |";
        int total = 0;
        for (int l=0; l<scores.size(); l++) { // this for loop works on creating the total score and outputing to the table
            if (l == scores.size()-2) {
                total += (scores[l]+scores[l+1]);
                string o = to_string(total);
                string s(5-o.size(),' ');
                outputf << " " << s << total << " |";
                l++;
            } else {
                if (scores[l] == 10) {
                    if (scores[l+1]==10){
                    if ((scores[l+1]+scores[l+2])==20) {
                        total += 30;
                        string o = to_string(total);
                        string s(3-o.size(),' ');
                        outputf << " " << s << total << " |";
                        l++;
                    } else if ((scores[l+1]+scores[l+2])==10) {
                        total += 20;
                        string o = to_string(total);
                        string s(3-o.size(),' ');
                        outputf << " " << s << total << " |";
                        l++;
                    } else {
                        total += (10+scores[l+1]);
                        string o = to_string(total);
                        string s(3-o.size(),' ');
                        outputf << " " << s << total << " |";
                        l++;
                    }}
                } else if (scores[l]+scores[l+1]==10) {
                        total += (10 + scores[l+2]);
                    string o = to_string(total);
                    string s(3-o.size(),' ');
                    outputf << " " << s << total << " |";
                    l++;
                } else {
                    total += (scores[l]+scores[l+1]);
                    string o = to_string(total);
                    string s(3-o.size(),' ');
                    outputf << " " << s << total << " |";
                    l++;
                }
            }
        }
        outputf << endl << boxline << endl;
    }
    outputf << endl;
    sort(bowlers.begin(), bowlers.end(), sort_scores);
    for (int i=0; i <bowlers.size(); i++) { // for loop controls the small table at the bottom with just the name and the final score
        int num = 0;
        int l = bowlers[i].getfName().size()+bowlers[i].getlName().size()+1;
        if (bowlers[i].getFinalScore() < 10) {
            num = 1;
        } else if (bowlers[i].getFinalScore() > 9 && bowlers[i].getFinalScore() < 100) {
            num = 2;
        } else {
            num = 3;
        }
        int s = 17-l-num;
        string space(s, ' ');
        string score = bowlers[i].getfName() + " " + bowlers[i].getlName() + space + to_string(bowlers[i].getFinalScore());
        outputf << score << endl;
    }
}

void parse_file(ifstream & inputf, vector<Bowler> & bowlers) { // parses the file and creates Bowler objects and stores the objects in a vector
    string f;
    string l;
    int x;
    vector<int> score;
    while(inputf >> f >> l) { 
        while(inputf >> x) {
            score.push_back(x);
        }
        bowlers.push_back(Bowler(f, l, score));
        inputf.clear();
        score.clear();
    }
    inputf.close();
}

int main(int argc, char* argv []) {
    ifstream inputf(argv[1]);
    ofstream outputf(argv[2]);
    string method = string(argv[3]);
    vector<Bowler> bowlers;
    parse_file(inputf, bowlers);

    if (!outputf.good()) {
        cerr << "ERROR: File not outputted correctly" << endl;
        exit(1);
    }
    if (argc < 4) { // Will not run correctly with more than 4 arguments
        cerr << "ERROR: Too many arguments" << endl;
        exit(1);
    }
    if (method == "standard") { // This if else statement makes sure that the right function is called
        standard(bowlers, outputf);
    } else {
        cerr << "ERROR: Undefined method call" << endl;
        exit(1);
    }  

}
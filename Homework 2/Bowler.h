#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Bowler {
public:
    Bowler();
    Bowler(string f, string l, vector<int> scores);

    // ACCESSORS
    string getfName() const;
    string getlName() const;
    vector<int> getScores() const;
    int getFinalScore();

    // MODIFIERS
    void setfName(string f);
    void setlName(string l);
    void setScores(vector<int> scores);
    
    private: // REPRESENTATION (member variables)
    string fname;
    string lname;
    vector<int> scores;
};
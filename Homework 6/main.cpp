#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "point.h"

std::vector<std::string> update_board(const std::vector<std::string>& board, const std::vector < std::vector<point> > letters) {
    // this function when called creates a new copy board, and updates points not in letters (a vector of points with valid letters)
    // into hashtags.
    std::vector<std::string> solved_boards = board;
    int count=0;
    for (int i=0; i<solved_boards.size(); i++) {
        for (int j=0; j<solved_boards[i].size(); j++) {
            for (int k=0; k<letters.size(); k++) {
                for (int l=0; l<letters[k].size(); l++){
                    point p(i, j);
                    if (p == letters[k][l]) { 
                        count=1; 
                    }
                }        
            }
            if (count == 0) { solved_boards[i][j]='#'; }
            count=0;
        }
    }
    return solved_boards;
}

bool find_word(point position, const std::vector<std::string>& board, const std::string& word, std::vector<point>& path) {
    // this function takes a point and recursively calls the function to try and find the point locations of the rest of the word
    // returns a bool, updates a vector with all the points for the given word
    path.push_back(position);
    if (path.size() == word.size()) { return true; }
    int i = position.getR();
    int j = position.getC();
    if ((i+1 < board.size()) && (j+1 < board[i].size())) { // make sure we are not outside of the board size
        if (word[path.size()] == board[i+1][j]) {
            find_word(point((i+1),j),board,word,path);
            return true;
        } else if (word[path.size()] == board[i][j+1]) {
            find_word(point(i,(j+1)),board,word,path);
            return true;
        } else {
            path.pop_back();
            return false;
        }
    } else if (j+1 < board[i].size()) {
        if (word[path.size()] == board[i][j+1]) {
            find_word(point(i,(j+1)),board,word,path);
            return true;
        } else {
            path.pop_back();
            return false;
        }
    } else if (i+1 < board.size()) {
        if (word[path.size()] == board[i+1][j]) {
            find_word(point((i+1),j),board,word,path);
            return true;
        } else {
            path.pop_back();
            return false;
        }
    } else {
        path.pop_back();
        return false;
    }
}



std::vector<std::vector <point> > solve(std::vector<std::string> board, std::vector<std::vector <std::string> > & solutions, int num) {
    // goes through the board and finds the words in a give solution set, 
    // returns a vector of all of the words vector points.
    // num serves as which solution we are finding
    std::vector<std::vector <point> > letters;
    int count = solutions[num].size();
    for (int i=0; i<board.size(); i++) {
        for (int j=0; j<board[i].size(); j++) {
            for (int k=0; k<solutions[num].size(); k++) {
                if (count!=0) { // serves to make sure that we are finding the right amount of words
                    if (board[i][j] == solutions[num][k][0]) {
                        std::vector<point> path;
                        std::string word = solutions[num][k];
                        bool res = find_word(point(i,j),board,word,path);                     
                        if (res) {
                            letters.push_back(path);
                            count--;
                        }  
                    }
                } 
            }
        }
    }
    return letters;
}

bool sort_dict(const std::string a, const std::string b) { // sorts dictionary by size
   return a.size() < b.size();
}

bool findValidSolutions(std::vector<std::string> & b, std::vector<int> & constraints, std::vector<std::string> dictionary, std::vector<std::vector <point> > & letters, int num) {
    // this functions verifies that only the amount of constraints is in the solved board
    // returns a bool to indicate whether the board should be printed or not
    int count = 0;
    int c = constraints.size();
    for (int j=0; j<b.size(); j++) {
        for (int k=0; k<b[j].size(); k++) {
            for (int l=0; l<dictionary.size(); l++) {
                if (b[j][k] == dictionary[l][0]) {
                    std::vector<point> path;
                    std::string word = dictionary[l];
                    bool res = find_word(point(j,k),b,word,path);
                    if (res == true) {
                        count++;
                    }
                }
            }
        }
    }
    if (count==c) {
        return true;
    } else {
        return false;
    }
}

void findSolutions(std::vector<int> & constraints, std::vector<std::string> & dictionary, std::vector<std::vector <std::string> > & solutions) {
   // finds the amount of solutions given the constraints and dictionary
   // counts the amount of constraints with the same number and counts the number of words with the length of the current constraint
   // if the counts match - then all of those size words can be added
   // else delete the word from the copy dictionary and pass it along to a recursive call
   std::vector<std::string> s;
   std::vector<std::string> d = dictionary;
   if (d.size() < constraints.size()) {
       return;
   }
   int count = 0;
   int dict = 0;
   int check = 0;
   for (std::vector<std::string>::iterator i = d.begin(); i!=d.end(); i++) {
       int x = constraints[count];
       int count1=0;
       int count2=0;
       for (int j=0; j<constraints.size(); j++) {
           if (constraints[j]==x) { count1++; }
       } 
       for (int k=0; k<d.size(); k++)  {
           if (d[k].size()==x) { count2++; }
       }
       if (x != d[dict].size()) {
           dict++;
       } else if ((x == d[dict].size()) && (count1 == count2)) {
           s.push_back(d[dict]);
           count++;
           dict++;
       } else if ((x == d[dict].size()) && (count1 != count2)) {
           s.push_back(d[dict]);
           count++;
           dict++;
           i=d.erase(i);
           check = 1;
       } 
   }
   solutions.push_back(s);
   if (check==1) {
       findSolutions(constraints, d, solutions);
   }    
}   

void parseGrid(std::vector<std::string> & board, std::vector<int> & constraints, std::ifstream & input){
    std::string line;
    while(input>>line){
        if(line[0]=='+'){
            constraints.push_back(std::stoi(line));
        }
        else if(line[0]!='!'){
            board.push_back(line);
        }
    }
    input.close();
}

void parseDict(std::vector<std::string> & dictionary, std::ifstream & input) {
    std::string word;
    while(input>>word){
        dictionary.push_back(word);
    }
    input.close();
}

int main(int argc, char* argv []) {
    if (argc < 4) { // Will not run correctly with less than 4 arguments
        std::cerr << "ERROR: Not enough arguments" << std::endl;
        exit(1);
    }

    std::ifstream dict(argv[1]);
    std::ifstream _board(argv[2]);
    std::string solutionmode = std::string(argv[3]);
    std::string outputmode = std::string(argv[4]);
    std::vector<std::string> board;
    std::vector<std::string> dictionary;
    std::vector<int> constraints;
    std::vector<std::vector <std::string> > solutions;
    parseDict(dictionary, dict);
    parseGrid(board, constraints, _board);
    std::sort (constraints.begin(), constraints.end());
    std::sort (dictionary.begin(), dictionary.end(), sort_dict);
    findSolutions(constraints, dictionary, solutions);
    if (solutionmode == "one_solution" && outputmode == "count_only") { // This if else statement makes sure that the right function is called
        int count=0;
        for (int i=0; i<solutions.size(); i++) {
            std::vector < std::vector<point> > letters = solve(board, solutions, i);
            std::vector<std::string> b = update_board(board, letters);
            bool res = findValidSolutions(b, constraints, dictionary, letters, i);
            if (res == true) {
                count++;
            }
        }
        if (count>=1) {
            std::cout << "Number of solution(s): 1" << std::endl;
        } else {
            std::cout << "Number of solution(s): " << count << std::endl;
        }
    } else if (solutionmode == "all_solutions" && outputmode == "count_only") {
        int count=0;
        for (int i=0; i<solutions.size(); i++) {
            std::vector < std::vector<point> > letters = solve(board, solutions, i);
            std::vector<std::string> b = update_board(board, letters);
            bool res = findValidSolutions(b, constraints, dictionary, letters, i);
            if (res == true) {
                count++;
            }
        }
        std::cout << "Number of solution(s): " << count << std::endl;
    } else if (solutionmode == "one_solution" && outputmode == "print_boards") {
        std::vector<std::string> output;
        int count=0;
        for (int i=0; i<solutions.size(); i++) {
            std::vector < std::vector<point> > letters = solve(board, solutions, i);
            std::vector<std::string> b = update_board(board, letters);
            bool res = findValidSolutions(b, constraints, dictionary, letters, i);
            if (res == true) {
                count++;
                output.push_back("Board:");
                for (int j=0; j<b.size(); j++) {
                    output.push_back(b[j]);
                }
                break;
            }
        }
        std::cout << "Number of solution(s): " << count << std::endl;
        for (int i=0; i<output.size(); i++) {
            std::cout << output[i] << std::endl;
        }
    } else if ((solutionmode == "all_solutions" && outputmode == "print_boards")) {
        std::vector<std::string> output;
        int count=0;
        for (int i=0; i<solutions.size(); i++) {
            std::vector < std::vector<point> > letters = solve(board, solutions, i);
            std::vector<std::string> b = update_board(board, letters);
            bool res = findValidSolutions(b, constraints, dictionary, letters, i);
            if (res == true) {
                count++;
                output.push_back("Board:");
                for (int j=0; j<b.size(); j++) {
                    output.push_back(b[j]);
                }
            }
        }
        std::cout << "Number of solution(s): " << count << std::endl;
        for (int i=0; i<output.size(); i++) {
            std::cout << output[i] << std::endl;
        }
    } else {
        std::cerr << "ERROR: Undefined solution mode call" << std::endl;
        exit(1);
    }
}
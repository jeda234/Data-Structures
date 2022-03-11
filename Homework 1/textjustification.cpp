#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

void parse_word(vector<string> & output, ifstream & inputf){ // method use to seperate the file words into a vector
    string word;
    while(inputf >> word) {
        output.push_back(word);
    }
    inputf.close();
}

void flush_left(vector<string> text, int width, ofstream & outputf) {
    /* This function works to put all the words flushed to the left

       There is an initial for loop that runs through all of the words in a vector. Within multiple
       if statements, the code is analyzing if the word can fit in the box with the given width, and 
       updating the width in a variable by subtracting one more than the length of the word. The words
       that can fit in the box are put into a vector.

       Next, the else statment handles putting the words into the box and putting the correct amount of
       spaces after the words. This else statement also handles putting the "width" variable back to the 
       original width and clearing the vector that stores the designated words for the line.
     */
    vector<string> list; // vector of words to add after spaces are accounted for
    int number = width; // number to help keep track of space left on the line in the box
    string boxline(width+4, '-');
    outputf << boxline << endl;
    for (int i=0; i<text.size(); i++){
        if (text[i].size() <= number) { // gets all of the words that fit into the line
            if (i != (text.size()-1)) { // this if statements allows for the last word to be added
                list.push_back(text[i]);
                if (text[i].size() == number) { // if statement makes sure that number does not go below 0
                    number = number - text[i].size();
                } else {
                    number = number - text[i].size()-1;
                }
            } else {
                number = number - text[i].size();
                string emptyspace(number, ' '); 
                outputf << "| " << text[i] << emptyspace<< " |" << endl;
            }
        } else { // adds the words to the line with the additional spaces and makes a new line
            if (number != 0) { // if number does not equal 0, then spaces should be added according to the method
                string emptyspace(number, ' '); 
                outputf << "| ";
                for (int j=0; j<list.size(); j++) { // for loop to add the words that will fit in the box
                    outputf << list[j] << " ";
                }
                outputf << emptyspace << " |" << endl;
                list.clear();
                number = width;
                i--;
            } else { // spaces are added like a normal sentence -> everything fit perfectly
                outputf << "| ";
                for (int j=0; j<list.size(); j++) { // for loop to add the words that will fit in the box
                    if (j==(list.size()-1)) {
                        outputf << list[j] << " ";
                    } else {
                        outputf << list[j] << " ";
                    }  
                }
                outputf << " |" << endl;
                list.clear();
                number = width;
                i--;
            }
       }
    }
    outputf << boxline << endl; 
}

void flush_right(vector<string> text, int width, ofstream & outputf) {
    /* This function works to put all the words flushed to the right

       There is an initial for loop that runs through all of the words in a vector. Within multiple
       if statements, the code is analyzing if the word can fit in the box with the given width, and 
       updating the width in a variable by subtracting one more than the length of the word. The words
       that can fit in the box are put into a vector.

       Next, the else statment handles putting the words into the box and putting the correct amount of
       spaces in front of the words. This else statement also handles putting the "width" variable back 
       to the original width and clearing the vector that stores the designated words for the line. 
     */
    vector<string> list; // vector of words to add after spaces are accounted for
    unsigned int number = width; // number to help keep track of space left on the line in the box
    string boxline(width+4, '-');
    outputf << boxline << endl;
    for (int i=0; i<text.size(); i++){
        if (text[i].size() <= number) { // gets all of the words that fit into the line
            if (i == (text.size()-1)) { // this if statements allows for the last word to be added
                number = number - text[i].size() - 1;
                string emptyspace(number, ' '); 
                outputf << "| " << emptyspace;
                outputf << " " << text[i] << " |" << endl;
            } else {
                list.push_back(text[i]);
                if (text[i].size() == number) { // if statement makes sure that number does not go below 0
                    number = number - text[i].size();
                } else {
                    number = number - text[i].size()-1;
                }
            }
        } else { // adds the words to the line with the additional spaces and makes a new line
             if (number != 0) { // if number does not equal 0, then spaces should be added according to the method
                string emptyspace(number, ' '); 
                outputf << "| " << emptyspace;
                for (int j=0; j<list.size(); j++) { // for loop to add the words that will fit in the box
                    outputf << " " << list[j];
                }
            } else { // spaces are added like a normal sentence -> everything fit perfectly
                outputf << "| ";
                for (int j=0; j<list.size(); j++) { // for loop to add the words that will fit in the box
                    if (j!=(list.size()-1)) {
                        outputf  << " " << list[j];
                    } else {
                        outputf << " " << list[j] ;
                    }  
                } 
            }
            outputf << " |" << endl;
            list.clear();
            number = width;
            i--;
       }  
    }
    outputf << boxline << endl; 
}

void full_justify(vector<string> text, int width, ofstream & outputf) {
    /* This function works to put all the words full justified

       There is an initial for loop that runs through all of the words in a vector. Within multiple
       if statements, the code is analyzing if the word can fit in the box with the given width, and 
       updating the width in a variable by subtracting one more than the length of the word. The words
       that can fit in the box are put into a vector.

       Next, the else statment handles putting the words into the box and putting the correct amount of
       spaces in between the words. This else statement also handles putting the "width" variable back 
       to the original width and clearing the vector that stores the designated words for the line. 

       P.S. I tried every possible way to make this function and I can not seem to understand where I 
       went wrong. I tried to disperse the remainder amount of spaces between the words but it would not
       work right, so I just put them after the first word.
     */
    string words;
    vector<string> list; // vector of words to add after spaces are accounted for
    unsigned int number = width; // number to help keep track of space left on the line in the box
    string boxline(width+4, '-');
    outputf << boxline << endl;
    for (int i=0; i<text.size(); i++){
        if (text[i].size() <= number) { // gets all of the words that fit into the line
            if (i == (text.size()-1)) { // this if statements allows for the last word to be added
                number = number - text[i].size()-1;
                string emptyspace(number, ' '); 
                outputf << "| ";
                outputf << text[i] << " " << emptyspace << " |" << endl;
            } else {
                list.push_back(text[i]);
                if (text[i].size() == number) { // if statements makes sure that number does not go below 0
                    number = number - text[i].size();
                } else {
                    number = number - text[i].size()-1;
                }
            }
        } else { // adds the words to the line with the additional spaces and makes a new line
            if (number != 0) { // if number does not equal 0, then spaces should be added according to the method
                 outputf << "| ";
                for (int j=0; j<list.size(); j++) { // for loop to add the words that will fit in the box
                    if (number%list.size()!=0 && j==0) {
                        string space((number/list.size()+(number%list.size())), ' ');
                        outputf << list[j] << " " << space;
                    } else { // spaces are added like a normal sentence -> everything fit perfectly
                        if (j != list.size()-1) {
                            string space(number/list.size(), ' ');
                            outputf << list[j] << " " << space;
                        } else {
                            string space(number/list.size(), ' ');
                            outputf << " " << space << list[j] ;
                        }
                    }  
                }
            } else { 
                outputf << "| ";
                for (int j=0; j<list.size(); j++) { // for loop to add the words that will fit in the box
                    if (j!=(list.size()-1)) {
                        outputf << list[j] << " ";
                    } else {
                        outputf << list[j];
                    }  
                }
            }
        outputf << " |" << endl;
        list.clear();
        number = width;
        i--;
        }
    }
    outputf << boxline << endl;; 
}  

int main(int argc, char* argv []) {
    vector<string> words;
    int width = atoi(argv[3]);
    ifstream inputf(argv[1]);
    ofstream outputf(argv[2]);
    string method = string(argv[4]);
    parse_word(words, inputf); // this call seperates the words from the document and puts it into a vector

    if (width < 2) { // Makes sure that there is a valid width
        cerr << "ERROR: Not a valid width" << endl;
        exit(1);
    }
    /*if (!inputf.good()) {
        cerr << "ERROR: File not opened correctly" << endl; // without this commented out it gave me an error :(
        exit(1);
    }
    */
    if (!outputf.good()) {
        cerr << "ERROR: File not outputted correctly" << endl;
        exit(1);
    }
    if (argc < 5) { // Will not run correctly with more than 5 arguments
        cerr << "ERROR: Too many arguments" << endl;
        exit(1);
    }
    if (method == "flush_left") { // This if else statement makes sure that the right function is called
        flush_left(words, width, outputf);
    } else if (method == "flush_right") {
        flush_right(words, width, outputf);
    } else if (method == "full_justify") {
        full_justify(words, width, outputf);
    } else {
        cerr << "ERROR: Undefined method call" << endl;
        exit(1);
    }  
}

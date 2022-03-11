#ifndef __DVD_h_
#define __DVD_h_
#include <string>
#include <list>
#include <iostream>
using namespace std;

class DVD {
public:
    DVD(string t, int c);

    // ACCESSORS
    string getTitle() const;
    int getTotalCopies() const;
    unsigned int getCopiesAvailable() const;
    unsigned int getNumRented() const;
    bool available();

    // MODIFIERS
    void setTitle(string t);
    void setNumCopies(int c);
    void setNumAvailable(int a);
    void setNumRented(int r);
    void shipped();

private:
    string title;
    int num_copies;
    unsigned int num_available;
    unsigned int num_rented;
};
#endif
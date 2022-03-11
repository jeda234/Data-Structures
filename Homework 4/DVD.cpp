#include <iostream>
#include <string>
#include "DVD.h"
using namespace std;

DVD::DVD(string t, int c) { // construct with given values
    title = t;
    num_copies = c;
    num_available = c;
    num_rented = 0;
}

string DVD::getTitle() const {
    return title;
}

int DVD::getTotalCopies() const {
    return num_copies;
}

unsigned int DVD::getCopiesAvailable() const {
    return num_available;
}

unsigned int DVD::getNumRented() const {
    return num_rented;
}

bool DVD::available() {
    return(getCopiesAvailable()>=1);
}

void DVD::setTitle(string t) {
    title = t;
}

void DVD::setNumCopies(int c) {
    num_copies = c;
}

void DVD::setNumAvailable(int a) {
    num_available = a;
}

void DVD::setNumRented(int r) {
    num_rented = r;
}

void DVD::shipped() {
    setNumAvailable(num_available-1);
    setNumRented(num_rented+1);
}
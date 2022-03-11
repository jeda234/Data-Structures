#include <iostream>
#include <string>
#include "customer.h"
using namespace std;

Customer::Customer(string n, int num, list<string> p) { // construct with given values
    name = n;
    num_movies = num;
    pref = p;
}

string Customer::getName() const {
    return name;
}

int Customer::getLengthMovieList() const {
    return movie_list.size();
}

int Customer::getPrefLength() const {
    return pref.size();
}
    
string Customer::getMovieList(int num) const {
    int count=0;
    for (list<string>::const_iterator string_itr = movie_list.begin(); string_itr != movie_list.end(); string_itr++) {
        if (count == num) {
            return *string_itr;
        }
    count++;
    } 
    return "";
}

string Customer::getPref(int num) const {
    int count=0;
    for (list<string>::const_iterator string_itr = pref.begin(); string_itr != pref.end(); string_itr++) {
        if (count == num) {
            return *string_itr;
        }
    count++;
    } 
    return "";
}

bool Customer::has_max_num_movies() const {
    return(getLengthMovieList()==3);
}

bool Customer::preference_list_empty() const {
    return(getPrefLength()==0);
}

list<string> Customer::get_preferences() const {
    return pref;
}

void Customer::setName(string n) {
    name = n;
}

void Customer::setNumMovies(int num) {
    num_movies = num;
}

void Customer::add_preference(string movie_title) {
    pref.push_back(movie_title);
}

void Customer::receives(string p) {
    movie_list.push_back(p);
    for (list<string>::const_iterator string_itr = pref.begin(); string_itr != pref.end(); string_itr++) {
        if (*string_itr == p) {
            string_itr = pref.erase(string_itr);
        }
    } 
}

void Customer::remove_returned(string m) {
    for (list<string>::const_iterator string_itr = movie_list.begin(); string_itr != movie_list.end(); string_itr++) {
        if (*string_itr == m) {
            string_itr = movie_list.erase(string_itr);
        }
    } 
}

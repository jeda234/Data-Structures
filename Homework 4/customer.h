#ifndef __customer_h_
#define __customer_h_
#include <string>
#include <list>
#include <iostream>
#include "DVD.h"
using namespace std;

class Customer {
public:
    Customer(string n, int num, list<string> p);

    // ACCESSORS
    string getName() const;
    string getMovieList(int num) const;
    int getLengthMovieList() const;
    int getPrefLength() const;
    list<string> get_preferences() const;
    string getPref(int num) const;
    bool has_max_num_movies() const;
    bool preference_list_empty() const;

    // MODIFIERS
    void setName(string n);
    void setNumMovies(int num);
    void add_preference(string movie_title);
    void receives(string p);
    void remove_returned(string m);

private:
    string name;
    int num_movies;
    list<string> movie_list;
    list<string> pref;
};
#endif
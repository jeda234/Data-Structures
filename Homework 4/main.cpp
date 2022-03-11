// ==================================================================
// Important Note: You are encouraged to read through this provided
//   code carefully and follow this structure.  You may modify the
//   file as needed to complete your implementation.
// ==================================================================

#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <cassert>
#include "customer.h"

// several type defs to keep things neat
// (hint, these are STL lists)
typedef std::list<DVD> inventory_type;
typedef std::list<Customer> customers_type;
typedef std::list<std::string> preference_type;

// ==================================================================

// Helper function prototypes
std::string read_customer_name(std::istream &istr);
std::string read_dvd_name(std::istream &istr);
inventory_type::iterator find_DVD(inventory_type &inventory, const std::string &dvd_name);
customers_type::iterator find_Customer(customers_type &customers, const std::string &customer_name);

// The main algorithm for DVD distribution
void shipping_algorithm(inventory_type &inventory, customers_type &customers, std::ostream &ostr);

// ==================================================================
void usage(const char* program_name) {
  std::cerr << "Usage: " << program_name << " <input_file> <output_file>" << std::endl;
  std::cerr << " -or-  " << program_name << " <input_file> <output_file> --analysis" << std::endl;
  std::cerr << " -or-  " << program_name << " <input_file> <output_file> --improved" << std::endl;
  std::cerr << " -or-  " << program_name << " <input_file> <output_file> --improved --analysis" << std::endl;
  exit(1);
}

int main(int argc, char* argv[]) {

  if (argc < 3 || argc > 5) {
    usage(argv[0]);
  }

  // open input and output file streams
  std::ifstream istr(argv[1]);
  if (!istr) {
    std::cerr << "ERROR: Could not open " << argv[1] << " for reading." << std::endl;
    usage(argv[0]); 
  }
  std::ofstream ostr(argv[2]);
  if (!ostr) {
    std::cerr << "ERROR: Could not open " << argv[2] << " for writing." << std::endl;
    usage(argv[0]); 
  }

  // optional parameters for extra credit
  bool use_improved_algorithm = false;
  bool print_analysis = false;
  for (int i = 3; i < argc; i++) {
    if (std::string(argv[i]) == "--improved") {
      use_improved_algorithm = true;
    } else if (std::string(argv[i]) == "--analysis") {
      print_analysis = true;
    } else {
      usage(argv[0]);
    }
  }

  // stores information about the DVDs
  inventory_type inventory;
  // stores information about the customers
  customers_type customers;

  // read in and handle each of the 8 keyword tokens
  std::string token;
  while (istr >> token) {
    if (token == "dvd") {
      std::string dvd_name = read_dvd_name(istr);
      int copies;
      istr >> copies; 
      if (find_DVD(inventory, dvd_name) == inventory.end()) {  
        DVD d(dvd_name, copies);
        inventory.push_back(d);
        ostr << copies;
        if (copies > 1) {
          ostr << " copies of " << dvd_name << " added" << std::endl;
        } else {
          ostr << " copy of " << dvd_name << " added" << std::endl;
        } 
      } else {
        inventory_type::iterator e = find_DVD(inventory, dvd_name);
        e->setNumCopies(e->getTotalCopies()+copies);
        ostr << copies;
        if (copies > 1) {
          ostr << " copies of " << dvd_name << " added" << std::endl;
        } else {
          ostr << " copy of " << dvd_name << " added" << std::endl;
        } 
      }
    } else if (token == "customer") { // check movies not in dvd list and duplicates
      std::string customer_name = read_customer_name(istr);
      int num_movies;
      istr >> num_movies;
      std::list<std::string> pref;
      if (find_Customer(customers, customer_name) == customers.end()) {
        for (int i = 0; i < num_movies; i++) {
          std::string dvd_name = read_dvd_name(istr);
          if (find_DVD(inventory, dvd_name) == inventory.end()) {
            ostr << "WARNING: No movie named " << dvd_name << " in the inventory" << std::endl;
          } else {
             pref.push_back(dvd_name);
            }
          }
          for (preference_type::const_iterator pref_itr = pref.begin(); pref_itr != pref.end(); pref_itr++) { 
            std::string dup=*pref_itr; // checking for duplicates in loop and deleting the second occurence
            int d = count(pref.begin(), pref.end(), *pref_itr);
            if (d>1) {
              ostr << "WARNING: Duplicate movie " << *pref_itr << " on preference list!" << std::endl;
              int count=0;
              for (preference_type::const_iterator pref_itr = pref.begin(); pref_itr != pref.end(); pref_itr++) {
                if (*pref_itr==dup) {
                  count++;
                  if (count==2) {
                    pref_itr = pref.erase(pref_itr);
                  }
                }
              }
            }
          }
        Customer c(customer_name, num_movies, pref); // creating customer class
        customers.push_back(c);
        ostr << "new customer: " << customer_name << std::endl;
      } else {
        ostr << "WARNING: Already have a customer named " << customer_name << std::endl;
        for (int i = 0; i < num_movies; i++) {
          std::string dvd_name = read_dvd_name(istr);
        }
      }
    } else if (token == "ship") {
      shipping_algorithm(inventory,customers,ostr);
    } else if (token == "return_oldest") {
      std::string customer_name = read_customer_name(istr);
      if (find_Customer(customers, customer_name) == customers.end()) {
        ostr << "WARNING: No customer name " << customer_name << std::endl;
      } else {
        customers_type::iterator c = find_Customer(customers, customer_name);
        int l = c->getLengthMovieList();
        if (l == 0) { // error checking
          ostr << "WARNING: " << customer_name << " has no DVDs to return!" << std::endl;
        } else {
          std::string m = c->getMovieList(0);
          ostr << customer_name << " returns " << m << std::endl;
          inventory_type::iterator e = find_DVD(inventory, m);
          c->remove_returned(m);
          int x = e->getNumRented(); // updating copies of DVDs rented and available
          int y = e->getCopiesAvailable();
          e->setNumRented(x-1);
          e->setNumAvailable(y+1);
        }
      }
    } else if (token == "return_newest") {
      std::string customer_name = read_customer_name(istr);
      if (find_Customer(customers, customer_name) == customers.end()) {
        ostr << "WARNING: No customer name " << customer_name << std::endl;
      } else {
        customers_type::iterator c = find_Customer(customers, customer_name); 
        int l = c->getLengthMovieList();
        if (l == 0) { // error checking
          ostr << "WARNING: " << customer_name << " has no DVDs to return!" << std::endl;
        } else {
          std::string m = c->getMovieList(l-1);
          ostr << customer_name << " returns " << m << std::endl;
          inventory_type::iterator e = find_DVD(inventory, m);
          c->remove_returned(m);
          int x = e->getNumRented(); // updating copies of DVDs rented and available
          int y = e->getCopiesAvailable();
          e->setNumRented(x-1);
          e->setNumAvailable(y+1);
        }
      }
    } else if (token == "print_customer") {
      std::string customer_name = read_customer_name(istr);
      if (find_Customer(customers, customer_name) == customers.end()) {
        ostr << "WARNING: No customer name " << customer_name <<  std::endl;
      } else {
        customers_type::iterator c = find_Customer(customers, customer_name);
        ostr << customer_name;
        int l = c->getLengthMovieList(); // after this line, starts with formatting print info for customers
        if (l>1) {
          ostr << " has " << l << " movies:" << std::endl;
          for (int i=0; i<l; i++) {
            ostr << "    " << c->getMovieList(i) << std::endl;
          }
          if (c->preference_list_empty()) {
            continue;
          } else {
            ostr << "  preference list:" << std::endl;
            int pl = c->getPrefLength();
            for (int j=0; j<pl; j++) {
              if (c->getPref(j) == c->getPref(j+1)) { // preference length is never updated, so this is to stop from repetition
                continue;
              } else {
                ostr << "    " << c->getPref(j) << std::endl;
              }
            }
          }
        } else if (l==1) {
          ostr << " has 1 movie" << std::endl;
          ostr << "    " << c->getMovieList(0) << std::endl;
          if (c->preference_list_empty()) {
            continue;
          } else {
            ostr << "  preference list:" << std::endl;
            int pl = c->getPrefLength();
            for (int j=0; j<pl; j++) {
              if (c->getPref(j) == c->getPref(j+1)) { // preference length is never updated, so this is to stop from repetition
                continue;
              } else {
                ostr << "    " << c->getPref(j) << std::endl;
              }
            }
          }
        } else {
          ostr << " has no movies" << std::endl;
          ostr << "  preference list:" << std::endl;
          int pl = c->getPrefLength();
          for (int j=0; j<pl; j++) {
            ostr << "    " << c->getPref(j) << std::endl;
          }
        }
      }
    } else if (token == "print_dvd") {
      std::string dvd_name = read_dvd_name(istr);
      if (find_DVD(inventory, dvd_name) == inventory.end()) {
        ostr << "WARNING: No movie named " << dvd_name << " in the inventory" << std::endl;
      } else {
        inventory_type::iterator e = find_DVD(inventory, dvd_name);
        ostr << dvd_name << ":" << std::endl;
        if (e->getNumRented()>1 && e->getCopiesAvailable()>1) { // formatting the output for different scenarios
          ostr << "  " << e->getNumRented() << " copies checked out and ";
          ostr << e->getCopiesAvailable() << " copies available" << std::endl;
        } else if (e->getNumRented()>1 && e->getCopiesAvailable()==0) {
          ostr << "  " << e->getNumRented() << " copies checked out" << std::endl;
        } else if (e->getNumRented()==0 && e->getCopiesAvailable()>1){
          ostr << "  " << e->getCopiesAvailable() << " copies available" << std::endl;
        } else if (e->getNumRented()==1 && e->getCopiesAvailable()>1) {
          ostr << "  " << e->getNumRented() << " copy checked out and ";
          ostr << e->getCopiesAvailable() << " copies available" << std::endl;
        } else if (e->getNumRented()==1 && e->getCopiesAvailable()==1) {
          ostr << "  " << e->getNumRented() << " copy checked out and ";
          ostr << e->getCopiesAvailable() << " copy available" << std::endl;
        } else if (e->getNumRented()==1 && e->getCopiesAvailable()==0) {
          ostr << "  " << e->getNumRented() << " copy checked out" << std::endl;
        } else if (e->getNumRented()==0 && e->getCopiesAvailable()==1) {
          ostr << e->getCopiesAvailable() << "copy checked out" << std::endl;
        } else {
          ostr << "  " << e->getNumRented() << " copies checked out and ";
          ostr << e->getCopiesAvailable() << " copies available" << std::endl;
        }
      }
    } else if (token == "add_preference") { 
      std::string customer_name = read_customer_name(istr);
      std::string dvd_name = read_dvd_name(istr);
      if (find_DVD(inventory, dvd_name) == inventory.end()) { // error checking pt1
          ostr << "WARNING: No movie named " << dvd_name << " in the inventory" <<std::endl;
      } else {
        if (find_Customer(customers, customer_name) == customers.end()) { // error checking pt2
          ostr << "WARNING: No customer name " << customer_name << std::endl;
        } else {
          customers_type::iterator c = find_Customer(customers, customer_name);
          std::list<std::string> pref = c->get_preferences();
          for (preference_type::const_iterator pref_itr = pref.begin(); pref_itr != pref.end(); pref_itr++) {
            if (*pref_itr != dvd_name) { // check to see if preference is already there
              c->add_preference(dvd_name);
            } else {
              ostr << "WARNING: " << customer_name << " already has " << dvd_name << " on his/her preference list!" << std::endl;
            }
          }
        }
      }
      
    } else {
      std::cerr << "ERROR: Unknown token " << token << std::endl;
      exit(1);
    }
  }
}

// ==================================================================
// A customer name is simply two strings, first & last name
std::string read_customer_name(std::istream &istr) {
  std::string first, last;
  istr >> first >> last;
  return first + " " + last;
}

// A movie name is one or more strings inside of double quotes
std::string read_dvd_name(std::istream &istr) {
  std::string token;
  istr >> token;
  assert (token[0] == '"');
  std::string answer = token;
  while (answer[answer.size()-1] != '"') {
    istr >> token;
    answer += " " + token;
  }
  return answer;
}

// A helper function to find a DVD from the inventory
inventory_type::iterator find_DVD(inventory_type &inventory, const std::string &dvd_name) {
  for (inventory_type::iterator inventory_itr = inventory.begin(); 
       inventory_itr != inventory.end(); inventory_itr++) {
    if (inventory_itr->getTitle() == dvd_name) {
      return inventory_itr;
    }
  }
  // if the DVD is not found, return the .end() iterator
  return inventory.end();
}

// A helper function to find a certain customer from the customers list
customers_type::iterator find_Customer(customers_type &customers, const std::string &customer_name) { // same implementation as find_DVD
  for (customers_type::iterator customer_itr = customers.begin(); 
       customer_itr != customers.end(); customer_itr++) {
    if (customer_itr->getName() == customer_name) {
      return customer_itr;
    }
  }
  // if the Customer is not found, return the .end() iterator
  return customers.end();
}

// ==================================================================

//
// A basic algorithm for determining which movies to ship to each customer
//
void shipping_algorithm(inventory_type &inventory, customers_type &customers, std::ostream &ostr) {

  ostr << "Ship DVDs" << std::endl;

  // Loop over the customers in priority order
  //
  // Note that we edit the customers list as we go, to add customers
  // to the back of the list if they receive a DVD.  This allows a
  // customer to receive multiple DVDs in one shipment cycle, but only
  // after all other customers have had a chance to receive DVDs.
  //
  customers_type::iterator customer_itr = customers.begin();
  while (customer_itr != customers.end()) {

    // skip this customer if they already have 3 movies or if their
    // preference list is empty (no outstanding requests)
    if (customer_itr->has_max_num_movies() || customer_itr->preference_list_empty()) {
      // move on to the next customer
      customer_itr++;
      continue;
    }

    // a helper flag variable
    bool sent_dvd = false;
 
    // loop over the customer's preferences
    const preference_type &preferences = customer_itr->get_preferences();
    for (preference_type::const_iterator preferences_itr = preferences.begin(); 
         preferences_itr != preferences.end(); preferences_itr++) {

      // locate this DVD in the inventory
      inventory_type::iterator inventory_itr = find_DVD(inventory,*preferences_itr);
      if (inventory_itr != inventory.end() && inventory_itr->available()) { 

        // if the DVD is available, ship it to the customer!
        ostr << "  " << customer_itr->getName() << " receives " << *preferences_itr << std::endl;
        inventory_itr->shipped();
        customer_itr->receives(*preferences_itr);
        
        // move this customer to the back of the priority queue
        // they will get a chance to receive another DVD, but only
        // after everyone else gets a chance
        customers.push_back(*customer_itr);
        customer_itr = customers.erase(customer_itr);

        // after setting the flag to true, leave the iteration over preferences
        sent_dvd = true;        
        break;
      }
    }

    // if no DVD was sent to this customer, then we move on to the next customer 
    // (do not change this customer's priority for tomorrow's shipment)
    if (!sent_dvd) {
      customer_itr++;
    }
  }


}

// ==================================================================

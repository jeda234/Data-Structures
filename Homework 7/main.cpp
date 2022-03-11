#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

typedef map<string, pair<int, vector<string> > > COSTUME_SHOP_TYPE;
typedef map<pair<string, string>, string> PEOPLE_TYPE;

// prototypes for the helper functions
void addCostume(COSTUME_SHOP_TYPE &costume_shop);
void rentCostume(COSTUME_SHOP_TYPE& costume_shop, PEOPLE_TYPE& people);
void lookup(COSTUME_SHOP_TYPE& costume_shop);
void printPeople(PEOPLE_TYPE& people);

int main() {
  // two data structures store all of the information for efficiency
  COSTUME_SHOP_TYPE costume_shop;
  PEOPLE_TYPE people;
  char c;
  while (cin >> c) {
    if (c == 'a') {
      addCostume(costume_shop);
    } else if (c == 'r') {
      rentCostume(costume_shop,people);
    } else if (c == 'l') {
      lookup(costume_shop);
    } else if (c == 'p') {
      printPeople(people);
    } else {
      cerr << "error unknown char " << c << endl;
      exit(0);
    }
  }
}


void addCostume(COSTUME_SHOP_TYPE& costume_shop) {
  string costume_name;
  int num;
  cin >> costume_name >> num;
  COSTUME_SHOP_TYPE::iterator it = costume_shop.find(costume_name);
  if (it!=costume_shop.end()) {
    it->second.first+=num;
  } else {
    vector<string> v;
    costume_shop[costume_name]=make_pair(num, v);
  }
  if (num==1) {
    cout << "Added 1 " << costume_name << " costume." << endl;
  } else {
    cout << "Added " << num << " " << costume_name << " costumes." << endl;
  }
}


void rentCostume(COSTUME_SHOP_TYPE& costume_shop, PEOPLE_TYPE& people) {
  string first_name, last_name, costume_name;
  cin >> first_name >> last_name >> costume_name;
  COSTUME_SHOP_TYPE::iterator it = costume_shop.find(costume_name);
  PEOPLE_TYPE::iterator itr = people.find({last_name, first_name});
  if (itr==people.end()) {
    if (it!=costume_shop.end() && ((it->second.first-it->second.second.size())!=0)) {
      people[{last_name, first_name}]=costume_name;
      cout << first_name << " " << last_name << " rents a " << costume_name << " costume." << endl;
      string name = first_name + " " + last_name;
      it->second.second.push_back(name);
    } else if (it!=costume_shop.end() && ((it->second.first-it->second.second.size())==0)) {
      people[{last_name, first_name}]="NULL";
      cout << "No " << costume_name << " costumes available." << endl;
    } else {
      people[{last_name, first_name}]="NULL";
      cout << "The shop doesn't carry " << costume_name << " costumes." << endl;
    }
  } else if ((it->first == costume_name) && ((it->second.first-it->second.second.size())!=0) && (itr->second=="NULL")) {
      string name = first_name + " " + last_name;
      it->second.second.push_back(name);
      itr->second = costume_name;
      cout << first_name << " " << last_name << " rents a " << costume_name << " costume." << endl;
  } else if ((it->first == costume_name) && ((it->second.first-it->second.second.size())!=0)) {
      string name = first_name + " " + last_name;
      COSTUME_SHOP_TYPE::iterator i = costume_shop.find(itr->second);
      if (i->first==costume_name) {
          cout << first_name << " " << last_name << " already has a " << costume_name << " costume." << endl;
      } else {
        int count=0;
        for (int x=0; x<(i->second.second.size()); x++) {
          if ((i->second.second)[x]==name) {
            break;
          }
          count++;
        }
        i->second.second.erase(i->second.second.begin()+count);
        itr->second = costume_name;
        cout << first_name << " " << last_name << " returns a " << i->first << " costume before renting a " << costume_name << " costume." << endl;
        it->second.second.push_back(name);
      }
  } else if ((it->first == costume_name) && ((it->second.first-it->second.second.size())==0)) {
      cout << "No " << costume_name << " costumes available." << endl;
  } else if (it==costume_shop.end()) {
      cout << "The shop doesn't carry " << costume_name << " costumes." << endl;
  }
}


void lookup(COSTUME_SHOP_TYPE& costume_shop) {
  string costume_name;
  cin >> costume_name;
  COSTUME_SHOP_TYPE::const_iterator it = costume_shop.find(costume_name);
  if (it!=costume_shop.end()) {
    std::cout << "Shop info for " << costume_name << " costumes:" << std::endl;
    if (it->second.second.size()!=0) {
      int x = it->second.first-it->second.second.size();
      if (x==1) {
        cout << "  1 copy available" << endl;
      } else if (x!=0) {    
        cout << "  " << x << " copies available" << endl;
      } 
      if (it->second.second.size()==1) {
        cout << "  1 copy rented by:" << endl;
        cout << "    " << it->second.second[0] << endl;
      } else {
        cout << "  " << it->second.second.size() << " copies rented by:" << endl;
        for (int i=0; i<it->second.second.size(); i++) {
          cout << "    " << it->second.second[i] << endl;
        }
      }
    } else {
      int x = it->second.first-it->second.second.size();
      if (x==1) {
        cout << "  1 copy available" << endl;
      } else if (x!=0) {    
        cout << "  " << x << " copies available" << endl;
      } else {
        cout << "No " << costume_name << " costumes available." << endl;
      }
    }
  } else {
    cout << "The shop doesn't carry " << costume_name << " costumes." << endl;
  }
}


void printPeople(PEOPLE_TYPE& people) {
    PEOPLE_TYPE::const_iterator it = people.begin();
    if (people.size()==0) {
        cout << "No current customer info." << endl;
    } else if (people.size()==1) {
        cout << "Costume info for the 1 party attendee:" << endl;
        if (it->second=="NULL") {
            cout << "  " << it->first.second << " " << it->first.first << " does not have a costume." << endl;
        } else {
            cout << "  " << it->first.second << " " << it->first.first << " is wearing a " << it->second << " costume." << endl;
        }
    } else {
        cout << "Costume info for the " << people.size() << " party attendees:" << endl;
        while (it!=people.end()) {
            if (it->second=="NULL") {
                cout << "  " << it->first.second << " " << it->first.first << " does not have a costume." << endl;
            } else {
                cout << "  " << it->first.second << " " << it->first.first << " is wearing a " << it->second << " costume." << endl;
            }
            it++;
        }
    }
}
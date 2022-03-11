#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include "BPlusTree.h"

int main () {
    BPlusTree<std::string> b1(3);
    b1.insert("a");
    b1.insert("b");
    b1.insert("c");
    b1.insert("ant");
    b1.insert("abum");
    //assert(b1.find("a"));
	//assert(b1.find("a")->contains("a"));
    b1.print_BFS(std::cout);
    std::cout << std::endl;
    b1.print_sideways(std::cout);
    std::cout << std::endl;
    std::cout << "cheeks" << std::endl;
};

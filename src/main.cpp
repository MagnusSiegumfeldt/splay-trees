#include <cstring>
#include <vector>
#include <limits>
#include "splay_tree.h"



void ignoreLine() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    std::cout << "Simple integer splay tree demo" << std::endl;

    std::string command;
    int key;
    SplayTree<int> splay_tree = SplayTree<int>(); 
    std::cout << "Use: \"insert [key]\", \"delete [key]\" or \"print\"" << std::endl;
    while (true) {
        std::cin >> command;
        if (command.compare(std::string("insert")) == 0) {
            std::cin >> key;
            if (std::cin.fail()) {
                std::cout << "Insert failed. Use \"insert [key]\"" << std::endl;
                std::cin.clear();
                ignoreLine();
                continue;
            } 
            ignoreLine();
            
            if (splay_tree.insert(key)) {
                std::cout << "Inserted: " << key << std::endl;
            } else {
                std::cout << "Element does already exist." << std::endl;
            }
            
        } else if (command.compare(std::string("delete")) == 0) {
            std::cin >> key;
            if (std::cin.fail()) {
                std::cout << "Delete failed. Use \"delete [key]\"." << std::endl;
                std::cin.clear();
                ignoreLine();
                continue;
            }
            ignoreLine();
            if (splay_tree.remove(key)) {
                std::cout << "Deleted: " << key << std::endl;
            } else {
                std::cout << "Element does not exist." << std::endl;
            }
        } else if (command.compare(std::string("print")) == 0) {
            std::cout << splay_tree.print() << std::endl;
            ignoreLine();
        } else {
            std::cerr << "Wrong input. Use: \"insert [key]\", \"delete [key]\" or \"print\"" << std::endl;
            std::cin.clear();
            ignoreLine();
        }
    
    }
    

    return 0;
}
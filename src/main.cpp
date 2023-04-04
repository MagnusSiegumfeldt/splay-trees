#include <iostream>
#include <string>
#include "splay_tree.h"

using namespace std;

int main() {
    cout << "Simple splay tree demo" << endl;

    string command;
    int key;
    SplayTree<int>* splay_tree = new SplayTree<int>(); 
    
    while (true) {
        cin >> command >> key;
        if (command.compare("insert")) {
            splay_tree->insert(key);
        } else if (command.compare("delete")) {
            splay_tree->remove(key);
        } else if (command.compare("print")) {
            splay_tree->in_order();
        } else {
            cout << "Wrong input. Use: \"insert [key]\", \"delete [key]\" or \"print\"";
        }
    }



    return 0;
}
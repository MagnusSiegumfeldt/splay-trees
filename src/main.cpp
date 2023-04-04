#include <cstring>
#include <vector>
#include "splay_tree.h"

using namespace std;


int main() {
    cout << "Simple integer splay tree demo" << endl;

    string command;
    int key;
    SplayTree<int>* splay_tree = new SplayTree<int>(); 
    
    cout << "Use: \"insert [key]\", \"delete [key]\" or \"print\"" << endl;
    while (true) {
        cin >> command;
        if (command.compare(string("insert")) == 0) {
            cin >> key;
            splay_tree->insert(key);
        } else if (command.compare(string("delete")) == 0) {
            cin >> key;
            splay_tree->remove(key);
        } else if (command.compare(string("print")) == 0) {
            cout << splay_tree->print() << endl;
        } else {
            cout << "Wrong input. Use: \"insert [key]\", \"delete [key]\" or \"print\"" << endl;
        }
    }

    return 0;
}
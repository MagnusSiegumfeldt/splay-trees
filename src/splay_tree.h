#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <tuple>
#include <vector>
#include <string>
#include <memory>


template <class T>
class Node {
    public: 
    T data;
    
    std::weak_ptr<Node<T>> parent;
    std::shared_ptr<Node<T>> left;
    std::shared_ptr<Node<T>> right;

    Node<T>(T);
    bool is_left_child();
    bool is_right_child();
};

template <class T>
class SplayTree {
    std::shared_ptr<Node<T>> root = nullptr;


    void rotate_left(std::shared_ptr<Node<T>>);
    void rotate_right(std::shared_ptr<Node<T>>);
    void splay(std::shared_ptr<Node<T>>);
    std::shared_ptr<Node<T>> get_maximum(std::shared_ptr<Node<T>>);    


    std::string print_helper(std::shared_ptr<Node<T>>, std::string, bool);


    public:
    std::shared_ptr<Node<T>> search(T);
    bool insert(T);
    bool remove(T);

    std::vector<T> in_order();    
    std::string print();
};


#include "splay_tree.hpp"
#endif
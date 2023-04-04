#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <tuple>
#include <vector>

template <class T>
class Node {
    public: 
    T* data;
    Node<T>* parent = nullptr;
    Node<T>* left = nullptr;
    Node<T>* right = nullptr;

    Node<T>(T*);
    bool is_left_child();
    bool is_right_child();
};

template <class T>
class SplayTree {
    Node<T>* root = nullptr;


    void rotate_left(Node<T>*);
    void rotate_right(Node<T>*);
    void splay(Node<T>*);
    Node<T>* get_maximum(Node<T>*);


    public:
    Node<T>* search(T*);
    void insert(T*);
    void remove(T*);

    std::vector<T*> in_order();    
};


#include "splay_tree.hpp"
#endif
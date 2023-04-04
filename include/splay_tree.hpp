#include <cassert>
#include <iostream>

#include "splay_tree.h"

template <class T>
Node<T>::Node(T data) {
    this->data = data;
}
template <class T>
bool Node<T>::is_left_child() {
    if (!this->parent)
        return false;
    return parent->left == this;
}
template <class T>
bool Node<T>::is_right_child() {
    if (!this->parent)
        return false;
    return parent->right == this;
}

template <class T>
void SplayTree<T>::rotate_right(Node<T>* x) {
    Node<T>* y = x->parent;
    Node<T>* z = y->parent;

    if (z) {
        if (y->is_left_child()) {
            z->left = x;
        } else if (y->is_right_child()) {
            z->right = x;
        }
    }
    y->left = x->right;
    y->parent = x;
    x->right = y;    
    x->parent = z; 
    if (y->left)
        y->left->parent = y;
}

template <class T>
void SplayTree<T>::rotate_left(Node<T>* x) {
    Node<T>* y = x->parent;
    Node<T>* z = y->parent;

    if (z) {
        if (y->is_left_child()) {
            z->left = x;
        } else if (y->is_right_child()) {
            z->right = x;
        }
    }
    y->right = x->left;
    y->parent = x;
    x->left = y;    
    x->parent = z; 
    if (y->right)
        y->right->parent = y;
}

template <class T>
void SplayTree<T>::splay(Node<T>* node) {
    while (node->parent) {
        if (!node->parent->parent) {
            if (node->is_right_child()) { // Zag
                rotate_left(node);
            } else if (node->is_left_child()) { // Zig
                rotate_right(node); 
            }
        } else if (node->parent->is_left_child()) { 
            if (node->is_left_child()) {
                rotate_right(node->parent);
                rotate_right(node);
            } else if (node->is_right_child()) {
                rotate_left(node);
                rotate_right(node);
            }
        } else if (node->parent->is_right_child()) { 
            if (node->is_right_child()) { 
                rotate_left(node->parent);
                rotate_left(node);
            } else if (node->is_left_child()) {
                rotate_right(node);
                rotate_left(node);
            }
        }
    }
    this->root = node;
}


template <class T>
Node<T>* SplayTree<T>::get_maximum(Node<T>* node) {
    while (node->right) {
        node = node->right;
    }
    return node;
}


template <class T>
Node<T>* SplayTree<T>::search(T data) {
    Node<T>* node = this->root;
    if (!node)
        return nullptr;

    Node<T>* last_node;
    while (node) {
        last_node = node;
        if (node->data == data) {
            splay(node);
            return node;
        } else if (node->data > data) {
            node = node->left;
        } else if (node->data < data) {
            node = node->right;
        }
    }
    
    this->splay(last_node);
    return nullptr;
}



template <class T>
void SplayTree<T>::insert(T data) {
    Node<T>* node = this->root;
    Node<T>* new_node = new Node<T>(data);
    while (node) {
        if (node->data < data) {
            if (node->right) {
                node = node->right;
            } else {
                node->right = new_node;
                new_node->parent = node;
                break;
            }
        } else if (node->data > data) {
            if (node->left) {
                node = node->left;
            } else {
                node->left = new_node;
                new_node->parent = node;
                break;
            }
        } else {
            assert(false);
        }
    }
    this->splay(new_node);
}

template <class T>
void SplayTree<T>::remove(T data) {
    Node<T>* root = this->search(data);
    assert(root == this->root);
    Node<T>* left = root->left;
    Node<T>* right = root->right;
    if (left) {
        Node<T>* left_max = this->get_maximum(left);
        this->splay(left_max);
        this->root->right = right;
        if (this->root->right)
            this->root->right->parent = this->root;
    } else {
        this->root = right;
        this->root->parent = nullptr;
    }
}

template <class T>
std::vector<T> SplayTree<T>::in_order() {
    Node<T>* node = this->root;

    std::vector<Node<T>*> stack;
    std::vector<T> order;

    while (node || stack.size() > 0) {
        // Explore left as much as possible
        while (node) {
            stack.push_back(node);
            node = node->left;
        }
        node = stack.back();
        stack.pop_back();

        order.push_back(node->data);
        // Explore one step right
        node = node->right;
    }
    return order;
}


template <class T>
std::string SplayTree<T>::print() {
    std::string res = "    ";
    res += std::to_string(this->root->data);
    res += "\n";
    res += print_helper(this->root->right, "    ", true);
    res += print_helper(this->root->left, "    ", false);
    return res;
}

template <class T>
std::string SplayTree<T>::print_helper(Node<T> *node, std::string prefix, bool is_right) {
    std::string res;
    //if( node != nullptr){
    res += prefix;
    res += (is_right ? "|---" : "L---" );
    

        // print the value of the node
    if (node) {
        res += std::to_string(node->data) + "\n";
    } else {
        res += "*\n";
        return res;
    }

        // enter the next tree level - left and right branch
    //if (node->left)
    res += print_helper(node->right, prefix + (is_right ? "|   " : "    "), true);
    //if (node->right)
    res += print_helper(node->left, prefix + (is_right ? "|   " : "    "), false);
    //}
    return res;
}
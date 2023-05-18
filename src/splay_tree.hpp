#include <cassert>
#include <iostream>

#include "splay_tree.h"

template <class T>
Node<T>::Node(T data) {
    this->data = data;
}
template <class T>
bool Node<T>::is_left_child() {
    std::shared_ptr<Node<T>> parent = this->parent.lock();
    if (!parent)
        return false;
    return parent->left.get() == this;
}
template <class T>
bool Node<T>::is_right_child() {
    std::shared_ptr<Node<T>> parent = this->parent.lock();
    if (!parent)
        return false;
    return parent->right.get() == this;
}

template <class T>
void SplayTree<T>::rotate_right(std::shared_ptr<Node<T>> x) {
    std::shared_ptr<Node<T>> y = x->parent.lock();
    std::shared_ptr<Node<T>> z = y->parent.lock();

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
void SplayTree<T>::rotate_left(std::shared_ptr<Node<T>> x) {
    std::shared_ptr<Node<T>> y = x->parent.lock();
    std::shared_ptr<Node<T>> z = y->parent.lock();

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
void SplayTree<T>::splay(std::shared_ptr<Node<T>> node) {
    std::shared_ptr<Node<T>> parent = node->parent.lock();
    while (parent) {
        std::shared_ptr<Node<T>> grandparent = parent->parent.lock();
        if (!grandparent) {
            if (node->is_right_child()) { // Zag
                rotate_left(node);
            } else if (node->is_left_child()) { // Zig
                rotate_right(node); 
            }
        } else if (parent->is_left_child()) { 
            if (node->is_left_child()) { // Zig-Zig
                rotate_right(parent);
                rotate_right(node);
            } else if (node->is_right_child()) { // Zag-Zig
                rotate_left(node);
                rotate_right(node);
            }
        } else if (parent->is_right_child()) { 
            if (node->is_right_child()) { // Zag-Zag
                rotate_left(parent);
                rotate_left(node);
            } else if (node->is_left_child()) { // Zig-Zag
                rotate_right(node);
                rotate_left(node);
            }
        }
        parent = node->parent.lock();
    }
    this->root = node;
}


template <class T>
std::shared_ptr<Node<T>> SplayTree<T>::get_maximum(std::shared_ptr<Node<T>> node) {
    while (node->right) {
        node = node->right;
    }
    return node;
}


template <class T>
std::shared_ptr<Node<T>> SplayTree<T>::search(T data) {
    std::shared_ptr<Node<T>> node = this->root;
    if (!node)
        return nullptr;

    std::shared_ptr<Node<T>> last_node;
    while (node) {
        last_node = node;
        if (node->data == data) {
            this->splay(node);
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
bool SplayTree<T>::insert(T data) {
    std::shared_ptr<Node<T>> node = this->root;
    std::shared_ptr<Node<T>> new_node = std::make_shared<Node<T>>(data);
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
            return false;
        }
    }
    this->splay(new_node);
    return true;
}

template <class T>
bool SplayTree<T>::remove(T data) {
    std::shared_ptr<Node<T>> root = this->search(data);
    if (!root) return false;

    std::shared_ptr<Node<T>> left = root->left;
    std::shared_ptr<Node<T>> right = root->right;
    if (left) {
        std::shared_ptr<Node<T>> left_max = this->get_maximum(left);
        this->splay(left_max);
        this->root->right = right;
        if (this->root->right)
            this->root->right->parent = this->root;
    } else {
        this->root = right;
        if (this->root) {
            this->root->parent.reset();
        }
        
    }
    return true;
}

template <class T>
std::vector<T> SplayTree<T>::in_order() {
    std::shared_ptr<Node<T>> node = this->root;

    std::vector<std::shared_ptr<Node<T>>> stack;
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
std::string SplayTree<T>::print_helper(std::shared_ptr<Node<T>> node, std::string prefix, bool is_right) {
    std::string res;
    res += prefix;
    res += (is_right ? "|---" : "L---" );
    
    if (node) {
        res += std::to_string(node->data) + "\n";
    } else {
        res += "*\n";
        return res;
    }

    res += print_helper(node->right, prefix + (is_right ? "|   " : "    "), true);
    res += print_helper(node->left, prefix + (is_right ? "|   " : "    "), false);
    return res;
}










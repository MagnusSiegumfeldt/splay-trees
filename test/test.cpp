#include <array>
#include <algorithm>

#include <catch2/catch_test_macros.hpp>
#include "splay_tree.h"

TEST_CASE("Small case") {

    SplayTree<int>* splay_tree = new SplayTree<int>();

    int elems[] = {4, 5, 3};
    int res[] = {3, 4, 5};

    for (int i = 0; i < 3; i++) {
        splay_tree->insert(&(elems[i]));
    }

    std::vector<int*> in_order = splay_tree->in_order();
    REQUIRE(*in_order[0] == res[0]);
    REQUIRE(*in_order[1] == res[1]);
    REQUIRE(*in_order[2] == res[2]);
}


// Test that numbers appear in sorted order when traversing inorder.
TEST_CASE("Search tree invariant") {

    SplayTree<int>* splay_tree = new SplayTree<int>();

    int elems[] = {4, 5, 3, 1, 2, 7, 6, 10, -2, 11, 8, 9};
    int length = sizeof(elems) / sizeof(int);
    
    // Copy and sort
    int sorted[length];
    std::copy(elems, elems + length, sorted);
    std::sort(sorted, sorted + length);

    for (int i = 0; i < length; i++) {
        splay_tree->insert(&(elems[i]));
    }

    std::vector<int*> in_order = splay_tree->in_order();

    for (int i = 0; i < length; i++) {
        REQUIRE(sorted[i] == *in_order[i]);
    }
}

TEST_CASE("Deletions") {

    SplayTree<int>* splay_tree = new SplayTree<int>();

    int elems[] = {4, 5, 3, 1, 2, 7, 6};
    int length = sizeof(elems) / sizeof(int);
    
    // Copy and sort
    int result[] = {1, 2, 4, 6, 7};
    
    splay_tree->insert(&elems[0]);
    splay_tree->insert(&elems[1]);
    splay_tree->insert(&elems[2]);
    splay_tree->insert(&elems[3]);
    splay_tree->insert(&elems[4]);
    splay_tree->remove(&elems[1]);
    splay_tree->insert(&elems[5]);
    splay_tree->insert(&elems[6]);
    splay_tree->remove(&elems[2]);
    

    std::vector<int*> in_order = splay_tree->in_order();

    REQUIRE(result[0] == *in_order[0]);
    REQUIRE(result[1] == *in_order[1]);
    REQUIRE(result[2] == *in_order[2]);
    REQUIRE(result[3] == *in_order[3]);
    REQUIRE(result[4] == *in_order[4]);
}

class CustomData {
    public:
    int key;
    int data;
    CustomData(int key, int data) {
        this->key = key;
        this->data = data;
    };
    bool operator<(const CustomData& other) const {
        return this->key < other.key;
    };
    bool operator>(const CustomData& other) const {
        return this->key > other.key;
    };
    bool operator==(const CustomData& other) const {
        return this->key == other.key;
    };
};

TEST_CASE("Custom data") {

    SplayTree<CustomData>* splay_tree = new SplayTree<CustomData>();

    int elements[] = {4, 5, 3, 1, 2, 7, 6, 10, -2, 11, 8, 9};
    int length = sizeof(elements) / sizeof(int);
    for (int i = 0; i < length; i++) {
        splay_tree->insert(new CustomData(elements[i], elements[i]));
    }

    std::sort(elements, elements + length);
    std::vector<CustomData*> in_order = splay_tree->in_order();

    for (int i = 0; i < length; i++) {
        REQUIRE(elements[i] == in_order[i]->key);
        REQUIRE(elements[i] == in_order[i]->data);
    }
}




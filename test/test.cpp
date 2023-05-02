#include <array>
#include <algorithm>


#include <catch2/catch_test_macros.hpp>
#include "splay_tree.h"

// Test that numbers appear in sorted order when traversing inorder.
TEST_CASE("Search tree invariant") {

    SplayTree<int> splay_tree = SplayTree<int>();

    int size = 200;
    int elems[200];
    for (int i = 0; i < size; i++) {
        elems[i] = i;
    }
    std::random_shuffle(&elems[0], &elems[size]);

    SECTION("Insertions") {
        for (int i = 0; i < size; i++) {
            splay_tree.insert(elems[i]);
        }

        std::vector<int> in_order = splay_tree.in_order();
        REQUIRE(in_order.size() == size);

        for (int i = 0; i < in_order.size(); i++) {
            REQUIRE(in_order[i] == i);
        }
    }
    SECTION("Insertions and deletions") {
        std::vector<int> inserted;
        // Insert 200/16 per j iteration. Remove every 4th after.
        int removed = 0;
        int parts = 16;
        for (int j = 0; j < parts; j++) {
            for (int i = size * j / parts; i < size * (j + 1) / parts; i++) {
                splay_tree.insert(elems[i]);
                inserted.push_back(elems[i]);
                
            }
            for (int i = size * j / parts; i < size * (j + 1) / parts; i += 4) {
                splay_tree.remove(elems[i]);
                inserted.erase(std::remove(inserted.begin(), inserted.end(), elems[i]), inserted.end());
                removed++;
            }
        }
        std::vector<int> in_order = splay_tree.in_order();
        std::sort(inserted.begin(), inserted.end());
        REQUIRE(in_order.size() == size - removed);
        REQUIRE(in_order.size() == inserted.size());
        for (int i = 0; i < in_order.size(); i++) {
            REQUIRE(in_order[i] == inserted[i]);
        }
    }
    
}

class CustomData {
    public:
    int key;
    int data;
    CustomData(){};
    CustomData(int key, int data) {
        this->key = key;
        this->data = data;
    };
    bool operator<(const CustomData& other) {
        return this->key < other.key;
    };
    bool operator>(const CustomData& other) {
        return this->key > other.key;
    };
    bool operator==(const CustomData& other) {
        return this->key == other.key;
    };
};

TEST_CASE("Custom data") {

    SplayTree<CustomData> splay_tree = SplayTree<CustomData>();

    int size = 200;
    int elems[200];
    for (int i = 0; i < size; i++) {
        elems[i] = i;
    }
    std::random_shuffle(&elems[0], &elems[size]);

    SECTION("Insertions") {
        for (int i = 0; i < size; i++) {
            splay_tree.insert(CustomData(elems[i], 10));
        }

        std::vector<CustomData> in_order = splay_tree.in_order();
        REQUIRE(in_order.size() == size);

        for (int i = 0; i < in_order.size(); i++) {
            REQUIRE(in_order[i].key == i);
            REQUIRE(in_order[i].data == 10);
        }
    }
    SECTION("Insertions and deletions") {
        std::vector<int> inserted;
        // Insert 200/16 per j iteration. Remove every 4th after.
        int removed = 0;
        int parts = 16;
        for (int j = 0; j < parts; j++) {
            for (int i = size * j / parts; i < size * (j + 1) / parts; i++) {
                splay_tree.insert(CustomData(elems[i], 10));
                inserted.push_back(elems[i]);
                
            }
            for (int i = size * j / parts; i < size * (j + 1) / parts; i += 4) {
                splay_tree.remove(CustomData(elems[i], 10));
                inserted.erase(std::remove(inserted.begin(), inserted.end(), elems[i]), inserted.end());
                removed++;
            }
        }
        std::vector<CustomData> in_order = splay_tree.in_order();
        std::sort(inserted.begin(), inserted.end());
        REQUIRE(in_order.size() == size - removed);
        REQUIRE(in_order.size() == inserted.size());
        for (int i = 0; i < in_order.size(); i++) {
            REQUIRE(in_order[i].key == inserted[i]);
            REQUIRE(in_order[i].data == 10);
        }
    }
}





#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>
#include <cmath>

#include "splay_tree.h"



long double median(std::vector<long double>& results) {
    int n = results.size() / 2;
    std::nth_element(results.begin(), results.begin() + n, results.end());
    return results[n];
}


std::vector<long double> compute_medians(std::vector<std::vector<long double>>& results) {
    std::vector<long double> result;
    for (int i = 0; i < results.size(); i++) {
        result.push_back(median(results[i]));
    }
    return result;
}

std::vector<long double> compute_stdevs(std::vector<std::vector<long double>>& results) {
    std::vector<long double> stdevs;

    for (int i = 0; i < results.size(); i++) {
        long double sum = 0;
        for (int j = 0; j < results[i].size(); j++) {
            sum += (results[i][j]);
        }
        long double mean = sum / results[i].size();
        long double var = 0;
        for (int j = 0; j < results[i].size(); j++) {
            var += (results[i][j] - mean) * (results[i][j] - mean);
        }
        var /= results[i].size();
        stdevs.push_back(sqrt(var));
    }
    return stdevs;
}

std::vector<double> compute_stdevs(std::vector<std::vector<unsigned long>>& results) {
    std::vector<double> stdevs;

    for (int i = 0; i < results.size(); i++) {
        double sum = 0;
        for (int j = 0; j < results[i].size(); j++) {
            sum += (results[i][j]);
        }
        double mean = sum / results[i].size();
        double var = 0;
        for (int j = 0; j < results[i].size(); j++) {
            var += (results[i][j] - mean) * (results[i][j] - mean);
        }
        var /= results[i].size();
        stdevs.push_back(sqrt(var));
    }
    return stdevs;
}

void uniform_test(std::vector<int>& sizes, int iterations, int warmups) {
    std::vector<std::vector<long double>> results = std::vector<std::vector<long double>>(sizes.size());
    for (int k = 0; k < sizes.size(); k++) { // For every size
        int N = sizes[k];
        std::cout << k << std::endl;
        for (int l = 0; l < iterations; l++) { // For iterations
            // Create and shuffle
            std::vector<int> to_insert = std::vector<int>(N); 
            std::vector<int> to_access = std::vector<int>(N); 
            std::vector<int> to_delete = std::vector<int>(N);
            for (int i = 0; i < N; i++) {
                to_insert[i] = i;
                to_access[i] = i;
                to_delete[i] = i;
            }

            auto rng = std::default_random_engine {};
            rng.seed(0);

            std::shuffle(to_insert.begin(), to_insert.end(), rng);
            std::shuffle(to_access.begin(), to_access.end(), rng);
            std::shuffle(to_delete.begin(), to_delete.end(), rng);
            
            // Warmup
            for (int j = 0; j < warmups; j++) {
                SplayTree<int> splay_tree = SplayTree<int>();
                for (int i = 0; i < N; i++) {
                    splay_tree.insert(to_insert[i]);
                }
                for (int i = 0; i < N; i++) {
                    splay_tree.search(to_access[i]);
                }
                for (int i = 0; i < N; i++) {
                    splay_tree.remove(to_delete[i]);
                }
            }
            
            // Time
            auto start = std::chrono::high_resolution_clock::now();

            SplayTree<int> splay_tree = SplayTree<int>();
            for (int i = 0; i < N; i++) {
                splay_tree.insert(to_insert[i]);
            }
            for (int i = 0; i < N; i++) {
                splay_tree.search(to_access[i]);
            }
            for (int i = 0; i < N; i++) {
                splay_tree.remove(to_delete[i]);
            }

            auto stop = std::chrono::high_resolution_clock::now();

            long double duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
            results[k].push_back(duration);
        }
    }
    std::vector<long double> medians = compute_medians(results);
    std::vector<long double> stdevs = compute_stdevs(results);


    std::ofstream file;
    file.open ("../logs/uniform_log.csv");
    for (int i = 0; i < sizes.size(); i++) {
        file << sizes[i] << "," << medians[i] << "," << stdevs[i] << std::endl;
    }
    file.close();
}

enum OpType {Insert, Delete, Search};

struct Ops {
    OpType type;
    int val;
};

void operation_test(std::vector<int>& sizes, int iterations, int operations, int warmups) {
    std::vector<std::vector<long double>> results = std::vector<std::vector<long double>>(sizes.size());
    for (int k = 0; k < sizes.size(); k++) { // For every size
        int N = sizes[k];
        std::cout << k << std::endl;
        for (int l = 0; l < iterations; l++) { // For iterations
            // Create and shuffle
            std::vector<Ops> ops;
            std::vector<int> in_tree;
                        
            std::vector<int> base_insert = std::vector<int>(N); 
            for (int i = 0; i < N; i++) {
                base_insert[i] = i + 100;
                in_tree.push_back(i + 100);
            }

            auto rng = std::default_random_engine {};
            rng.seed(0);

            std::shuffle(base_insert.begin(), base_insert.end(), rng);
            
            // generate operations
            for (int i = 0; i < operations; i++) {
                int type = rng() % 3;
                Ops op;
                if (type == 0) {
                    op.type = Insert;
                    int val = rng() % (N + 100);
                    while (std::count(in_tree.begin(), in_tree.end(), val)) {
                        val = rng() % (N + 100);
                    }
                    op.val = val;
                    in_tree.push_back(val);
                } else if (type == 1) {
                    op.type = Delete;
                    op.val = in_tree[rng() % in_tree.size()];
                    remove(in_tree.begin(), in_tree.end(), op.val);
                } else {
                    op.type = Search;
                    op.val = in_tree[(rng() % in_tree.size())];
                }
                ops.push_back(op);
            }
            

            // Warmup
            for (int j = 0; j < warmups; j++) {
                SplayTree<int> splay_tree = SplayTree<int>();
                for (int i = 0; i < N; i++) {
                    splay_tree.insert(base_insert[i]);
                }
                for (int i = 0; i < ops.size(); i++) {
                    if (ops[i].type == Insert) {
                        splay_tree.insert(ops[i].val);
                    } else if (ops[i].type == Delete) {
                        splay_tree.remove(ops[i].val);
                    } else if (ops[i].type == Search) {
                        splay_tree.search(ops[i].val);
                    }
                }
            }
            
            // Time

            SplayTree<int> splay_tree = SplayTree<int>();
            for (int i = 0; i < N; i++) {
                splay_tree.insert(base_insert[i]);
            }
            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < ops.size(); i++) {
                if (ops[i].type == Insert) {
                    splay_tree.insert(ops[i].val);
                } else if (ops[i].type == Delete) {
                    splay_tree.remove(ops[i].val);
                } else if (ops[i].type == Search) {
                    splay_tree.search(ops[i].val);
                }
            }

            auto stop = std::chrono::high_resolution_clock::now();

            long double duration = ((long double) std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count()) / ops.size();
            results[k].push_back(duration);
        }
    }
    std::vector<long double> medians = compute_medians(results);
    std::vector<long double> stdevs = compute_stdevs(results);


    std::ofstream file;
    file.open ("../logs/operation_log.csv");
    for (int i = 0; i < sizes.size(); i++) {
        file << sizes[i] << "," << medians[i] << "," << stdevs[i] << std::endl;
    }
    file.close();
}




int main() {
    int warmups = 3;
    int iterations = 7;
    int operations = 2000;
    int size = 24;

    std::vector<int> sizes = std::vector<int>(size);
    for (int i = 0; i < size; i++) {
        sizes[i] = pow(1.3, i) * 100;
    }
    uniform_test(sizes, iterations, warmups);
    operation_test(sizes, iterations, operations, warmups);

    return 0;
}
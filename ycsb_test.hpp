#ifndef YCSB_TEST_HPP
#define YCSB_TEST_HPP

#include "rb_tree.hpp"
#include "radix_tree.hpp"
#include "compressed_radix_tree.hpp"
#include "tree.hpp"
#include "util.hpp"
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <algorithm>

// enum TreeType {
//     RadixTree,
//     CompressedRadixTree,
//     RbTree,
// };

enum OpType {
    Find,
    Insert,
    Remove,
};

std::string treeTypeToString(TreeType treeType){
    switch (treeType) {
        case RadixTree:
            return "Radix Tree";
        case CompressedRadixTree:
            return "Compressed Radix Tree";
        case RbTree:
            return "RB Tree";
    }
}

std::string opTypeToString(OpType opType){
    switch (opType) {
        case Find:
            return "Find";
        case Insert:
            return "Insert";
        case Remove:
            return "Remove";
    }
}

void doWorkLoad1(Tree* tree, std::ofstream& outFile, TreeType treeType);
void doWorkLoad2(Tree* tree, std::ofstream& outFile, TreeType treeType);
void doWorkLoad3(Tree* tree, std::ofstream& outFile, TreeType treeType);

void preLoad(Tree *tree1, Tree *tree2, Tree *tree3){
    for(int i = 0; i < 1000; i++){
        int key = zipf();
        tree1->insert(key);
        tree2->insert(key);
        tree3->insert(key);
    }
}

void statistics(std::vector<double> durations, std::ofstream& outFile, TreeType treeType, OpType opType){
    double average = std::accumulate(durations.begin(), durations.end(), 0.0) / durations.size();

    std::sort(durations.begin(), durations.end());
    double P50 = durations[durations.size() * 0.5];
    double P90 = durations[durations.size() * 0.9];
    double P99 = durations[durations.size() * 0.99];

    outFile << "Tree type: " << treeTypeToString(treeType) << std::endl;
    outFile << "Operation type: " << opTypeToString(opType) << std::endl;
    outFile << "Average: " << average << std::endl;
    outFile << "P50: " << P50 << std::endl;
    outFile << "P90: " << P90 << std::endl;
    outFile << "P99: " << P99 << std::endl;
    outFile << std::endl;
}

void workLoad1(){
    Tree* tree1 = new class RadixTree();
    Tree* tree2 = new class CompressedRadixTree();
    Tree* tree3 = new class RBTree();
    preLoad(tree1, tree2, tree3);

    std::ofstream outFile("workload1_statistics.txt");

    doWorkLoad1(tree1, outFile, RadixTree);
    std::cout << "Radix tree done" << std::endl;
    doWorkLoad1(tree2, outFile, CompressedRadixTree);
    std::cout << "Compressed radix tree done" << std::endl;
    doWorkLoad1(tree3, outFile, RbTree);
    std::cout << "RB tree done" << std::endl;
    
    outFile.close();

    std::cout << "Workload 1 done" << std::endl;
}

void doWorkLoad1(Tree* tree, std::ofstream& outFile, TreeType treeType){
    std::vector<double> findDurations;
    std::vector<double> insertDurations;

    auto start = std::chrono::high_resolution_clock::now();
    while (true) {
        int key = zipf();
        int op = rand() % 2;
        
        if (op == 0) {
            auto start1 = std::chrono::high_resolution_clock::now();
            tree->find(key);
            auto end1 = std::chrono::high_resolution_clock::now();
            auto elapsed_seconds1 = std::chrono::duration_cast<std::chrono::duration<double>>(end1 - start1);
            findDurations.push_back(elapsed_seconds1.count());

        } else {
            auto start1 = std::chrono::high_resolution_clock::now();
            tree->insert(key);
            auto end1 = std::chrono::high_resolution_clock::now();
            auto elapsed_seconds1 = std::chrono::duration_cast<std::chrono::duration<double>>(end1 - start1); 
            insertDurations.push_back(elapsed_seconds1.count());

        }

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

        if (elapsed_seconds.count() >= 45.0) {
            break;
        }
    }

    statistics(findDurations, outFile, treeType, Find);
    statistics(insertDurations, outFile, treeType, Insert);
}

void workLoad2(){
    Tree* tree1 = new class RadixTree();
    Tree* tree2 = new class CompressedRadixTree();
    Tree* tree3 = new class RBTree();
    preLoad(tree1, tree2, tree3);

    std::ofstream outFile("workload2_statistics.txt");

    doWorkLoad2(tree1, outFile, RadixTree);
    std::cout << "Radix tree done" << std::endl;
    doWorkLoad2(tree2, outFile, CompressedRadixTree);
    std::cout << "Compressed radix tree done" << std::endl;
    doWorkLoad2(tree3, outFile, RbTree);
    std::cout << "RB tree done" << std::endl;
    
    outFile.close();

    std::cout << "Workload 2 done" << std::endl;
}

void doWorkLoad2(Tree* tree, std::ofstream& outFile, TreeType treeType){
    std::vector<double> findDurations;

    auto start = std::chrono::high_resolution_clock::now();
    while (true) {

        auto start1 = std::chrono::high_resolution_clock::now();
        tree->find(zipf());
        auto end1 = std::chrono::high_resolution_clock::now();
        auto elapsed_seconds1 = std::chrono::duration_cast<std::chrono::duration<double>>(end1 - start1);
        findDurations.push_back(elapsed_seconds1.count());

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

        if (elapsed_seconds.count() >= 45.0) {
            break;
        }
    }

    statistics(findDurations, outFile, treeType, Find);
}

void workLoad3(){
    Tree* tree1 = new class RadixTree();
    Tree* tree2 = new class CompressedRadixTree();
    Tree* tree3 = new class RBTree();
    preLoad(tree1, tree2, tree3);

    std::ofstream outFile("workload3_statistics.txt");

    doWorkLoad3(tree1, outFile, RadixTree);
    std::cout << "Radix tree done" << std::endl;
    doWorkLoad3(tree2, outFile, CompressedRadixTree);
    std::cout << "Compressed radix tree done" << std::endl;
    doWorkLoad3(tree3, outFile, RbTree);
    std::cout << "RB tree done" << std::endl;
    
    outFile.close();

    std::cout << "Workload 3 done" << std::endl;
}

void doWorkLoad3(Tree* tree, std::ofstream& outFile, TreeType treeType){
    std::vector<double> findDurations;
    std::vector<double> insertDurations;
    std::vector<double> removeDurations;

    auto start = std::chrono::high_resolution_clock::now();
    while (true) {
        int key = zipf();
        int op = rand() % 4;
        
        if (op == 0 || op == 1) {
            auto start1 = std::chrono::high_resolution_clock::now();
            tree->find(key);
            auto end1 = std::chrono::high_resolution_clock::now();
            auto elapsed_seconds1 = std::chrono::duration_cast<std::chrono::duration<double>>(end1 - start1);
            findDurations.push_back(elapsed_seconds1.count());

        } else if (op == 2) {
            auto start1 = std::chrono::high_resolution_clock::now();
            tree->insert(key);
            auto end1 = std::chrono::high_resolution_clock::now();
            auto elapsed_seconds1 = std::chrono::duration_cast<std::chrono::duration<double>>(end1 - start1); 
            insertDurations.push_back(elapsed_seconds1.count());

        } else {
            auto start1 = std::chrono::high_resolution_clock::now();
            tree->remove(key);
            auto end1 = std::chrono::high_resolution_clock::now();
            auto elapsed_seconds1 = std::chrono::duration_cast<std::chrono::duration<double>>(end1 - start1); 
            removeDurations.push_back(elapsed_seconds1.count());

        }

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

        if (elapsed_seconds.count() >= 45.0) {
            break;
        }
    }

    statistics(findDurations, outFile, treeType, Find);
    statistics(insertDurations, outFile, treeType, Insert);
    statistics(removeDurations, outFile, treeType, Remove);
}

void run_ycsb_test(){
    workLoad1();
    workLoad2();
    workLoad3();
}

#endif // YCSB_TEST_HPP

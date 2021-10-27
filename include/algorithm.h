#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "blocks.h"

#include <algorithm>

#include <iostream>
#include <string>

class Algorithms{
private:
    Blocks& data;               // Reference to array of data to sort

    std::thread sortingThread;  // Thread for sorting the blocks

    int algcount;               // Total number of algs in alglist

    void algo();                // Function that keeps running in the thread

    // Sorting algorithms
    void check();
    void shuffle();
    void bubblesort();
    void mergesort();   void m_ms(int left, int right);         void m_merge(int left, int mid, int right);
    void quicksort();   void q_qs(int low, int high);           int q_fix(int low, int high);
    void radixsort();   void r_cs(int place);                         int r_max();

    // Algorithm list
    const std::vector<std::string> alglist = {"Check", "Shuffle", "Bubblesort", "Mergesort", "Quicksort", "Radixsort"};
public:
    // Constructor
    Algorithms(Blocks& data_array);

    // Controllers
    void start();
    void stop();

    // State variables
    bool working;                           // Set true when the algo is performing task
    bool sorted;
    int selectedAlg;                        // Currently selected algorithm index from alglist


    // Setters
    void setalg(int algnumber);             // Set Algorithm to use

    // Getters
    std::string getalg();                   // Get currently selected alg name
};

#endif // ALGORITHM_H

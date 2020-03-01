////////////////////////////////////////////////////////////////////////////
//    Catherine Ding
//    
//    Tufts University, Comp 160 randSelect coding assignment  
//    randSelect.cpp
//    randomized selection
//
//    includes functions provided and function students need to implement
//
////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <vector>
#include <stdlib.h>

#include "randSelect.h"

using namespace std;

void printVector(std::vector<int> v) {
    std::cout << "[ ";
    for (int i : v)
        std::cout << i << " ";
    std::cout << "]\n";
}

// TODO: implement this function
int randSelect(std::vector<int> v, int rankIndex)
{
    if (v.size() <= 5) { //base case
        return brute_force(v, rankIndex);
    }
    int pivot = rand() % (int)v.size(); //rand pivot
    int pos = partition(v, pivot); //partition
    if (pos == rankIndex)
        return v[pos];
    vector<int> subarr;
    if (pos > rankIndex) {
        for (int i = 0; i < pos; i++)
            subarr.push_back(v[i]);
        return randSelect(subarr, rankIndex);
    } else {
        for (int i = pos+1; i < (int)v.size(); i++)
            subarr.push_back(v[i]);
        return randSelect(subarr, rankIndex-pos);
    }
}

// brute_force
// purpose: finds the kth smallest elem in an array by brute force
//          (insertion sort)
// parameters: the vector v and the rank you are looking for
// returns: the kth smallest element
int brute_force(vector<int> v, int rankIndex)
{
    int curr, j;
    for (unsigned int i = 1; i < v.size(); i++) {
        curr = v[i];
        j = i - 1;
        while (j >= 0 and v[j] > curr) {
            v[j+1] = v[j];
            j = j - 1;
        }
        v[j+1] = curr;
    }
    return v[rankIndex];
}

// partition
// purpose: partitions the array around a given pivot position
// parameters: the vector v and the current pivot position
// returns the index of the pivot after partitioning
int partition(vector<int> &v, int pivot_pos)
{
    int pivot = v[pivot_pos];
    vector<int> smaller;
    vector<int> larger;
    for (int i = 0; i < (int)v.size(); i++) {
        if (i != pivot_pos) {
            if (v[i] > pivot) {
                larger.push_back(v[i]);
            } else {
                smaller.push_back(v[i]);
            }
        }
    }
    int pos = smaller.size();
    for (int i = 0; i < (int)smaller.size(); i++)
        v[i] = smaller[i];
    v[pos] = pivot;
    for (int i = 0; i < (int)larger.size(); i++) 
        v[i+pos] = larger[i];
    return pos;
}
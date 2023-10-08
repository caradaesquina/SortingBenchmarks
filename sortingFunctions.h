#ifndef SORTING_FUNCITONS_H
#define SORTING FUNCTIONS_H

#include <string>
#include <vector>   


typedef void (*SortFunction)(std::vector<std::string>&, int);

void bubbleSort(std::vector<std::string>&, int);
void selectionSort(std::vector<std::string>&, int);
void insertionSort(std::vector<std::string>&, int);
void shellSort(std::vector<std::string>&, int);
void mergeSort(std::vector<std::string>&, int);
void quickSortBridge(std::vector<std::string>&, int);

SortFunction* getSortingFunctions();

std::string* getFunctionNames();

#endif

#ifndef _SORT_H_
#define _SORT_H_

#include <iostream>
#include <algorithm>
#include <vector>

template <class Comparable>
const Comparable &median3(vector<Comparable> &v, int left, int right);

template <class Comparable>
void quickSort(vector<Comparable> &v, int left, int right);

template <class Comparable>
void quickSort(vector<Comparable> &v);

template <class Comparable>
void insertionSort(vector<Comparable> &v);


#endif /* SRC_SORT_H_ */

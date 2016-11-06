#include "Sort.h"

/* QUICK SORT - muito eficiente, mas indicado para vetores com mais de 20 elementos*/

template <class Comparable>  // Comparable: deve possuir construtor cópia, operadores atribuição (=) e comparação(<)
const Comparable &median3(vector<Comparable> &v, int left, int right)
{
 int center = (left+right) /2;
 if (v[center] < v[left])
 swap(v[left], v[center]);
 if (v[right] < v[left])
 swap(v[left], v[right]);
 if (v[right] < v[center])
 swap(v[center], v[right]);
 //coloca pivot na posicao right-1
 swap(v[center], v[right-1]);
 return v[right-1];
}

template <class Comparable>
void quickSort(vector<Comparable> &v, int left, int right)
{
 if (right-left <= 10) // se vetor pequeno
 insertionSort(v,left,right);
 else {
 Comparable x = median3(v,left,right); // x é o pivot
 int i = left; int j = right-1; // passo de partição
for(; ; ) {
 while (v[++i] < x) ;
 while (x < v[--j]) ;
 if (i < j)
 swap(v[i], v[j]);
 else break;
}
swap(v[i], v[right-1]); //repoe pivot
 quickSort(v, left, i-1);
 quickSort(v, i+1, right);
 }
}

template <class Comparable>
void quickSort(vector<Comparable> &v)
{
 quickSort(v,0,v.size()-1);
}


/* INSERTION SORT - ideal para vetores pequenos (até 20 elementos) */

template <class Comparable>
void insertionSort(vector<Comparable> &v)
{
 for (unsigned int p = 1; p < v.size(); p++)
 {
Comparable tmp = v[p];
int j;
for (j = p; j > 0 && tmp < v[j-1]; j--)
 v[j] = v[j-1];
v[j] = tmp;
 }
}

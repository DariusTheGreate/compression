#ifndef _RADIX_SORT_
#define _RADIX_SORT_

#include <iostream>

//doesnt work, in progress
template<typename Arr, size_t len>
class RadixSort
{
public:
	RadixSort(Arr* array_in, int len) : arr(array_in){
        quickSortIterative(0, len-1);
	}

private:
	Arr* arr;

    void swap(Arr* a, Arr* b)
    {
        Arr t = *a;
        *a = *b;
        *b = t;
    }

    Arr partition(int l, int h)
    {
        Arr x = arr[h];
        Arr i = (l - 1);

        for (int j = l; j <= h - 1; j++) {
            if (arr[j] <= x) {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
        swap(&arr[i + 1], &arr[h]);
        return (i + 1);
    }

    void quickSortIterative(int l, int h)
    {
        int stack[len];

        int top = -1;

        stack[++top] = l;
        stack[++top] = h;

        while (top >= 0) {
            h = stack[top--];
            l = stack[top--];

            Arr p = partition(l, h);

            if (--p > l) {
                stack[++top] = l;
                stack[++top] = p - 1;
            }

            if (++p < h) {
                stack[++top] = p + 1;
                stack[++top] = h;
            }
        }
    }
};

#endif

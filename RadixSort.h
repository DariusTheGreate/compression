#ifndef _RADIX_SORT_
#define _RADIX_SORT_

#include <iostream>

template<typename Arr, size_t len>
class RadixSort
{
public:
	RadixSort(Arr* array_in) : array(array_in){
		radixsort();
	}

private:
	Arr* array;
	int getMax(Arr& arr)
	{
		int mx = arr[0];
		for (int i = 1; i < len; i++)
			if (arr[i] > mx)
				mx = arr[i];
		return mx;
	}

	void countSort(Arr& arr, int exp)
	{
		int output[len]; // output array
		int i, count[10] = { 0 };

		for (i = 0; i < len; i++)
			count[(arr[i] / exp) % 10]++;

		for (i = 1; i < 10; i++)
			count[i] += count[i - 1];

		for (i = len - 1; i >= 0; i--) {
			output[count[(arr[i] / exp) % 10] - 1] = arr[i];
			count[(arr[i] / exp) % 10]--;
		}
		for (i = 0; i < len; i++)
			arr[i] = output[i];
	}

	void radixsort()
	{
		int m = getMax(*array);

		for (int exp = 1; m / exp > 0; exp *= 10)
			countSort(*array, exp);
		
		for (size_t i = 0; i < len; ++i) {
			std::cout << (*array)[i] << " ";
		}
	}
};

#endif

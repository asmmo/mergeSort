#include <iostream>
#include <vector>

template <class T>
void heapifyMax(std::vector<T>& arr, const size_t & rootInd, const size_t & heapEnd)
{
    size_t largestInd {rootInd};
    if(2 * rootInd + 1 < heapEnd && arr[2*rootInd + 1] > arr[rootInd])
        largestInd = 2 * rootInd + 1;

    if(2 * rootInd + 2 < heapEnd && arr[2*rootInd + 2] > arr[largestInd])
        largestInd = 2 * rootInd + 2;

    if(largestInd != rootInd) {
        std::swap(arr[largestInd], arr[rootInd ]);
        heapifyMax(arr, largestInd, heapEnd);
    }
}

template <class T>
void buildHeapMax(std::vector<T>& arr, const size_t & heapEnd)
{

    for(long int internals = heapEnd / 2; internals > - 1l; )
        heapifyMax(arr, internals--, heapEnd);
}

template <class T>
void heapSort(std::vector<T>& arr)
{
    size_t heapEnd = arr.size();
    buildHeapMax(arr, heapEnd);
    std::swap(arr[ 0 ], arr[ --heapEnd ]);

    while ( heapEnd > 0 ){
        heapifyMax(arr, 0, heapEnd);
        std::swap(arr[ 0 ], arr[ --heapEnd ]);

    }
}

int main()
{
    std::vector<int> A = {1,3,60,9,7,0, 0};

    heapSort(A);

    for(auto const & el : A)
        std::cout << el << ", ";
}

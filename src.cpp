#include <mutex>
#include <condition_variable>
#include <iostream>
#include <future>
#include <vector>
#include <utility>
#include <functional>

template <class T1, template<typename T2, typename T3 = std::allocator<T1>> class container>
void merge(container<T1>& cont, size_t beg, const size_t end){
    auto temp = cont;
    auto end1 = (beg + end) / 2;
    auto beg1 = beg;
    auto beg2 = end1 + 1;

    while( beg <= end){

        if(beg1 <= end1 && (beg2 > end || cont[beg1] < cont[beg2]) )
            temp[beg++] = cont[beg1++];
        else
            temp[beg++] = cont[beg2++];
    }
    cont = temp;
}

template <class T1, template<typename T2, typename T3 = std::allocator<T1>> class container>
void mergeSort(container<T1>& cont, const size_t beg, const size_t end){
    if( end - beg < 2 ) {
        if (cont[beg] > cont[end])  std::swap(cont[beg], cont[end]);
        return;
    }

    mergeSort(cont, beg, (beg+end)/2);
    mergeSort(cont, (beg+end)/2 + 1, end);
    merge(cont, beg, end);

}

int main(){
    std::vector<double> vec{{-9.4, 5, 5, 6, 7, 6, -90, 0}};
    for(auto const& el:vec)
        std::cout << el << " ";
    std::cout << "\n\n\n";
    mergeSort(vec, 0, vec.size()-1);
    for(auto const& el:vec)
        std::cout << el << " ";

}

/*
mergeSort O( nlg(n) )
Worst complexity: n*log(n)
Average complexity: n*log(n)
Best complexity: n*log(n)
Space complexity: n
stable: true
*/
#include <iostream>
#include <vector>

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
void mergeSort(container<T1>& cont, const size_t beg, const size_t end)
{
    if( end == beg  ) return;

    mergeSort(cont, beg, (beg+end)/2);
    mergeSort(cont, (beg+end)/2 + 1, end);
    merge(cont, beg, end);

}

int main()
{
    std::vector<double> vec{{-9.4, 5, 5, 6, 7, 6, -90, 0}};
    for(auto const& el:vec)
        std::cout << el << " ";
    std::cout << "\n\n\n";
    mergeSort(vec, 0, vec.size()-1);
    for(auto const& el:vec)
        std::cout << el << " ";

}




/*with contigious mem c++20*/
template <class T>
std::span<T> combine(std::span<T> x1, std::span<T> x2) {
    std::queue<T> combined;
    size_t smallest_index_not_combined_from_x1{};
    size_t smallest_index_not_combined_from_x2{};
    for (; smallest_index_not_combined_from_x1 < x1.size() &&
           smallest_index_not_combined_from_x2 < x2.size();) {
        if (x1[smallest_index_not_combined_from_x1] <=
            x2[smallest_index_not_combined_from_x2]) {
            combined.push(x1[smallest_index_not_combined_from_x1++]);
        } else {
            combined.push(x2[smallest_index_not_combined_from_x2++]);
        }
    }
    if (smallest_index_not_combined_from_x1 < x1.size()) {
        for (auto it = x1.begin() + smallest_index_not_combined_from_x1;
             it != x1.end(); ++it) {
            combined.push(std::move(*it));
        }
    }
    for (auto& el : x1) {
        el = std::move(combined.front());
        combined.pop();
    }
    for (auto& el : x2) {
        if (combined.empty()) break;
        el = std::move(combined.front());
        combined.pop();
    }
    return std::span{x1.begin(), x2.end()};
}

template <class T>
std::span<T> merge_sort(std::span<T> x) {
    if (x.size() < 2) return x;
    auto x1 = std::span(x.begin(), x.begin() + x.size() / 2);
    auto x2 = std::span(x.begin() + x.size() / 2, x.end());
    return combine(merge_sort(x1), merge_sort(x2));
}

int main() {
    std::vector a{'k', 'a', 'c', 'd', 'b'};
    merge_sort(std::span(a));
    for (auto& x : a) {
        std::cout << x;
    }
}

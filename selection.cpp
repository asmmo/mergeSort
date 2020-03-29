/*
 Worst complexity: n^2
Average complexity: n^2
Best complexity: n^2
Space complexity: 1
 */
#include <iostream>
#include <vector>

template<class T, template<class E, class R = std::allocator<T>> class cont>
void selectionSort(cont<T>& vec, size_t beg, size_t end){
    for (; beg < end; ++beg) {
        T* min = &vec[beg];
        for(size_t i {beg+1}; i <= end; ++i) {
            if(vec[i] < *min)
                min = &vec[i];
        }
        std::swap(vec[beg], *min);
    }
}

int main()
{
    std::vector<double> vec{{-9.4, 5, 5, 6, 7, 6, -90, 0}};
    for(auto const& el:vec)
        std::cout << el << " ";
    std::cout << "\n\n\n";
    selectionSort(vec, 0, vec.size()-1);
    for(auto const& el:vec)
        std::cout << el << " ";

}

#include <iostream>
#include <vector>

template<class T, template<class E, class R = std::allocator<T>> class cont>
void bubbleSort(cont<T>& vec, size_t beg, size_t end){
    for (; end; end--) {
        for(size_t i {beg}; i < end; ++i) {
            if(vec[i] > vec[i+1])
                std::swap(vec[i], vec[i+1]);
        }
    }
}

int main()
{
    std::vector<double> vec{{-9.4, 5, 5, 6, 7, 6, -90, 0}};
    for(auto const& el:vec)
        std::cout << el << " ";
    std::cout << "\n\n\n";
    bubbleSort(vec, 0, vec.size()-1);
    for(auto const& el:vec)
        std::cout << el << " ";

}

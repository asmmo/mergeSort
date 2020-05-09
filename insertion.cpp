/*
https://stackoverflow.com/questions/17270628/insertion-sort-vs-bubble-sort-algorithms
Insertion sort O(n^2)
Worst complexity: n^2
Average complexity: n^2
Best complexity: n
Space complexity: 1
stable(*) true
(*) Stable sort algorithms sort repeated elements in the same order that they appear in the input.
*/

//for (auto i = v.begin(); i != v.end(); ++i)     std::rotate(std::upper_bound(v.begin(), i, *i), i, i+1);


#include <vector>
#include <iostream>
template<typename E, template<class T, class alloc = std::allocator<T>> class container>
void insertionSort(container<E> & vec, size_t beg, size_t end)
{
    for(size_t i{beg+1}; i < end; ++i){
        for( size_t j = i; j > beg && vec[j] < vec [j-1]; --j)
            std::swap(vec[j], vec[j-1]);//space comp is Theta(1)
    }
}

int main(){
    std::vector<double> vec{{-9.4, 5, 5, 6, 7, 6, -90, 0,77, 7, -100, 4}};
    for(auto const& el:vec)
        std::cout << el << " ";
    std::cout << "\n\n\n";
    insertionSort(vec, 2, vec.size() - 3);
    for(auto const& el:vec)
        std::cout << el << " ";

}
/*----------------------STL Implementation-----------------------------*/
#include <vector>
#include <functional>
#include <iostream>

template <typename Iterator, typename Comparator = std::less<>>
void insertionSort( const Iterator & begin, const Iterator & end, Comparator callableComp = std::less<>{})
{
    if( begin == end ) return;
    for( Iterator i = begin + 1; i != end; )
    {
        for( Iterator j { i++ }; j != begin && callableComp( *j, *(j - 1) ); --j)
            std::swap(*j, *(j - 1));
    }
}

int main(){

    std::vector<int> vec {1, -2, 30, 7};

    insertionSort(vec.begin()+1, vec.end());
    for(auto const & el : vec) std::cout << el << ",";

}

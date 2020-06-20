//The follownig function uses FP (functional programming) pradigm. It facilitates the concurrency
/*
The term functional programming (FP) refers to a style of programming where the result of a function
call depends solely on the parameters to that function and doesn’t depend on any external state.
There is no reference/ptr, static or global vars
*/
template<typename T>
std::list<T> sequentialQuickSort(std::list<T> input)
{
    if(input.empty()) return input;

    std::list<T> result;
    result.splice(result.begin(),input,input.begin());
    T const& pivot=*result.begin();
    auto dividePoint=std::partition(input.begin(),input.end(), [&](T const& t){return t<pivot;});
    std::list<T> lower;
    lower.splice(lower.end(),input,input.begin(), dividePoint);

    auto newLower{ sequentialQuickSort(std::move(lower))};
    auto newHigher{ sequentialQuickSort(std::move(input))};
    result.splice(result.end(),newHigher);
    result.splice(result.begin(),newLower);
    return result;
}

template<typename T>
std::list<T> parallelQuickSort(std::list<T> input)
{

    if(input.empty()) return input;

    std::list<T> result;
    result.splice(result.begin(),input,input.begin());
    T const& pivot=*result.begin();
    auto dividePoint=std::partition(input.begin(),input.end(), [&](T const& t){return t<pivot;});
    std::list<T> lower;
    lower.splice(lower.end(),input,input.begin(), dividePoint);

    std::future<std::list<T> > newLower{ std::async(&parallelQuickSort<T>,std::move(lower))};
    auto newHigher{ parallelQuickSort(std::move(input))};
    result.splice(result.end(),newHigher);
    result.splice(result.begin(),newLower.get() );
    return result;

}

#ifndef MATHFUNC_H
#define MATHFUNC_H
#include <utility>
#include <iterator>
#include <cmath>

template <class InputIterator, class T>
std::pair<T,T> calculateMeanStDv (InputIterator first, InputIterator last, T init)
{
    if(first==last)
        return std::pair<T,T>(*first,0);

    for(InputIterator i=first;i<last;i++)
    {
        init+=*i;
    }
    int count=std::distance(first,last);
    T mean= init/count;

    T dispersio=0;
    for(InputIterator i=first;i<last;i++)
    {
        dispersio+=std::pow((*i)-mean,2);
    }
    dispersio=dispersio/count;
    T stdv= std::sqrt(dispersio);
    return std::pair<T,T>(mean,stdv);

}


template <class InputIterator, class T, class UnaryOperation>
std::pair<T,T> calculateMeanStDv (InputIterator first, InputIterator last, T init, UnaryOperation extractWtC)
{
    if(first==last)
        return std::pair<T,T>(extractWtC(first),0);
    for(InputIterator i=first;i<last;i++)
    {
        init+=extractWtC(i);
    }
    int count=std::distance(first,last);
    T mean= init/count;

    T dispersio=0;
    for(InputIterator i=first;i<last;i++)
    {
        dispersio+=std::pow(extractWtC(i)-mean,2);
    }
    dispersio=dispersio/count;
    T stdv= std::sqrt(dispersio);
    return std::pair<T,T>(mean,stdv);

}
#endif // MATHFUNC_H

#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED
#include<cstring>
#define USE_STD_LIST
namespace datastruture{
    const unsigned int  PrimeTableSize=17;

    template<class T>
    void swap(T& a,T& b)
    {
        T tmp = a;
        a = b;
        b = tmp;
    };

    template <typename T>
    class datatraits
    {
    public:
        typedef typename T::value_type value_type;
        typedef typename T::value_type size_type;
    };

    template<>
    class datatraits<int>
    {
    public:
        typedef int value_type;
        typedef int size_type;
    };

    template <typename T>
    class HashObj
    {
    public:
      typedef typename datatraits<T>::size_type size_type;
      size_type operator()(const T& val)
      {
          return (val%PrimeTableSize);
      }

    };

};


#endif // UTILITY_H_INCLUDED

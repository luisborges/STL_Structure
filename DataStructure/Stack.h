#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include "Queue.h"

template<class T,class Container=Deque<T> >
class Stack
{
public:
    typedef int size_type;

    Stack():c()
    {

    }
    explicit Stack(const Container& container)
    :c(container)
    {

    }
    ~Stack()
    {

    }
    void push(const T&val)
    {
       c.push_back(val);
    }
    void pop()
    {
        c.pop_back();
    }
    T top()
    {
      return c.front();
    }

    size_type size()
    {
        return c.size();
    }
    bool empty()
    {
        return c.empty();
    }
private:
    Container c;
};


#endif // STACK_H_INCLUDED

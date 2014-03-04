#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

//采用std::allocator<T>进行内存管理与分配
#include<exception>
#include<memory>
//using namespace std;
template<class T,class Alloc=std::allocator<T> >
class Vector
{
public:
    typedef T value_type;
    typedef int size_type;
    typedef T* iterator;
    typedef T* pointer;

    Vector():first(0),last(0),tail(0)
    {

    }
    Vector(size_type count)
    {
        _construct_n(count,T());
    }
    Vector(size_type count,const T& val)
    {
        _construct_n(count,val);
    }
    Vector(const Vector& right)
    {
        if(_growcapicity(right.size()))
            last = _ucopy(right.begin(),right.end());

    }
    Vector& operator=(const Vector& right)
    {
        if(this==&right);
        else
        {
            if(right.size()==0)
                clear();
            else if(right.size()<size())
            {
              clear();
              _ucopy(right.begin(),right.end(),first);
              last = first + right.size();
            }
            else if(right.size()<capacity())
            {
              clear();
              _ucopy(right.begin(),right.end(),first);
              last = first + right.size();
            }
            else
            {
                if(first!=0)
                    _tidy();
                if(_growcapicity(right.size()))
                {
                    _ucopy(right.begin().right.end(),first);
                    last  = first + right.size();
                }
            }
        }

        return (*this);
    }

    ~Vector()
    {
        _tidy();
    }
    void assign(iterator tobegin,iterator toend)
    {
       if((toend - tobegin)>capacity())
       {
           if(_growcapicity(toend-tobegin))
                _ucopy(tobegin,tail,first);
       }
       else
       {

       }
    };
    void assign(size_type count,const value_type& val)
    {

    };
    value_type at(size_type index)
    {
        return*(first+index);
    };
    value_type back()
    {
        return *(last - 1);
    };
	iterator begin()
	{
        return first;
	};
    size_type capacity()
    {
        return (first==0?0:tail-first);
    };

    void clear()
    {
        erase(begin(),end());
    };
   // void crbegin();
    //void crend();
    //void emplace();
    //void emplace_back();
    bool empty()
    {
        return (first==last);
    };
    iterator erase(iterator tobegin,iterator toend=0)
    {
        if(_invaliditerator(tobegin)&&_invaliditerator(toend)&&tobegin>=toend)
        {
          if(!toend)
            return erase(tobegin,tobegin+1);
         pointer res = tobegin;
          for(;res<toend;res++)
          {
              this->alloc.destroy(res);
          }
          _ucopy(toend,last,tobegin);
          last = tobegin +(last-toend);
        }
        return tobegin;


    };

    iterator end()
    {
        return last;
    };

    value_type front()
    {
        return (*first);
    };
    iterator insert(iterator where,const value_type& val)
    {
        size_type off = 0;
        if(_invaliditerator(where))
        {
            off = size()==0?0:where-begin();
            insert(where,(size_type)1,val);
            return (begin()+off);
        }
        else
            throw exception("Iteraor Out of Range!");

    };
    void insert(iterator where, size_type count, const value_type& val)
    {
        size_type off = 0;
        if(_invaliditerator(where))
        {
            off = size()==0?0:where-begin();
            if(count==0);
            else if(max_size()<count+size())
               throw  exception("Insert Too Much!");
            else if(capacity()<size()+count)
            {
                size_type cap = max_size()<(capacity()+capacity()/2)?
                                0:(capacity()+capacity()/2);
                if(cap<(count+size()))
                    cap=count+size();
                pointer newvec = this->alloc.allocate(cap);

                _ufill(newvec+off,count,val);
                _ucopy(first,where,newvec);
                _ucopy(where,last,newvec+off+count);

                if(first!=0)
                {
                    _tidy();
                }

                first = newvec;
                last = newvec+count+size();
                tail = newvec+cap;

            }
            else
            {
                _umove(begin+off,last,where);
                _ufill(begin+off,count,val);

                last = last + count;
            }
        }
        else
            throw exception("Iteraor Out of Range!");

    };
    void insert(iterator where, iterator tobegin, iterator toend)
    {
        size_type off = 0;
        if(!_invaliditerator(where))
        {
             throw exception("Iteraor Out of Range!");
        }
        else
        {
            size_type count = toend - tobegin;

             off = size()==0?0:where-begin();
            if(count==0);
            else if(max_size()<count+size())
               throw  exception("Insert Too Much!");
            else if(capacity()<size()+count)
            {
                size_type cap = max_size()<(capacity()+capacity()/2)?
                                0:(capacity()+capacity()/2);
                if(cap<count+size())
                    cap = count +size();
                pointer newvec = this->alloc.allocate(cap);

                _ucopy(tobegin,toend,newvec+off);
                _ucopy(first,where,newvec);
                _ucopy(where,last,newvec+off+count);

                if(first!=0)
                {
                    _tidy();
                }

                first = newvec;
                last = newvec+count+size();
                tail = newvec+cap;

            }
            else
            {
                _umove(first+off,last,where);
                _ucopy(tobegin,toend,first+off);

                last = last + count;
            }

        }
    };

    void pop_back()
    {
        erase(end()-1,end());
    };
    void push_back(value_type val)
    {
        insert(end(),val);
    };
/*
    reverse_iterator rbegin()
    {

    };
    reverse_iterator rend()
    {

    };
*/
    void reserve(size_type count)
    {
        if(max_size()<count)
            throw exception("Reserve too Much!@");
        else if(capacity()<count)
        {
            pointer newvec = this->alloc.allocate(count);

            _ucopy(first,last,newvec);
            if(first!=0)
                _tidy();

            first = newvec;
            last = newvec + size();
            tail = newvec + count;
        }
    };
    void resize(size_type count,T val=T())
    {
        if(size()<count)
            insert(end(),count,val);
        else if(count<size())
            erase(begin()+count,end());
    };
    size_type size()
    {
        return (last - first);
    };
    size_type max_size()
    {
        return size_t(-1)/sizeof(T);
    }
    void swap(Vector<T>& right)
    {
        if(this==&right);
        else if(this->alloc==right.alloc)
        {
            std::swap(first,right.first);
            std::swap(last,right.last);
            std::swap(tail,right.tail);
        }
        else
        {
            Vector temp = *this;
            *this = right;
            right = temp;
        }

    };

private:

    bool _invaliditerator(pointer it)
    {
        return (it>=first&&it<last);
    }

    bool _growcapicity(size_type count)
    {
        if(count==0)
            return true;
        else if(max_size()<count)
        {
            throw exception("Grow too Much!");
            return false;
        }
        else
        {
            first = this->alloc.allocate(count);
            last = first;
            tail = first+count;
        }
        return true;

    };

    void _construct_n(size_type count,const T& val)
    {
      if(_growcapicity(count))
      {
          last = _ufill(first,count,val);
      }
    };

    void _ufill(pointer where,size_type count,const T& val)
    {
        pointer res=where;
        for(size_type i=0;i<count;i++)
        {
            this->alloc.construct(res,val);
            res+=1;
        }
        return (where+count);
    }

    void _ucopy(pointer tobegin,pointer toend,pointer where)
    {
        pointer temp=tobegin;
        pointer res=where;

        for(;temp!=tail;temp++)
        {
            this->alloc.construct(where,*temp);
            res+=1;
        }

    }

    void _umove(pointer tobegin,pointer toend,pointer where)
    {
        pointer temp = where + (toend - tobegin)-1;
        pointer it = toend -1;
        for(;toend !=tobegin-1;--toend)
        {
            this.alloc.construct(*temp);
            temp = temp-1;
        }
    }
    void _tidy()
    {
        if(first!=0)
        {
            pointer res = first;
            for(;res!=last;res++)
            {
                this->alloc.destroy(res);
            }
            this->alloc.deallocate(first,tail-first);
        }
        first = 0;
        last = 0;
        tail = 0;
    }
private:
    pointer first;
    pointer last;
    pointer tail;

    static Alloc alloc;
};

template<class T,class Alloc>
Alloc Vector<T,Alloc>::alloc;
#endif // VECTOR_H_INCLUDED

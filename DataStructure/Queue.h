#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#include "Utility.h"
#include<vector>
#include<memory>
#include<iostream>
#include<exception>
using namespace std;
//-------------deque的实现原理-------------------------
/*
	T**  _Map;	// pointer to array of pointers to blocks
	size_type _Mapsize;	// size of map array
	size_type _Myoff;	// offset of initial element
	size_type _Mysize;	// current length of sequence

_Map指向一个数组，该数组元素为指针,_Mapsize表示数组的大小；
_Map中的每一个指针，均指向一个block，block表示一个数组，其中
存放的元素即为deque维护的元素；
因为deque可以双端操作，故deque中维护两个位置：_Myoff表示deque
的第一个(队头元素)距离_Map起始的偏移量，_Mysize表示deque中维护
的元素数量。
注意：利用图形说明更清晰。

*/


template<class T>
class Deque
{
public:
    typedef int size_type;
    typedef T* iterator;

    static    const int DEQUEMAPSIZE = 8;//_Mapsize至少为1
    static  const int DEQUESIZ =(sizeof(T)<=1?16 \
                             :sizeof(T)<=2?8 \
                             :sizeof(T)<=4?4 \
                             :sizeof(T)<=8?2:1);//每一个block数组的大小，均为2的幂数

    Deque(): _Map(0),_Mapsize(0), _Myoff(0), _Mysize(0)
    {
    }
    Deque(const Deque& right): _Map(0),_Mapsize(0), _Myoff(0), _Mysize(0)
    {
        insert(begin(),right.begin(),right.end());
    }
    ~Deque()
    {
       _tidy();
    }


    void assign(size_type count,const T& val)
    {
        T tmp = val;
        erase(begin(),end());
        insert(begin(),count,tmp);
    }
    const T& at(size_type pos)
    {
        if(pos<=_Mysize)
            return *((*_Map)+_Myoff+pos-1);
        else
            return;
            //throw runtime_error("out_of_range!");
    }
    const T& back()
    {
        return *((*_Map)+_Myoff+_Mysize-1);
    }
    const T& front()
    {
        return *((*_Map)+_Myoff);
    }
    void clear()
    {
        _tidy();
    }

    void pop_back()
    {
        if(empty())
            return;
        size_type newoff = _Mysize+_Myoff-1;
        size_type block = newoff/DEQUESIZ;

        //当newoff比较靠近map后部，且deque中元素数目（_Mysize）比较大，
        //block会比map的大小要大，此时表明deque的队尾在map 的前部，故需要
        //做如下处理。
        if(_Mapsize<=block)
            block-=_Mapsize;
        _Map[block][newoff%DEQUESIZ]=0;
        //memset((*(_Map+block)+newoff%DEQUESIZ),0,sizeof(T));
        if(--_Mysize==0)
            _Myoff-=0;
    }

    void pop_front()
    {
        if(empty())
            return;
        //size_type newoff = _Myoff;
        size_type block = _Myoff/DEQUESIZ;
        _Map[block][_Myoff%DEQUESIZ]=0;
        //memset((*(_Map+block)+_Myoff%DEQUESIZ),0,sizeof(T));
        if(_Mapsize*DEQUESIZ<=++_Myoff)
            _Myoff-=0;
        if(--_Mysize==0)
            _Myoff-=0;

    }

     void push_back(T& val)
        {
            //判断队列空间是否已经完全被使用：判断条件很重要
            //1. 队末指针指向block的尾部；
            //2. 数组内剩余空间不足一个block的大小；
            if((_Myoff+_Mysize)%DEQUESIZ==0
               &&_Mapsize<=(_Mysize+DEQUESIZ)/DEQUESIZ)
               _growmap(1);
            size_type newoff = _Myoff + _Mysize;
            size_type block = newoff/DEQUESIZ;

            //元素个数如果超过map的下界，则回到开头的空间继续存储
            if(_Mysize<=block)
                block-=_Mysize;
            if(_Map[block]==0)
                _Map[block] = new T[DEQUESIZ];
            _Map[block][newoff%DEQUESIZ] = T(val);
            _Mysize+=1;

        }

    void push_front(T& val)
    {
         //判断队列空间是否已经完全被使用：判断条件很重要
            //1. 队头指针指向block的头部；
            //2. 数组内剩余空间不足一个block的大小；
            //【注】：与Push_back的第一个判断条件不太一样
            //判断与_growmap包含了队列在_Map中的多种情况：
            //1)普通的队头在前，队尾在后；
            //2)队尾越过index为Mapsize*DEQUESIZ界限，跑到_Map空间中前面的block中；
            //3)队头越过index为0的界限，跑到_Map空间中最后面的block中；
            if((_Myoff)%DEQUESIZ==0
               &&_Mapsize<=(_Mysize+DEQUESIZ)/DEQUESIZ)
               _growmap(1);
            size_type newoff = _Myoff!=0?_Myoff:_Mapsize*DEQUESIZ;
            size_type block = --newoff/DEQUESIZ;

            if(_Map[block]==0)
                _Map[block] = new T[DEQUESIZ];
            _Map[block][newoff%DEQUESIZ] = T(val);
            _Myoff = newoff;
            _Mysize+=1;
    }

    bool empty()
    {
        return (_Mysize==0);
    }

    T* begin()
    {
        return ((*_Map)+_Myoff);
        //return &(_map[(Myoff+_Mysize)%DEQUESIZ][_Mysize%DEQUESIZ]);
    }

    T* end()
    {
        return ((*_Map)+_Myoff+_Mysize);
        //return &(_map[(Myoff+_Mysize)%DEQUESIZ][_Mysize%DEQUESIZ]);
    }
    iterator erase(iterator first,iterator last)
    {
        if(last<first||first<begin()||last>end())
            //throw runtime_error("Iterator Invalid!");
            return 0;
        size_type off = first - begin();
        size_type count = (last - first);

        if(off<(end()-last))
        {
            int mvcount = first-begin();
            memcpy(last-mvcount,begin(),mvcount);
            for(;count>0;--count)
                pop_front();//begin()已经变化
        }
        else
        {
            int mvcount = end()-last;
            memcpy(first,last,mvcount);
            for(;count>0;--count)
                pop_back();//begin()未发生变化
        }
        return (begin()+off);//指向删除元素之后的下一个元素
    }

    void insert(iterator where,size_type count,const T& val)
    {
        iterator mid;
        size_type  num = 0;
        size_type off = where - begin();
        size_type rem = _Mysize - off;
        size_type oldsize = _Mysize;

        if(_Mysize<off)
            //throw runtime_error("Iterator Insert invalid!");
            return;

        if(off<rem)
        //贴近font
        {
            if(off<count)
            {
                for(num=count-off;num>0;--num)
                    push_front(val);
                for(num=off;num>0;--num)
                    push_back(begin()[count-1]);//注意begin在变化,count-1保持不变

                mid = begin()+count;
                std::fill(mid,mid+off,val);

            }
            else
            {
                for(num=count;num>0;--num)
                    push_back(begin()[count-1]);//注意begin在变化,count-1保持不变

                mid = begin()+count;
                T tmp = val;
                std::copy(mid+count,mid+off,mid);
                std::fill(begin+off,mid+off,tmp);
             }
             for(;oldsize<_Mysize;)
                pop_front();

        }
        else
        //贴近back
        {
            if(rem<count)
            {
                for(num=count-rem;num>0;--num)
                    push_back(val);
                for(num=0;num<rem;++num)
                    push_back(begin()[off+num]);//注意begin在变化,count-1保持不变

                mid = begin()+off;
                std::fill(mid,mid+rem,val);

            }
            else
            {
                for(num=rem;num>0;--num)
                    push_back(begin()[off+rem-count+num]);

                mid = begin()+off;
                T tmp = val;

                //向后拷贝，注意第三个参数与copy不一样：
                //普通拷贝为开始地址，向后为结束地址
                std::copy_backward(mid+count,mid+rem-count,mid+rem);
                std::fill(begin+off,mid+off,tmp);
             }
             for(;oldsize<_Mysize;)
                pop_back();

        }
    }

    void insert(iterator where,iterator first,iterator last)
    {
        size_type off = where - begin();
        size_type rem = _Mysize - off;
        size_type oldsize = _Mysize;

        if(first==last);
        else if(off<rem)
        {
            for(;first!=last;++first)
                push_front((T)*first);
            size_type num = _Mysize - oldsize;
            if(off!=0)
            {
               reverse(num,num+off);
               reverse(0,num+off);
            }
            else
                reverse(0,num);
        }
        else
        {
            for(;first!=last;++first)
                push_back((T)*first);
            size_type num = _Mysize - oldsize;
            if(rem!=0)
            {
               reverse(off,off+rem);
               reverse(off+rem,_Mysize);
               reverse(off,_Mysize);
            }

        }
    }
    void reverse(iterator first,iterator last)
    {
        iterator start = begin();
        for(;first!=last&&first!=--last;first++)
            datastruture::swap<T>(start[first],start[last]);
    }
    size_type size()
    {
        return _Mysize;
    }

    iterator rbegin()
    {
        return ((*_Map)+_Myoff+_Mysize-1);
    }
    iterator rend()
    {
        return ((*_Map)+_Myoff-1);
    }

    void resize(size_type count, const T& val)
    {
		if (_Mysize < count)
			insert(end(), count - _Mysize, val);
		else if (count < _Mysize)
			erase(begin() + count, end());
    }

private:
    void _growmap(size_type count)
    {
        size_type inc = _Mapsize/2;
        if(inc<DEQUEMAPSIZE)
            inc = DEQUEMAPSIZE;
        if(count<inc)
            count = inc;
        size_type blockoff = _Myoff/DEQUEMAPSIZE;
        T** newmap = new T*[_Mapsize+count];//(写new (T*)[_Mapsize+count]不正确
        T** newoff = newmap + blockoff;
        newoff = memcpy(newoff,_Map+blockoff,sizeof(T)*_Mysize);
        //参照push_back与push_front实现，当map尾部无空间时，
        //将把新插入队尾的元素放进map头部，故重新申请空间的时候，
        //需要将旧的map头部的数据copy给新的map
        //内存拷贝覆盖了列在_Map中分布的多种情况：
            //1)普通的队头在前，队尾在后；
            //2)队尾越过index为Mapsize*DEQUESIZ界限，跑到_Map空间中前面的block中；
            //3)队头越过index为0的界限，跑到_Map空间中最后面的block中；
        if(blockoff<=count)
        {
            newoff = memcpy(newoff,_Map,sizeof(T)*blockoff);
            memset(newoff,0,sizeof(T)*(count-blockoff));
            memset(newmap,0,sizeof(T)*blockoff);
        }
        else
        {
            memcpy(newoff,_Map,sizeof(T)*count);
            newoff = memcpy(newmap,_Map+count,sizeof(T)*(blockoff-count));
            memset(newoff,0,count);
        }

        //释放旧的map的空间
        delete []_Map;
        //memset(_Map,0,_Mapsize);
        //free(_Map);

        _Map = newmap;
        _Mapsize +=count;
     }

     void _tidy()
     {
        while(!empty)
            pop_back();
        for(size_type count = _Mapsize;0<count;)
        {
            if(*(_Map+--count)!=0)
                delete [](*(_Map+count));
        }
        if(_Map)
            delete []_Map;
        _Mapsize=0;
        _Map=0;
     }
private:
	T**  _Map;	// pointer to array of pointers to blocks
	size_type _Mapsize;	// size of map array
	size_type _Myoff;	// offset of initial element
	size_type _Mysize;	// current length of sequence

};

template<class T,class Container=Deque<T> >
class Queue
{
public:

    typedef int size_type;

    Queue():c()
    {

    }
    explicit Queue(const Container& container)
    :c(container)
    {

    }
    ~Queue()
    {

    }

    void push(const T&val)
    {
       c.push_back(val);
    }
    void pop()
    {
        c.pop_front();
    }
    T front()
    {
      return c.front();
    }
    T back()
    {
       return c.back();
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

template<class T,class Container=std::vector<T>,class Compare=std::less<T> >
class Priority_Queue
{
public:
    typedef T value_type;
    typedef int size_type;


    Priority_Queue(const Container& s=Container(),const Compare&comp=Compare())
                    :_c(s),_comp(comp)
    {

    }
    void push(const value_type& val)
    {
        _c.push_back(val);
        _make_heap();
        /*
        size_type index = this->size();
        while(index>0)
        {
            if(_comp(_c[(index-1)/2],val))
            {
                _c[index]=_c[(index-1)/2];
                index = (index-1)/2;
            }
            else
                break;
        }
        _c[index]=val;
        */
    }

    void pop()
    {
        if(this->empty())
            return;
        if(this->size()==1)
        {
            _c.pop_back();
            return;
        }
        else
        {
            datastruture::swap<value_type>(_c[0],_c[_c.size()-1]);
            _c.pop_back();
            _make_heap();
            return;
        }

        /*
        size_type index = 0;
        size_type child;
        while(index<(this->size())/2)
        {
            child = _leftchild(index);
             if(_comp(_c[child],_c[child+1]))
                child++;
            if(_comp(_c[index],_c[child]))
                datastruture::swap<value_type>(_c[index],_c[child]);
            index=child;

        }
        if(index!=this->size()-1)
        {
            datastruture::swap<value_type>(_c[index],_c[_c.size()-1]);
        }
       */

    }

    value_type top()
    {
        if(this->size())
            return _c.front();
        return value_type(0);
    }
    bool empty()
    {
        return _c.empty();
    }
    size_type size()
    {
        return _c.size();
    }

    void print()
    {
        for(typename Container::size_type i=0;i<_c.size();++i)
            std::cout<<_c[i]<<" ";
        std::cout<<endl;
    }
private:
    void _make_heap()
    {
        if(this->size()<2)
            return;
        size_type index = this->size()-2;
        index/=2;
        size_type child = 0;
        while(index>=0)
        {
            child = _leftchild(index);
            if(child!=(this->size()-1)&&_comp(_c[child],_c[child+1]))
                child++;
            if(_comp(_c[index],_c[child]))
                datastruture::swap<value_type>(_c[index],_c[child]);
            index--;
        }
        return;

    }
    size_type _leftchild(size_type index)
    {
        return (2*index+1);
    }
private:
    Container _c;
    Compare _comp;
};
#endif // QUEUE_H_INCLUDED

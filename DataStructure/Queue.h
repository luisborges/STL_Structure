#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#include "Utility.h"
#include<vector>
#include<memory>
#include<iostream>
#include<exception>
using namespace std;
//-------------deque��ʵ��ԭ��-------------------------
/*
	T**  _Map;	// pointer to array of pointers to blocks
	size_type _Mapsize;	// size of map array
	size_type _Myoff;	// offset of initial element
	size_type _Mysize;	// current length of sequence

_Mapָ��һ�����飬������Ԫ��Ϊָ��,_Mapsize��ʾ����Ĵ�С��
_Map�е�ÿһ��ָ�룬��ָ��һ��block��block��ʾһ�����飬����
��ŵ�Ԫ�ؼ�Ϊdequeά����Ԫ�أ�
��Ϊdeque����˫�˲�������deque��ά������λ�ã�_Myoff��ʾdeque
�ĵ�һ��(��ͷԪ��)����_Map��ʼ��ƫ������_Mysize��ʾdeque��ά��
��Ԫ��������
ע�⣺����ͼ��˵����������

*/


template<class T>
class Deque
{
public:
    typedef int size_type;
    typedef T* iterator;

    static    const int DEQUEMAPSIZE = 8;//_Mapsize����Ϊ1
    static  const int DEQUESIZ =(sizeof(T)<=1?16 \
                             :sizeof(T)<=2?8 \
                             :sizeof(T)<=4?4 \
                             :sizeof(T)<=8?2:1);//ÿһ��block����Ĵ�С����Ϊ2������

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

        //��newoff�ȽϿ���map�󲿣���deque��Ԫ����Ŀ��_Mysize���Ƚϴ�
        //block���map�Ĵ�СҪ�󣬴�ʱ����deque�Ķ�β��map ��ǰ��������Ҫ
        //�����´���
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
            //�ж϶��пռ��Ƿ��Ѿ���ȫ��ʹ�ã��ж���������Ҫ
            //1. ��ĩָ��ָ��block��β����
            //2. ������ʣ��ռ䲻��һ��block�Ĵ�С��
            if((_Myoff+_Mysize)%DEQUESIZ==0
               &&_Mapsize<=(_Mysize+DEQUESIZ)/DEQUESIZ)
               _growmap(1);
            size_type newoff = _Myoff + _Mysize;
            size_type block = newoff/DEQUESIZ;

            //Ԫ�ظ����������map���½磬��ص���ͷ�Ŀռ�����洢
            if(_Mysize<=block)
                block-=_Mysize;
            if(_Map[block]==0)
                _Map[block] = new T[DEQUESIZ];
            _Map[block][newoff%DEQUESIZ] = T(val);
            _Mysize+=1;

        }

    void push_front(T& val)
    {
         //�ж϶��пռ��Ƿ��Ѿ���ȫ��ʹ�ã��ж���������Ҫ
            //1. ��ͷָ��ָ��block��ͷ����
            //2. ������ʣ��ռ䲻��һ��block�Ĵ�С��
            //��ע������Push_back�ĵ�һ���ж�������̫һ��
            //�ж���_growmap�����˶�����_Map�еĶ��������
            //1)��ͨ�Ķ�ͷ��ǰ����β�ں�
            //2)��βԽ��indexΪMapsize*DEQUESIZ���ޣ��ܵ�_Map�ռ���ǰ���block�У�
            //3)��ͷԽ��indexΪ0�Ľ��ޣ��ܵ�_Map�ռ���������block�У�
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
                pop_front();//begin()�Ѿ��仯
        }
        else
        {
            int mvcount = end()-last;
            memcpy(first,last,mvcount);
            for(;count>0;--count)
                pop_back();//begin()δ�����仯
        }
        return (begin()+off);//ָ��ɾ��Ԫ��֮�����һ��Ԫ��
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
        //����font
        {
            if(off<count)
            {
                for(num=count-off;num>0;--num)
                    push_front(val);
                for(num=off;num>0;--num)
                    push_back(begin()[count-1]);//ע��begin�ڱ仯,count-1���ֲ���

                mid = begin()+count;
                std::fill(mid,mid+off,val);

            }
            else
            {
                for(num=count;num>0;--num)
                    push_back(begin()[count-1]);//ע��begin�ڱ仯,count-1���ֲ���

                mid = begin()+count;
                T tmp = val;
                std::copy(mid+count,mid+off,mid);
                std::fill(begin+off,mid+off,tmp);
             }
             for(;oldsize<_Mysize;)
                pop_front();

        }
        else
        //����back
        {
            if(rem<count)
            {
                for(num=count-rem;num>0;--num)
                    push_back(val);
                for(num=0;num<rem;++num)
                    push_back(begin()[off+num]);//ע��begin�ڱ仯,count-1���ֲ���

                mid = begin()+off;
                std::fill(mid,mid+rem,val);

            }
            else
            {
                for(num=rem;num>0;--num)
                    push_back(begin()[off+rem-count+num]);

                mid = begin()+off;
                T tmp = val;

                //��󿽱���ע�������������copy��һ����
                //��ͨ����Ϊ��ʼ��ַ�����Ϊ������ַ
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
        T** newmap = new T*[_Mapsize+count];//(дnew (T*)[_Mapsize+count]����ȷ
        T** newoff = newmap + blockoff;
        newoff = memcpy(newoff,_Map+blockoff,sizeof(T)*_Mysize);
        //����push_back��push_frontʵ�֣���mapβ���޿ռ�ʱ��
        //�����²����β��Ԫ�طŽ�mapͷ��������������ռ��ʱ��
        //��Ҫ���ɵ�mapͷ��������copy���µ�map
        //�ڴ濽������������_Map�зֲ��Ķ��������
            //1)��ͨ�Ķ�ͷ��ǰ����β�ں�
            //2)��βԽ��indexΪMapsize*DEQUESIZ���ޣ��ܵ�_Map�ռ���ǰ���block�У�
            //3)��ͷԽ��indexΪ0�Ľ��ޣ��ܵ�_Map�ռ���������block�У�
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

        //�ͷžɵ�map�Ŀռ�
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

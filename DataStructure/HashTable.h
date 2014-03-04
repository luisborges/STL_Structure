#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#include "Utility.h"

#if defined(USE_STD_LIST)
    #include<list>
#else
    #include "List.h"
#endif



template<class T,class Hash=datastruture::HashObj<T> >
class HashTable
{

public:
    typedef T value_type;
    typedef std::size_t size_type;

    HashTable(size_type count):hasher(datastruture::HashObj<T>())
    {
        this->count = count;
        this->table = new value_type[count];
        //this->hasher = datastruture::HashObj<T>();
        this->sential = new char[count];
        std::memset(this->table,0,sizeof(value_type)*count);
        std::memset(this->sential,0,sizeof(char)*count);
        this->size = 0;
    }

    ~HashTable()
    {
        if(this->table!=NULL)
        {
            delete []this->table;
            this->table = NULL;
        }
        if(this->sential!=NULL)
        {
            delete []this->sential;
            this->sential = NULL;
        }
    }


    void insert (value_type val)
    {
        if(find(val)!=-1)
            return;
        else
        {
            size_type pos = this->hasher(val);
            while(pos<this->count)
            {
                if(this->table[pos]==0)
                {
                    this->table[pos]=val;
                    this->size++;
                    break;
                }
                pos++;
            }

        }
    }

    int find(value_type val)
    {
        size_type pos = this->hasher(val);
        if(this->table[pos]==0&&this->sential[pos]==0)
            return -1;
        while(pos<this->count)
        {
            if(this->table[pos]==val)
                return pos;
            if(this->table[pos]==0&&this->sential[pos]==0)
                return -1;
            pos++;
        }
        return -1;
    }
    void remove(value_type val)
    {
        int pos = this->find(val);
        if(pos<0)
            return;
        this->table[pos]=0;
        this->sential[pos]=1;
        this->size--;
    }


    size_type getsize()
    {
        return this->size;
    }

private:
    size_type count;
    value_type *table;

    size_type size;
    Hash hasher;
    char* sential;
};


#endif // HASHTABLE_H_INCLUDED





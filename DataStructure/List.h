#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include "Utility.h"
#include <iostream>
using namespace std;
//#define NULL 0

template<class T>
class Node
{
public:
    Node* next;
    Node* pre;
    T  val;

    Node(){}
    ~Node(){next = NULL;pre = NULL;val.~T();}
};

template<class T>
class List
{
public:
/*'
    class Node
    {
    public:
        Node* next;
        Node* pre;
        T  val;

        Node(){}
        ~Node(){next = NULL;pre = NULL;val.~T();}
    };
*/
    typedef  Node<T>* _ListNode;
    typedef  unsigned int size_type;


    List():_head(NULL),_size(0)
    {
        this->_head = new Node<T>();
        this->_head->next = this->_head;
        this->_head->pre = this->_head;
    }

    void push_back(T val)
    {
        _ListNode node = new Node<T>();
        if(!node)
            return;
        node->val = val;

        node->pre = this->_head->pre;
        node->next = this->_head;
        this->_head->pre->next = node;
        this->_head->pre = node;

        this->_size+=1;
    }

    void pop_back()
    {
        _ListNode temp = this->_head->pre;
        this->_head->pre = this->_head->pre->pre;
        temp->pre->next = this->_head;

        this->_size-=1;

        delete temp;
    }

    void push_front(T val)
    {
        _ListNode node = new Node<T>();
        if(!node)
            return;
        node->val = val;

        node->pre = this->_head;
        node->next = this->_head->next;
        this->_head->next->pre = node;
        this->_head->next = node;

        this->_size+=1;
    }

    void pop_front()
    {
        _ListNode temp = this->_head->next;
        this->_head->next = this->_head->next->next;
        temp->next->pre = this->_head;

        this->_size-=1;
        delete temp;
    }

    T back()
    {
        if(!this->empty())
            return this->_head->pre->val;
        else
            return T(0);
    }

    T front()
    {
        if(!this->empty())
            return this->_head->next->val;
        else
            return T(0);
    }

    bool empty()
    {
        return (this->_size==0);
    }
    size_type size()
    {
        return this->_size;
    }


    void remove(T val)
    {
        _ListNode tmp = this->_head->next;
        while(tmp!=this->_head)
        {
            if(tmp->val==val)
            {
                tmp->pre->next = tmp->next;
                tmp->next->pre = tmp->pre;
                this->_size-=1;
                delete tmp;
                break;
            }
            else
                tmp = tmp->next;
        }
    }

    void unique()
    {
        _ListNode tmp = this->_head->next;
        _ListNode freenode = NULL;
        while(tmp!=this->_head)
        {
            if(tmp->val==tmp->next->val)
            {
                freenode = tmp;

                tmp->pre->next = tmp->next;
                tmp->next->pre = tmp->pre;
                tmp = tmp->next;

                this->_size-=1;
                delete freenode;
            }
            else
                tmp = tmp->next;
        }

    }

    void reverse()
    {
        _ListNode iternode = this->_head->next;
        _ListNode tmp = NULL;
        while(iternode!=this->_head)
        {
            tmp = iternode->next;
            swap<_ListNode>(iternode->pre,iternode->next);
            iternode = tmp;
        }
         swap<_ListNode>(this->_head->pre,this->_head->next);
    }

    void resize(size_type newsize,T val=0)
    {
            size_type i = 0;
            size_type numsize = this->_size;
            /*手动实现
            _ListNode endnode = NULL;
            _ListNode iternode = this->_head;
            _ListNode rmnode = NULL;
            */
            if(numsize>newsize)
            {
                /*手动实现
                while(i<this->_size)
                {
                    iternode = iternode->next;
                    i+=1;
                    if(i==newsize)
                        endnode = iternode;
                    else if(i>newsize)
                    {
                        rmnode = iternode;
                        delete rmnode;
                        rmnode = NULL;
                    }
                }
            endnode->next = this->_head;
            this->_head->pre = endnode;
            this->_size = newsize;
            */
            //调用pop_pack实现
                while(i<numsize-newsize)
                {
                    pop_back();
                    i+=1;
                }
            }
            else if(numsize<newsize)
            {
                while(i<newsize-numsize)
                {
                    this->push_back(val);
                    i+=1;
                }

            }
            //this->_size = newsize;

    }

    void sort()
    {
       // if(this->_size<2)
        //    return;
        _ListNode ordernode = this->_head->next;
        _ListNode minnode = NULL;
        _ListNode tempnode = NULL;
        while(ordernode->next!=this->_head)
        {
            minnode = ordernode;
            tempnode = ordernode->next;
            while(tempnode!=this->_head)
            {
               if(tempnode->val<minnode->val)
                    minnode = tempnode;
                tempnode = tempnode->next;
            }
            datastruture::swap<T>(ordernode->val,minnode->val);
            ordernode = ordernode->next;
        }
    }
    void printout()
    {
        cout<<"----正序打印-----"<<endl;
        _ListNode tempnode = this->_head->next;
        while(tempnode!=this->_head)
        {
            cout<<tempnode->val<<endl;
            tempnode = tempnode->next;
        }


    }
    void rprintout()
    {
        cout<<"----逆序打印-----"<<endl;
        _ListNode tempnode = this->_head->pre;
        while(tempnode!=this->_head)
        {
            cout<<tempnode->val<<endl;
            tempnode = tempnode->pre;
        }

    }
private:
    _ListNode _head;
    size_type _size;
};


#endif // LIST_H_INCLUDED

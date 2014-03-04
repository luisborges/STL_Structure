
#include "List.h"
#include "Queue.h"
#include "HashTable.h"
#include "Vector.h"
//#include "BinaryTree.h"


#include <set>
#include<vector>
#include<stdlib.h>
//#include<queue>
#include <iostream>

using namespace std;

int main()
{
  //  priority_queue<int> pqu;

    /*
    double aa =1;
	void* bb=&aa;
	void* cc=bb+1;
	//int dd = cc -bb;
 int xx = sizeof(bb);
	char e = 'a';
	char* ff =&e;
	char* gg = ff+1;
	int hh = gg -ff;
int yy =sizeof(ff);
    vector<int> vec;

vector<int> vec;
vec.push_back(0);

vector<int> vec1;
vec1.push_back(1);
vec1.push_back(1);
vec1.push_back(1);
vec1.push_back(1);
vec1.push_back(1);

std::cout<<"0 vec size: "<<vec.size()<<endl;
std::cout<<"0 vec Cap: "<<vec.capacity()<<endl;
std::cout<<"0 vec1 size: "<<vec1.size()<<endl;
std::cout<<"0 vec1 Cap: "<<vec1.capacity()<<endl;

vec1.pop_back();
vec1.pop_back();
vec1.pop_back();
vec1.pop_back();

std::cout<<"1 vec size: "<<vec.size()<<endl;
std::cout<<"1 vec Cap: "<<vec.capacity()<<endl;
std::cout<<"1 vec1 size: "<<vec1.size()<<endl;
std::cout<<"1 vec1 Cap: "<<vec1.capacity()<<endl;


vec = vec1;

std::cout<<"2 vec size: "<<vec.size()<<endl;
std::cout<<"2 vec Cap: "<<vec.capacity()<<endl;
std::cout<<"2 vec1 size: "<<vec1.size()<<endl;
std::cout<<"2 vec1 Cap: "<<vec1.capacity()<<endl;


    List<int> lst;
    int a = lst.empty();

    lst.push_back(9);
	lst.push_back(5);
	lst.push_back(3);
	lst.push_front(2);

    lst.sort();
    lst.printout();

	lst.remove(5);
	a = lst.back();
	a = lst.front();
	lst.printout();

	lst.resize(10,8);
	a = lst.back();
	a = lst.front();
	a = lst.size();
	lst.printout();

	lst.resize(3,7);
	a = lst.back();
	a = lst.front();
	a = lst.size();
	lst.printout();

	lst.push_back(2);
	lst.push_front(2);
	lst.push_back(2);
	lst.printout();
    a = lst.back();
	a = lst.front();
	a = lst.size();
    lst.printout();

	lst.unique();
	a = lst.back();
	a = lst.front();
	a = lst.size();
	lst.printout();

	lst.reverse();
	a = lst.back();
	a = lst.front();
	a = lst.size();
	lst.printout();

    HashTable<int> hatbl(17);
    hatbl.insert(9);
    hatbl.insert(8);
    hatbl.insert(7);
    hatbl.insert(6);
    hatbl.insert(15);
    hatbl.insert(17);
    hatbl.insert(2);

    cout<<"HashTable Size: "<<hatbl.getsize()<<endl;
    hatbl.insert(8);
    cout<<"HashTable Size: "<<hatbl.getsize()<<endl;
    hatbl.insert(26);
    cout<<"HashTable Size: "<<hatbl.getsize()<<endl;

    int pos = hatbl.find(7);
    cout<<"HashTable 7 Pos: "<<pos<<endl;
    pos = hatbl.find(26);
    cout<<"HashTable 26 Pos: "<<pos<<endl;
    pos = hatbl.find(9);
    cout<<"HashTable 9 Pos: "<<pos<<endl;
    hatbl.remove(17);
    cout<<"HashTable Size: "<<hatbl.getsize()<<endl;
    hatbl.remove(9);
    cout<<"HashTable Size: "<<hatbl.getsize()<<endl;
    hatbl.remove(26);
    cout<<"HashTable Size: "<<hatbl.getsize()<<endl;
*/
/*
    BinaryTree<int> bst(15);

    bst.insert(12);
    bst.insert(3);
    bst.insert(13);
    bst.insert(8);
    bst.insert(7);
    bst.insert(10);
    bst.insert(5);

    bst.insert(18);
    bst.insert(16);
    bst.insert(20);


  //  bst.insert(12);
  //  bst.insert(18);
    bst.clear(bst.root);
    cout << "****Recur PreOrder****" << endl;
    bst.PreOrderVisit(bst.root,true);
    std::cout<<std::endl;
    cout << "----NonRecur PreOrder---" << endl;
    bst.PreOrderVisit(bst.root,false);
    std::cout<<std::endl;
    std::cout<<std::endl;

    bst.clear(bst.root);
   // std::cout<<"Clear: "<<std::endl;
   // bst.PreOrderVisit(bst.root,false);
   // std::cout<<std::endl;
    cout << "****Recur InOrder****" << endl;
    bst.InOrderVisit(bst.root,true);
    std::cout<<std::endl;
    cout << "----NonRecur InOrder---" << endl;
    bst.InOrderVisit(bst.root,false);
    std::cout<<std::endl;
    std::cout<<std::endl;

    bst.clear(bst.root);
    cout << "****Recur PassOrder****" << endl;
    bst.PassOrderVisit(bst.root,true);
    std::cout<<std::endl;
    cout << "----NonRecur PassOrder---" << endl;
    bst.PassOrderVisit(bst.root,false);
    std::cout<<std::endl;
    std::cout<<std::endl;

    bst.clear(bst.root);
    cout << "++++Level PassOrder++++" << endl;
    bst.LevelOrderVisit(bst.root);
    std::cout<<std::endl;


    cout << "%%%% Function Test %%%%" << endl;
    BinaryTree<int>::TreeNode* res = bst.find(8);
    cout<<"Find "<<res->data<<endl;
    cout<<"size "<<bst.getsize()<<endl;

    bst.remove(8);
    cout<<"size "<<bst.getsize()<<endl;
    bst.remove(15);
    cout<<"size "<<bst.getsize()<<endl;

    bst.clear(bst.root);
    cout << "++++Level PassOrder++++" << endl;
    bst.LevelOrderVisit(bst.root);
    std::cout<<std::endl;
*/
    Priority_Queue<int> pqe;
    pqe.push(1);
    pqe.push(7);
    pqe.push(5);
    pqe.push(9);
    pqe.push(2);
    cout<<"%Pqe Size: "<<pqe.size()<<endl;
    pqe.push(8);
    pqe.push(4);
    cout<<"%Pqe Size: "<<pqe.size()<<endl;
    pqe.print();
    Priority_Queue<int>::value_type temp = pqe.top();
    cout<<"--Pqe Max: "<<temp<<endl;
    pqe.pop();
    pqe.print();
    cout<<"%Pqe Size: "<<pqe.size()<<endl;

    temp = pqe.top();
    cout<<"--Pqe Max: "<<temp<<endl;
    cout<<"%Pqe Size: "<<pqe.size()<<endl;

    bool em = pqe.empty();
    cout<<"?Pqe Empty?: "<<em <<endl;


    cout<<endl;
    cout << "Hello world!" << endl;
    system("pause");
    return 0;
}

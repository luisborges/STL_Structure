#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED

#include "Utility.h"
#include<iostream>
#include<stack>
#include<queue>
template<typename T>
struct NodeBase
{
    NodeBase(T val=0):data(T(val)),parent(NULL),left(NULL),right(NULL),visited(false){};
    ~NodeBase()
    {
        if(parent!=NULL)
        {
            //delete parent;
            parent = NULL;
        }
        if(left!=NULL)
        {
            //delete left;
            left = NULL;
        }
        if(right!=NULL)
        {
            //delete right;
            right = NULL;
        }
    }
    T data;
    NodeBase* parent;
    NodeBase* left;
    NodeBase* right;
    bool visited;
};

template<typename T>
class BinaryTree
{
public:
    typedef T value_type;
    typedef NodeBase<T> TreeNode;
    TreeNode* root;
    std::size_t size;

public:
    BinaryTree(value_type rootval=0):root(new TreeNode(rootval)),size(1)
    {
        //this->root=new TreeNode(rootval);
        /*
        root->parent = NULL;
        root->left = NULL;
        root->right = NULL;
        root->data = rootval;
        root->visited = false;
        */
    }
    ~BinaryTree()
    {
        _destroy(this->root);
    }
    TreeNode* insert(value_type val)
    {
        TreeNode* node = new TreeNode(val);
        TreeNode* temp = root;
        TreeNode* preTemp = NULL;
        while(temp!=NULL)
        {
            preTemp = temp;
            if(val<preTemp->data)
                temp = preTemp->left;
            else
                temp = preTemp->right;
        }

        if(val<preTemp->data)
            preTemp->left = node;
        else
            preTemp->right = node;

        node->parent = preTemp;
        this->size++;
        return this->root;
    }

    TreeNode* remove(value_type val)
    {
        TreeNode* temp = find(val);
        if(temp==NULL)
            return this->root;

        //递归
        /*
        if(temp->right==NULL&&temp->left==NULL)
        {
            if(temp==temp->parent->left)
                temp->parent->left = NULL;
            else if(temp==temp->parent->right)
                temp->parent->right = NULL;

        }
        else if(temp->right==NULL)
        {
            if(temp==temp->parent->left)
                temp->parent->left = temp->left;
            else if(temp==temp->parent->right)
                temp->parent->right = temp->left;
            //return this->root;
        }
        else if(temp->left==NULL)
        {
            if(temp==temp->parent->left)
                temp->parent->left = temp->right;
            else if(temp==temp->parent->right)
                temp->parent->right = temp->right;
            //return this->root;
        }
        else
        {
            TreeNode* node = _findSuccessor(temp);
            temp->data = node->data;
            ((TreeNode*)(temp->right))->remove(node->data);
        }
        delete temp;
    */
        //非递归

        TreeNode* toDelNode = NULL;
        if(temp->right==NULL||temp->left==NULL)
            toDelNode=temp;
        else
            toDelNode = _findSuccessor(temp);

        TreeNode* chlTemp = NULL;
        if(toDelNode->left!=NULL)
            chlTemp=toDelNode->left;
        else
            chlTemp=toDelNode->right;

        if(chlTemp!=NULL)
            chlTemp->parent = toDelNode->parent;
        if(toDelNode->parent==NULL)
            this->root = chlTemp;
        else if(toDelNode==toDelNode->parent->left)
            toDelNode->parent->left = chlTemp;
        else
            toDelNode->parent->right = chlTemp;

        if(temp!=toDelNode)
            temp->data = toDelNode->data;
        delete toDelNode;

        this->size--;
        return this->root;
    }

    TreeNode* find(value_type val)
    {
        TreeNode* temp = root;
        while(temp!=NULL)
        {
            if(temp->data==val)
                return temp;
            else if(val<temp->data)
                temp = temp->left;
            else
                temp = temp->right;
        }
        return NULL;
    }

    void PreOrderVisit(TreeNode* root,bool beRecur=false)
    {
        if(root==NULL)
            return;

        TreeNode* temp = root;

        if(beRecur)//递归
        {
            if(temp!=NULL)
            {
                std::cout<<temp->data<<" ";
                PreOrderVisit(temp->left,beRecur);
                PreOrderVisit(temp->right,beRecur);
            }

            return;//此语句很重要，没有就会无限循环输出最底层的左节点
        }
        else //非递归
        {
            std::stack<TreeNode*>  stk;
            std::cout<<temp->data<<" ";
            temp->visited = true;
            stk.push(temp);
            while(!stk.empty())
            {
                while(temp->left!=NULL)
                {
                    temp=temp->left;
                    std::cout<<temp->data<<" ";
                    temp->visited = true;
                    stk.push(temp);
                }
                TreeNode* node = stk.top();
                if(node->right!=NULL&&!node->right->visited)
                {
                    temp=node->right;
                    std::cout<<temp->data<<" ";
                    temp->visited = true;
                    stk.push(temp);
                    continue;
                }
                stk.pop();
            }

        }
    }

    void InOrderVisit(TreeNode* root,bool beRecur=false)
    {
         if(root==NULL)
            return;

        TreeNode* temp = root;

        if(beRecur)//递归
        {
            if(temp!=NULL)
            {
                InOrderVisit(temp->left,beRecur);
                std::cout<<temp->data<<" ";
                InOrderVisit(temp->right,beRecur);
            }

            return;//此语句很重要，没有就会无限循环输出最底层的左节点
        }
        else
        {
            std::stack<TreeNode*>  stk;

            stk.push(temp);
            while(!stk.empty())
            {
                while(temp->left!=NULL)
                {
                    temp=temp->left;
                    stk.push(temp);
                }

                TreeNode* node = stk.top();
                std::cout<<node->data<<" ";
                stk.pop();

                if(node->right!=NULL)
                {
                    temp=node->right;
                    stk.push(temp);
                    continue;
                }

            }

        }

    }


    void PassOrderVisit(TreeNode* root,bool beRecur=false)
    {
        if(root==NULL)
            return;

        TreeNode* temp = root;

        if(beRecur)//递归
        {
            if(temp!=NULL)
            {
                PassOrderVisit(temp->left,beRecur);
                PassOrderVisit(temp->right,beRecur);
                std::cout<<temp->data<<" ";
            }

            return;//此语句很重要，没有就会无限循环输出最底层的左节点
        }
        else
        {
            std::stack<TreeNode*>  stk;
            stk.push(temp);
            while(!stk.empty())
            {
                while(temp->left!=NULL)
                {
                    temp=temp->left;
                    //std::cout<<temp->data<<" ";
                    //temp->visited = true;
                    stk.push(temp);
                }
                TreeNode* node = stk.top();
                if(node->visited)
                {
                    std::cout<<node->data<<" ";
                    stk.pop();
                }
                //node->visited = true;
                else if(node->right!=NULL&&!node->right->visited)
                {
                    node->visited = true;
                    temp=node->right;
                    //std::cout<<temp->data<<" ";
                    //temp->visited = true;
                    stk.push(temp);
                    continue;
                }
                else
                {
                    node->visited = true;
                    std::cout<<node->data<<" ";
                    stk.pop();
                }

            }
        }
    }


    void LevelOrderVisit(TreeNode* root)
    {
        if(root==NULL)
            return;

        TreeNode* temp = root;

        std::queue<TreeNode*> que;
        que.push(temp);
        while(!que.empty())
        {
            TreeNode* node = que.front();
            std::cout<<node->data<<" ";
            que.pop();
            if(node->left!=NULL)
                que.push(node->left);
            if(node->right!=NULL)
                que.push(node->right);
        }
        return;
    }

    void clear(TreeNode* root)
    {
        if(root==NULL)
            return;

        TreeNode* temp = root;
        if(temp!=NULL)
        {
            temp->visited=false;
            clear(temp->left);
            clear(temp->right);
        }
        return;

    }

    std::size_t getsize()
    {
        return this->size;
    }
private:
    void _destroy(TreeNode* node)
    {
        if(node==NULL)
            return;
        TreeNode* temp = this->root;
        if(temp->left)
            _destroy(temp->left);
        if(temp->right)
            _destroy(temp->right);
        delete temp;

    }
    TreeNode* _findSuccessor(TreeNode* node)
    {
        if(node==NULL)
            return NULL;
        if(node->right!=NULL)
            return _findMin(node->right);
        else
        {
            TreeNode* temp = node;
            TreeNode* pre = node->parent;
            while(pre&&temp==pre->right)
            {
                temp = pre;
                pre = pre->parent;
            }
            return pre;
        }

    }
    TreeNode* _findMin(TreeNode* node)
    {
        if(node==NULL)
            return NULL;
        TreeNode* temp = node;
        TreeNode* preTemp = NULL;
        while(temp)
        {
            preTemp = temp;
            temp = temp->left;
        }

        return preTemp;
    }

};

#endif // BINARYTREE_H_INCLUDED

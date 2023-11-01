#include <bits/stdc++.h>
#include <ctime>
#include <fstream>
#include <chrono>
using namespace std;
typedef long long ll;
class Node
{
public:
    int key;
    Node *left, *right;
    int height;
    Node(int k1) : key(k1), left(nullptr), right(nullptr), height(1) {}
};
class bstAvl
{
    Node *root;

public:
    bstAvl() { root = nullptr; }
    int maxHeight(Node *node)
    {
        if (node == nullptr)
            return 0;
        int left = 1 + maxHeight(node->left);
        int right = 1 + maxHeight(node->right);
        return max(left, right);
    }
    int Height(Node *node)
    {
        if (node == nullptr)
            return 0;
        return node->height;
    }
    /*
        node            x
         /\            / \
        A  x    =>  node  z
           /\        /\
          y  z      A  y
    */
    Node *leftRotate(Node *node)
    {
        Node *x = node->right;
        Node *y = x->left;
        x->left = node;
        node->right = y;
        node->height = 1 + max(Height(node->left), Height(node->right));
        x->height = 1 + max(Height(x->left), Height(x->right));
        return x;
    }
    /*
        node          x
         /\          / \
        x  A  =>    z  node
       /\               / \
      z  y             y   A
    */
    Node *rightRotate(Node *node)
    {
        Node *x = node->left;
        Node *y = x->right;
        x->right = node;
        node->left = y;
        node->height = 1 + max(Height(node->left), Height(node->right));
        x->height = 1 + max(Height(x->left), Height(x->right));
        return x;
    }
    void preorder(Node *node)
    {
        if (!node)
            return;
        cout << node->key;
        if (node->left == nullptr and node->right == nullptr)
            return;
        cout << "(";
        preorder(node->left);
        cout << ",";
        preorder(node->right);
        cout << ")";
    }
    void inorder(Node *node)
    {
        if (node == nullptr)
            return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }
    void traverse()
    {
        inorder(root);
        cout << endl;
    }
    double traversal()
    {
        auto start = chrono::high_resolution_clock::now();
        inorder(root);
        cout << endl;
        auto end = chrono::high_resolution_clock::now();
        return chrono::duration_cast<chrono::duration<double, milli>>(end - start).count();
    }
    void print()
    {
        preorder(root);
    }
    bool findUtil(Node *node, int key)
    {
        if (node == nullptr)
            return false;
        if (key == node->key)
            return true;
        else if (key < node->key)
            return findUtil(node->left, key);
        else
            return findUtil(node->right, key);
    }
    string Find(int key)
    {
        if (findUtil(root, key))
            return "found\n";
        else
            return "not found\n";
    }
    double findWithClock(int key){
        auto start = chrono::high_resolution_clock::now();
        bool found = findUtil(root,key);
        auto end = chrono::high_resolution_clock::now();
        cout <<((found)?"found":"not found")<<endl;
        return chrono::duration_cast<chrono::duration<double, milli>>(end - start).count();
    }
    Node *insertUtil(Node *node, int key)
    {
        if (node == nullptr)
            return new Node(key);
        if (key < node->key)
            node->left = insertUtil(node->left, key);
        else
            node->right = insertUtil(node->right, key);
        int difference = Height(node->left) - Height(node->right);
        node->height = 1 + max(Height(node->left), Height(node->right));
        if (difference > 1)
        {
            if (key > node->left->key) // means height of left child is greater and the new inserted node is at right subtree of left child
                node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        else if (difference < -1)
        {
            if (key < node->right->key) // means height of right child is greater and the new inserted node is at left subtree of right child
                node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }
    void insert(int key)
    {
        root = insertUtil(root, key);
        print();
        cout << endl;
    }
    double insertWithClock(int key)
    {
        auto start = chrono::high_resolution_clock::now();
        root = insertUtil(root, key);
        auto end = chrono::high_resolution_clock::now();
        print();
        cout << endl;
        return chrono::duration_cast<chrono::duration<double, milli>>(end - start).count();
    }
    Node *getMin(Node *node)
    {
        if (node->left == nullptr)
            return node;
        return getMin(node->left);
    }
    Node *getMax(Node *node)
    {
        if (node->right == nullptr)
            return node;
        return getMax(node->right);
    }

    Node *deleteUtil(Node *node, int key)
    {
        if (node == nullptr)
            return node;
        if (key < node->key)
            node->left = deleteUtil(node->left, key);
        else if (key > node->key)
            node->right = deleteUtil(node->right, key);
        else
        {

            if (node->left == nullptr)
            {
                Node *temp = node;
                node = node->right;
                delete temp;
            }
            else if (node->right == nullptr)
            {
                Node *temp = node;
                node = temp->left;
                delete temp;
            }
            else
            {
                node->key = getMin(node->right)->key;
                node->right = deleteUtil(node->right, node->key);
            }
        }
        if (node == nullptr)
            return node;
        int difference = Height(node->left) - Height(node->right);
        node->height = 1 + max(Height(node->left), Height(node->right));
        // cout<<node->key<<" "<< maxHeight(node->left)<<" "<<maxHeight(node->right)<<endl;
        if (difference > 1)
        {
            // cout<<"out of bal "<<node->key<<endl;
            if (Height(node->left->left) < Height(node->left->right))
                node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        else if (difference < -1)
        {
            // cout<<"out of bal "<<node->key<<endl;
            if (Height(node->right->right) < Height(node->right->left))
                node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }
    void Delete(int key)
    {
        root = deleteUtil(root, key);
        print();
        cout << endl;
    }
    double deleteWithClock(int key)
    {
         auto start = chrono::high_resolution_clock::now();
        root = deleteUtil(root, key);
        auto end = chrono::high_resolution_clock::now();print();
        cout << endl;
        return chrono::duration_cast<chrono::duration<double, milli>>(end - start).count();
    
    }
};
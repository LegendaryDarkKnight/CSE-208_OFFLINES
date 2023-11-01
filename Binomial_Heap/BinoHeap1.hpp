#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Node
{
public:
    int degree, value, level;
    Node *leftChild, *rightSibling, *parent;
    Node(int val) : value(val), degree(0), rightSibling(nullptr), leftChild(nullptr), parent(nullptr), level(-1) {}
};
class BinoHeap
{
private:
    list<Node *> _heap;
    Node *minNode;
public:
    BinoHeap();
    ~BinoHeap();
    list<Node *> getHeap()
    {
        return _heap;
    }
    Node *join(Node *node1, Node *node2)
    {
        if (node1->value < node2->value)
        {
            node2->rightSibling = node1->leftChild;
            node1->leftChild = node2;
            node2->parent = node1;
            node1->degree += 1;
            return node1;
        }
        else
        {
            node1->rightSibling = node2->leftChild;
            node2->leftChild = node1;
            node1->parent = node2;
            node2->degree += 1;
            return node2;
        }
    }
    list<Node *> MELD2(list<Node *> _heap1, list<Node *> _heap2)
    {
        auto it1 = _heap1.begin();
        auto it2 = _heap2.begin();
        stack<Node *> stck;
        while (it1 != _heap1.end() and it2 != _heap2.end())
        {
            if ((*it1)->degree == (*it2)->degree)
            {
                stck.push(join((*it2), (*it1))); // matched all ans when it changed to this sequence in join
                it1++, it2++;
            }
            else if ((*it1)->degree < (*it2)->degree)
            {
                if (stck.size() and stck.top()->degree == (*it1)->degree)
                {
                    auto temp = stck.top();
                    stck.pop();
                    stck.push(join( (*it1),temp));
                }
                else
                    stck.push((*it1));
                it1++;
            }
            else
            {
                if (stck.size() and stck.top()->degree == (*it2)->degree)
                {
                    auto temp = stck.top();
                    stck.pop();
                    stck.push(join((*it2),temp));
                }

                else
                    stck.push((*it2));
                it2++;
            }
        }
        while (it1 != _heap1.end())
        {
            if (stck.size() and stck.top()->degree == (*it1)->degree)
            {
                auto temp = stck.top();
                stck.pop();
                stck.push(join((*it1),temp));
            }
            else
                stck.push((*it1));
            it1++;
        }
        while (it2 != _heap2.end())
        {
            if (stck.size() and stck.top()->degree == (*it2)->degree)
            {
                auto temp = stck.top();
                stck.pop();
                stck.push(join((*it2),temp));
            }

            else
                stck.push((*it2));
            it2++;
        }
        list<Node *> temp;
        while(stck.size()){
            temp.push_front(stck.top());
            stck.pop();
        }
        return temp;
    }
    list<Node *> MELD(list<Node *> _heap1, list<Node *> _heap2)
    {
        int maxDegree = 0;
        list<Node *> temp;
        for (auto h : _heap1)
            maxDegree = max(maxDegree, h->degree);
        for (auto h : _heap2)
            maxDegree = max(maxDegree, h->degree);
        queue<Node *> collection[maxDegree + 2];
        for (auto h : _heap2)
            collection[h->degree].push(h);
        for (auto h : _heap1)
            collection[h->degree].push(h);
        for (int i = 0; i <= maxDegree + 1; i++)
        {
            if (collection[i].size() == 1)
            {
                temp.push_back(collection[i].front());
                collection[i].pop();
                continue;
            }
            else if (collection[i].size() >= 2)
            {
                Node *n1 = collection[i].front();
                collection[i].pop();
                Node *n2 = collection[i].front();
                collection[i].pop();
                Node *n3 = join(n1, n2);
                collection[i + 1].push(n3);
                if (collection[i].size())
                {
                    temp.push_back(collection[i].front());
                    collection[i].pop();
                }
            }
        }
        return temp;
    }
    void insert(int val)
    {
        Node *temp = new Node(val);
        if (_heap.size() == 0)
        {
            minNode = temp;
            _heap.push_back(temp);
            return;
        }
        if(temp->value < minNode->value)
            minNode = temp;
        list<Node *> tempHeap = {temp};
        _heap = MELD2(_heap, tempHeap);
    }
    Node *getMin()
    {
        return minNode;
    }
    Node *extractMin()
    {
        Node *temp = getMin(), *v;
        list<Node *> _temp1, _temp2;
        for (auto h : _heap)
        {
            if (temp != h)
            {
                _temp1.push_back(h);
            }
        }
        Node *i = temp->leftChild;
        while (i)
        {
            i->parent = nullptr;
            v = i->rightSibling;
            i->rightSibling = nullptr;
            _temp2.push_front(i);
            i = v;
        }
        _heap = MELD2(_temp1, _temp2);
        minNode = _heap.front();
        for (auto h : _heap)
        {
            if ( h->value < minNode->value)
                minNode = h;
        }
        return temp;
    }
    void Union(BinoHeap &b)
    {
        _heap = MELD2(_heap, b.getHeap());
        minNode = _heap.front();
        for (auto h : _heap)
        {
            if ( h->value < minNode->value)
                minNode = h;
        }
    }
    void printTree(Node *h)
    {
        int currentLevel = -1;
        queue<Node *> q;
        q.push(h);
        while (!q.empty())
        {
            Node *currentNode = q.front();
            q.pop();

            if (currentNode->level != currentLevel)
            {
                cout << "\nLevel " << currentNode->level << " : ";
                currentLevel = currentNode->level;
            }

            cout << currentNode->value << " ";

            Node *child = currentNode->leftChild;
            while (child != nullptr)
            {
                child->level = currentNode->level + 1;
                q.push(child);
                child = child->rightSibling;
            }
        }
    }
    void printHeap()
    {
        cout << "Printing Binomial Heap..." << endl;
        for (auto h : _heap)
        {
            cout << "Binomial Tree, B" << h->degree;
            h->level = 0;
            printTree(h);
            cout << endl;
        }
    }
};

BinoHeap::BinoHeap(/* args */)
{
    minNode = nullptr;
}

BinoHeap::~BinoHeap()
{
}

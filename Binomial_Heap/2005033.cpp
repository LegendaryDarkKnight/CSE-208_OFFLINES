#include "BinoHeap1.hpp"

// success in all cases

int main()
{
    // freopen("..\\..\\Generator\\in4.txt","r",stdin);
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    char ins;
    string s;
    int num;
    BinoHeap bHeap;
    vector<string> query;
    while (cin >> s)
    {
        query.push_back(s);
    }
    int i = 0;
    while (i < query.size())
    {
        if (query[i][0] == 'U')
        {
            i++;
            BinoHeap temp;
            while (i < query.size())
            {
                if (query[i][0] >= 'A')
                    break;
                temp.insert(stoi(query[i]));
                i++;
            }
            bHeap.Union(temp);
        }
        else if (query[i][0] == 'I')
        {
            bHeap.insert(stoi(query[i + 1]));
            i += 2;
        }
        else if (query[i][0] == 'E')
        {
            if (bHeap.getMin() == nullptr)
                cout << "Empty Heap" << endl;
            else
                cout << "Extract-Min returned " << bHeap.extractMin()->value << endl;
            i++;
        }
        else if (query[i][0] == 'F')
        {
            if (bHeap.getMin() == nullptr)
                cout << "Empty Heap" << endl;
            else
                cout << "Find-Min returned " << bHeap.getMin()->value << endl;
            i++;
        }
        else if (query[i][0] == 'P')
        {
            bHeap.printHeap();
            i++;
        }
        else
        {
            break;
        }
    }
}
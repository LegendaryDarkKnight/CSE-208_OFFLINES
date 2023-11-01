#include <bits/stdc++.h>
class DSU
{
private:
    int *parent;
    int *size;

public:
    DSU(int n);
    ~DSU();
    void make_set(int v);
    int find_set(int v);
    void pair_set(int a, int b);
};

DSU::DSU(int n)
{
    parent = new int[n];
    size = new int[n];
}

DSU::~DSU()
{
    delete parent;
    delete size;
}

void DSU::make_set(int v)
{
    parent[v] = v;
    size[v] = 1;
}

int DSU::find_set(int v)
{
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void DSU::pair_set(int a, int b)
{
    int a1 = find_set(a);
    int b1 = find_set(b);
    if (a1 != b1)
    {
        if (size[a1] < size[b1])
        {
            parent[a1] = b1;
            size[b1] += size[a1];
        }
        else
        {
            parent[b1] = a1;
            size[a1] += size[b1];
        }
    }
}

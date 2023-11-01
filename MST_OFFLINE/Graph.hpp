#include <bits/stdc++.h>
#include <cmath>
using namespace std;
class Triplet
{
public:
    double d;
    int u, v;
    Triplet(int u, int v, double d)
    {
        this->u = u, this-> v = v, this->d = d;   
    }

}; 
class Pair
{
    int v;
    double wt;

public:
    Pair(int v = -1, double wt = INFINITY)
    {
        this->v = v, this->wt = wt;
    }
    int getV() { return v; }
    double getWt() { return wt; }
    void setV(int v) { this->v = v; }
    void setWt(double wt) { this->wt = wt; }
};

class Graph
{

    // vector<vector<Pair>> adj;
    list<Pair> *adj;
    vector<Triplet> edgeList;

public:
    Graph(int n = 1)
    {
        // adj.resize(n);
        adj = new list<Pair>[n];
    }
    void addEdge(int u, int v, double wt)
    {
        adj[u].push_back(Pair(v, wt));
        adj[v].push_back(Pair(u, wt));
        edgeList.push_back(Triplet(u,v,wt));
    }
    vector<Triplet> getEdge() { return edgeList; }
    list<Pair> successor(int n)
    {
        return adj[n];
    }
};

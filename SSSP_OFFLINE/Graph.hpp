#include <bits/stdc++.h>
#include <cmath>
#include <cfloat>
typedef long long ll;
using namespace std;
class Triplet
{
public:
    ll d;
    ll u, v;
    Triplet(ll u, ll v, ll d)
    {
        this->u = u, this-> v = v, this->d = d;   
    }

}; 
class Pair
{
    ll v;
    ll wt;

public:
    Pair(ll v = -1, ll wt = LONG_LONG_MAX)
    {
        this->v = v, this->wt = wt;
    }
    ll getV() { return v; }
    ll getWt() { return wt; }
    void setV(ll v) { this->v = v; }
    void setWt(ll wt) { this->wt = wt; }
};

class Graph
{

    vector<vector<Pair>> adj;
    vector<Triplet> edgeList;

public:
    Graph(ll n = 1)
    {
        adj.resize(n);
    }
    void addEdge(ll u, ll v, ll wt, bool un)
    {
        adj[u].push_back(Pair(v, abs(wt)));
        if(un)
            adj[v].push_back(Pair(u, abs(wt)));
        edgeList.push_back(Triplet(u,v,wt));
    }
    vector<Triplet> getEdge() { return edgeList; }
    vector<Pair> successor(ll n)
    {
        return adj[n];
    }
    void prll()
    {
        for(ll i=0; i<adj.size(); i++)
        {
            cout<<i<<": ";
            for(auto v:adj[i])
            {
                cout<<v.getV()<<"("<<v.getWt()<<") ";
            }
            cout<<endl;
        }
    }
};

#include "PQueue.hpp"
#include "Graph.hpp"

ll ssspD(ll n, Graph graph, vector<ll> &tree, ll src, ll dst)
{
    ll ans = 0;
    PQueue<ll, ll> pqueue(n);
    ll parent[n];
    ll weights[n];
    pqueue.insertKey(src, 0);
    parent[src] = src;
    weights[src] = 0;
    for (ll i = 0; i < n; i++)
    {
        if (i == src)
            continue;
        pqueue.insertKey(i, LONG_LONG_MAX);
        weights[i] = LONG_LONG_MAX;
    }
    while (pqueue.size())
    {
        pair<ll, ll> u = pqueue.getMin();
        pqueue.extractMin();
        for (auto &p : graph.successor(u.first))
        {
            if (weights[p.getV()] > u.second + p.getWt())
            {
                weights[p.getV()] = u.second + p.getWt();
                parent[p.getV()] = u.first;
                pqueue.decreaseKey(p.getV(), weights[p.getV()]);
            }
        }
    }
    ll i = dst;
    if (weights[dst] != LONG_LONG_MAX)
    {
        while (parent[i] != i)
        {
            tree.push_back(i);
            i = parent[i];
        }
    }

    return weights[dst];
}
void ssspB(ll n, Graph graph, ll src, ll dst)
{
    ll parent[n];
    ll weights[n];
    bool change[n];
    weights[src] = 0;
    for (ll i = 0; i < n; i++)
    {
        if (i != src)
            weights[i] = LONG_LONG_MAX;
        // cout<<weights[i]<<endl;
        parent[i] = -1;
    }
    for (ll i = 0; i < n - 1; i++)
    {
        for (auto e : graph.getEdge())
        {
            if (weights[e.u] != LONG_LONG_MAX and weights[e.v] > weights[e.u] + e.d)
            {
                weights[e.v] = weights[e.u] + e.d;
                parent[e.v] = e.u;
                change[e.v] = true;
            }
        }
    }
    ll temp = weights[dst];
    bool reach = false;
    cout << "Bellman Ford Algorithm:\n";
    for (ll i = 0; i < n - 1; i++)
    {
        for (auto e : graph.getEdge())
        {
            if (weights[e.u] != LONG_LONG_MAX and weights[e.v] > weights[e.u] + e.d)
            {
                weights[e.v] = weights[e.u] + e.d;
                parent[e.v] = e.u;
                change[e.v] = true;
                reach = true;
            }
        }
    }
    if (reach) // reach is true if any negative cycle remains in graph
    {
        cout << "Negative Cycle Detected";
    }
    if (change[dst])
    {
        
        if (temp == weights[dst] and reach)
            cout << "\nBut Reachable From " << src << " to " << dst << endl;
        else if(reach)
            return;
        cout << weights[dst] << endl;
        vector<ll> tree;
        while (dst != src)
        {
            tree.push_back(dst);
            dst = parent[dst];
        }
        cout << src;
        while (tree.size())
        {
            cout << "->" << tree.back();
            tree.pop_back();
        }
    }
    else
        cout << "Not Reachable\n"
             << endl;
}
int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    ll n, m, u, v, src, dst;
    ll d;
    cin >> n >> m;
    Graph graph(n);
    for (ll i = 0; i < m; i++)
    {
        cin >> u >> v >> d;
        graph.addEdge(u, v, d, false);
    }

    cin >> src >> dst;
    vector<ll> tree;

    ssspB(n, graph, src, dst);
    cout << "\n\nDijkstra's Algorithm: " << endl;
    cout << ssspD(n, graph, tree, src, dst) << endl;
    cout << src;
    while (tree.size())
    {
        cout << "->" << tree.back();
        tree.pop_back();
    }
}
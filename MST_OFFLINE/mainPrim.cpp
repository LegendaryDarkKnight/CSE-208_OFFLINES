#include "PQueue.hpp"
#include "Graph.hpp"
#include <cfloat>
double mstPrim(int n, Graph graph, vector<Triplet> &tree, int root)
{
    double ans = 0;
    PQueue<int, double> pqueue(n);
    int parent[n];
    double weights[n];
    pqueue.insertKey(root, 0);
    parent[root] = -1;
    weights[root] = 0;
    for (int i = 0; i < n; i++)
    {
        if (i == root)
            continue;
        pqueue.insertKey(i, INFINITY);
        weights[i] = INFINITY;
    }
    // pqueue.print();
    while (pqueue.size())
    {
        pair<int, double> u = pqueue.getMin();
        if (parent[u.first] != -1)
            tree.push_back(Triplet(parent[u.first], u.first, u.second));
        ans += u.second;
        pqueue.extractMin();
        for (auto &p : graph.successor(u.first))
        {
            if (pqueue.isAvailable(p.getV()) and weights[p.getV()] > p.getWt())
            {
                parent[p.getV()] = u.first;
                weights[p.getV()] = p.getWt();
                pqueue.decreaseKey(p.getV(), p.getWt());
            }
        }
    }
    return ans;
}
int main()
{
    freopen("in.txt", "r", stdin);
    freopen("prims.txt", "w", stdout);
    int n, m, u, v;
    double d;
    cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> d;
        graph.addEdge(u, v, d);
    }
    int root = 0;
    vector<Triplet> tree;

    cout << "Prim's Algorithm\n";
    cout << "Total weight = " << mstPrim(n, graph, tree, root) << endl;
    cout << "Root Node = " << root << endl;
    for (auto &t : tree)
        cout << t.u << " " << t.v << endl;
}
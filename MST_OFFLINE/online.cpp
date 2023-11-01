#include "DSU.hpp"
#include "Graph.hpp"
using namespace std;
bool comparator(Triplet t1, Triplet t2)
{
    return t1.d > t2.d;
}
double Kruskal(Graph graph, vector<Triplet> &tree, vector<Triplet> edgeList, int n)
{
    sort(edgeList.begin(), edgeList.end(), comparator);
    double total = 1;
    DSU dsu(n);
    for(int i=0; i<n; i++)
        dsu.make_set(i);
    for(auto &e:edgeList){
        if(dsu.find_set(e.u)!=dsu.find_set(e.v))
        {
            tree.push_back(Triplet(e.u,e.v,e.d));
            total*=e.d;
            dsu.pair_set(e.u,e.v);
        }
    }
    return total;
}
int main()
{
    freopen("in.txt", "r", stdin);
    freopen("onl.txt", "w", stdout);
    int n, m, u, v;
    double d;
    cin >> n >> m;
    Graph graph(n);
    for (size_t i = 0; i < m; i++)
    {
        cin >> u >> v >> d;
        graph.addEdge(u, v, d);
    }
    vector<Triplet> edgeList = graph.getEdge();
    vector<Triplet> tree;

    cout<<"Maximum product\n";
    cout<<"Total Weights = "<<Kruskal(graph,tree,edgeList,n)<<endl;
    for(auto &t:tree)
        cout<<t.u<<" "<<t.v<<endl;
}
#include "DSU.hpp"
#include <ctime>
using namespace std;
typedef long long ll;

bool checker(vector<vector<ll>> graph, ll n)
{
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < n; j++)
        {
            for (ll k = 0; k < n; k++)
            {
                if (i == j or j == k or k == i)
                    continue;
                if (graph[i][k] + graph[j][k] < graph[i][j])
                {
                    cout << "gotcha" << graph[i][k] << " " << graph[j][k] << " " << graph[i][j] << endl;
                    return true;
                }
            }
        }
    }
    return false;
}
vector<vector<ll>> Create_Random_Graph(ll v)
{
    srand(time(0));
    if (v < 0)
        v = 1;
    vector<vector<ll>> graph;
    graph.resize(v, vector<ll>(v, INT_MAX));
    for (ll i = 0; i < v; i++)
        graph[i][i] = 0;
    for (ll i = 0; i < v; i++)
    {
        for (ll j = i + 1; j < v; j++)
        {
            ll upper = 200, lower = 50;
            for (ll k = 0; k < v; k++)
            {
                if (graph[i][k] == INT_MAX or graph[k][j] == INT_MAX)
                    continue;
                else
                {
                    lower = max(lower, abs(graph[i][k] - graph[k][j]));
                    upper = min(upper, abs(graph[i][k] + graph[k][j]));
                }
            }
            if (graph[i][j] == INT_MAX)
                graph[i][j] = graph[j][i] = (lower + rand() % (upper - lower + 1));
        }
    }
    return graph;
}
class Graph
{
private:
    vector<vector<ll>> graph;
    vector<vector<ll>> tour1;
    vector<vector<ll>> tour2;
    ll n;

public:
    Graph(ll n);
    vector<vector<ll>> getGraph()
    {
        return graph;
    }
    void setGraph(vector<vector<ll>> graph)
    {
        this->graph = graph;
    }
    ll getSize()
    {
        return n;
    }
    void printGraph()
    {
        for (auto g : graph)
        {
            for (auto g1 : g)
            {
                cout << g1 << " ";
            }
            cout << endl;
        }
    }
};
Graph::Graph(ll n)
{
    this->n = n;
    graph.resize(n);
    for (auto g : graph)
        g.resize(n);
    graph = Create_Random_Graph(n);
}
vector<ll> Exact_TSP(Graph &g)
{
    vector<vector<ll>> graph = g.getGraph();
    vector<vector<ll>> dp;
    vector<vector<pair<ll, ll>>> parent;
    ll n = graph.size();
    dp.resize(n, vector<ll>((1 << n), INT_MAX));
    parent.resize(n, vector<pair<ll, ll>>((1 << n), {-1, -1}));

    for (ll mask = (1 << n) - 1; mask > 0; mask--)
    {
        for (ll i = 0; i < graph.size(); i++)
        {

            if (mask == ((1 << n) - 1))
            {
                dp[i][mask] = graph[i][0];
                continue;
            }
            ll ans = INT_MAX;
            for (ll j = 0; j < n; j++)
            {
                if (i == j)
                    continue;
                if ((mask & (1 << j)) == 0)
                {
                    if (graph[i][j] + dp[j][mask | (1 << j)] < ans)
                    {
                        ans = graph[i][j] + dp[j][mask | (1 << j)];
                        parent[i][mask] = {j, mask | (1 << j)};
                    }
                }
            }
            dp[i][mask] = ans;
        }
    }
    pair<ll, ll> p = {0, 1};
    vector<ll> tour;
    while (p.first != -1 or p.second != -1)
    {
        tour.push_back(p.first);
        p = parent[p.first][p.second];
    }
    tour.push_back(0);
    return tour;
    
}

ll Calculate_Tour_Length(vector<ll> tour, vector<vector<ll>> graph)
{
    ll tour_length = 0;
    for (ll i = 1; i < tour.size(); i++)
    {
        tour_length += (graph[tour[i-1]][tour[i]]);
    }
    return tour_length;
}

void dfs(vector<list<ll>> mst, bool visited[], ll u, ll n, vector<ll> &tour){
    visited[u] = true;
    tour.push_back(u);
    for(auto l:mst[u]){
        if(!visited[l])
            dfs(mst,visited,l,n,tour);
    }
}
vector<ll> Metric_Approximation_TSP(Graph &g)
{
    vector<vector<ll>> graph =  g.getGraph();
    ll n = g.getSize();
    DSU dsu(n);
    vector<pair<ll, pair<ll, ll>>> edgeList;
    vector<list<ll>> mst;
    mst.resize(n);
    for (ll i = 0; i < n - 1; i++)
    {
        for (ll j = i + 1; j < n; j++)
        {
            edgeList.push_back({graph[i][j], {i, j}});
        }
    }
    for (ll i = 0; i < n; i++)
    {
        dsu.make_set(i);
    }
    sort(edgeList.begin(), edgeList.end());
    for (auto e : edgeList)
    {
        if (dsu.find_set(e.second.first) != dsu.find_set(e.second.second))
        {
            dsu.pair_set(e.second.first, e.second.second);
            mst[e.second.first].push_back(e.second.second);
            mst[e.second.second].push_back(e.second.first);

        }
    }
    ll source = 0;
    bool visited[n] = {0};
    vector<ll> tour;
    dfs(mst,visited,0,n,tour);
    tour.push_back(0);
    return tour;
}
#include <bits/stdc++.h>
using namespace std;

#define MAXN 1000

#define INF INT_MAX

int w[MAXN], l[MAXN], r[MAXN], g[MAXN][MAXN], capacity[MAXN][MAXN];

int n;

string name[MAXN];

pair<int, int> faceOff[MAXN];

int count = 0;

bool visited[MAXN];

void reachEnd(int u, list<int> adj[])
{
    if (u == ::count + n + 1)
        return;
    cout << u << " ";
    for (auto v : adj[u])
    {
        reachEnd(v, adj);
    }
}

void modifYGraph(int x)
{
    for (int i = 1; i <= ::count; i++)
    {
        if (faceOff[i].first == x or faceOff[i].second == x)
            capacity[0][i] = 0;
        else
            capacity[0][i] = g[faceOff[i].first][faceOff[i].second];
        capacity[i][0] = 0;
        capacity[i][::count + faceOff[i].first + 1] = capacity[i][::count + faceOff[i].second + 1] = INF;
        capacity[::count + faceOff[i].first + 1][i] = capacity[::count + faceOff[i].second + 1][i] = 0;
    }
    for (int i = 0; i < ::n; i++)
    {
        capacity[::count + i + 1][::count + ::n + 1] = w[x] + r[x] - w[i];
        capacity[::count + ::n + 1][::count + i + 1] = 0;
    }
}

int augPath(list<int> adj[], int parent[], int src, int dst, int n1)
{
    parent[0] = -2;
    for (int i = 1; i < n1; i++)
        parent[i] = -1;

    queue<pair<int, int>> q;
    q.push({src, INF});
    while (q.size())
    {
        pair<int, int> p = q.front();
        q.pop();
        for (auto v : adj[p.first])
        {
            if (capacity[p.first][v] > 0 and parent[v] == -1)
            {

                parent[v] = p.first;
                int minSoFar = min(p.second, capacity[p.first][v]);
                if (v == dst)
                {
                    return minSoFar;
                }
                q.push({v, minSoFar});
            }
        }
    }
    return 0;
}
bool canBeEliminated(int src, int dst, list<int> adj[], int n1)
{
    int u, v, addFlow = 0;
    int parent[n1];
    while (addFlow = augPath(adj, parent, src, dst, n1))
    {
        u = dst;
        while (u != src)
        {
            capacity[parent[u]][u] -= addFlow;
            capacity[u][parent[u]] += addFlow;
            u = parent[u];
        }
    }
    for (int i = 1; i <= ::count; i++)
    {
        if (capacity[0][i])
        {
            return true;
        }
    }
    return false;
}

void matchPediction(list<int> adj[])
{
    for (int i = 0; i < ::n; i++)
    {
        modifYGraph(i);
        bool flag = false;
        for (int j = ::count + 1; j <= ::count + n; j++)
        {
            if (capacity[j][::count + n + 1] < 0)
            {
                cout << name[i] << " is eliminated\n";
                cout << "They can win at most " << w[i] << " + " << r[i] << " = " << w[i] + r[i] << " games\n";
                cout << name[j - ::count - 1] << " have won a total of " << w[j - ::count - 1] << " games\n";
                cout << "They play each other " << 0 << " times\n";
                cout << "So on average, each of the teams wins " << w[j - ::count - 1] << "/" << 1 << " = " << w[j - ::count - 1] << " games\n\n";
                flag = true;
                break;
            }
        }
        if (flag)
            continue;

        if (canBeEliminated(0, ::count + ::n + 1, adj, ::count + ::n + 2))
        {
            cout << name[i] << " is eliminated\n";
            cout << "They can win at most " << w[i] << " + " << r[i] << " = " << w[i] + r[i] << " games\n";
            int tot = 0, rem = 0;
            vector<int> teams;
            for (int j = ::count + 1; j < ::count + n + 1; j++)
            {
                if (j - ::count - 1 == i)
                    continue;
                if (capacity[j][::count + n + 1] == 0)
                {
                    teams.push_back(j - ::count - 1);
                    tot += w[j - ::count - 1];
                }
            }
            for (int j = 0; j < teams.size(); j++)
            {
                for (int k = j + 1; k < teams.size(); k++)
                {
                    rem += g[teams[j]][teams[k]];
                }
            }
            for (auto s : teams)
                cout << name[s] << ", ";
            cout << "have won a total of " << tot << " games\n";
            cout << "They play each other " << rem << " times\n";
            cout << "So on average, each of the teams wins " << tot + rem << "/" << teams.size() << " = " << (tot + rem) * 1.0 / teams.size() << " games\n\n";
        }
    }
}
int main()
{
    freopen("input2.txt", "r", stdin);
    freopen("output2.txt", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> name[i] >> w[i] >> l[i] >> r[i];
        for (int j = 0; j < n; j++)
            cin >> g[i][j];
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (g[i][j])
            {
                faceOff[++::count] = {i, j}; 
            }
        }
    }
    // cout<<::count;
    list<int> adj[::count + n + 2];
    for (int i = 1; i <= ::count; i++)
    {
        adj[0].push_back(i);
        adj[i].push_back(0);
        pair<int, int> p = faceOff[i];
        adj[i].push_back(::count + p.first + 1);
        adj[i].push_back(::count + p.second + 1);
        adj[::count + p.first + 1].push_back(i);
        adj[::count + p.first + 1].push_back(::count + n + 1);
        adj[::count + p.second + 1].push_back(i);
        adj[::count + p.second + 1].push_back(::count + n + 1);
    }
    matchPediction(adj);
}
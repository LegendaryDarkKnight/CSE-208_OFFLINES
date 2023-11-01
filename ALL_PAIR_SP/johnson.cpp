#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    ll n, m, u, v;
    double w;
    cin >> n >> m;
    vector<vector<double>> matrix;
    matrix.resize(n + 1);
    for (auto &m : matrix)
        m.resize(n + 1);
    for (ll i = 1; i <= n; i++)
        for (ll j = 1; j <= n; j++)
            matrix[i][j] = (i == j) ? 0 : INFINITY;
    for (ll i = 1; i <= m; i++)
    {
        cin >> u >> v >> w;
        if (w < matrix[u][v])
            matrix[u][v] = w;
    }
    for(ll i=1; i<= n; i++)
}
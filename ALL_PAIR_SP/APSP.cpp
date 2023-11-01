#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int nextArr[100][100];
vector<vector<double>> FLOYD_WARSHALL(vector<vector<double>> matrix)
{
    ll n = matrix.size() - 1;
    for (ll k = 1; k <= n; k++)
    {
        for (ll i = 1; i <= n; i++)
        {
            if (i == k)
                continue;
            for (ll j = 1; j <= n; j++)
            {
                if (i == j or j == k)
                    continue;
                if (matrix[i][k] + matrix[k][j] < matrix[i][j]){
                    nextArr[i][j] = nextArr[i][k];
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                }
            }
        }
    }
    return matrix;
}
vector<vector<double>> matMulti(vector<vector<double>> A, vector<vector<double>> B)
{
    ll n = A.size() - 1;
    vector<vector<double>> C;
    C.resize(n + 1);
    for (auto &c : C)
        c.resize(n + 1);
    for (ll i = 1; i <= n; i++)
    {
        for (ll j = 1; j <= n; j++)
        {
            C[i][j] = INFINITY;
            for (ll k = 1; k <= n; k++)
            {
                C[i][j] = min(C[i][j], A[i][k] + B[k][j]);
            }
        }
    }
    return C;
}
vector<vector<double>> APSP_matMult(vector<vector<double>> matrix)
{
    ll n = matrix.size() - 1;
    vector<vector<double>> ans = matrix;
    ll m = 1;
    while (m <= n - 1)
    {
        ans = matMulti(ans, ans);
        m *= 2;
    }
    return ans;
}
template <class T>
ostream &operator<<(ostream &out, vector<vector<T>> &v)
{
    for (ll i = 1; i < v.size(); i++)
        for (ll j = 1; j < v[i].size(); j++)
            out << v[i][j] << ((j == v[i].size() - 1) ? "\n" : " ");
    return out;
}
vector<int> constructPath(int u,
                        int v)
{
    if (nextArr[u][v] == -1)
        return {};
    vector<int> path = { u };
    while (u != v) {
        u = nextArr[u][v];
        path.push_back(u);
    }
    return path;
}
void printPath(vector<int>& path)
{
    int n = path.size();
    for (int i = 0; i < n - 1; i++)
        cout << path[i] << " -> ";
    cout << path[n - 1] << endl;
}
int main()
{
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
    for (ll i = 1; i <= n; i++)
        for (ll j = 1; j <= n; j++)
            nextArr[i][j] = (matrix[i][j]==INFINITY)?-1:j;
    vector<vector<double>> ans_matrix = APSP_matMult(matrix);
    // cout << "(a)Matrix Multiplication:\n"
    //      << ans_matrix << endl;
    ans_matrix = FLOYD_WARSHALL(matrix);
    cout << "(b) FLOYD_MARSHALL:\n"
         << ans_matrix << endl;
    cout << "Shortest path from 1 to 6: ";
    vector<int> path = constructPath(1, 6);
    printPath(path);
    //cout<<matrix<<endl;
}
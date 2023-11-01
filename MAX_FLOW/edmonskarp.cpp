#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int totalCap[100][100];
int augPath(list<int> adj[], int parent[], int src, int dst, int n){
    int minSoFar = INT_MAX;
    for(int i=0; i<n; i++)
        parent[i] = -1;
    queue<int> q;
    q.push(src);
    while (q.size())
    {
        for(auto v:adj[q.front()]){
            if(totalCap[q.front()][v] and parent[v] == -1){
                parent[v] = q.front();
                minSoFar = min(minSoFar,totalCap[q.front()][v]);
                if(v == dst)
                    return minSoFar;
                q.push(v);
            }
        }
        q.pop();   
    }
    cout<<endl;
    return 0;
    
}
int maxFlow(int src, int dst, list<int> adj[], int n){
    int totalFlow = 0,u,v,addFlow = 0;
    int parent[n];
    for(int i=0; i<n; i++) parent[i] = -1;
    do
    {
        addFlow = augPath(adj,parent,src,dst,n);
        if(!addFlow) break;
        cout<<"New Flow: "<<addFlow<<endl;
        totalFlow +=addFlow;
        u = dst;
        while(u!=src){
            totalCap[parent[u]][u] -=addFlow;
            totalCap[u][parent[u]]  +=addFlow;
            u = parent[u];
        }
    
    } while (addFlow);
    return totalFlow;
}
int main(){
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    int n, m, u, v, w;
    cin>>n>>m;
    list<int> adj[n];
    while(m--){
        cin>>u>>v>>w;
        adj[u].push_back(v);
        totalCap[u][v] = w;
    }
    cin>>u>>v;
    cout<<maxFlow(u,v,adj,n);
}
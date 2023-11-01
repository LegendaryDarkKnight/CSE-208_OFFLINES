#include "Graph.hpp"

int main(){  
    int x ;
    cout<<"Enter x: ";
    cin>>x;
    int exact[x], approx[x];


    for(int i=0; i<x; i++){
        Graph graph(20);
        vector<ll>  tour1 = Exact_TSP(graph);
        vector<ll> tour2 = Metric_Approximation_TSP(graph);
        exact[i] = Calculate_Tour_Length(tour1,graph.getGraph());
        approx[i] = Calculate_Tour_Length(tour2,graph.getGraph());
    }
        
    for(int i=0; i<x; i++)
        cout<<"("<<i+1<<" , "<<approx[i]*1.0/exact[i]<<")"<<endl;
}